#include "InputSystem.h"


InputSystem *InputSystem::GetInputSystemInstance()
{
	if (_instance == NULL)
	{
		_instance = new InputSystem();
	}
	return _instance;
}

InputSystem::InputSystem()
{
	mousePosition = { 0,0 };
	SetDefaultSetting();
}

// ゲームでの入力とキーやパッドなどの入力との対応情報をデフォルト設定にする
void InputSystem::SetDefaultSetting()
{
	int i;
	// デフォルト設定の情報をコピーする
	for (i = 0; i < EInputType_Num; i++)
	{
		inputSystemData.inputTypeInfo[i] = defaultInputTypeInfo[i];
	}

}


InputSystem::~InputSystem()
{
}

//最新入力状態を更新する
bool InputSystem::InputSystemUpdate(float stepTime)
{
	int x, y;

	DINPUT_JOYSTATE * DIJState;
	int	inputState[EInputType_Num];

	SInputTypeInfo * inputTypeInfo;

	// パッドの数を取得する
	int padNum = GetJoypadNum();

	// パッドの数がプログラムが対応している数より多い場合は、対応している数に制限する
	if (padNum > MAX_GAMEPAD_NUM)
	{
		padNum = MAX_GAMEPAD_NUM;
	}

	// パッドの入力情報を DirectInput から取得する
	for (int i = 0; i < padNum; i++)
	{
		GetJoypadDirectInputState(padIDTable[i], &inputSystemData.directInputState[i]);
	}

	// 現在のキーの入力状態を取得する
	GetHitKeyStateAll(inputSystemData.keyInput);


	//マウスの入力状態取得
	inputSystemData.mouseInputButton = GetMouseInput();

	//ホイールの回転量取得
	inputSystemData.mouseInputWheel = GetMouseWheelRotVol();  

	//マウス現在の座標取得
	GetMousePoint(&x, &y);

	//マウス現在の位置と前フレームに比べ　移動の量を算出
	inputSystemData.mouseMoveDirection = { x - mousePosition.u,y - mousePosition.v };
	mousePosition = {(float)x,(float)y};

	// ゲームで使用する入力情報を構築する
	inputTypeInfo = inputSystemData.inputTypeInfo;

	for (int i = 0; i < EInputType_Num; i++, inputTypeInfo++)
	{
		// 『入力なし』状態にしておく
		inputState[i] = 0;

		// 対応しているキーボードのキーが押されていたら『入力あり』にする
		if (inputSystemData.keyInput[inputTypeInfo->keyInput] != 0)
		{
			inputState[i] = DIRECTINPUT_MAX_VALUE;
		}




		//これからキーボードを対応するパッドの入力種類によって処理を分岐する
		DIJState = &inputSystemData.directInputState[inputTypeInfo->padNo];

		switch (inputTypeInfo->directInputType)
		{
		case EDInputType_X:	// スティックのＸ軸の場合
			ProcessInput_Assist(&inputState[i], inputTypeInfo->subInfo[0], DIJState->X);
			break;

		case EDInputType_Y:	// スティックのＹ軸の場合
			ProcessInput_Assist(&inputState[i], inputTypeInfo->subInfo[0], DIJState->Y);
			break;

		case EDInputType_Z:	// スティックのＺ軸の場合
			ProcessInput_Assist(&inputState[i], inputTypeInfo->subInfo[0], DIJState->Z);
			break;

		case EDInputType_Rx:	// スティックのＸ軸回転の場合
			ProcessInput_Assist(&inputState[i], inputTypeInfo->subInfo[0], DIJState->Rx);
			break;

		case EDInputType_Ry:	// スティックのＹ軸回転の場合
			ProcessInput_Assist(&inputState[i], inputTypeInfo->subInfo[0], DIJState->Ry);
			break;

		case EDInputType_Rz:	// スティックのＺ軸回転の場合
			ProcessInput_Assist(&inputState[i], inputTypeInfo->subInfo[0], DIJState->Rz);
			break;

		case EDInputType_POV:	// 方向コントローラの場合
								// 設定されている方向に入力されていたら『入力あり』にする
			if (DIJState->POV[inputTypeInfo->subInfo[0]] == inputTypeInfo->subInfo[1])
			{
				inputState[i] = DIRECTINPUT_MAX_VALUE;
			}
			break;

		case EDInputType_Button:	// ボタンの場合
									// 設定されているボタンが押されていたら『入力あり』にする
			if (DIJState->Buttons[inputTypeInfo->subInfo[0]] == 128)
			{
				inputState[i] = DIRECTINPUT_MAX_VALUE;
			}
			break;
		}
		// １フレーム前の入力状態をとっておく
		int ButtonPrevInput = inputSystemData.buttonInput;

		// 入力状態の初期化
		inputSystemData.buttonInput = 0;

		// 各入力に対応するビットを『入力あり』の場合は立てる
		for (i = 0; i < EInputType_Num; i++)
		{
			if (inputState[i] > 0)
			{
				inputSystemData.buttonInput |= 1 << i;
			}
		}

		// 今回のフレームで『入力あり』になり始めたビットを算出する
		inputSystemData.buttonEdgeInput = inputSystemData.buttonInput & ~ButtonPrevInput;

		// カメラ操作用のスティック入力状態を算出する
		int total = inputState[EInputType_Camera_Right] - inputState[EInputType_Camera_Left];
		inputSystemData.cameraStickInput.x = total / (float)DIRECTINPUT_MAX_VALUE;

		total = inputState[EInputType_Camera_Down] - inputState[EInputType_Camera_Up];
		inputSystemData.cameraStickInput.y = total / (float)DIRECTINPUT_MAX_VALUE;

		inputSystemData.cameraStickInput.z = 0.0f;
	}

	return true;
}

