#include "SceneManager.h"

Scene * SceneManager::nowPlayScene= NULL;

SceneManager::SceneManager()
{
}

void SceneManager::InitSceneManager()
{
	nowPlayScene = SceneGameStartMenu::GetSceneInstance();
}

//シーンを切り替え
void SceneManager::LoadSceneLevel(EGameScene sence)
{
	switch (sence)
	{
	case StartMenu:
		nowPlayScene = SceneGameStartMenu::GetSceneInstance();
		break;
	case GameMain:
		nowPlayScene = SceneGameMain::GetSceneInstance();
		break;
	case GameOver:
		break;
	default:
		break;
	}
}

//現在進行中のシーンのオブジェクトポインターを貰う
Scene * SceneManager::GetNowPlayScene()
{

	if (nowPlayScene == NULL)
	{
		//FOR TEST:
		InitSceneManager();
	}

	return nowPlayScene;
}

SceneManager::~SceneManager()
{

}

