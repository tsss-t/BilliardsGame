#include "SceneGameStartMenu.h"
#include "System.h"

SceneGameStartMenu *SceneGameStartMenu::_instance = NULL;
SceneGameStartMenu::_EGameStartMenuNext SceneGameStartMenu::nextScene = GameMain;
SceneGameStartMenu::SceneGameStartMenu()
{
	sceneNowState = EStartSceneMenuState::FadeInWait;

	//背景図の設定
	spriteBG = new Sprite("Data/Sprite/Background.jpg");
	spriteBG->SetPosition(0, 0);
	spriteBG->SetScale(0.7f, 0.7f);

	//左上ゲームタイトル画像の設定
	spriteTitle = new Sprite("Data/Sprite/Title.png");
	spriteTitle->SetPosition(70, 50);
	spriteTitle->SetScale(2.0f, 2.0f);

	//右下Logo画像の設定
	spriteLogo = new Sprite("Data/Sprite/logokoYellow.png");
	spriteLogo->SetPosition(1060, 620);
	spriteLogo->SetScale(0.5f, 0.5f);

	//ボタンの切り替え用画像の導入
	buttonSpriteHandle = LoadGraph("Data/Sprite/button2.png");
	buttonSpriteHighLightHanel = LoadGraph("Data/Sprite/button1.png");

	//StartGame　ボタンの設定
	spStartGame = new  Sprite(buttonSpriteHandle);
	lbStartGame = new  Label();
	lbStartGame->SetString("New Game");
	lbStartGame->SetOffset(75, 22);
	btStartGame = new Button(lbStartGame, spStartGame);
	btStartGame->SetScale({ 2.0f,1.5f });
	btStartGame->SetPosition(200, 400);
	btStartGame->SetHoverSpriteHandle(buttonSpriteHighLightHanel);
	btStartGame->SetClickEvent(GameStart);

	//SettingGame ボタンの設定
	spSettingGame = new  Sprite(buttonSpriteHandle);
	lbSettingGame = new  Label();
	lbSettingGame->SetString("Setting");
	lbSettingGame->SetOffset(75, 22);
	btSettingGame = new Button(lbSettingGame, spSettingGame);
	btSettingGame->SetScale({ 2.0f,1.5f });
	btSettingGame->SetPosition(200, 480);
	btSettingGame->SetHoverSpriteHandle(buttonSpriteHighLightHanel);

	//ExitGame ボタンの設定
	spExitGame = new  Sprite(buttonSpriteHandle);
	lbExitGame = new  Label();
	lbExitGame->SetString("Exit Game");
	lbExitGame->SetOffset(75, 22);
	btExitGame = new Button(lbExitGame, spExitGame);
	btExitGame->SetScale({ 2.0f,1.5f });
	btExitGame->SetPosition(200, 560);
	btExitGame->SetHoverSpriteHandle(buttonSpriteHighLightHanel);
	btExitGame->SetClickEvent(GameEixt);


	//シーンの中に追加（各オブジェクトのdraw/update関数を実行リストに追加）
	AddToScene(spriteTitle);
	AddToScene(spriteLogo);
	AddToScene(btStartGame);
	AddToScene(btSettingGame);
	AddToScene(btExitGame);
	AddToScene(spriteBG);
}

SceneGameStartMenu * SceneGameStartMenu::GetSceneInstance()
{
	if (_instance == NULL)
	{
		_instance = new SceneGameStartMenu();
	}
	return _instance;
}

bool SceneGameStartMenu::SceneUpdate(float stepTime)
{
	if (!Scene::SceneUpdate(stepTime))
	{
		return false;
	}
	switch (sceneNowState)
	{
	case EStartSceneMenuState::FadeInWait:
	{
		timer += stepTime;
		if (timer > FADE_IN_WAIT_TIME)
		{
			timer = 0;
			sceneNowState = EStartSceneMenuState::FadeIn;
		}
		break;
	}
	case EStartSceneMenuState::FadeIn:
	{
		timer += stepTime;
		if (timer > FADE_IN_TIME)
		{
			sceneNowState = EStartSceneMenuState::MenuSelect;
			timer = 0;
		}
		else
		{
			System::GetSystemInstance()->System_FadeIn();
		}
		break;
	}
	case EStartSceneMenuState::MenuSelect:
	{
		btStartGame->SetEnable(true);
		btSettingGame->SetEnable(true);
		btExitGame->SetEnable(true);
		break;
	}
	case EStartSceneMenuState::FadeOut:
	{
		btStartGame->SetEnable(false);
		btSettingGame->SetEnable(false);
		btExitGame->SetEnable(false);
		timer += stepTime;
		if (timer > FADE_OUT_TIME)
		{
			sceneNowState = EStartSceneMenuState::End;
			timer = 0;
		}
		else
		{
			System::GetSystemInstance()->System_FadeOut();
		}
		break;
	}
	case EStartSceneMenuState::End:
	{

		switch (nextScene)
		{
		case SceneGameStartMenu::GameMain:
		{
			SceneManager::LoadSceneLevel(EGameScene::GameMain);
			break;
		}
		case SceneGameStartMenu::GameSetting:
		{
			break;
		}
		case SceneGameStartMenu::GameExit:
		{
			System::GetSystemInstance()->System_Exit();
		}
			break;
		default:
			break;
		}
	}

	default:
		break;
	}
	return true;
}

bool SceneGameStartMenu::SceneDraw(void)
{
	if (!Scene::SceneDraw())
	{
		return false;
	}
	return true;
}

void SceneGameStartMenu::GameStart()
{
	SceneGameStartMenu::GetSceneInstance()->sceneNowState = EStartSceneMenuState::FadeOut;
	nextScene = GameMain;
}

void SceneGameStartMenu::GameEixt()
{
	SceneGameStartMenu::GetSceneInstance()->sceneNowState = EStartSceneMenuState::FadeOut;
	nextScene = GameExit;
}

SceneGameStartMenu::~SceneGameStartMenu()
{
}