// ProcessInput 用の軸入力タイプの処理を行う補助関数
// 処理結果を代入する変数のアドレス
// 軸入力タイプのサブ情報
//    (  1:InputValue がプラスの値の場合に入力ありとする
//      -1:InputValue がマイナスの値の場合に入力ありとする )
// 軸入力の値
void InputSystem::ProcessInput_Assist(int *inputState, int subInfo, int inputValue)
{
	// サブ情報が 1 か -1 かで処理を分岐
	switch (subInfo)
	{
	case 1:		// 1の場合は InputValue がプラスの場合のみ入力ありとする
		if (inputValue > 0)
		{
			*inputState = inputValue;
		}
		break;

	case -1:	// -1の場合は InputValue がプラスの場合のみ入力ありとする
		if (inputValue < 0)
		{
			*inputState = -inputValue;
		}
		break;
	}
}

// ボタンの入力状態を取得する
//     戻り値 : ボタンの入力状態
int InputSystem::GetInput(void)
{
	return inputSystemData.buttonInput;
}

// ボタンの押された瞬間のみの入力状態を取得する
//     戻り値 : ボタンの押された瞬間のみの入力状態
int InputSystem::GetEdgeInput(void)
{
	return inputSystemData.buttonEdgeInput;
}

//　マウスのホイール入力状態を取得する
int InputSystem::GetMouseInputWheel()
{
	return inputSystemData.mouseInputWheel;
}

//　マウスのボタン入力状態を取得する
int InputSystem::GetMouseInputButton()
{
	return inputSystemData.mouseInputButton;
}

//  マウスの現在座標を取得する
//     戻り値 :u=x v=y
FLOAT2 InputSystem::GetMouseNowPosition()
{
	return mousePosition;
}

//  マウスの移動量を取得する
FLOAT2 InputSystem::GetMouseMoveDirection()
{
	return inputSystemData.mouseMoveDirection;
}


#pragma region static 初期化


InputSystem *InputSystem::_instance = NULL;

SInputSystemData InputSystem::inputSystemData;

// ゲームでの各入力とキーやパッドなどの入力とのデフォルトの対応設定
SInputTypeInfo InputSystem::defaultInputTypeInfo[EInputType_Num] =
{
	0, EDInputType_X,      -1, 0, KEY_INPUT_A,		// EInputType_Left
	0, EDInputType_X,       1, 0, KEY_INPUT_D,		// EInputType_Right
	0, EDInputType_Y,      -1, 0, KEY_INPUT_W,			// EInputType_Up 
	0, EDInputType_Y,       1, 0, KEY_INPUT_S,		// EInputType_Down 
	0, EDInputType_Rx,     -1, 0, KEY_INPUT_LEFT,			// EInputType_Camera_Left
	0, EDInputType_Rx,      1, 0, KEY_INPUT_RIGHT,			// EInputType_Camera_Right
	0, EDInputType_Ry,     -1, 0, KEY_INPUT_UP,			// EInputType_Camera_Up
	0, EDInputType_Ry,      1, 0, KEY_INPUT_DOWN,			// EInputType_Camera_Down
	0, EDInputType_Button,  0, 0, KEY_INPUT_E,			// EInputType_Submit
	0, EDInputType_Button,  1, 0, KEY_INPUT_Q,			// EInputType_Cancel
	0, EDInputType_Button,  3, 0, KEY_INPUT_SPACE,		// EInputType_Pause
};

