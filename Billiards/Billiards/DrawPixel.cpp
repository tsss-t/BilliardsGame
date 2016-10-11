//#include "DxLib.h"
//#define PI 3.141592654
//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{
//	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
//	VECTOR pos1 = VGet(300.0f, 200.0f, -000.0f);
//	VECTOR pos2 = VGet(000.0f, 0.0f, -000.0f);
//
//	if (MessageBox(NULL,"start?","test",MB_YESNO)==IDYES) {
//
//	}
//
//	int x = 0;
//	int handle;     // 画像格納用ハンドル
//	handle = MV1LoadModel("dat/Biliards/biliards1.mv1"); // 画像のロード
//										  // while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
//	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
//
//		MV1SetPosition(handle, VGet(300.0f,0.0f,400.0f - x));
//		MV1SetRotationXYZ(handle, VGet(-x/10.0f, 0, 0));
//		MV1DrawModel(handle);
//		x++;	// xを1増やす
//	}
//	//WaitKey();
//	DxLib_End();
//	return 0;
//}