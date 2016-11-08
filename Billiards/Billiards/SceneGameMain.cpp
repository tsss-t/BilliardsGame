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
	cameraManager->SetCamaraViewPR(Top, VGet(1.87f, 102.0f, 24.0f), VGet(1.352f, -3.1415f, 0.0f));
	cameraManager->SetCamaraViewPR(Back, VGet(3.52f, 84.448f, -50.417f), VGet(0.933f, -0.000003f, 0.0f));
	cameraManager->SetCamaraViewPR(Left, VGet(76.185f, 57.65f, -1.52f), VGet(0.66f, -4.7f, 0.0f));
	cameraManager->SetCamaraViewPR(Right, VGet(-67.72f, 59.32f, 0.177f), VGet(0.706f, 1.579f, 0.0f));


	isPressed = false;
	pressTime = 0.0f;
	pressTimeLimit = 2.0f;
	forceAdd = true;
	forceRatio = 100;
	hitPosition = VGet(0, 0, 0);

	//--------3D Model-------
	ballWhite = new Ball(VGet(20.0f, 29.1f, 0.0f), VGet(90.0f, 0.0f, 0.0f), VGet(0.04f, 0.04f, 0.04f), MV1LoadModel("Data/Model/BallWhite.mv1"));
	poolStick = new PoolStick(VGet(0.0f, 27.6f, 0.0f), VGet(0.0f, (float)PI, 0.0f));
	billiardTable = new BilliardsTable();
	float originX = -20.0f;
	float originY = 29.1f;
	float originZ = 0.0f;
	float r = 1.2f;
	float offsetX, offsetZ;
	char s[30];

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

	//--------2D UI---------
	spTableLeft = new Sprite("Data/Sprite/Table.png", 12);
	spTableLeft->SetPosition(1020, 570);
	spTableLeft->SetCenterPoint(0, 0);
	spTableLeft->SetScale(0.5f, 0.5f);

	spLog = new Sprite("Data/Sprite/List.png", 12);
	spLog->SetPosition(600, 668);

	sldForce = new Slider("Data/Sprite/ProgressBar.png", "Data/Sprite/ProgressFram.png", 12);
	sldForce->SetPosition(1020, 13);
	sldForce->SetFrontSpriteOffset(13, 25);

	handleMenu = LoadGraph("Data/Sprite/button3.png");
	handleMenuHightLight = LoadGraph("Data/Sprite/button4.png");
	//StartGame　ボタンの設定
	spMenu = new  Sprite(handleMenu);
	spMenu->SetCenterPoint(0, 0);
	lbMenu = new  Label("Menu", NULL, 20, 9, DX_FONTTYPE_NORMAL);
	lbMenu->SetOffset(40, 13.5f);
	btMenu = new Button(lbMenu, spMenu);
	btMenu->SetPosition(10, 670);
	btMenu->SetHoverSpriteHandle(handleMenuHightLight);
	//btMenu->SetClickEvent(GameStart);

	spFollowMode =new Sprite("Data/Sprite/ViewFollow.png");
	spFollowMode->SetScale(0.2f, 0.2f);
	spFollowMode->SetCenterPoint(0, 0);
	spFixedMode = new Sprite("Data/Sprite/ViewFixed.png");
	spFixedMode->SetScale(0.2f, 0.2f);
	spFixedMode->SetCenterPoint(0, 0);
	spFreeMode = new Sprite("Data/Sprite/ViewFree.png");
	spFreeMode->SetScale(0.2f, 0.2f);
	spFreeMode->SetCenterPoint(0, 0);

	btFollowMode = new Button(spFollowMode,13);
	btFixedMode=new Button(spFixedMode,13);
	btFreeMode = new Button(spFreeMode,13);
	btFollowMode->SetPosition(1020,570);
	btFixedMode->SetPosition(1020, 620);
	btFreeMode->SetPosition(1020, 670);
	btFollowMode->SetClickEvent(ChangeCameraModeToFollow);
	btFixedMode->SetClickEvent(ChangeCameraModeToFixed);
	btFreeMode->SetClickEvent(ChangeCameraModeToFree);

	AddToScene(btFollowMode);
	AddToScene(btFixedMode);
	AddToScene(btFreeMode);


	AddToScene(spLog);
	AddToScene(sldForce);
	AddToScene(spTableLeft);
	AddToScene(btMenu);

	AddToScene(billiardTable);
	AddToScene(ballWhite);
	AddToScene(poolStick);
}

SceneGameMain::~SceneGameMain()
{
	for (int i = 0; i < BallNum; i++)
	{
		delete ballList[i];
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
	DrawFormatString(0, 32, GetColor(255, 255, 255), "pressTime   %f",
		pressTime);

	FLOAT2 mousePosition = InputSystem::GetInputSystemInstance()->GetMouseNowPosition();

	// マウスポインタがある画面上の座標に該当する３Ｄ空間上の Near 面の座標を取得
	VECTOR StartPos = ConvScreenPosToWorldPos(VGet(mousePosition.u, mousePosition.v, 0.0f));

	// マウスポインタがある画面上の座標に該当する３Ｄ空間上の Far 面の座標を取得
	VECTOR EndPos = ConvScreenPosToWorldPos(VGet(mousePosition.u, mousePosition.v, 1.0f));

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
			else
			{
				//左ボタンを離した瞬間、力の大きさと方向を計算しボールに与える
				if (isPressed)
				{
					isPressed = false;
					VECTOR dis = poolStick->GetDistance();
					ballWhite->GetRigidBody()->activate();
					ballWhite->GetRigidBody()->applyCentralImpulse(btVector3(force*dis.x, 0, force*dis.z));
				}
			}
		}
		//ボールが運動している状態になったら、ステックを隠し
		else
		{
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

//シーン全体の描画処理を行う
bool SceneGameMain::SceneDraw(void)
{

#ifdef _DEBUG

	// 交差した座標を描画
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Hit Pos   %f  %f  %f",
		hitPosition.x, hitPosition.y, hitPosition.z);


#endif // _DEBUG
	if (!Scene::SceneDraw())
	{
		return false;
	}
	return  true;
}

void SceneGameMain::ChangeCameraModeToFree()
{
	CameraManager::GetCameraManagerInstance()->ChangeCameraMode(FreeMode);
}

void SceneGameMain::ChangeCameraModeToFollow()
{
	CameraManager::GetCameraManagerInstance()->ChangeCameraMode(FollowMode);
}

void SceneGameMain::ChangeCameraModeToFixed()
{
	CameraManager::GetCameraManagerInstance()->ChangeCameraMode(FixedMode);
}
