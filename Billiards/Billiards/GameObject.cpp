#include "GameObject.h"

void GameObject::GameObjectInit()
{
	//SGameObjectInfo SGo = {};
	//goInfo = &SGo;
	//STransform ST = {};
	//transform = &ST;
	goInfo = (SGameObjectInfo *)calloc(1, sizeof(SGameObjectInfo));
	goInfo->goBaseInfo = (SGameObjectBaseInfo *)calloc(1, sizeof(SGameObjectBaseInfo));
	transform = (STransform *)calloc(1, sizeof(STransform));
	//memset(goInfo, 0, sizeof(SGameObjectInfo));
	//memset(transform, 0, sizeof(STransform));
	this->goInfo->goBaseInfo->drawPriority = 0;
	this->goInfo->goBaseInfo->updatePriority = 0;
	goInfo->go = this;
}
GameObject::GameObject(int modelHandle)
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
}
GameObject::GameObject(float x, float y, float z, int modelHandle)
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = VGet(x, y, z);
	this->transform->rotation = VGet(0, 0, 0);
	this->transform->scale = VGet(1, 1, 1);
}
GameObject::GameObject(VECTOR position, int modelHandle)
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = VGet(0, 0, 0);
	this->transform->scale = VGet(1, 1, 1);
}
GameObject::GameObject(VECTOR position, VECTOR rotation, int modelHandle)
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = rotation;
	this->transform->scale = VGet(1, 1, 1);
}
GameObject::GameObject(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandle)
{
	this->GameObject::GameObjectInit();
	this->modelHandle = modelHandle;
	this->transform->postion = position;
	this->transform->rotation = rotation;
	this->transform->scale = scale;
}
GameObject::~GameObject()
{
	//if (goInfo->goBaseInfo != NULL)
	//{
	//	delete goInfo->goBaseInfo;
	//}
	//if (goInfo)
	//{
	//	free(goInfo);
	//}
}
int x=0;
bool GameObject::Update(float stepTime)
{
	x++;
	return true;
}

bool GameObject::Draw()
{
	DrawPixel(420, 100 + x, GetColor(255, 255, 255));
	MV1SetPosition(this->modelHandle, VGet(100.0f, 0.0f, 200.0f));
	MV1SetRotationXYZ(this->modelHandle, VGet(0, 0, 0));
	MV1DrawModel(this->modelHandle);
	return true;
}

void GameObject::SetUpdatePriority(int updatePriority)
{
	if (updatePriority > PRIORITY_MAX - 1)
	{
		goInfo->goBaseInfo->updatePriority = PRIORITY_MAX - 1;
	}
	else if (updatePriority < 0)
	{
		goInfo->goBaseInfo->updatePriority = 0;
	}
	else
	{
		goInfo->goBaseInfo->updatePriority = updatePriority;
	}
}
void GameObject::SetDrawPriority(int drawPriority)
{
	if (drawPriority > PRIORITY_MAX - 1)
	{
		goInfo->goBaseInfo->drawPriority = PRIORITY_MAX - 1;
	}
	else if (drawPriority < 0)
	{
		goInfo->goBaseInfo->drawPriority = 0;
	}
	else
	{
		goInfo->goBaseInfo->drawPriority = drawPriority;
	}
}