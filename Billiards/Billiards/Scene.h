#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "GameObjectBase.h"
#include "CameraManager.h"


#pragma region シーンの状態時間数定義
//フェードインする前に待つ時間
#define FADE_IN_WAIT_TIME		(0.5f)

// フェードインにかける時間
#define FADE_IN_TIME			(1.0f)

// メニュー項目をフェードインする前に待つ時間
#define MENU_IN_WAIT_TIME		(0.2f)

// メニュー項目のフェードインにかける時間
#define MENU_IN_TIME			(0.25f)

// メニュー項目の明滅１周にかける時間
#define MENU_BRINK_TIME			(2.0f)

// フェードアウトにかける時間
#define FADE_OUT_TIME			(1.0f)
#pragma endregion



class Scene
{
public:


	Scene();
	// シーンの状態推移処理
	virtual bool SceneUpdate(float stepTime);

	// シーン描画処理
	virtual bool SceneDraw(void);

	//新しいゲームオブジェクトをシーンの中に追加
	virtual bool AddToScene(GameObjectBase * gameObject);

	//新しいゲームオブジェクトをシーンの中から削除
	virtual bool DeleteFromScene(GameObjectBase * gameObject);

	//指定したゲームオブジェクトの状態推移処理順位変更
	virtual bool AdjustGameObjectUpdatePriority(GameObjectBase * gameObject, int priority);

	//指定したゲームオブジェクトの描画処理順位変更
	virtual bool AdjustGameObjectDrawPriority(GameObjectBase * gameObject, int priority);

private:
	// 状態推移処理のリストの各優先順位の先頭タスクへのポインタ
	GameObjectBase * updateList[PRIORITY_MAX];

	// 描画処理のリストの各優先順位の先頭タスクへのポインタ
	GameObjectBase * drawList[PRIORITY_MAX];

	// 追加するゲームオブジェクトのリストの先頭タスクへのポインタ
	GameObjectBase * addGameObjectInfoList;

	// 削除するゲームオブジェクトのリストの先頭タスクへのポインタ
	GameObjectBase * delGameObjectList;

protected:
	// タスクの処理を実行中かどうかのフラグ
	bool run;

	float timer;

	CameraManager * cameraManager;

	bool InitGameObjectList(void);

	bool GameObjectUpdate(float stepTime);

	bool GameObjectDraw(void);

	//描画処理の順位と状態推移処理の順位を更新
	bool RefreshList(void);

	~Scene();
};



#endif