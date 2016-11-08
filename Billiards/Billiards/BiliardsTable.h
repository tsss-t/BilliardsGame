#pragma once
#ifndef BILIARDSTABLE_H
#define BILIARDSTABLE_H
#include "GameObject.h"
class BilliardsTable :public GameObject
{
public:
	BilliardsTable();
	~BilliardsTable();
	bool Draw();
	bool Update(float stepTime);

private:

};

#endif // !BILIARDSTABLE_H