#include "SceneGameMain.h"
#include "System.h"


SceneGameMain *SceneGameMain::_instance = NULL;

SceneGameMain::SceneGameMain()
{
	//入口と環境設定
	sceneNowState = ESceneMainState::FadeInWait;
	SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));

	//カメラ設定
	cameraManager->SetCameraPR(VGet(1.87f, 102.0f, 24.0f), VGet(1.352f, -3.1415f, 0.0f));

	cameraManager->SetCamaraViewPR(Top, VGet(1.87f, 102.0f, 24.0f), VGet(1.352f, -3.1415f, 0.0f));
	cameraManager->SetCamaraViewPR(Back, VGet(3.52f, 84.448f, -50.417f), VGet(0.933f, -0.000003f, 0.0f));
	cameraManager->SetCamaraViewPR(Left, VGet(76.185f, 57.65f, -1.52f), VGet(0.66f, -1.56f, 0.0f));
	cameraManager->SetCamaraViewPR(Right, VGet(-67.72f, 59.32f, 0.177f), VGet(0.706f, 1.579f, 0.0f));

	isPressed = false;
	pressTime = 0.0f;
	pressTimeLimit = 2.0f;
	forceAdd = true;
	forceRatio = 100;
	hitPosition = VGet(0, 0, 0);
#pragma region Trigger


	//*******************************Trigger*******************************
	triggerList[0] = new STriggerBox();
	triggerList[0]->position = { -53,28,28.5f };
	triggerList[0]->size = { 6,2,5 };
	triggerList[1] = new STriggerBox();
	triggerList[1]->position = { -53,28,-28.5f };
	triggerList[1]->size = { 6,2,5 };
	triggerList[2] = new STriggerBox();
	triggerList[2]->position = { 61.0f,28,28.5f };
	triggerList[2]->size = { 6,2,5 };
	triggerList[3] = new STriggerBox();
	triggerList[3]->position = { 61.0f,28,-28.5f };
	triggerList[3]->size = { 6,2,5 };
	triggerList[4] = new STriggerBox();
	triggerList[4]->position = { 3.75,28,28.5f };
	triggerList[4]->size = { 3.5f,2,5 };
	triggerList[5] = new STriggerBox();
	triggerList[5]->position = { 3.75,28,-28.5f };
	triggerList[5]->size = { 0.35f,2,5 };

#pragma endregion


#pragma region 3D Model


	//*******************************3D Model*******************************
	ballWhite = new Ball(VGet(20.0f, 29.1f, 0.0f), VGet(90.0f, 0.0f, 0.0f), VGet(0.0395f, 0.0395f, 0.0395f), MV1LoadModel("Data/Model/BallWhite.mv1"));
	poolStick = new PoolStick(VGet(0.0f, 27.6f, 0.0f), VGet(0.0f, (float)PI, 0.0f));
	billiardTable = new BilliardsTable();
	float originX = -20.0f;
	float originY = 29.1f;
	float originZ = 0.0f;
	float r = 1.2f;
	float offsetX, offsetZ;
	char s[30];

	//Ball Object
	for (int i = 1; i <= 5; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			offsetX = originX - ((float)i - 1.0f) * 2.0f * r;
			offsetZ = originZ - ((float)i - 1.0f)*r + ((float)j - 1.0f) * 2.0f * r;

			int index = (i*(i - 1)) / 2 + j - 1;

			sprintf(s, "Data/Model/Ball%d.mv1", index + 1);
			ballList[index] =
				new Ball(VGet(offsetX, originY, offsetZ), VGet(0, 0, 0), VGet(0.04f, 0.04f, 0.04f), MV1LoadModel(s));
			AddToScene(ballList[index]);
		}
	}
#pragma endregion


