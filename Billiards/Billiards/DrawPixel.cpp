//#include "DxLib.h"
//#define PI 3.141592654
//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{
//	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモ�`ド�筝�と兜豚晒と�Y鮫中�O協
//	VECTOR pos1 = VGet(300.0f, 200.0f, -000.0f);
//	VECTOR pos2 = VGet(000.0f, 0.0f, -000.0f);
//
//	if (MessageBox(NULL,"start?","test",MB_YESNO)==IDYES) {
//
//	}
//
//	int x = 0;
//	int handle;     // 鮫�餮饉{喘ハンドル
//	handle = MV1LoadModel("dat/Biliards/biliards1.mv1"); // 鮫�颪離踪`ド
//										  // while(�Y鮫中を燕鮫中に郡啌, メッセ�`ジ�I尖, 鮫中クリア)
//	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
//
//		MV1SetPosition(handle, VGet(300.0f,0.0f,400.0f - x));
//		MV1SetRotationXYZ(handle, VGet(-x/10.0f, 0, 0));
//		MV1DrawModel(handle);
//		x++;	// xを1��やす
//	}
//	//WaitKey();
//	DxLib_End();
//	return 0;
//}