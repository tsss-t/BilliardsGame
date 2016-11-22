#include "GameObject.h"
#include "SceneManager.h"

//右手→左手位置変換
VECTOR btVGet(const btVector3 &inv) { return VGet(inv.getX(), inv.getY(), -inv.getZ()); }
//右手→左手回転変換
VECTOR btRotVGet(const btVector3 &inv) { return VGet(-inv.getX(), -inv.getY(), inv.getZ()); }
//左手→右手位置変換
btVector3 DxVGet(const VECTOR &inv) { return btVector3(inv.x, inv.y, -inv.z); };
//左手→右手回転変換
btVector3 DxRotVGet(const VECTOR &inv) { return btVector3(-inv.x, -inv.y, inv.z); }


#pragma region 構造方法
void GameObject::SetPriority(int updatePriority, int drawPriority)
{
	this->goInfo->goBaseInfo->drawPriority = updatePriority;
	this->goInfo->goBaseInfo->updatePriority = drawPriority;
}

//　基本構造方法
void GameObject::GameObjectInit()
{
	enable = true;
	mass = 0.f;
	transform = (STransform3D *)calloc(1, sizeof(STransform3D));
	transform->postion = VGet(0, 0, 0);
	transform->rotation = VGet(0, 0, 0);
	transform->scale = VGet(1, 1, 1);
}

GameObject::GameObject(int modelHandle) :GameObjectBase()
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
}
GameObject::GameObject(float x, float y, float z, int modelHandle) : GameObjectBase()
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = VGet(x, y, z);
	this->transform->rotation = VGet(0, 0, 0);
	this->transform->scale = VGet(1, 1, 1);
}
GameObject::GameObject(float x, float y, float z, int modelHandle, int updatePriority, int drawPriority) :GameObjectBase()
{
	GameObject(x, y, z, modelHandle);
	SetPriority(updatePriority, drawPriority);
}
GameObject::GameObject(VECTOR position, int modelHandle) : GameObjectBase()
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = VGet(0, 0, 0);
	this->transform->scale = VGet(1, 1, 1);
}
GameObject::GameObject(VECTOR position, int modelHandle, int updatePriority, int drawPriority) :GameObjectBase()
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = VGet(0, 0, 0);
	this->transform->scale = VGet(1, 1, 1);
	SetPriority(updatePriority, drawPriority);
}

GameObject::GameObject(VECTOR position, VECTOR rotation, int modelHandle) :GameObjectBase()
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = rotation;
	this->transform->scale = VGet(1, 1, 1);
}
GameObject::GameObject(VECTOR position, VECTOR rotation, int modelHandle, int updatePriority, int drawPriority) :GameObjectBase()
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = rotation;
	this->transform->scale = VGet(1, 1, 1);
	SetPriority(updatePriority, drawPriority);
}
GameObject::GameObject(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandle) : GameObjectBase()
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = rotation;
	this->transform->scale = scale;
}
GameObject::GameObject(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandle, int updatePriority, int drawPriority) :GameObjectBase()
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = rotation;
	this->transform->scale = scale;
	SetPriority(updatePriority, drawPriority);
}

#pragma endregion
GameObject::~GameObject()
{
	MV1DeleteModel(this->modelHandle);
	//if (goInfo->goBaseInfo != NULL)
	//{
	//	delete goInfo->goBaseInfo;
	//}
	//if (goInfo)
	//{
	//	free(goInfo);
	//}
}

bool GameObject::IsGUI()
{
	return false;
}

bool GameObject::IsRigidBody()
{
	return isRigidBody;
}

btRigidBody * GameObject::GetRigidBody()
{
	return rigidBody;
}

void GameObject::SetPosition(VECTOR position)
{
	if (isRigidBody)
	{
		if (!isStatic)
		{
			btMotionState * motionState = this->rigidBody->getMotionState();
			btTransform transform;
			transform.setIdentity();
			transform.setOrigin(btVector3(position.x, position.y, position.z));
			this->transform->postion = position;
			motionState->setWorldTransform(transform);
			this->rigidBody->setMotionState(motionState);
			rigidBody->clearForces();
			rigidBody->setLinearVelocity({ 0,0,0 });
			rigidBody->setAngularVelocity({ 0,0,0 });
		}
	}
	else
	{
		this->transform->postion = position;
	}
}

void GameObject::SetRotation(VECTOR rotation)
{
	if (isRigidBody)
	{
		if (!isStatic)
		{
			transform->rotation = rotation;
		}
	}
	else
	{
		this->transform->rotation = rotation;
	}
}

void GameObject::SetScale(VECTOR scale)
{
	if (!isStatic)
	{
		transform->scale = scale;
	}
}

VECTOR GameObject::GetPosition()
{
	return transform->postion;
}

VECTOR GameObject::GetRotation()
{
	return transform->rotation;
}

VECTOR GameObject::GetScale()
{
	return transform->scale;
}

VECTOR2D GameObject::GetPositionInWindow()
{
	return VECTOR2D();
}


bool GameObject::SetRigidBody(btScalar mass, btCollisionShape * collision)
{
	this->isRigidBody = true;
	this->mass = mass;
	this->collision = collision;
	btVector3 inertia(0, 0, 0);
	btQuaternion quaternion(-btScalar(transform->rotation.x), -btScalar(transform->rotation.y), btScalar(transform->rotation.z));
	// MotionStateの設定
	btDefaultMotionState* motionState = new btDefaultMotionState(
		btTransform(
			quaternion,
			btVector3(btScalar(transform->postion.x), btScalar(transform->postion.y), btScalar(-transform->postion.z))
		)
	);

	collision->calculateLocalInertia(mass, inertia);
	// 初期情報を設定
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, collision, inertia);
	// 剛体の作成
	rigidBody = new btRigidBody(rigidBodyCI);
	return true;
}

void GameObject::SetUpdatePriority(int updatePriority)
{
	GameObjectBase::SetUpdatePriority(updatePriority);
}

void GameObject::SetDrawPriority(int drawPriority)
{
	GameObjectBase::SetDrawPriority(drawPriority);
}

void GameObject::SetEnable(bool enable)
{
	this->enable = enable;

}

bool GameObject::GetEnable()
{
	return enable;
}

//ゲームオブジェクトの状態推移処理
bool GameObject::Update(float stepTime)
{
	if (enable)
	{
		if (isRigidBody && !isStatic)
		{
			btTransform trans;
			rigidBody->getMotionState()->getWorldTransform(trans);
			this->transform->postion = btVGet(trans.getOrigin());

			// 角度取得
			btMatrix3x3 rot = trans.getBasis();
			btVector3 euler;
			rot.getEulerZYX(euler[2], euler[1], euler[0]);
			this->transform->rotation = btRotVGet(euler);
		}
	}
	return true;
}



//ゲームオブジェクトの描画
bool GameObject::Draw()
{
	if (enable)
	{
		MV1SetPosition(this->modelHandle, transform->postion);
		MV1SetRotationXYZ(this->modelHandle, transform->rotation);
		MV1SetScale(this->modelHandle, transform->scale);
		MV1DrawModel(this->modelHandle);
	}
	return true;
}

