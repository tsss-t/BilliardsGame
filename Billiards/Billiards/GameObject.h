#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "DxLib.h"

// タスクの実行優先順位の最大値 - 1
#define PRIORITY_MAX		(16)

using namespace DxLib;

typedef struct _STransform
{
	VECTOR postion;
	VECTOR rotation;
	VECTOR scale;
}STransform;
typedef struct _SGameObjectBaseInfo {
	int updatePriority;
	int drawPriority;

}SGameObjectBaseInfo;
typedef struct _SGameObjectInfo {

	SGameObjectBaseInfo *goBaseInfo;
	class GameObject *go;
	struct _SGameObjectInfo* updateNext;
	struct _SGameObjectInfo* drawNext;
	struct _SGameObjectInfo* addOrDelNext;

}SGameObjectInfo;

class GameObject
{
public:
	int modelHandle;
	bool isStatic;
	_STransform * transform;
	_SGameObjectInfo * goInfo;

	GameObject(int modelHandel);
	GameObject(float x, float y, float z, int modelHandel);
	GameObject(VECTOR position, int modelHandel);
	GameObject(VECTOR position, VECTOR rotation, int modelHandel);
	GameObject(VECTOR position, VECTOR rotation, VECTOR scale, int modelHandel);
	~GameObject();

	void SetUpdatePriority(int updatePriority);
	void SetDrawPriority(int drawPriority);
	virtual bool Draw();
	virtual bool Update(float stepTime);

private:
	void GameObjectInit();
};


#endif // !GAMEOBJECT_H