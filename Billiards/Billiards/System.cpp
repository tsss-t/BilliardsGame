#include "System.h"
#include <iostream>

System *System::_instance = NULL;
SSystemInfo System::systemInfo{};
//test:
//int x;
//int handle;     // 画像格納用ハンドル
System::System()
{
	//x = 0;
}
System *System::GetSystemInstance()
{
	if (_instance == NULL)
	{
		_instance = new System();
	}
	return _instance;
}
bool System::SystemInit(void)
{
#pragma region システム設定
	//ウインドウモードで起動するか確認する
	if (MessageBox(NULL, "using the window mode？", "Screen mode select", MB_YESNO) == IDYES)
	{
		// 「はい」が選択された場合はウインドウモードで起動
		ChangeWindowMode(TRUE);
	}

	//低処理負荷モードで起動するか確認する
	//if (MessageBox(NULL, "Low？", "処理負荷モード確認", MB_YESNO) == IDYES)
	//{
		// 「はい」が選択された場合は低処理負荷モードフラグを立てる
		//systemInfo.lowSpecMode = true;
	//}

	//ゲーム画面の解像度を設定
	SetGraphMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);
	SetMainWindowText("Biliards Game");
	SetEnableXAudioFlag(systemInfo.lowSpecMode ? FALSE : TRUE);
	Set3DSoundOneMetre(100.0f);



#pragma region Fade関連
	systemInfo.fade = FALSE;
	systemInfo.fadeOut = TRUE;
	systemInfo.fadeOutRate = 1.0f;
#pragma endregion

#pragma endregion

#pragma region Dxlib初期化
	if (DxLib_Init() == -1)
	{
		return false;
	}
#pragma endregion

#pragma region FONT導入
	systemInfo.fontHandle[EFontHandle_Small] = CreateFontToHandle(
		NULL, FONTHANDLE_SMALL_SIZE, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);

	systemInfo.fontHandle[EFontHandle_Midium] = CreateFontToHandle(
		NULL, FONTHANDLE_MIDIUM_SIZE, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);

	systemInfo.fontHandle[EFontHandle_Big] = CreateFontToHandle(
		NULL, FONTHANDLE_BIG_SIZE, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
#pragma endregion

#pragma region Audio導入及び初期化
	char filePath[MAXPATH];
	for (int i = 0; i < ECommonSE_Num; i++)
	{
		sprintf_s(filePath, "Data\\Sound\\SE\\Common\\%s", CommonSEFileName[i]);
		systemInfo.commonSEHandle[i] = LoadSoundMem(filePath);
		if (systemInfo.commonSEHandle[i] == -1)
		{
			return false;
		}
	}
#pragma endregion

#pragma region playerInfo初期化
	//TODO:playerInfo初期化
#pragma endregion

#pragma region Camera初期化
	SetDrawScreen(DX_SCREEN_BACK);
	CameraManager::GetCameraManagerInstance();

#pragma endregion

#pragma region Bullet物理システム初期化

	// ワールドの広さ
	worldAabbMin = btVector3(-10000, -10000, -10000);
	worldAabbMax = btVector3(10000, 10000, 10000);

	// プロキシの最大数（衝突物体のようなもの）
	maxProxies = 1024;

	// broadphaseの作成
	btAxisSweep3* broadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);

	// デフォルトの衝突設定とディスパッチャの作成
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	// 衝突解決ソルバ
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	// 離散動的世界の作成
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	// 重力の設定
	dynamicsWorld->setGravity(btVector3(0, -100, 0));

#ifdef _DEBUG
	dynamicsWorld->setDebugDrawer(&g_debugdraw);
	dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
#endif  
#pragma endregion

#pragma region scence管理システムの初期化
	//シーン初期化
	SceneManager::InitSceneManager();
#pragma endregion

#pragma region 入力システムの初期化
	//TODO：入力システムの初期化
#pragma endregion

#pragma region 起動
	//TODO：起動
#ifdef DEBUG_START_MODE
#else


