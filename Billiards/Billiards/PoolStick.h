#pragma once
#ifndef _POOLSTICK_H
#define _POOLSTICK_H 
#include "GameObject.h"
class PoolStick:public GameObject
{

public:
	void InitPoolStick();
	PoolStick();
	PoolStick(VECTOR position);
	PoolStick(VECTOR position, VECTOR rotation);
	~PoolStick();
	void SetEnabel(bool enable);
	bool IsEnable();
	bool Draw();
	bool Update(float stepTime);
	VECTOR GetDistance();

private:
	bool enable;
};



#endif // !_POOLSTICK_H