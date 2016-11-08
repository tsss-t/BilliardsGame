#include "Scene.h"
#include "System.h"

Scene::Scene()
{
	InitGameObjectList();
}

bool Scene::InitGameObjectList(void)
{
	timer = 0;
	*updateList = NULL;
	*drawList = NULL;
	cameraManager = CameraManager::GetCameraManagerInstance();
	return true;
}
// シーンの状態推移処理
bool Scene::SceneUpdate(float stepTime)
{
	CameraManager::GetCameraManagerInstance()->CameraUpdate(stepTime);
	GameObjectBase * goBase;
	run = true;
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		for (goBase = updateList[i]; goBase != NULL; goBase = goBase->goInfo->updateNext)
		{
			if (!goBase->Update(stepTime))
			{
				return false;
			}
		}
	}
	run = false;
	RefreshList();
	return true;
}
// シーン描画処理
bool Scene::SceneDraw(void)
{
	GameObjectBase * goBase;
	run = true;
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		for (goBase = drawList[i]; goBase != NULL; goBase = goBase->goInfo->drawNext)
		{
			if (!goBase->Draw())
			{
				return false;
			}
		}
	}
	run = false;
	return true;
}

//新しいゲームオブジェクトをシーンの中に追加
bool Scene::AddToScene(GameObjectBase * goBase)
{
	goBase->goInfo->addOrDelNext = addGameObjectInfoList;
	addGameObjectInfoList = goBase;
	if (!run)
	{
		return RefreshList();
	}
	return true;
}

//新しいゲームオブジェクトをシーンの中から削除
bool Scene::DeleteFromScene(GameObjectBase * gameObject)
{
	gameObject->goInfo->addOrDelNext = delGameObjectList;
	delGameObjectList = gameObject;
	if (!run)
	{
		return RefreshList();
	}
	return true;
}

//指定したゲームオブジェクトの状態推移処理順位変更
bool Scene::AdjustGameObjectUpdatePriority(GameObjectBase * goBase, int priority)
{
	SGameObjectInfo * tempGoInfo;

	// 先頭だった場合は先頭を外すゲームオブジェクトの次のゲームオブジェクトにする
	if (updateList[goBase->goInfo->goBaseInfo->updatePriority] == goBase)
	{
		updateList[goBase->goInfo->goBaseInfo->updatePriority] = goBase->goInfo->updateNext;
	}
	else
	{
		// 状態推移処理のゲームオブジェクトのリストの先頭ではなかったら
		// 状態推移処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
		tempGoInfo = updateList[goBase->goInfo->goBaseInfo->updatePriority]->goInfo;
		while (true)
		{
			// リストの終端に来てしまった場合はループを抜ける
			if (tempGoInfo->updateNext == NULL)
			{
				//TODO:ERROR
				return false;
			}

			// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
			if (tempGoInfo->updateNext == goBase)
			{
				tempGoInfo->updateNext = goBase->goInfo->updateNext;
				break;
			}
			tempGoInfo = tempGoInfo->updateNext->goInfo;
		}
	}
	// 状態推移処理のゲームオブジェクトのリストの先頭に追加する
	goBase->goInfo->updateNext = updateList[priority];
	updateList[priority] = goBase->goInfo->updateNext;

	goBase->goInfo->goBaseInfo->updatePriority = priority;

	return true;
}

//指定したゲームオブジェクトの描画処理順位変更
bool Scene::AdjustGameObjectDrawPriority(GameObjectBase * goBase, int priority)
{
	SGameObjectInfo * tempGoInfo;
	// 先頭だった場合は先頭を外すゲームオブジェクトの次のゲームオブジェクトにする
	if (drawList[goBase->goInfo->goBaseInfo->drawPriority] == goBase)
	{
		drawList[goBase->goInfo->goBaseInfo->drawPriority] = goBase->goInfo->drawNext;
	}
	else
	{
		// 状態推移処理のゲームオブジェクトのリストの先頭ではなかったら
		// 状態推移処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
		tempGoInfo = drawList[goBase->goInfo->goBaseInfo->drawPriority]->goInfo;
		while (true)
		{
			// リストの終端に来てしまった場合はループを抜ける
			if (tempGoInfo->drawNext == NULL)
			{
				//TODO:not find
				return false;
			}

			// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
			if (tempGoInfo->drawNext == goBase)
			{
				tempGoInfo->drawNext = goBase->goInfo->drawNext;
				break;
			}
			tempGoInfo = tempGoInfo->drawNext->goInfo;
		}
	}
	// 状態推移処理のゲームオブジェクトのリストの先頭に追加する
	goBase->goInfo->updateNext = drawList[priority];
	drawList[priority] = goBase->goInfo->drawNext;

	goBase->goInfo->goBaseInfo->drawPriority = priority;

	return true;
}

