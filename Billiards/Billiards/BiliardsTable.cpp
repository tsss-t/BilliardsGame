#include "BiliardsTable.h"
BilliardsTable::BilliardsTable() :GameObject(MV1LoadModel("Data/Model/biliards1.mv1"))
{
	//goInfo->go = this;
	transform->postion = VGet(300.0f, 0.0f, 350.0f);
}

BilliardsTable::~BilliardsTable()
{
}

bool BilliardsTable::Draw()
{
	GameObject::Draw();
	return true;
}

bool BilliardsTable::Update(float stepTime)
{
	GameObject::Update(stepTime);
	return true;
}
