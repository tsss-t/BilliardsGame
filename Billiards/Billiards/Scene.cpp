#include "Scene.h"

Scene::Scene()
{
	InitGameObjectList();
}
bool Scene::InitGameObjectList(void)
{
	*updateList = NULL;
	*drawList = NULL;

	return true;
}
// シーンの状態推移処理
bool Scene::SceneUpdate(float stepTime)
{
	SGameObjectInfo * goInfo;
	run = true;
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		for (goInfo = updateList[i]; goInfo != NULL; goInfo = goInfo->updateNext)
		{
			if (!goInfo->go->Update(stepTime))
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
	SGameObjectInfo * goInfo;
	run = true;
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		for (goInfo = drawList[i]; goInfo != NULL; goInfo = goInfo->drawNext)
		{
			if (!goInfo->go->Draw())
			{
				return false;
			}
		}
	}
	run = false;
	return true;
}
// ゲームオブジェクトの状態推移処理
bool Scene::GameObjectUpdate(float stepTime)
{
	return false;
}
bool Scene::AddToScene(GameObject * gameObject)
{
	gameObject->goInfo->addOrDelNext = addGameObjectInfoList;
	addGameObjectInfoList = gameObject->goInfo;
	if (!run)
	{
		return RefreshList();
	}
	return true;
}
bool Scene::DeleteFromScene(GameObject * gameObject)
{
	gameObject->goInfo->addOrDelNext = delGameObjectList;
	delGameObjectList = gameObject->goInfo;
	if (!run)
	{
		return RefreshList();
	}
	return true;
}
bool Scene::AdjustGameObjectUpdatePriority(GameObject * gameObject, int priority)
{
	SGameObjectInfo * goInfo;
	SGameObjectInfo * nextGoInfo;
	SGameObjectInfo * tempGoInfo;

	goInfo = gameObject->goInfo;


	// 先頭だった場合は先頭を外すゲームオブジェクトの次のゲームオブジェクトにする
	if (updateList[goInfo->goBaseInfo->updatePriority] == goInfo)
	{
		updateList[goInfo->goBaseInfo->updatePriority] = goInfo->updateNext;
	}
	else
	{
		// 状態推移処理のゲームオブジェクトのリストの先頭ではなかったら
		// 状態推移処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
		tempGoInfo = updateList[goInfo->goBaseInfo->updatePriority];
		while (true)
		{
			// リストの終端に来てしまった場合はループを抜ける
			if (tempGoInfo->updateNext == NULL)
			{
				//TODO:ERROR
				return false;
			}

			// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
			if (tempGoInfo->updateNext == goInfo)
			{
				tempGoInfo->updateNext = goInfo->updateNext;
				break;
			}
			tempGoInfo = tempGoInfo->updateNext;
		}
	}
	// 状態推移処理のゲームオブジェクトのリストの先頭に追加する
	goInfo->updateNext = updateList[priority];
	updateList[priority] = goInfo->updateNext;

	return true;
}
bool Scene::AdjustGameObjectDrawPriority(GameObject * gameObject, int priority)
{
	SGameObjectInfo * goInfo;
	SGameObjectInfo * nextGoInfo;
	SGameObjectInfo * tempGoInfo;

	goInfo = gameObject->goInfo;

	// 先頭だった場合は先頭を外すゲームオブジェクトの次のゲームオブジェクトにする
	if (drawList[goInfo->goBaseInfo->drawPriority] == goInfo)
	{
		drawList[goInfo->goBaseInfo->drawPriority] = goInfo->drawNext;
	}
	else
	{
		// 状態推移処理のゲームオブジェクトのリストの先頭ではなかったら
		// 状態推移処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
		tempGoInfo = drawList[goInfo->goBaseInfo->drawPriority];
		while (true)
		{
			// リストの終端に来てしまった場合はループを抜ける
			if (tempGoInfo->drawNext == NULL)
			{
				//TODO:ERROR
				return false;
			}

			// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
			if (tempGoInfo->drawNext == goInfo)
			{
				tempGoInfo->drawNext = goInfo->drawNext;
				break;
			}
			tempGoInfo = tempGoInfo->drawNext;
		}
	}
	// 状態推移処理のゲームオブジェクトのリストの先頭に追加する
	goInfo->updateNext = drawList[priority];
	drawList[priority] = goInfo->drawNext;

	return true;
}
// ゲームオブジェクトの描画処理
bool Scene::GameObjectDraw(void)
{
	return false;
}
bool Scene::RefreshList(void)
{
	SGameObjectInfo * goInfo;
	SGameObjectInfo * nextGoInfo;
	SGameObjectInfo * tempGoInfo;
#pragma region <追加するゲームオブジェクトのリスト>に登録されているゲームオブジェクトをリストに追加する
	if (addGameObjectInfoList != NULL)
	{
		for (goInfo = addGameObjectInfoList; goInfo != NULL; goInfo = nextGoInfo)
		{
			// <追加するゲームオブジェクトのリスト>の次のゲームオブジェクトのアドレスを保持しておく
			nextGoInfo = goInfo->addOrDelNext;

			// 状態推移処理のリストに追加する
			goInfo->updateNext = updateList[goInfo->goBaseInfo->updatePriority];
			updateList[goInfo->goBaseInfo->updatePriority] = goInfo;

			// 描画処理のリストに追加する
			goInfo->updateNext = drawList[goInfo->goBaseInfo->drawPriority];
			drawList[goInfo->goBaseInfo->drawPriority] = goInfo;

			// <追加するゲームオブジェクトのリスト>の次のゲームオブジェクトのアドレスを初期化する
			goInfo->addOrDelNext = NULL;
		}
		addGameObjectInfoList = NULL;
	}
#pragma endregion 
#pragma region <削除するゲームオブジェクトのリスト>に登録されているゲームオブジェクトをリストから外す
	if (delGameObjectList != NULL)
	{
		for (goInfo = delGameObjectList; goInfo != NULL; goInfo = nextGoInfo)
		{
			// <削除するゲームオブジェクトのリスト>の次のゲームオブジェクトのアドレスを保持しておく
			nextGoInfo = goInfo->addOrDelNext;

			// 外すゲームオブジェクトが状態推移処理のゲームオブジェクトのリストの先頭かをチェック
			if (updateList[goInfo->goBaseInfo->updatePriority] == goInfo)
			{
				updateList[goInfo->goBaseInfo->updatePriority] = goInfo->updateNext;
			}
			else
			{
				// 状態推移処理のゲームオブジェクトのリストの先頭ではなかったら
				// 状態推移処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
				tempGoInfo = updateList[goInfo->goBaseInfo->updatePriority];

				while (true)
				{
					// リストの終端に来てしまった場合はループを抜ける
					if (tempGoInfo->updateNext == NULL)
					{
						break;
					}
					// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
					if (tempGoInfo->updateNext == goInfo)
					{
						tempGoInfo->updateNext = goInfo->updateNext;
						break;
					}
					tempGoInfo = tempGoInfo->updateNext;
				}

			}
			// 外すゲームオブジェクトが描画処理のゲームオブジェクトのリストの先頭かをチェック
			if (drawList[goInfo->goBaseInfo->drawPriority] == goInfo)
			{
				// 先頭だった場合は先頭を外すゲームオブジェクトの次のゲームオブジェクトにする
				drawList[goInfo->goBaseInfo->drawPriority] = goInfo->drawNext;
			}
			else
			{
				// 描画処理のゲームオブジェクトのリストの先頭ではなかったら
				// 描画処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
				tempGoInfo = drawList[goInfo->goBaseInfo->drawPriority];

				while (true)
				{
					// リストの終端に来てしまった場合はループを抜ける
					if (tempGoInfo->drawNext == NULL)
					{
						break;
					}
					// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
					if (tempGoInfo->drawNext == goInfo)
					{
						tempGoInfo->drawNext = goInfo->drawNext;
						break;
					}
					tempGoInfo = tempGoInfo->drawNext;
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
