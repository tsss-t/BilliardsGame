#pragma once
#ifndef GAMEOBJECTBASE_H
#define GAMEOBJECTBASE_H

#include "btBulletDynamicsCommon.h"
#include <math.h>
#include "DxLib.h"

// タスクの実行優先順位の最大値 - 1
#define PRIORITY_MAX		(16)
typedef struct _SVECTOR2D
{
	float x;
	float y;
}VECTOR2D;
typedef struct _SVECTOR2DINT
{
	int x;
	int y;
}VECTOR2DINT;
typedef struct _SGameObjectBaseInfo {
	int updatePriority;
	int drawPriority;
}SGameObjectBaseInfo;

typedef struct _SGameObjectInfo {
	SGameObjectBaseInfo *goBaseInfo;
	class GameObjectBase* updateNext;
	class GameObjectBase* drawNext;
	class GameObjectBase* addOrDelNext;
}SGameObjectInfo;

class GameObjectBase
{
public:

	_SGameObjectInfo * goInfo;
	GameObjectBase();
	~GameObjectBase();
	virtual bool Update(float stepTime) = 0;
	virtual bool Draw() = 0;
	//ゲームオブジェクトの状態推移処理順番を変更
	virtual void SetUpdatePriority(int updatePriority);

	//ゲームオブジェクトの描画処理順番を変更
	virtual void SetDrawPriority(int drawPriority);

	//ゲームオブジェクトはRigidBodyですか
	virtual bool IsRigidBody();

	virtual bool IsGUI();

	virtual VECTOR2D GetPositionInWindow();

	//ゲームオブジェクトのRigidBodyを貰う
	//isRigidBody==false  ->  return null
	virtual btRigidBody *GetRigidBody();

	virtual VECTOR2DINT GetUISize();

private:

protected:
	//＊要注意＊　　構造方法用
	virtual void SetPriority(int updatePriority, int drawPriority);
};


#endif // !GAMEOBJECTBASE_H