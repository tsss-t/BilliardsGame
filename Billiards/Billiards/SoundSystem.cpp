#include "SoundSystem.h"
#include "system.h"

SoundSystem * SoundSystem::_instance = NULL;

static SSoundSystemData soundSystemData;

bool SoundSystem::SoundSystemInit()
{
	int             i;
	SBgmInfo       *BGMInfo;
	char			bgmName[256];

	// サウンドの数を初期化
	soundSystemData.soundNum = 0;

	// 作成するサウンドのタイプをファイルストリーミング形式に変更する
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);

	// ＢＧＭの数だけ繰り返し
	BGMInfo = soundSystemData.bgm;

	for (i = 0; i < EBGM_Num; i++, BGMInfo++)
	{
		// ＢＧＭ用のサウンドファイルのパスを取得する
		sprintf(bgmName, FILE_DIRECTORY_PATH "BGM/BGM%d.ogg", i);

		BGMInfo->soundHandle = LoadSoundMem(bgmName);

		// 読み込みに失敗したらエラー
		if (BGMInfo->soundHandle == -1)
		{
			return false;
		}

		// 有効なループ位置が得られた場合はループ位置をサウンドハンドルに設定する
		if (BGMInfo->loopStartPosition >= 0 &&
			BGMInfo->loopEndPosition > 0)
		{
			SetLoopSamplePosSoundMem(BGMInfo->loopStartPosition, BGMInfo->soundHandle);
			SetLoopStartSamplePosSoundMem(BGMInfo->loopEndPosition, BGMInfo->soundHandle);
		}
	}

	// 作成するサウンドのタイプを標準形式に戻す
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);

	// 『現在再生中のBGM』を初期化
	soundSystemData.nowPlayBgm = EBGM_Num;

	// 成功終了
	return true;
}

SoundSystem::SoundSystem()
{
	SoundSystemInit();
}

SoundSystem::~SoundSystem()
{

}

SoundSystem *SoundSystem::GetSoundSystemInstance()
{
	if (_instance == NULL)
	{
		_instance = new SoundSystem();
	}
	return _instance;
}
int SoundSystem::AddSound(const char * filePath, bool is3DSound)
{
	int             i;
	int             Index;
	SSoundInfo     *Info;
	char            FilePath2[MAX_PATH];
	float           Radius;
	int             Volume;

	// 既に登録してあるサウンドの中に、登録しようとしているサウンドが存在するか調べる
	Info = soundSystemData.sound;
	for (Index = 0; Index < soundSystemData.soundNum; Index++, Info++)
	{
		if (Info->Is3DSound == is3DSound && strcmp(Info->FilePath, filePath) == 0)
		{
			// 存在した場合は、既に登録済みのサウンドの登録番号を返す
			return Index;
		}
	}

	// 登録しているサウンドの数が最大数に達していたらエラー
	if (soundSystemData.soundNum == MAX_SOUNDINFO_NUM)
	{
		return -1;
	}

	// ３Ｄサウンドかどうかを保存
	Info->Is3DSound = is3DSound;

	// 作成するサウンドが３Ｄサウンドかどうかを設定する
	SetCreate3DSoundFlag(is3DSound);

	// ３Ｄサウンドの場合は聞こえる距離や音量をテキストファイルから読み取る
	if (Info->Is3DSound)
	{
		Radius = DEFAULT_RADIUS;
		Volume = 255;
	}

	// サウンドファイルを読み込む
	Info->HandleNum = 0;
	for (i = 0; i < MAX_HANDLE_NUM; i++)
	{
		// サウンドファイルパスの作成
		sprintf(FilePath2, "%s%s_%02d.%s",
			FILE_DIRECTORY_PATH, filePath, i, FILE_EXENAME);

		// サウンドファイルが無かったらループを抜ける
		if (FileRead_size(FilePath2) < 0)
		{
			break;
		}

		// サウンドファイルの読み込み
		Info->Handle[i] = LoadSoundMem(FilePath2, DEFAULT_BUFFER_NUM);
		if (Info->Handle[i] == -1)
		{
			return -1;
		}

		// サウンドファイルの場合は聞こえる距離と音量をサウンドハンドルに設定する
		if (Info->Is3DSound)
		{
			Set3DRadiusSoundMem(Radius, Info->Handle[i]);
			ChangeVolumeSoundMem(Volume, Info->Handle[i]);
		}
	}

	// サウンドハンドルの数を保存
	Info->HandleNum = i;

	// 一つも読み込めなかった場合はエラー
	if (Info->HandleNum == 0)
	{
		return -1;
	}

	// ファイルパスを保存
	strcpy(Info->FilePath, filePath);

	// サウンドの数を増やす
	soundSystemData.soundNum++;

	// サウンドの登録番号を返す
	return Index;
}

void SoundSystem::PlaySoundNormal(int soundIndex, int playType)
{
	SSoundInfo *Info;

	// 指定の登録番号が有効かチェック
	if (soundIndex < 0 || soundIndex >= soundSystemData.soundNum)
	{
		return;
	}
	Info = &soundSystemData.sound[soundIndex];

	// サウンドハンドルが複数ある場合はランダムで鳴らすサウンドを決定する
	PlaySoundMem(Info->Handle[GetRand(Info->HandleNum - 1)], playType);
}

void SoundSystem::PlaySound3D(VECTOR Position, int soundIndex, int playType)
{
	SSoundInfo *Info;
	int         playIndex;

	// 指定の登録番号が有効かチェック
	if (soundIndex < 0 || soundIndex >= soundSystemData.soundNum)
	{
		return;
	}
	Info = &soundSystemData.sound[soundIndex];

	// サウンドハンドルが複数ある場合は鳴らすサウンドをランダムで決定する
	playIndex = GetRand(Info->HandleNum - 1);

	// 鳴らすワールド座標を設定する
	SetNextPlay3DPositionSoundMem(Position, Info->Handle[playIndex]);

	// サウンドを再生する
	PlaySoundMem(Info->Handle[playIndex], playType);
}

void SoundSystem::PlayBGM(EBGM BGM)
{
	SBgmInfo *BInfo = &soundSystemData.bgm[BGM];

	// 現在再生しているBGMと同じ場合は何もせずに終了
	if (soundSystemData.nowPlayBgm == BGM)
	{
		return;
	}

	// 現在他のBGMを再生していたら停止する
	if (soundSystemData.nowPlayBgm != EBGM_Num)
	{
		StopBGM();
	}

	// BGMの再生を開始する
	// 有効なループポイントがある場合はループ再生する
	PlaySoundMem(BInfo->soundHandle,
		BInfo->loopStartPosition >= 0 ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK
	);

	// 『現在再生中のBGM』を更新する
	soundSystemData.nowPlayBgm = BGM;
}

void SoundSystem::StopBGM()
{
	// 現在何のBGMも再生していない場合は何もせず終了
	if (soundSystemData.nowPlayBgm == EBGM_Num)
	{
		return;
	}

	// BGMのサウンドハンドルの再生を停止する
	StopSoundMem(soundSystemData.bgm[soundSystemData.nowPlayBgm].soundHandle);

	// 『現在再生中のBGM』を何も再生していないことを示す値にする
	soundSystemData.nowPlayBgm = EBGM_Num;
}
