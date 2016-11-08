#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include "DxLib.h"
#include "Mathematics.h"
#include "SceneGameMain.h"
#include "SceneManager.h"
#include "InputSystem.h"
#include "btBulletDynamicsCommon.h"
#include "DxDebugDraw.h"

#pragma region Define

#define NULL 0

#define MAXPATH 260
// ゲーム画面の幅
#define GAME_SCREEN_WIDTH			(1280)

// ゲーム画面の高さ
#define GAME_SCREEN_HEIGHT			(720)

// 小フォントのサイズ
#define FONTHANDLE_SMALL_SIZE		(24)

// 中フォントのサイズ
#define FONTHANDLE_MIDIUM_SIZE		(32)

// 大フォントのサイズ
#define FONTHANDLE_BIG_SIZE			(80)

// フェードアウト、フェードインの速度
#define FADE_SPEED			(1.0f)

// １フレームの最大時間
#define MAX_DELTA_TIME		(1.0f / 120.0f)

// 一度に処理する最大フレーム数
#define MAX_FRAME_NUM		(8)

// 編集できる整数パラメータの最大数
#define DEBUG_INT_MAXNUM	(20)
#pragma endregion
#pragma region enum
//フォント
typedef enum _EFontHandle
{
	EFontHandle_Small,		// 小フォントハンドル
	EFontHandle_Midium,		// 中フォントハンドル
	EFontHandle_Big,		// 大フォントハンドル

	EFontHandle_Num			// フォントハンドルの数
} EFontHandle;

//共有効果音
typedef enum _ECommonSE
{
	ECommonSE_Alert,		// 警告
	ECommonSE_Cancel,		// キャンセル
	ECommonSE_Counter,		// カウント
	ECommonSE_Cursor,		// カーソル
	ECommonSE_Enter,		// 決定

	ECommonSE_Num			// 共有効果音の数
} ECommonSE;
#pragma endregion
#pragma region Struct

// 整数パラメータ情報
typedef struct _SParamInt
{
	// 整数パラメータ
	int         param;

	// パラメータ名
	const char *name;
} SParamInt;

// システムの情報
typedef struct _SSystemInfo
{
	// 一つ前のフレームの時間
	LONGLONG        prevTime;

	// 状態推移処理で推移させる時間
	float           stepTime;

	// １フレームで状態推移処理を行う回数
	int             stepNum;

	// ソフトを終了するかどうかのフラグ
	bool            exitGame;

	// プレイヤーキャラのキャラ情報構造体のアドレスを格納するポインタ変数
	//PlayerInfo *    playerInfo;

	// ゲーム開始時のステージ
	int            startStage;

	// 動的編集をする整数パラメータの数
	int            debugParamIntNum;

	// 動的編集をする整数パラメータ配列の先頭アドレスを格納するポインタ変数
	SParamInt *     debugParamInt;

	// デバッグ情報を表示するかどうかのフラグ
	bool            dispDebugInfo;

	// タスクシステム情報
	//STaskSystemInfo taskSystemInfo;

	// ソフト全体で使用するフォントハンドル
	int             fontHandle[EFontHandle_Num];

	// 共有効果音のハンドル
	int				commonSEHandle[ECommonSE_Num];

	// フェード処理を行っているかどうかのフラグ
	bool            fade;

	// フェードアウト状態かどうかのフラグ
	bool            fadeOut;

	// フェードアウト率
	float           fadeOutRate;

	// 前回フレームレート表示用にフレームカウントをリセットした時間
	LONGLONG        backDispFrameTime;

	// フレームレート表示用のフレームカウンタ
	int             frameCounter;

	// フレームレート表示で表示するフレームレート
	int             dispFrameCount;

	// ゲームメインタスクのタスク情報構造体のアドレスを格納するポインタ変数
	//STaskInfo *     gameMainTaskInfo;

	// 低処理負荷モードかどうかのフラグ
	bool			lowSpecMode;
} SSystemInfo;

#pragma endregion
#pragma region Global
//共有効果音のファイル名
static const char *CommonSEFileName[ECommonSE_Num] =
{
	"system_alert.wav",
	"system_cancel.wav",
	"system_counter.wav",
	"system_cursor.wav",
	"system_enter.wav",
};
#pragma endregion

class System
{
public:
	static System *GetSystemInstance();
	btDiscreteDynamicsWorld* dynamicsWorld;
	bool SystemMain(void);
	bool System_CheckFade(void);
	void System_FadeOut(void);
	void System_FadeIn(void);

	// ゲーム終了
	void System_Exit();
	~System();
private:

	static System *_instance;
	// システムの情報
	static SSystemInfo systemInfo;
	System();

	// プロキシの最大数
	int maxProxies;

	// ワールドの広さ
	btVector3 worldAabbMin;
	btVector3 worldAabbMax;
	DxDebugDraw g_debugdraw;

	bool SystemInit(void);
	bool SystemLoop(void);
	bool SystemUpdate(float stepTime);
	bool SystemDraw(void);
	void SystemFadeUpdate(float stepTime);
	void SystemFadeDraw(void);

};

#endif