// ゲームオブジェクトの状態推移処理
bool Scene::GameObjectUpdate(float stepTime)
{
	return false;
}

// ゲームオブジェクトの描画処理
bool Scene::GameObjectDraw(void)
{
	return false;
}

//描画処理の順位と状態推移処理の順位を更新
bool Scene::RefreshList(void)
{
	GameObjectBase * goBase;
	GameObjectBase * nextGo;
	GameObjectBase * tempGo;
#pragma region <追加するゲームオブジェクトのリスト>に登録されているゲームオブジェクトをリストに追加する
	if (addGameObjectInfoList != NULL)
	{
		for (goBase = addGameObjectInfoList; goBase != NULL; goBase = nextGo)
		{
			// <追加するゲームオブジェクトのリスト>の次のゲームオブジェクトのアドレスを保持しておく
			nextGo = goBase->goInfo->addOrDelNext;

			// 状態推移処理のリストに追加する
			goBase->goInfo->updateNext = updateList[goBase->goInfo->goBaseInfo->updatePriority];
			updateList[goBase->goInfo->goBaseInfo->updatePriority] = goBase;

			// 描画処理のリストに追加する
			goBase->goInfo->drawNext = drawList[goBase->goInfo->goBaseInfo->drawPriority];
			drawList[goBase->goInfo->goBaseInfo->drawPriority] = goBase;

			// <追加するゲームオブジェクトのリスト>の次のゲームオブジェクトのアドレスを初期化する
			goBase->goInfo->addOrDelNext = NULL;
			if (goBase->IsRigidBody())
			{
				System::GetSystemInstance()->dynamicsWorld->addRigidBody(goBase->GetRigidBody());
			}
		}
		addGameObjectInfoList = NULL;
	}
#pragma endregion 
#pragma region <削除するゲームオブジェクトのリスト>に登録されているゲームオブジェクトをリストから外す
	if (delGameObjectList != NULL)
	{
		for (goBase = delGameObjectList; goBase != NULL; goBase = nextGo)
		{
			// <削除するゲームオブジェクトのリスト>の次のゲームオブジェクトのアドレスを保持しておく
			nextGo = goBase-> goInfo->addOrDelNext;

			// 外すゲームオブジェクトが状態推移処理のゲームオブジェクトのリストの先頭かをチェック
			if (updateList[goBase->goInfo->goBaseInfo->updatePriority] ==goBase )
			{
				updateList[goBase->goInfo->goBaseInfo->updatePriority] = goBase->goInfo->updateNext;
			}
			else
			{
				// 状態推移処理のゲームオブジェクトのリストの先頭ではなかったら
				// 状態推移処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
				tempGo = updateList[goBase->goInfo->goBaseInfo->updatePriority];

				while (true)
				{
					// リストの終端に来てしまった場合はループを抜ける
					if (tempGo->goInfo->updateNext == NULL)
					{
						break;
					}
					// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
					if (tempGo->goInfo->updateNext == goBase)
					{
						tempGo->goInfo->updateNext = goBase-> goInfo->updateNext;
						break;
					}
					tempGo = tempGo->goInfo->updateNext;
				}

			}
			// 外すゲームオブジェクトが描画処理のゲームオブジェクトのリストの先頭かをチェック
			if (drawList[goBase->goInfo->goBaseInfo->drawPriority] == goBase)
			{
				// 先頭だった場合は先頭を外すゲームオブジェクトの次のゲームオブジェクトにする
				drawList[goBase->goInfo->goBaseInfo->drawPriority] = goBase-> goInfo->drawNext;
			}
			else
			{
				// 描画処理のゲームオブジェクトのリストの先頭ではなかったら
				// 描画処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
				tempGo = drawList[goBase->goInfo->goBaseInfo->drawPriority];

				while (true)
				{
					// リストの終端に来てしまった場合はループを抜ける
					if (tempGo->goInfo->drawNext == NULL)
					{
						break;
					}
					// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
					if (tempGo->goInfo->drawNext == goBase)
					{
						tempGo->goInfo->drawNext = goBase-> goInfo->drawNext;
						break;
					}
					tempGo = tempGo->goInfo->drawNext;
				}

			}
		}
		delGameObjectList = NULL;
	}
#pragma endregion
	return true;
}

Scene::~Scene()
{
}
