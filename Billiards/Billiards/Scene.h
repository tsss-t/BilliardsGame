#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
class Scene
{
public:

	Scene();


private:
	// 状態推移処理のリストの各優先順位の先頭タスクへのポインタ
	SGameObjectInfo * updateList[PRIORITY_MAX];

	// 描画処理のリストの各優先順位の先頭タスクへのポインタ
	SGameObjectInfo * drawList[PRIORITY_MAX];

	// 追加するゲームオブジェクトのリストの先頭タスクへのポインタ
	SGameObjectInfo * addGameObjectInfoList;

	// 削除するゲームオブジェクトのリストの先頭タスクへのポインタ
	SGameObjectInfo * delGameObjectList;

protected:
	// タスクの処理を実行中かどうかのフラグ
	bool run;

	bool InitGameObjectList(void);

	// シーンの状態推移処理
	bool SceneUpdate(float stepTime);

	// シーン描画処理
	bool SceneDraw(void);

	bool GameObjectUpdate(float stepTime);

	bool AddToScene(GameObject * gameObject);

	bool DeleteFromScene(GameObject * gameObject);

	bool AdjustGameObjectUpdatePriority(GameObject * gameObject, int priority);

	bool AdjustGameObjectDrawPriority(GameObject * gameObject, int priority);

	bool GameObjectDraw(void);

	bool RefreshList(void);

	~Scene();
};



#endif