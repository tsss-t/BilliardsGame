#include "Ball.h"



Ball::Ball(int modelHandle) :GameObject(modelHandle)
{
}

Ball::Ball(float x, float y, float z, int modelHandel) : GameObject(x, y, z, modelHandle)
{
}

Ball::Ball(VECTOR position, int modelHandel) : GameObject(position, modelHandle)
{
}

Ball::Ball(VECTOR position, VECTOR rotation, int modelHandel) : GameObject(position, rotation, modelHandle)
{
}

Ball::Ball(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandel) : GameObject(position, rotation, scale, modelHandle)
{
}



Ball::~Ball()
{

}


bool Ball::Draw() {
	return GameObject::Draw();
}
bool Ball::Update()
{
	return GameObject::Update(1.0f);
}
bool Ball::Move()
{
	return false
		;
}
bool Ball::Rote()
{
	return false
		;
}