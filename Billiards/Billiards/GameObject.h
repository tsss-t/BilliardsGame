#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameObjectBase.h"

typedef struct _STransform3D
{
	VECTOR postion;
	VECTOR rotation;
	VECTOR scale;
}STransform3D;

class GameObject:public GameObjectBase
{
public:

#pragma region 構造方法
	GameObject(int modelHandel);
	GameObject(float x, float y, float z, int modelHandel);
	GameObject(float x, float y, float z, int modelHandle, int updatePriority, int drawPriority);
	GameObject(VECTOR position, int modelHandel);
	GameObject(VECTOR position, int modelHandle, int updatePriority, int drawPriority);
	GameObject(VECTOR position, VECTOR rotation, int modelHandel);
	GameObject(VECTOR position, VECTOR rotation, int modelHandle, int updatePriority, int drawPriority);
	GameObject(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandel);
	GameObject(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandle, int updatePriority, int drawPriority);
#pragma endregion

	~GameObject();

	//物理システム
	virtual bool IsRigidBody();

	virtual btRigidBody* GetRigidBody();

	virtual bool SetRigidBody(btScalar mass, btCollisionShape* collision);

	//位置、サイズ、回転角関連
	virtual void SetPosition(VECTOR position);

	virtual void SetRotation(VECTOR rotation);

	virtual void SetScale(VECTOR scale);

	virtual VECTOR GetPosition();

	virtual VECTOR GetRotation();

	virtual VECTOR GetScale();

	//ゲームオブジェクトの状態推移処理順番を変更
	virtual void SetUpdatePriority(int updatePriority);

	//ゲームオブジェクトの描画処理順番を変更
	virtual void SetDrawPriority(int drawPriority);

	//描画処理
	virtual bool Draw();

	//状態推移処理
	virtual bool Update(float stepTime);


private:
	//＊要注意＊　　構造方法用
	void SetPriority(int updatePriority, int drawPriority);

	void GameObjectInit();

protected:
	int modelHandle;
	bool isRigidBody = false;
	bool isStatic = false;
	_STransform3D * transform;

	btRigidBody* rigidBody;
};


#endif // !GAMEOBJECT_H