#pragma region  2D UI


	//*******************************2D UI*******************************
	fontHandle = CreateFontToHandle("ＭＳ ゴシック", 20, 9, DX_FONTTYPE_NORMAL);

	spLog = new UISprite("Data/Sprite/List.png", 11);
	spLog->SetPosition(420, 580);
	spLog->SetScale(1.1f, 1.4f);
	nextBallIconPosition = { 430,590 };
	initBallIconPosition = { 430,590 };

	sldForce = new UISlider("Data/Sprite/ProgressBar.png", "Data/Sprite/ProgressFram.png", 12);
	sldForce->SetPosition(1020, 13);
	sldForce->SetFrontSpriteOffset(13, 25);

	buttonBackgroundHandle = LoadGraph("Data/Sprite/button3.png");
	buttonBackgroundLightHandle = LoadGraph("Data/Sprite/button4.png");
	//--------------------Menu　ボタンの設定--------------------
	spMenu = new  UISprite(buttonBackgroundHandle);
	lbMenu = new  UILabel("Menu", fontHandle);
	lbMenu->SetOffset(40, 13.5f);
	btMenu = new UIButton(lbMenu, spMenu, 12);
	btMenu->SetPosition(10, 670);
	btMenu->SetHoverSpriteHandle(buttonBackgroundLightHandle);
	//btMenu->SetClickEvent(GameStart);

	//--------------------View Mode Panel--------------------
	plViewMode = new UIPanel(1020, 500, 11);

	//背景図の初期化
	spTableLeft = new UISprite("Data/Sprite/Table.png", 1);
	spTableLeft->SetPosition(0, 0);
	spTableLeft->SetScale(0.5f, 0.8f);

	//ラベルの初期化
	lbViewMode = new UILabel("View Mode:", NULL, 16, 9, DX_FONTTYPE_NORMAL);
	lbViewMode->SetPosition(32, 8);
	lbFollowMode = new UILabel("Follow Mode(TODO)", fontHandle);
	lbFollowMode->SetOffset(17, 13.5);
	lbFixedMode = new UILabel("Fixed Mode", fontHandle);
	lbFixedMode->SetOffset(40, 13.5);
	lbFreeMode = new UILabel("Free Mode", fontHandle);
	lbFreeMode->SetOffset(45, 13.5);

	//ボタン画像の初期化
	spFollowMode = new UISprite(buttonBackgroundHandle);
	spFixedMode = new UISprite(buttonBackgroundHandle);
	spFreeMode = new UISprite(buttonBackgroundHandle);

	//ボタンの初期化
	btFollowMode = new UIButton(lbFollowMode, spFollowMode, 13);
	btFixedMode = new UIButton(lbFixedMode, spFixedMode, 13);
	btFreeMode = new UIButton(lbFreeMode, spFreeMode, 13);

	//位置とサイズ設定
	btFollowMode->SetPosition(37, 45);
	btFollowMode->SetScale(1.5f, 1);
	btFixedMode->SetPosition(37, 95);
	btFixedMode->SetScale(1.5f, 1);
	btFreeMode->SetPosition(37, 145);
	btFreeMode->SetScale(1.5f, 1);

	//クリック事件設定
	btFollowMode->SetClickEvent(ChangeCameraModeToFollow);
	btFixedMode->SetClickEvent(ChangeCameraModeToFixed);
	btFreeMode->SetClickEvent(ChangeCameraModeToFree);

	//Hover反応設定
	btFollowMode->SetHoverSpriteHandle(buttonBackgroundLightHandle);
	btFixedMode->SetHoverSpriteHandle(buttonBackgroundLightHandle);
	btFreeMode->SetHoverSpriteHandle(buttonBackgroundLightHandle);

	//Panelに置く
	plViewMode->AddUI(lbViewMode);
	plViewMode->AddUI(spTableLeft);
	plViewMode->AddUI(btFollowMode);
	plViewMode->AddUI(btFixedMode);
	plViewMode->AddUI(btFreeMode);

	//--------------------View Panel--------------------
	plView = new UIPanel(0, 0, 11);
	plView->SetEnable(false);

	lbTopView = new UILabel("TopView", fontHandle);
	lbTopView->SetOffset(18, 13.5);
	lbLeftView = new UILabel("LeftView", fontHandle);
	lbLeftView->SetOffset(14, 13.5);
	lbRightView = new UILabel("RightView", fontHandle);
	lbRightView->SetOffset(11, 13.5);
	lbBackView = new UILabel("BackView", fontHandle);
	lbBackView->SetOffset(14, 13.5);

	spTopView = new UISprite(buttonBackgroundHandle);
	spLeftView = new UISprite(buttonBackgroundHandle);
	spRightView = new UISprite(buttonBackgroundHandle);
	spBackView = new UISprite(buttonBackgroundHandle);

	btTopView = new UIButton(lbTopView, spTopView, 11);
	btLeftView = new UIButton(lbLeftView, spLeftView, 11);
	btRightView = new UIButton(lbRightView, spRightView, 11);
	btBackView = new UIButton(lbBackView, spBackView, 11);

	btTopView->SetHoverSpriteHandle(buttonBackgroundLightHandle);
	btLeftView->SetHoverSpriteHandle(buttonBackgroundLightHandle);
	btRightView->SetHoverSpriteHandle(buttonBackgroundLightHandle);
	btBackView->SetHoverSpriteHandle(buttonBackgroundLightHandle);

	btTopView->SetPosition(0, 0);
	btLeftView->SetPosition(0, 50);
	btRightView->SetPosition(0, 100);
	btBackView->SetPosition(0, 150);

	btTopView->SetClickEvent(ChangeCameraViewToTop);
	btLeftView->SetClickEvent(ChangeCameraViewToLeft);
	btRightView->SetClickEvent(ChangeCameraViewToRight);
	btBackView->SetClickEvent(ChangeCameraViewToBack);

	plView->AddUI(btTopView);
	plView->AddUI(btLeftView);
	plView->AddUI(btRightView);
	plView->AddUI(btBackView);

	//--------------------Ball Sprite--------------------
	for (int i = 0; i < BallNum; i++)
	{
		sprintf(s, "Data/Sprite/ball%d.png", i + 1);
		spBallList[i] = new UISprite(s, 12);
		spBallList[i]->SetScale(0.3f, 0.3f);
	}
