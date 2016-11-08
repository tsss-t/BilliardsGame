#include "PoolStick.h"


void PoolStick::InitPoolStick()
{
	enable = true;
}

PoolStick::PoolStick() :GameObject(MV1LoadModel("Data/Model/pool-stick.MV1"))
{
	transform->postion = VGet(0, 0, 0);
}
PoolStick::PoolStick(VECTOR position) : GameObject(MV1LoadModel("Data/Model/pool-stick.MV1"))
{
	this->transform->postion = position;
}
PoolStick::PoolStick(VECTOR position, VECTOR rotation) : GameObject(MV1LoadModel("Data/Model/pool-stick.MV1"))
{

	this->transform->postion = position;
	this->transform->rotation = rotation;
}
PoolStick::~PoolStick()
{
}

void PoolStick::SetEnabel(bool enable)
{
	this->enable = enable;
}


bool PoolStick::IsEnable()
{
	return enable;
}

bool PoolStick::Draw()
{
	if (enable)
	{
		MV1SetPosition(this->modelHandle, VGet(transform->postion.x, transform->postion.y, transform->postion.z));
		MV1SetRotationXYZ(this->modelHandle, transform->rotation);
		MV1DrawModel(this->modelHandle);
	}
	return true;
}

bool PoolStick::Update(float stepTime)
{
	if (enable)
	{
		GameObject::Update(stepTime);
		//x++;
	}
	return true;
}

VECTOR PoolStick::GetDistance()
{
	return VGet(-cos(this->transform->rotation.y), 0, -sin(this->transform->rotation.y));
}