#pragma once
#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball :public GameObject
{
public:
	int num;

	void InitBall();

	Ball(int modelHandle);
	Ball(float x, float y, float z, int modelHandel);
	Ball(VECTOR position, int modelHandel);
	Ball(VECTOR position, VECTOR rotation, int modelHandel);
	Ball(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandel);

	~Ball();

	void SetEnable(bool enable);

	void ResetPosition();

	bool AddForce(VECTOR force, VECTOR forcePos);

	bool Draw();

	bool Update(float stepTime);


private:

	Ball();
	VECTOR firstPosition;

};

#endif // !BALL_H