#endif // DEBUG_START_MODE
#pragma endregion

#pragma region フレームレート計測変数初期化
	//フレームレート計測変数初期化
	systemInfo.backDispFrameTime = GetNowHiPerformanceCount();
	systemInfo.frameCounter = 0;
	systemInfo.dispFrameCount = 0;
#pragma endregion

	return true;
}
bool System::SystemMain(void)
{
	if (!SystemInit())
	{
		return false;
	}
	if (!SystemLoop())
	{
		return false;
	}
	delete _instance;
	return true;
}
bool System::SystemLoop(void)
{
	int i;
	LONGLONG nowTime;
	//初期化フレームの状態推移時間
	systemInfo.stepTime = MAX_DELTA_TIME;
	systemInfo.prevTime = GetNowHiPerformanceCount();
	systemInfo.stepNum = 1;
	while (!ProcessMessage())
	{
		for (i = 0; i < systemInfo.stepNum; i++)
		{
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || systemInfo.exitGame)
			{
				systemInfo.exitGame = true;
				break;
			}
#ifdef _DEBUG
			//int p = 1;
			// TODO:デバッグ関係の状態推移処理を行う
			//System_DebugStep();

#endif
			// 状態推移処理を行う
			if (!SystemUpdate(systemInfo.stepTime))
			{
				return false;
			}
		}

		// ソフトを終了するかどうかのフラグが立っていたらループを抜ける
		if (systemInfo.exitGame)
		{
			break;
		}

		// 描画処理を行う
		SystemDraw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		// 現在の時間を取得
		nowTime = GetNowHiPerformanceCount();

		// 前回取得した時間からの経過時間を算出
		systemInfo.stepTime = (nowTime - systemInfo.prevTime) / 1000000.0f;

		// 状態推移処理を行う回数を算出
		systemInfo.stepNum = (int)(systemInfo.stepTime / MAX_DELTA_TIME);

		// 状態推移処理を行う回数が少なくとも１回にする
		if (systemInfo.stepNum == 0)
		{
			systemInfo.stepNum = 1;
		}
		else
		{
			// ０回ではない場合は状態推移で進める時間を状態推移を行う回数で割る
			systemInfo.stepTime /= systemInfo.stepNum;

			// もし状態推移を行う回数が最大値を超えていたら最大値に抑える
			if (systemInfo.stepNum > MAX_FRAME_NUM)
			{
				systemInfo.stepNum = MAX_FRAME_NUM;
			}
		}
		// 今回の時間を保存する
		systemInfo.prevTime = nowTime;

		// フレームレート計測用のカウンタを１足す
		systemInfo.frameCounter++;

		// 前回フレームレートを更新してから１秒経過したら表示用フレームカウントを更新する
		if (nowTime - systemInfo.backDispFrameTime > 1000000)
		{
			// 表示用フレームカウントを更新
			systemInfo.dispFrameCount = systemInfo.frameCounter;

			// 計測用フレームカウンタを初期化
			systemInfo.frameCounter = 0;

			// 表示用フレームカウントを更新した時間を更新
			systemInfo.backDispFrameTime = nowTime;
		}

		// 画面を初期化する
		ClearDrawScreen();
	}
	// 正常終了
	return true;
}
bool System::SystemUpdate(float stepTime)
{
	// bulletシミュレーションを進める。
	dynamicsWorld->stepSimulation(stepTime, 10);

	//入力処理を行う
	InputSystem::GetInputSystemInstance()->InputSystemUpdate(stepTime);

	//// フェード処理の状態推移を行う
	SystemFadeUpdate(stepTime);

	//// シーンの状態推移処理を行う
	//if (!TaskSystem_Step(&g_SystemInfo.TaskSystemInfo, StepTime))
	//{
	//	return false;
	//}
	// 正常終了
	//test:
	//x++;
	SceneManager::GetNowPlayScene()->SceneUpdate(stepTime);
	return true;
}
bool System::SystemDraw(void)
{
	//TODO: シーン描画


	//test:
	//MV1SetPosition(handle, VGet(300.0f, 0.0f, 400.0f - x));
	//MV1SetRotationXYZ(handle, VGet(-x / 10.0f, 0, 0));
	//DrawPixel(420, 100 + x, GetColor(255, 255, 255));

	//MV1SetPosition(handle, VGet(300.0f, 0.0f, 350.0f));
	//MV1SetRotationXYZ(handle, VGet(-x / 10.0f, 0, 0));
	//MV1DrawModel(handle);
	//MV1SetPosition(handle, VGet(300.0f, 0.0f, 400.0f ));
	//MV1SetRotationXYZ(handle, VGet(0, 0, 0));
	//MV1DrawModel(handle);

	SceneManager::GetNowPlayScene()->SceneDraw();
	//Ｚバッファは使用しない設定にする
	SetUseZBufferFlag(FALSE);

	//フェード処理の描画を行う
	SystemFadeDraw();

	//フレームレートを画面右下に描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawFormatString(GAME_SCREEN_WIDTH - 84, GAME_SCREEN_HEIGHT - 20,
		GetColor(255, 255, 255), "FPS:%d", (int)systemInfo.dispFrameCount);

	//TODO: デバッグ関係の描画処理を行う
	//System_DebugDraw();
