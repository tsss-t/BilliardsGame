#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>
#include "Scene.h"
#include "SceneGameMain.h"
#include "SceneGameStartMenu.h"

using namespace std;

typedef enum _EGameScene
{
	StartMenu = 0,
	GameMain = 1,
	GameOver = 2
} EGameScene;


static class SceneManager
{
public:
	//初期化
	static void InitSceneManager();

	//シーンを切り替え
	static void LoadSceneLevel(EGameScene sence);

	//現在進行中のシーンのオブジェクトポインターを貰う
	static  Scene * GetNowPlayScene();

	~SceneManager();
private:
	static Scene * nowPlayScene;
	SceneManager();
};

#endif // !SCENEMANAGER_H
