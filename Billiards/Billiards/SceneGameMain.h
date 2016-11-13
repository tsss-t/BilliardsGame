#pragma once
#ifndef SceneGameMain_H
#define SceneGameMain_H
#include "Scene.h";
#include "Ball.h"
#include "PoolStick.h"
#include "BiliardsTable.h";
#include "Slider.h"
#include "Button.h"

using namespace std;

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
	Sprite * spTableLeft;
	Slider * sldForce;
	Sprite * spLog;

	int handleMenu;
	int handleMenuHightLight;
	Sprite * spMenu;
	Label * lbMenu;
	Button * btMenu;

	Button * btFollowMode;
	Button * btFixedMode;
	Button * btFreeMode;

	Sprite * spFollowMode;
	Sprite * spFixedMode;
	Sprite * spFreeMode;

	VECTOR2D nextBallIconPosition;
	Sprite * spBallList[BallNum];

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