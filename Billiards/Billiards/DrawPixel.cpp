//#include "DxLib.h"
//#define PI 3.141592654
//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{
//	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //������ɥ���`�ɉ���ȳ��ڻ����Y�����O��
//	VECTOR pos1 = VGet(300.0f, 200.0f, -000.0f);
//	VECTOR pos2 = VGet(000.0f, 0.0f, -000.0f);
//
//	if (MessageBox(NULL,"start?","test",MB_YESNO)==IDYES) {
//
//	}
//
//	int x = 0;
//	int handle;     // �����{�åϥ�ɥ�
//	handle = MV1LoadModel("dat/Biliards/biliards1.mv1"); // ����Υ�`��
//										  // while(�Y��������˷�ӳ, ��å��`���I��, ���楯�ꥢ)
//	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
//
//		MV1SetPosition(handle, VGet(300.0f,0.0f,400.0f - x));
//		MV1SetRotationXYZ(handle, VGet(-x/10.0f, 0, 0));
//		MV1DrawModel(handle);
//		x++;	// x��1���䤹
//	}
//	//WaitKey();
//	DxLib_End();
//	return 0;
//}