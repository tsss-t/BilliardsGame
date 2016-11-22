#include "RenderSystem.h"

RenderSystem * RenderSystem::_instance = NULL;
RenderSystem::RenderSystem()
{
	if (!System::GetSystemInstance()->System_GetLowSpecMode())
	{
		// アンチエイリアスレンダリング用の描画対象にできるグラフィックハンドルを作成する
		SetCreateDrawValidGraphMultiSample(4, 4);
		antialiasScreenHandle =
			MakeScreen(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, FALSE);
		//SetCreateDrawValidGraphMultiSample(0, 0);
	}
}

RenderSystem * RenderSystem::GetRenderSystemInstance()
{
	if (_instance == NULL)
	{
		_instance = new RenderSystem();
	}
	return _instance;
}

void RenderSystem::Render3D()
{
	// 低処理負荷モードではない場合は描画先をアンチエイリアス用画面に、
	// 低処理負荷モードの場合は描画先を裏画面にする
	if (!System::GetSystemInstance()->System_GetLowSpecMode())
	{
		SetDrawScreen(antialiasScreenHandle);

		// アンチエイリアス用画面を初期化
		ClearDrawScreen();
	}
	else
	{
		SetDrawScreen(DX_SCREEN_BACK);
	}
}
void RenderSystem::Render2D()
{
	// 低処理負荷モードではない場合は裏画面にアンチエイリアス用画面を描画する
	if (!System::GetSystemInstance()->System_GetLowSpecMode())
	{
		// 描画先を裏画面に設定
		SetDrawScreen(DX_SCREEN_BACK);

		// アンチエイリアス画面を裏画面に描画
		DrawGraph(0, 0, antialiasScreenHandle, FALSE);
	}
}
RenderSystem::~RenderSystem()
{
	if (!System::GetSystemInstance()->System_GetLowSpecMode())
	{
		DeleteGraph(antialiasScreenHandle);
	}
}
