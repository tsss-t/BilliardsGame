#pragma once
#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "DxLib.h"

#pragma region define
// ３Ｄサウンドのデフォルトの音が聞こえる範囲
#define DEFAULT_RADIUS			(5000.0f)

// サウンドのデフォルト同時再生可能数
#define DEFAULT_BUFFER_NUM		(6)

// ファイルパスの最大長
#define MAX_PATH_LENGTH			(64)

// １サウンド辺りの最大バリエーション数
#define MAX_HANDLE_NUM			(8)

// 登録できるサウンドの最大数
#define MAX_SOUNDINFO_NUM		(1024)

// サウンドファイルが存在するフォルダパス
#define FILE_DIRECTORY_PATH		"Data/Sound/"

// サウンドファイルの拡張子
#define FILE_EXENAME			"wav"
#pragma endregion




// 素材タイプ
typedef enum _EMaterialType
{
	EMaterialType_Ball,	// ボール
	EMaterialType_Table,	// テーブル

	EMaterialType_Num		// 素材タイプの数
} EMaterialType;

// BGM
typedef enum _EBGM
{
	EBGM_Title,				// タイトル
	EBGM_GameMain,			// ゲーム

	EBGM_Num				// BGMの数
} EBGM;

// サウンドの情報
typedef struct _SSoundInfo
{
	// ３Ｄサウンドかどうか( true:3Dサウンド  false:2Dサウンド )
	bool                 Is3DSound;

	// ファイルパス
	char                 FilePath[MAX_PATH_LENGTH];

	// サウンドハンドルの数
	int                  HandleNum;

	// サウンドハンドル
	int                  Handle[MAX_HANDLE_NUM];
} SSoundInfo;

// ＢＧＭの情報
typedef struct _SBgmInfo
{
	// サウンドハンドル
	int                  soundHandle;

	// ＢＧＭのループ時に戻る位置
	int                  loopStartPosition;

	// ＢＧＭのループをする位置
	int                  loopEndPosition;
} SBgmInfo;

// サウンドシステムの情報
typedef struct _SSoundSystemData
{
	// サウンドの数
	int                  soundNum;

	// サウンドの情報
	SSoundInfo           sound[MAX_SOUNDINFO_NUM];

	// ＢＧＭの情報
	SBgmInfo             bgm[EBGM_Num];

	// 現在鳴らしているＢＧＭ
	EBGM                 nowPlayBgm;
} SSoundSystemData;

class SoundSystem
{
public:

	~SoundSystem();

	static SoundSystem *GetSoundSystemInstance();

	int AddSound(const char * filePath, bool is3DSound);

	void PlaySound(int soundIndex, int playType);

	void PlaySound3D(VECTOR Position, int soundIndex, int playType);

	void PlayBGM(EBGM BGM);

	void StopBGM();
private:

	static SoundSystem * _instance;

	bool SoundSystemInit();

	SoundSystem();
};





#endif // !SOUNDMANAGER_H