#pragma endregion

	AddToScene(plViewMode);

	AddToScene(spLog);
	AddToScene(sldForce);
	AddToScene(btMenu);

	AddToScene(billiardTable);
	AddToScene(ballWhite);
	AddToScene(poolStick);

}

SceneGameMain::~SceneGameMain()
{
	for (int i = 0; i < BallNum; i++)
	{
		delete spBallList[i];
		delete ballList[i];
	}
	for (int i = 0; i < 6; i++)
	{
		delete triggerList[i];
	}
	delete poolStick;
	delete billiardTable;


}

//SceneGameMain唯一のオブジェクトのポインターを貰う
SceneGameMain * SceneGameMain::GetSceneInstance()
{
	if (_instance == NULL)
	{
		_instance = new SceneGameMain();
	}
	return _instance;
}



//シーン全体の状態推移処理を行う
bool SceneGameMain::SceneUpdate(float stepTime)
{
	//DrawFormatString(0, 32, GetColor(255, 255, 255), "pressTime   %f",
	//	pressTime);

	FLOAT2 mousePosition = InputSystem::GetInputSystemInstance()->GetMouseNowPosition();

	// マウスポインタがある画面上の座標に該当する３Ｄ空間上の Near 面の座標を取得
	VECTOR StartPos = ConvScreenPosToWorldPos(VGet(mousePosition.u, mousePosition.v, 0.0f));

	// マウスポインタがある画面上の座標に該当する３Ｄ空間上の Far 面の座標を取得
	VECTOR EndPos = ConvScreenPosToWorldPos(VGet(mousePosition.u, mousePosition.v, 1.0f));

	//マウスのポインターとテーブルの面と会う点を計算
	if ((StartPos.y > TableHight&&EndPos.y < TableHight) || (StartPos.y < TableHight&&EndPos.y > TableHight))
	{
		float slope = ((TableHight - StartPos.y) / (EndPos.y - StartPos.y));
		float hitZ = slope  * (EndPos.z - StartPos.z) + StartPos.z;
		float hitX = slope  * (EndPos.x - StartPos.x) + StartPos.x;
		this->hitPosition = VGet(hitX, TableHight, hitZ);
	}

	if (!Scene::SceneUpdate(stepTime))
	{
		return false;
	}
	switch (sceneNowState)
	{
	case ESceneMainState::FadeInWait:
	{
		timer += stepTime;
		if (timer > FADE_IN_WAIT_TIME)
		{
			SoundSystem::GetSoundSystemInstance()->PlayBGM(EBGM::EBGM_GameMain);

			timer = 0;
			sceneNowState = ESceneMainState::FadeIn;
		}
		break;
	}
	case ESceneMainState::FadeIn:
	{
		timer += stepTime;
		if (timer > FADE_IN_TIME)
		{
			sceneNowState = ESceneMainState::GamePlaying;
			btFollowMode->SetEventEnable(true);
			btFixedMode->SetEventEnable(true);
			btFreeMode->SetEventEnable(true);
			btMenu->SetEventEnable(true);
			btTopView->SetEventEnable(true);
			btLeftView->SetEventEnable(true);
			btRightView->SetEventEnable(true);
			btBackView->SetEventEnable(true);
			timer = 0;
		}
		else
		{
			System::GetSystemInstance()->System_FadeIn();
		}
		break;
	}
	case ESceneMainState::GamePause:
	{
		break;
	}
	case ESceneMainState::GamePlaying:
	{
		if (poolStick->IsEnable())
		{
			this->poolStick->SetPosition(this->ballWhite->GetPosition());

			float cos_sita = VCos(VGet(hitPosition.x - this->ballWhite->GetPosition().x, 0, hitPosition.z - this->ballWhite->GetPosition().z), VGet(1, 0, 0));

			if (hitPosition.z - this->ballWhite->GetPosition().z > 0)
			{
				this->poolStick->SetRotation(VGet(0.0f, -acosf(cos_sita), 0.0f));
			}
			else
			{
				this->poolStick->SetRotation(VGet(0.0f, acosf(cos_sita), 0.0f));
			}
		}

		//運動停止している状態
		if (ballWhite->GetRigidBody()->getActivationState() == 2)
		{
			//ステックを起動
			if (!poolStick->IsEnable())
			{
				poolStick->SetEnabel(true);
				sldForce->SetProccess(0);
			}
			//左ボタンを押したら

			if (InputSystem::GetInputSystemInstance()->GetMouseInputButton() & MOUSE_INPUT_LEFT)
			{
				FLOAT2 mousePosition = InputSystem::GetInputSystemInstance()->GetMouseNowPosition();
				if (!Scene::IsPointInUI({ mousePosition.u,mousePosition.v }))
				{
					//押す状態に変更、押す時間を初期化した後、計算を始る
					if (!isPressed)
					{
						isPressed = true;
						forceAdd = true;
						pressTime = 0;
					}
					else
					{
						pressTime += stepTime;
						if (pressTime > pressTimeLimit)
						{
							pressTime -= pressTimeLimit;
							forceAdd = !forceAdd;
						}
						if (forceAdd)
						{
							force = forceRatio* pressTime / pressTimeLimit;
							sldForce->SetProccess(pressTime / pressTimeLimit);
						}
						else
						{
							force = forceRatio*(pressTimeLimit - pressTime) / pressTimeLimit;
							sldForce->SetProccess((pressTimeLimit - pressTime) / pressTimeLimit);
						}
					}
					//ballWhite->AddForce(VGet(0, 0, 0), VGet(0, 0, 0));
				}
			}
			else
			{
				//左ボタンを離した瞬間、力の大きさと方向を計算しボールに与える
				if (isPressed)
				{
					isPressed = false;
					VECTOR dis = poolStick->GetDistance();
					ballWhite->GetRigidBody()->activate();
					ballWhite->GetRigidBody()->applyCentralImpulse(btVector3(force*dis.x, -0.5f, force*dis.z));
				}
			}
		}
		//ボールが運動している状態になったら、ステックを隠し
		else
		{
			//ボールの位置情報をチェックするし　ゴールなどの状態を監視する
			CheckBallPosition();
			if (poolStick->IsEnable())
			{
				poolStick->SetEnabel(false);
			}
		}
		break;
	}
	case ESceneMainState::FadeOut:
	{
		break;
	}
	case ESceneMainState::End:
	{
		break;
	}
	case ESceneMainState::MenuFadeInWait:
	{
		break;
	}
	case ESceneMainState::MenuFadeIn:
	{
		break;
	}
	default:
		break;
	}
	return true;
}