// パッドの識別子テーブル
int InputSystem::padIDTable[MAX_GAMEPAD_NUM] =
{
	DX_INPUT_PAD1,
	DX_INPUT_PAD2
};

// キーコードの情報(キーボード
SKeyInfo InputSystem::keyInfoTable[] =
{
	KEY_INPUT_BACK,			"BACK",			// バックスペースキー
	KEY_INPUT_TAB,			"TAB",			// タブキー
	KEY_INPUT_RETURN,		"ENTER",		// エンターキー

	KEY_INPUT_LSHIFT,		"L SHIFT",		// 左シフトキー
	KEY_INPUT_RSHIFT,		"R SHIFT",		// 右シフトキー
	KEY_INPUT_LCONTROL,		"L CONTROL",	// 左コントロールキー
	KEY_INPUT_RCONTROL,		"R CONTROL",	// 右コントロールキー
	KEY_INPUT_ESCAPE,		"ESCAPE",		// エスケープキー
	KEY_INPUT_SPACE,		"SPACE",		// スペースキー
	KEY_INPUT_PGUP,			"PAGE UP",		// ＰａｇｅＵＰキー
	KEY_INPUT_PGDN,			"PAGE DOWN",	// ＰａｇｅＤｏｗｎキー
	KEY_INPUT_END,			"END",			// エンドキー
	KEY_INPUT_HOME,			"HOME",			// ホームキー
	KEY_INPUT_LEFT,			"LEFT",			// 左キー
	KEY_INPUT_UP,			"UP",			// 上キー
	KEY_INPUT_RIGHT,		"RIGHT",		// 右キー
	KEY_INPUT_DOWN,			"DOWN",			// 下キー
	KEY_INPUT_INSERT,		"INSERT",		// インサートキー
	KEY_INPUT_DELETE,		"DELETE",		// デリートキー

	KEY_INPUT_MINUS,		"-",			// －キー
	KEY_INPUT_YEN,			"\\",			// ￥キー
	KEY_INPUT_PREVTRACK,	"^",			// ＾キー
	KEY_INPUT_PERIOD,		".",			// ．キー
	KEY_INPUT_SLASH,		"/",			// ／キー
	KEY_INPUT_LALT,			"L ALT",		// 左ＡＬＴキー
	KEY_INPUT_RALT,			"R ALT",		// 右ＡＬＴキー
	KEY_INPUT_SCROLL,		"SCROLL LOCK",	// ScrollLockキー
	KEY_INPUT_SEMICOLON,	";",			// ；キー
	KEY_INPUT_COLON,		":",			// ：キー
	KEY_INPUT_LBRACKET,		"[",			// ［キー
	KEY_INPUT_RBRACKET,		"]",			// ］キー
	KEY_INPUT_AT,			"@",			// ＠キー
	KEY_INPUT_BACKSLASH,	"BACK SLASH",	// ＼キー
	KEY_INPUT_COMMA,		",",			// ，キー
	KEY_INPUT_KANJI,		"KANJI",		// 漢字キー
	KEY_INPUT_CONVERT,		"CONVERT",		// 変換キー
	KEY_INPUT_NOCONVERT,	"NO CONVERT",	// 無変換キー
	KEY_INPUT_KANA,			"KANA",			// カナキー
	KEY_INPUT_APPS,			"APPS",			// アプリケーションメニューキー
	KEY_INPUT_CAPSLOCK,		"CAPS LOCK",	// CaspLockキー
	KEY_INPUT_SYSRQ,		"PRINT SCREEN",	// PrintScreenキー
	KEY_INPUT_PAUSE,		"PAUSE BREAK",	// PauseBreakキー
	KEY_INPUT_LWIN,			"L WIN",		// 左Ｗｉｎキー
	KEY_INPUT_RWIN,			"R WIN",		// 右Ｗｉｎキー

	KEY_INPUT_NUMLOCK,		"NUM LOCK",		// テンキー０
	KEY_INPUT_NUMPAD0,		"NUMPAD 0",		// テンキー０
	KEY_INPUT_NUMPAD1,		"NUMPAD 1",		// テンキー１
	KEY_INPUT_NUMPAD2,		"NUMPAD 2",		// テンキー２
	KEY_INPUT_NUMPAD3,		"NUMPAD 3",		// テンキー３
	KEY_INPUT_NUMPAD4,		"NUMPAD 4",		// テンキー４
	KEY_INPUT_NUMPAD5,		"NUMPAD 5",		// テンキー５
	KEY_INPUT_NUMPAD6,		"NUMPAD 6",		// テンキー６
	KEY_INPUT_NUMPAD7,		"NUMPAD 7",		// テンキー７
	KEY_INPUT_NUMPAD8,		"NUMPAD 8",		// テンキー８
	KEY_INPUT_NUMPAD9,		"NUMPAD 9",		// テンキー９
	KEY_INPUT_MULTIPLY,		"NUMPAD *",		// テンキー＊キー
	KEY_INPUT_ADD,			"NUMPAD +",		// テンキー＋キー
	KEY_INPUT_SUBTRACT,		"NUMPAD -",		// テンキー－キー
	KEY_INPUT_DECIMAL,		"NUMPAD .",		// テンキー．キー
	KEY_INPUT_DIVIDE,		"NUMPAD /",		// テンキー／キー
	KEY_INPUT_NUMPADENTER,	"NUMPAD ENTER",	// テンキーのエンターキー

	KEY_INPUT_F1,			"F1",			// Ｆ１キー
	KEY_INPUT_F2,			"F2",			// Ｆ２キー
	KEY_INPUT_F3,			"F3",			// Ｆ３キー
	KEY_INPUT_F4,			"F4",			// Ｆ４キー
	KEY_INPUT_F5,			"F5",			// Ｆ５キー
	KEY_INPUT_F6,			"F6",			// Ｆ６キー
	KEY_INPUT_F7,			"F7",			// Ｆ７キー
	KEY_INPUT_F8,			"F8",			// Ｆ８キー
	KEY_INPUT_F9,			"F9",			// Ｆ９キー
	KEY_INPUT_F10,			"F10",			// Ｆ１０キー
	KEY_INPUT_F11,			"F11",			// Ｆ１１キー
	KEY_INPUT_F12,			"F12",			// Ｆ１２キー

	KEY_INPUT_A,			"A",			// Ａキー
	KEY_INPUT_B,			"B",			// Ｂキー
	KEY_INPUT_C,			"C",			// Ｃキー
	KEY_INPUT_D,			"D",			// Ｄキー
	KEY_INPUT_E,			"E",			// Ｅキー
	KEY_INPUT_F,			"F",			// Ｆキー
	KEY_INPUT_G,			"G",			// Ｇキー
	KEY_INPUT_H,			"H",			// Ｈキー
	KEY_INPUT_I,			"I",			// Ｉキー
	KEY_INPUT_J,			"J",			// Ｊキー
	KEY_INPUT_K,			"K",			// Ｋキー
	KEY_INPUT_L,			"L",			// Ｌキー
	KEY_INPUT_M,			"M",			// Ｍキー
	KEY_INPUT_N,			"N",			// Ｎキー
	KEY_INPUT_O,			"O",			// Ｏキー
	KEY_INPUT_P,			"P",			// Ｐキー
	KEY_INPUT_Q,			"Q",			// Ｑキー
	KEY_INPUT_R,			"R",			// Ｒキー
	KEY_INPUT_S,			"S",			// Ｓキー
	KEY_INPUT_T,			"T",			// Ｔキー
	KEY_INPUT_U,			"U",			// Ｕキー
	KEY_INPUT_V,			"V",			// Ｖキー
	KEY_INPUT_W,			"W",			// Ｗキー
	KEY_INPUT_X,			"X",			// Ｘキー
	KEY_INPUT_Y,			"Y",			// Ｙキー
	KEY_INPUT_Z,			"Z",			// Ｚキー

	KEY_INPUT_0, 			"0",			// ０キー
	KEY_INPUT_1,			"1",			// １キー
	KEY_INPUT_2,			"2",			// ２キー
	KEY_INPUT_3,			"3",			// ３キー
	KEY_INPUT_4,			"4",			// ４キー
	KEY_INPUT_5,			"5",			// ５キー
	KEY_INPUT_6,			"6",			// ６キー
	KEY_INPUT_7,			"7",			// ７キー
	KEY_INPUT_8,			"8",			// ８キー
	KEY_INPUT_9,			"9",			// ９キー

	-1,						NULL,
};

#pragma endregion

