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

static bool myContactAddedCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);

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
		GameOverShow,
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
	static SceneGameMain * GetNewScene();
	~SceneGameMain();
	bool SceneUpdate(float stepTime);
	void CheckBallPosition();
	bool CheckBallInGoal(Ball * ball);
	void GoalIn(int ballNum);
	bool SceneDraw(void);

	void DisableViewPanel();
	void ShowViewPanel();

	void ShowGameOverPanel();

	void DisableGameOverPanel();

	static void ChangeCameraModeToFree();
	static void ChangeCameraModeToFollow();
	static void ChangeCameraModeToFixed();
	static void ChangeCameraViewToTop();
	static void ChangeCameraViewToBack();
	static void ChangeCameraViewToLeft();
	static void ChangeCameraViewToRight();

	static void BackToMenu();

private:
	static SceneGameMain * _instance;

	ESceneMainState sceneNowState;


	//--------物理世界の構築---------

	// プロキシの最大数
	int maxProxies;

	// ワールドの広さ
	btVector3 worldAabbMin;
	btVector3 worldAabbMax;

	DxDebugDraw g_debugdraw;
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

	//GameOverPanel
	UIPanel * plGameOver;
	UISprite * spMenuBackGround;

	UILabel * lbResult;
	UIButton * btBack;
	UILabel * lbBack;
	UISprite * spBack;

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
	void Reset();


	
	//test:

};
static Ball * tempBall;
#endif // !SceneGameMain_H