void SceneGameMain::CheckBallPosition()
{
	VECTOR ballPosition;

	for (int i = 0; i < BallNum; i++)
	{
		if (ballList[i]->GetEnable())
		{
			ballPosition = ballList[i]->GetPosition();
			//外部に飛んだ　OR　穴に入った
			if (ballPosition.y < 28.5f)
			{
				for (int j = 0; j < 6; j++)
				{
					//穴に入った 
					if (ballPosition.x > triggerList[j]->position.x - triggerList[j]->size.x / 2 &&
						ballPosition.x < triggerList[j]->position.x + triggerList[j]->size.x / 2 &&
						ballPosition.z > triggerList[j]->position.z - triggerList[j]->size.z / 2 &&
						ballPosition.z < triggerList[j]->position.z + triggerList[j]->size.z / 2)
					{
						ballList[i]->SetEnable(false);
						ballList[i]->SetPosition({ 0, 100, 0 });
						DeleteFromScene(ballList[i]);;
						GoalIn(i);
						break;
					}
					if (j == 5)
					{
						//外部に飛んだ
						ballList[i]->ResetPosition();
					}

				}
			}
		}
	}

	if (ballWhite->GetPosition().y < 28.5f)
	{
		ballWhite->ResetPosition();
	}
}

void SceneGameMain::GoalIn(int ballNum)
{
	if (nextBallIconPosition.x + spBallList[ballNum]->GetUISize().x > spLog->GetPosition().x + spLog->GetUISize().x)
	{
		nextBallIconPosition.x = initBallIconPosition.x;
		nextBallIconPosition.y += spBallList[ballNum]->GetUISize().y;
	}
	spBallList[ballNum]->SetPosition(nextBallIconPosition);
	spBallList[ballNum]->SetEnable(true);

	nextBallIconPosition.x += spBallList[ballNum]->GetUISize().x;
	AddToScene(spBallList[ballNum]);
}

