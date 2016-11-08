#pragma once
#ifndef SCENEGAMESTARTMENU_H
#define SCENEGAMESTARTMENU_H

#include "Scene.h"
#include "Sprite.h"
#include "Label.h"
#include "Button.h"



class SceneGameStartMenu:public Scene
{
public:
	typedef enum _ESceneStartMenuState {
		FadeInWait,
		FadeIn,
		MenuSelect,
		FadeOut,
		End
	}EStartSceneMenuState;
	typedef enum _EGameStartMenuNext
	{
		GameMain,
		GameSetting,
		GameExit,

	}EGameStartMenuNext;

	static SceneGameStartMenu *GetSceneInstance();

	_ESceneStartMenuState sceneNowState;

	bool SceneUpdate(float stepTime);
	bool SceneDraw(void);

	static void GameStart();
	static void GameEixt();
	~SceneGameStartMenu();

private:

	static SceneGameStartMenu * _instance;

	static _EGameStartMenuNext nextScene;

	Sprite * spriteBG;
	Sprite * spriteLogo;
	Sprite * spriteTitle;

	int buttonSpriteHandle;
	int buttonSpriteHighLightHanel;
	Button * btStartGame;
	Sprite * spStartGame;
	Label * lbStartGame;
	
	Button * btSettingGame;
	Sprite * spSettingGame;
	Label * lbSettingGame;

	Button * btExitGame;
	Sprite * spExitGame;
	Label * lbExitGame;

	SceneGameStartMenu();
};


#endif