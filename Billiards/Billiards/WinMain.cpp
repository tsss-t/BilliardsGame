#include "System.h"
#include <Windows.h>
#include "Label.h"
#include "Sprite.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	System* system =System :: GetSystemInstance();
	system->SystemMain();

	return 0;
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更,初期化,裏画面設定
//
//	int x, y, Mouse, Wheel, Image;
//	double size = 1.0;
//	//float q = 0;
//	int model;
//	model = MV1LoadModel("Data/Model/tableNormal.MV1");
//
//	FLOAT2 positionPre = { 0,0 };
//	FLOAT2 moveDis = { 0,0 };
//	//奥行0.1～1000までをカメラの描画範囲とする
//	SetCameraNearFar(0.1f, 1000.0f);
//	VECTOR xAxis, yAxis, zAxis;
//	Label * L1 = new Label();
//	L1->string = "test";
//	L1->SetPosition({ 100,100 });
//	
//	Sprite* s1 = new Sprite("Data/2D/1.png",17,6,3,80,69);
//	s1->SetPosition({ 200,100 });
//	s1->SimpleMove(3.0f, { 200,100 }, { 600,200 }, TweenType::Once);
//	s1->SetTweenColor(1.0f, TweenType::PingPong);
//	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
//	//SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));
//	SetCameraPositionAndAngle(VGet(0, 10, -20), 0, 0, 0);
//	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
//
//#pragma region input
//		Mouse = GetMouseInput();                //マウスの入力状態取得
//		Wheel = GetMouseWheelRotVol();  //ホイールの回転量取得
//		GetMousePoint(&x, &y);                //マウスの座標取得
//
//		moveDis = { x - positionPre.u,y - positionPre.v };
//		positionPre = { (float)x,(float)y };
//
//		//viewMatrix = GetCameraViewMatrix();
//
//
//		if (Mouse & MOUSE_INPUT_LEFT) { //マウスの左ボタンが押されていたら
//			DrawString(0, 0, "左ボタンが押されています", GetColor(255, 255, 255));
//			float x = GetCameraPosition().x;
//			float y = GetCameraPosition().y;
//			float z = GetCameraPosition().z;
//
//
//
//		}
//		if (Mouse & MOUSE_INPUT_RIGHT) { //マウスの左ボタンが押されていたら
//			DrawString(300, 0, "右ボタンが押されています", GetColor(255, 255, 255));
//
//			SetCameraPositionAndAngle(GetCameraPosition(),
//				GetCameraAngleVRotate() + moveDis.v* PI / 180, GetCameraAngleHRotate(), 0);
//			SetCameraPositionAndAngle(GetCameraPosition(), GetCameraAngleVRotate(), GetCameraAngleHRotate() + moveDis.u*PI / 180, 0);
//
//
//
//		}
//		if (Mouse & MOUSE_INPUT_MIDDLE) { //マウスの左ボタンが押されていたら
//			DrawString(300, 0, "中ボタンが押されています", GetColor(255, 255, 255));
//			//translateMatrix = MGetTranslate(VGet(moveDis.u*0.1f, -moveDis.v*0.1f, 0));
//			VECTOR cameraRight = GetCameraRightVector();
//			VECTOR cameraUp = GetCameraUpVector();
//			SetCameraPositionAndAngle(
//			{
//				GetCameraPosition().x - cameraRight.x*0.1f*moveDis.u + cameraUp.x*0.1f*moveDis.v,
//				GetCameraPosition().y - cameraRight.y*0.1f*moveDis.u + cameraUp.y*0.1f*moveDis.v,
//				GetCameraPosition().z - cameraRight.z*0.1f*moveDis.u + cameraUp.z*0.1f*moveDis.v }, GetCameraAngleVRotate(), GetCameraAngleHRotate(), 0
//				);
//
//		}
//		if (Wheel > 0) {        //ホイールが+方向に回転していたら
//			VECTOR cameraFront = GetCameraFrontVector();
//			SetCameraPositionAndAngle(
//			{
//				GetCameraPosition().x + cameraFront.x,
//				GetCameraPosition().y + cameraFront.y,
//				GetCameraPosition().z + cameraFront.z }, GetCameraAngleVRotate(), GetCameraAngleHRotate(), 0
//				);
//			//translateMatrix = MInverse(MGetTranslate(VGet(0, 0, 1.0f)));
//		}
//		if (Wheel < 0) {        //ホイールが－方向に回転していたら
//								//translateMatrix = MInverse(MGetTranslate(VGet(0, 0, -1.0f)));
//			VECTOR cameraFront = GetCameraFrontVector();
//			SetCameraPositionAndAngle(
//			{
//				GetCameraPosition().x - cameraFront.x,
//				GetCameraPosition().y - cameraFront.y,
//				GetCameraPosition().z - cameraFront.z }, GetCameraAngleVRotate(), GetCameraAngleHRotate(), 0
//				);
//		}
//#pragma endregion
//		
//
//		MV1DrawModel(model);
//		s1->Update(1.0f/60.0f);
//		s1->Draw();
//		L1->Draw();
//
//	}
//
//	DxLib_End();
//	return 0;
//}
//
