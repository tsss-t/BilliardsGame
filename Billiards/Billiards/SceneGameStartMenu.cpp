#include "SceneGameStartMenu.h"
#include "System.h"

SceneGameStartMenu *SceneGameStartMenu::_instance = NULL;
SceneGameStartMenu::_EGameStartMenuNext SceneGameStartMenu::nextScene = GameMain;
SceneGameStartMenu::SceneGameStartMenu()
{
	sceneNowState = EStartSceneMenuState::FadeInWait;

	//背景図の設定
	spriteBG = new UISprite("Data/Sprite/Background.jpg");
	spriteBG->SetPosition(0, 0);
	spriteBG->SetScale(0.7f, 0.7f);

	//左上ゲームタイトル画像の設定
	spriteTitle = new UISprite("Data/Sprite/Title.png");
	spriteTitle->SetPosition(70, 50);
	spriteTitle->SetScale(2.0f, 2.0f);

	//右下Logo画像の設定
	spriteLogo = new UISprite("Data/Sprite/logo.png");
	spriteLogo->SetPosition(1100, 620);
	spriteLogo->SetScale(1.f, 1.f);

	//ボタンの切り替え用画像の導入
	buttonSpriteHandle = LoadGraph("Data/Sprite/button2.png");
	buttonSpriteHighLightHanel = LoadGraph("Data/Sprite/button1.png");

	//StartGame　ボタンの設定
	spStartGame = new  UISprite(buttonSpriteHandle);
	lbStartGame = new  UILabel();
	lbStartGame->SetString("New Game");
	lbStartGame->SetOffset(75, 22);
	btStartGame = new UIButton(lbStartGame, spStartGame);
	btStartGame->SetScale({ 2.0f,1.5f });
	btStartGame->SetPosition(200, 400);
	btStartGame->SetHoverSpriteHandle(buttonSpriteHighLightHanel);
	btStartGame->SetClickEvent(GameStart);

	//SettingGame ボタンの設定
	spSettingGame = new  UISprite(buttonSpriteHandle);
	lbSettingGame = new  UILabel();
	lbSettingGame->SetString("Setting");
	lbSettingGame->SetOffset(75, 22);
	btSettingGame = new UIButton(lbSettingGame, spSettingGame);
	btSettingGame->SetScale({ 2.0f,1.5f });
	btSettingGame->SetPosition(200, 480);
	btSettingGame->SetHoverSpriteHandle(buttonSpriteHighLightHanel);

	//ExitGame ボタンの設定
	spExitGame = new  UISprite(buttonSpriteHandle);
	lbExitGame = new  UILabel();
	lbExitGame->SetString("Exit Game");
	lbExitGame->SetOffset(75, 22);
	btExitGame = new UIButton(lbExitGame, spExitGame);
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
			SoundSystem::GetSoundSystemInstance()->PlayBGM(EBGM::EBGM_Title);
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
		btStartGame->SetEventEnable(true);
		btSettingGame->SetEventEnable(true);
		btExitGame->SetEventEnable(true);
		break;
	}
	case EStartSceneMenuState::FadeOut:
	{
		btStartGame->SetEventEnable(false);
		btSettingGame->SetEventEnable(false);
		btExitGame->SetEventEnable(false);
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
		SoundSystem::GetSoundSystemInstance()->StopBGM();
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



