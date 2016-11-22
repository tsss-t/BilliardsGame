#include "Ball.h"

void Ball::InitBall()
{
	btCollisionShape* collision = new btSphereShape(btScalar(transform->scale.x * 30));
	SetRigidBody(0.4f, collision);

	rigidBody->setRestitution(btScalar(0.6f));
	rigidBody->setFriction(0.4f);
	rigidBody->setDamping(0.3f, 0.9f);

	firstPosition = { 0,0,0 };

	objectType = EObjectType::Dynamic;

	rigidBody->getCollisionShape()->setUserPointer(this);
	rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	//rigidBody->setAngularFactor(1.5f);
}

Ball::Ball(int modelHandle) :GameObject(modelHandle)
{
	InitBall();
}

Ball::Ball(float x, float y, float z, int modelHandle) : GameObject(x, y, z, modelHandle)
{
	InitBall();
	firstPosition = { x,y,z };
}

Ball::Ball(VECTOR position, int modelHandle) : GameObject(position, modelHandle)
{
	InitBall();
	firstPosition = { position.x,position.y,position.z };
}

Ball::Ball(VECTOR position, VECTOR rotation, int modelHandle) : GameObject(position, rotation, modelHandle)
{
	InitBall();
	firstPosition = { position.x,position.y,position.z };
}

Ball::Ball(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandle) : GameObject(position, rotation, scale, modelHandle)
{
	InitBall();
	firstPosition = { position.x,position.y,position.z };
}




Ball::~Ball()
{
}

void Ball::SetEnable(bool enable)
{
	this->enable = enable;
}


bool Ball::Draw() {
	if (enable)
	{
		return GameObject::Draw();
	}
}
bool Ball::Update(float stepTime)
{
	for (vector <GameObject*>::iterator iter = collisionList.begin(); iter != collisionList.end();)
	{
		if ((*iter)->objectType == EObjectType::Static)
		{
			if (transform->postion.x > -52 &&
				transform->postion.x < 59 &&
				transform->postion.z> -26.5f&&
				transform->postion.z < 26.5f)
			{
				iter = collisionList.erase(iter);
			}
			else
			{
				iter++;
			}
		}
		else
		{
			VECTOR targetPosition = (*iter)->GetPosition();
			btVector3 distance = { transform->postion.x - targetPosition.x,transform->postion.x - targetPosition.x,transform->postion.x - targetPosition.x };
			if (distance.length() > 2.f)
			{
				iter = collisionList.erase(iter);
				break;
			}
			else
			{
				iter++;
			}
		}
	}
	if (enable)
	{
		return GameObject::Update(stepTime);
	}
	return true;
}
void Ball::ResetPosition()
{
	SetPosition(firstPosition);
}


bool Ball::AddForce(VECTOR force, VECTOR forcePos)
{
	rigidBody->activate();
	rigidBody->applyCentralImpulse(btVector3(force.x, force.y, -force.z));

	//rigidBody->applyForce(btVector3(force.x, force.y,- force.z), btVector3(forcePos.x, forcePos.y,- forcePos.z));
	return true;
}
