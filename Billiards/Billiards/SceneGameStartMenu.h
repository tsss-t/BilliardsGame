#pragma once
#ifndef SCENEGAMESTARTMENU_H
#define SCENEGAMESTARTMENU_H

#include "Scene.h"
#include "UISprite.h"
#include "UILabel.h"
#include "UIButton.h"



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

	UISprite * spriteBG;
	UISprite * spriteLogo;
	UISprite * spriteTitle;

	int buttonSpriteHandle;
	int buttonSpriteHighLightHanel;
	UIButton * btStartGame;
	UISprite * spStartGame;
	UILabel * lbStartGame;
	
	UIButton * btSettingGame;
	UISprite * spSettingGame;
	UILabel * lbSettingGame;

	UIButton * btExitGame;
	UISprite * spExitGame;
	UILabel * lbExitGame;

	SceneGameStartMenu();
};


#endif