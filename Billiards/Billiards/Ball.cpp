#include "Ball.h"



void Ball::InitBall()
{
	btCollisionShape* collision = new btSphereShape(btScalar(transform->scale.x*30));
	SetRigidBody(0.5f, collision);
	rigidBody->setRestitution(btScalar(0.6f));
	rigidBody->setFriction(0.4f);
	rigidBody->setDamping(0.3f, 0.9f);
	firstPosition = { 0,0,0 };
	//rigidBody->setAngularFactor(0.5f);
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


bool Ball::Draw() {
	if (enable)
	{
		return GameObject::Draw();
	}
}
bool Ball::Update(float stepTime)
{
	if (enable)
	{
		return GameObject::Update(stepTime);
	}
}

void Ball::ResetPosition()
{
	// MotionStateの設定
	btMotionState * motionState = this->rigidBody->getMotionState();
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(firstPosition.x, firstPosition.y, firstPosition.z));
	motionState->setWorldTransform(transform);
	this->rigidBody->setMotionState(motionState);
	rigidBody->clearForces();
	rigidBody->setLinearVelocity({ 0,0,0 });
	rigidBody->setAngularVelocity({ 0,0,0 });

}


bool Ball::AddForce(VECTOR force, VECTOR forcePos)
{
	rigidBody->activate();
	rigidBody->applyCentralImpulse(btVector3(force.x, force.y, -force.z));

	//rigidBody->applyForce(btVector3(force.x, force.y,- force.z), btVector3(forcePos.x, forcePos.y,- forcePos.z));
	return true;
}