#ifdef _DEBUG
	//ClsDrawScreen();
	//dynamicsWorld->debugDrawWorld();
#endif  
	return false;
}

#pragma region Fade関連


// フェード処理の状態推移処理
void System::SystemFadeUpdate(float stepTime)
{
	// フェード処理を行っているかどうかのフラグが倒れている場合は何もせず終了
	if (!systemInfo.fade)
	{
		return;
	}

	// フェードアウト率の変更
	if (ParamChangeFloat(&systemInfo.fadeOutRate,
		systemInfo.fadeOut ? 1.0f : 0.0f, stepTime, FADE_SPEED))
	{
		// 値の変更が完了したらフェードアウトを行っているかどうかのフラグを倒す
		systemInfo.fade = false;
	}
}

// フェード処理の描画
void System::SystemFadeDraw(void)
{
	int Alpha;

	// フェードアウト率から不透明度を計算
	Alpha = (int)(systemInfo.fadeOutRate * 255.0f);

	// 不透明度が０以上なら描画
	if (Alpha > 0)
	{
		// 画面全体にフェードアウト用の黒い四角を描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
		DrawBox(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
	}
}

// 画面をフェードアウトさせる
void System::System_FadeOut(void)
{
	systemInfo.fadeOut = true;
	systemInfo.fade = true;
}

// 画面をフェードインする
void System::System_FadeIn(void)
{
	systemInfo.fadeOut = false;
	systemInfo.fade = true;
}

// ゲーム終了
void System::System_Exit()
{
	this->systemInfo.exitGame = true;
}

// 画面のフェード処理中かどうかを取得する
//     戻り値 : フェード処理中かどうか
//              ( true : フェード処理中   false : フェード処理は行われていない )
bool System::System_CheckFade(void)
{
	return systemInfo.fade;
}
#pragma endregion
System::~System()
{
	int i;

	//// サウンド処理の後始末
	//Sound_Terminate();

	//// キャラクターの処理の後始末
	//Chara_Terminate();

	//// エフェクトの処理の後始末
	//Effect_Terminate();

	//// ゲームメイン描画処理の後始末
	//GameMainRender_Terminate();

	// フォントハンドルの削除
	//for (i = 0; i < EFontHandle_Num; i++)
	//{
	//	DeleteFontToHandle(systemInfo.fontHandle[i]);
	//	systemInfo.fontHandle[i] = -1;
	//}

	// 共有効果音の削除
	for (i = 0; i < ECommonSE_Num; i++)
	{
		DeleteSoundMem(systemInfo.commonSEHandle[i]);
		systemInfo.commonSEHandle[i] = -1;
	}
	//if (system != NULL)
	//{
	//	delete system;
	//}

	// ＤＸライブラリの終了処理
	DxLib_End();
}
