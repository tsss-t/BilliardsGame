#pragma once
#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "DxLib.h"

#pragma region define
// チェックするゲームパッドの数
#define MAX_GAMEPAD_NUM				(2)

// キーボードの入力状態を取得するためのバッファのサイズ
#define KEY_STATE_BUFFER_SIZE		(256)

// DirectInput から得られる値の最大値
#define DIRECTINPUT_MAX_VALUE		(1000)
#pragma endregion

#pragma region enum
// 入力情報
typedef enum _EInputType
{
	EInputType_Left,				// 方向入力左
	EInputType_Right,				// 方向入力右
	EInputType_Up,					// 方向入力上
	EInputType_Down,				// 方向入力下

	EInputType_Camera_Left,			// カメラ用方向入力左
	EInputType_Camera_Right,		// カメラ用方向入力右
	EInputType_Camera_Up,			// カメラ用方向入力上
	EInputType_Camera_Down,			// カメラ用方向入力下

	EInputType_Submit,				// 確認ボタン
	EInputType_Cancel,				// キャンセルボタン
	EInputType_Pause,				// ポーズボタン

	EInputType_Num,					// 入力タイプの数

	EInputType_MouseLeft,
	EInputType_MouseRight,
	EInputType_MouseWheel
} EInputType;

// DirectInput の入力情報タイプ
typedef enum _EDInputType
{
	EDInputType_X,					// スティックのＸ軸
	EDInputType_Y,					// スティックのＹ軸
	EDInputType_Z,					// スティックのＺ軸
	EDInputType_Rx,					// スティックのＸ軸回転
	EDInputType_Ry,					// スティックのＹ軸回転
	EDInputType_Rz,					// スティックのＺ軸回転
	EDInputType_POV,				// 方向コントローラ
	EDInputType_Button,				// ボタン
} EDInputType;
#pragma endregion

#pragma region struct
// キーボードの１キー辺りの情報
typedef struct _SKeyInfo
{
	// 入力コード( KEY_INPUT_LEFT など )
	int              keyInput;

	// キーの名前
	const char *     name;
} SKeyInfo;

// ゲームでの入力とキーやパッドなどの入力との対応情報
typedef struct _SInputTypeInfo
{
	// パッド番号
	int              padNo;

	// DirectInput の入力情報タイプ
	EDInputType      directInputType;

	// サブ情報( DirectInputType によって意味が変わる )
	int              subInfo[2];

	// 対応するキーボードのキー( KEY_INPUT_UP など )
	int              keyInput;
} SInputTypeInfo;

// ゲーム用の入力情報統括
typedef struct _SInputSystemData
{
	// ゲーム中の入力とキーやパッドなどの入力との対応情報
	SInputTypeInfo   inputTypeInfo[EInputType_Num];

	// DirectInput のパッドの入力状態
	DINPUT_JOYSTATE  directInputState[MAX_GAMEPAD_NUM];

	// キーの入力状態
	char             keyInput[KEY_STATE_BUFFER_SIZE];

	// ボタンの入力状態
	int              buttonInput;

	// ボタンの押された瞬間のみの入力状態
	int              buttonEdgeInput;

	// カメラ操作用のスティック入力状態
	VECTOR           cameraStickInput;

	// マウスのボタンの入力状態
	int				 mouseInputButton;

	// マウスのホイールの入力状態
	int				 mouseInputWheel;

	// マウスの移動状態（前のフレームからの
	FLOAT2           mouseMoveDirection;
} SInputSystemData;
#pragma endregion

class InputSystem
{

public:

	static InputSystem * GetInputSystemInstance();

	//最新入力状態を更新する
	bool InputSystemUpdate(float stepTime);

	// ボタンの入力状態を取得する
	//     戻り値 : ボタンの入力状態
	int GetInput(void);

	// ボタンの押された瞬間のみの入力状態を取得する
	//     戻り値 : ボタンの押された瞬間のみの入力状態
	int GetEdgeInput(void);

	//　マウスのホイール入力状態を取得する
	//     戻り値 : ホイールの入力状態　プラスの場合は+方向　マイナスの場合は-方向
	int GetMouseInputWheel();

	//　マウスのボタン入力状態を取得する
	//     戻り値 : Mouse & MOUSE_INPUT_RIGHT　＝＝true の場合は右ボタンを押した状態
	//     戻り値 : Mouse & MOUSE_INPUT_LEFT　＝＝true の場合は左ボタンを押した状態
	int GetMouseInputButton();

	//  マウスの現在座標を取得する
	//     戻り値 :u=x v=y
	FLOAT2 GetMouseNowPosition();

	//  マウスの移動量を取得する
	//     戻り値 :u=x v=y
	FLOAT2 GetMouseMoveDirection();

	void SetDefaultSetting();

	~InputSystem();
private:

	FLOAT2 mousePosition;

	static InputSystem * _instance;

	static SInputTypeInfo defaultInputTypeInfo[EInputType_Num];
	static int padIDTable[MAX_GAMEPAD_NUM];
	static SKeyInfo keyInfoTable[];

	// 入力処理用の情報
	static SInputSystemData inputSystemData;

	// ProcessInput 用の軸入力タイプの処理を行う補助関数
	void ProcessInput_Assist(int * InputState, int SubInfo, int InputValue);

	InputSystem();

};

#endif // !INPUTSYSTEM_H
