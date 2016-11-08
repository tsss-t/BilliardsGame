#include "Ball.h"



void Ball::InitBall()
{
	btCollisionShape* collision =new btSphereShape(btScalar(1.2f));
	SetRigidBody(0.5f, collision);
	rigidBody->setRestitution(btScalar(0.6f));
	rigidBody->setFriction(0.4f);
	rigidBody->setDamping(0.3f, 0.9f);
	//rigidBody->setAngularFactor(0.5f);
}

Ball::Ball(int modelHandle) :GameObject(modelHandle)
{
	InitBall();
}

Ball::Ball(float x, float y, float z, int modelHandle) : GameObject(x, y, z, modelHandle)
{
	InitBall();
}

Ball::Ball(VECTOR position, int modelHandle) : GameObject(position, modelHandle)
{
	InitBall();
}

Ball::Ball(VECTOR position, VECTOR rotation, int modelHandle) : GameObject(position, rotation, modelHandle)
{
	InitBall();
}

Ball::Ball(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandle) : GameObject(position, rotation, scale, modelHandle)
{
	InitBall();
}



Ball::~Ball()
{

}


bool Ball::Draw() {
	return GameObject::Draw();
}
bool Ball::Update(float stepTime)
{
	return GameObject::Update(stepTime);

}
bool Ball :: AddForce(VECTOR force,VECTOR forcePos)
{
	rigidBody->activate();
	rigidBody->applyCentralImpulse( btVector3(force.x, force.y, -force.z));

	//rigidBody->applyForce(btVector3(force.x, force.y,- force.z), btVector3(forcePos.x, forcePos.y,- forcePos.z));
	return true;
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