//シーン全体の描画処理を行う
bool SceneGameMain::SceneDraw(void)
{

#ifdef _DEBUG

	// 交差した座標を描画
	//DrawFormatString(0, 16, GetColor(255, 255, 255), "Hit Pos   %f  %f  %f",
	//	hitPosition.x, hitPosition.y, hitPosition.z);


#endif // _DEBUG
	if (!Scene::SceneDraw())
	{
		return false;
	}
	return  true;
}

void SceneGameMain::DisableViewPanel()
{
	if (plView->IsEnabled())
	{
		this->plView->SetEnable(false);
		this->DeleteFromScene(plView);
	}
}

void SceneGameMain::ShowViewPanel()
{
	if (!plView->IsEnabled())
	{
		this->plView->SetEnable(true);
		this->AddToScene(plView);
	}
}

void SceneGameMain::ChangeCameraModeToFree()
{
	SceneGameMain::GetSceneInstance()->DisableViewPanel();
	CameraManager::GetCameraManagerInstance()->ChangeCameraMode(ECameraMode::FreeMode);
}

void SceneGameMain::ChangeCameraModeToFollow()
{

	CameraManager::GetCameraManagerInstance()->ChangeCameraMode(ECameraMode::FollowMode);
}

void SceneGameMain::ChangeCameraModeToFixed()
{
	SceneGameMain::GetSceneInstance()->ShowViewPanel();
	CameraManager::GetCameraManagerInstance()->ChangeCameraMode(ECameraMode::FixedMode);
}

void SceneGameMain::ChangeCameraViewToTop()
{
	CameraManager::GetCameraManagerInstance()->ChangeCameraView(ECameraView::Top);
}

void SceneGameMain::ChangeCameraViewToBack()
{
	CameraManager::GetCameraManagerInstance()->ChangeCameraView(ECameraView::Back);
}

void SceneGameMain::ChangeCameraViewToLeft()
{
	CameraManager::GetCameraManagerInstance()->ChangeCameraView(ECameraView::Left);
}

void SceneGameMain::ChangeCameraViewToRight()
{
	CameraManager::GetCameraManagerInstance()->ChangeCameraView(ECameraView::Right);
}

