#pragma once
#ifndef SceneGameMain_H
#define SceneGameMain_H
#include "Scene.h";
#include "Ball.h"
#include "PoolStick.h"
#include "BiliardsTable.h";
#include "UISlider.h"
#include "UIButton.h"
#include "UIPanel.h"

#define TableHight (28.1f)
#define BallNum (15)

class SceneGameMain :public Scene
{
public:
	//シーンの基本状態定義
	typedef enum _ESceneMainState
	{
		FadeInWait,
		FadeIn,
		GamePause,
		GamePlaying,
		FadeOut,
		End,
		MenuFadeInWait,
		MenuFadeIn,
	} ESceneMainState;

	typedef struct _STriggerBox
	{
		VECTOR position;

		VECTOR  size;
	}STriggerBox;

	static SceneGameMain *GetSceneInstance();

	~SceneGameMain();
	bool SceneUpdate(float stepTime);
	void CheckBallPosition();
	void GoalIn(int ballNum);
	bool SceneDraw(void);

	void DisableViewPanel();
	void ShowViewPanel();

	static void ChangeCameraModeToFree();
	static void ChangeCameraModeToFollow();
	static void ChangeCameraModeToFixed();
	static void ChangeCameraViewToTop();
	static void ChangeCameraViewToBack();
	static void ChangeCameraViewToLeft();
	static void ChangeCameraViewToRight();

private:
	static SceneGameMain * _instance;
	ESceneMainState sceneNowState;

	//--------Trigger---------
	STriggerBox * triggerList[6];

	//--------2D UI---------
	int fontHandle;

	UISprite * spTableLeft;
	UISlider * sldForce;
	UISprite * spLog;

	int buttonBackgroundHandle;
	int buttonBackgroundLightHandle;
	UISprite * spMenu;
	UILabel * lbMenu;
	UIButton * btMenu;

	//View Mode
	UIPanel * plViewMode;

	UILabel * lbViewMode;

	UISprite * spFollowMode;
	UISprite * spFixedMode;
	UISprite * spFreeMode;

	UILabel * lbFollowMode;
	UILabel * lbFixedMode;
	UILabel * lbFreeMode;

	UIButton * btFollowMode;
	UIButton * btFixedMode;
	UIButton * btFreeMode;

	//View
	UIPanel * plView;

	UIButton * btTopView;
	UIButton * btLeftView;
	UIButton * btRightView;
	UIButton * btBackView;
	UISprite * spTopView;
	UISprite * spLeftView;
	UISprite * spRightView;
	UISprite * spBackView;
	UILabel * lbTopView;
	UILabel * lbLeftView;
	UILabel * lbRightView;
	UILabel * lbBackView;

	VECTOR2D initBallIconPosition;
	VECTOR2D nextBallIconPosition;
	UISprite * spBallList[BallNum];

	//--------3D Model-------
	Ball * ballWhite;
	Ball * ballList[BallNum];

	PoolStick * poolStick;
	BilliardsTable * billiardTable;


	float isPressed;
	float pressTime;
	float pressTimeLimit;
	float force;
	bool forceAdd;
	float forceRatio;
	VECTOR hitPosition;
	SceneGameMain();
};

#endif // !SceneGameMain_H