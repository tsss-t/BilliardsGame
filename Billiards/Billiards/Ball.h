#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball :public GameObject
{
public:
	Ball(int modelHandle);
	Ball(float x, float y, float z, int modelHandel);
	Ball(VECTOR position, int modelHandel);
	Ball(VECTOR position, VECTOR rotation, int modelHandel);
	Ball(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandel);
	~Ball();

	bool Draw();

	bool Update();

private:
	bool Move();
	bool Rote();
};

#endif // !BALL_H