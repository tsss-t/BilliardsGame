#include "CameraManager.h"
#include "InputSystem.h"

CameraManager * CameraManager::_instance = NULL;


CameraManager::CameraManager()
{
	transform.postion = { 40,40,0 };
	transform.rotation = { 0,0,0 };
	SetCameraNearFar(0.1f, 1000.0f);
	SetCameraPositionAndAngle(transform.postion, 0, 0, 0);
	cameraMode = ECameraMode::FreeMode;
	cameraView = ECameraView::Top;

	topView = new SCameraView();
	backView = new SCameraView();
	leftView = new SCameraView();
	rightView = new SCameraView();
}

//カメラの位置を設置
bool CameraManager::SetCameraPos(VECTOR position)
{
	transform.postion = position;
	return true;
}

//カメラの角度を設置
// Elur角度使用
bool CameraManager::SetCameraRot(VECTOR rotation)
{
	transform.rotation.x = (float)rotation.x*PI / 360;
	transform.rotation.y = (float)rotation.y*PI / 360;
	transform.rotation.z = (float)rotation.z*PI / 360;
	return true;
}

//カメラの位置と角度を一緒に設定
// Elur角度使用
bool CameraManager::SetCameraPR(VECTOR position, VECTOR rotation)
{
	SetCameraPos(position);
	SetCameraRot(rotation);
	return true;
}

//カメラ追跡のターゲット（ゲームオブジェクトのみ）を設置
void CameraManager::SetCamaraTarget(GameObject * gameObject)
{
	this->targetGameObject = gameObject;
}

void CameraManager::SetCamaraViewPR(ECameraView view, VECTOR position, VECTOR rotation)
{
	switch (view)
	{
	case ECameraView::Top:
	{
		topView->position = position;
		topView->rotation = rotation;
		break;
	}
	case ECameraView::Back:
	{
		backView->position = position;
		backView->rotation = rotation;
		break;
	}
	case ECameraView::Left:
	{
		leftView->position = position;
		leftView->rotation = rotation;
		break;
	}
	case ECameraView::Right:
	{
		rightView->position = position;
		rightView->rotation = rotation;
		break;
	}
	default:
		break;
	}

}

//カメラを目標に注目
bool CameraManager::CameraLookAt(VECTOR targetPosition)
{
	SetCameraPositionAndTargetAndUpVec(transform.postion, targetPosition, VGet(0, 1, 0));
	transform.rotation.x = GetCameraAngleVRotate();
	transform.rotation.y = GetCameraAngleHRotate();
	transform.rotation.z = GetCameraAngleTRotate();

	return true;
}

//カメラ状態更新
bool CameraManager::CameraUpdate(float stepTime)
{
	bool result = false;

	switch (cameraMode)
	{
	case ECameraMode::FreeMode: {
		result = CameraModeFree(stepTime);
		break;
	}
	case ECameraMode::FixedMode:
	{
		result = CameraModeFixed(stepTime);
		break;
	}
	case ECameraMode::FollowMode:
	{
		if (targetGameObject == NULL || targetGameObject == nullptr)
		{
			cameraMode = FixedMode;
		}
		break;
	}
	default:
		break;
	}

	SetCameraPositionAndAngle(transform.postion, transform.rotation.x, transform.rotation.y, transform.rotation.z);
#if _DEBUG
	//>>>>>>>>>>>>>TestCode:現在カメラの位置と方位情報をスクリーンに出力
	DrawFormatString(0, 0, GetColor(255, 255, 255), "x:   %f      y:   %f      z:   %f      Rx:   %f      Ry:   %f      Rz:   %f",
		transform.postion.x, transform.postion.y, transform.postion.z, transform.rotation.x, transform.rotation.y, transform.rotation.z
	);
	//<<<<<<<<<<<<<TestEnd.
#endif // _DEBUG
	return result;
}

//カメラのモードを変更
void CameraManager::ChangeCameraMode(ECameraMode mode)
{
	this->cameraMode = mode;
}

//カメラの方位を変更
void CameraManager::ChangeCameraView(ECameraView view)
{
	this->cameraView = view;
}

//カメラのフリーモード実行方法
bool CameraManager::CameraModeFree(float stepTime)
{
	FLOAT2 mouseMoveDis;

	int mouseButton, mouseWheel;

	//　現在向いている方向
	VECTOR cameraFront, cameraRight, cameraUp;

	//　マウス状態取得
	mouseMoveDis = InputSystem::GetInputSystemInstance()->GetMouseMoveDirection();
	mouseButton = InputSystem::GetInputSystemInstance()->GetMouseInputButton();
	mouseWheel = InputSystem::GetInputSystemInstance()->GetMouseInputWheel();

	//　トランスフォーマー取得
	transform.postion = GetCameraPosition();

	transform.rotation.x = GetCameraAngleVRotate();
	transform.rotation.y = GetCameraAngleHRotate();
	transform.rotation.z = GetCameraAngleTRotate();

	//マウスの右ボタンが押されていたら、方向を自由に見ることができる
	if (mouseButton & MOUSE_INPUT_RIGHT) {

		if (transform.rotation.x + mouseMoveDis.v* PI / 180 > PI / 2)
		{
			transform.rotation.x = (float)PI / 2;
		}
		else if (transform.rotation.x + mouseMoveDis.v* PI / 180 < -PI / 2)
		{
			transform.rotation.x = (float)-PI / 2;
		}
		else
		{
			transform.rotation.x += (float)mouseMoveDis.v*PI / 360;
		}
		transform.rotation.y += (float)mouseMoveDis.u*PI / 360;
	}

	//マウスの中ボタンが押されていたら、カメラを水平移動することができる
	if (mouseButton & MOUSE_INPUT_MIDDLE) {
		cameraRight = GetCameraRightVector();
		cameraUp = GetCameraUpVector();
		transform.postion = {
			transform.postion.x - cameraRight.x*0.1f*mouseMoveDis.u + cameraUp.x*0.1f*mouseMoveDis.v,
				transform.postion.y - cameraRight.y*0.1f*mouseMoveDis.u + cameraUp.y*0.1f*mouseMoveDis.v,
				transform.postion.z - cameraRight.z*0.1f*mouseMoveDis.u + cameraUp.z*0.1f*mouseMoveDis.v };
	}

	//ホイール操作したら、カメラの前後距離を調整することができる
	if (mouseWheel != 0)
	{
		cameraFront = GetCameraFrontVector();
		if (mouseWheel > 0) {         //ホイールが+方向に回転していたら

			transform.postion = {
				transform.postion.x + cameraFront.x,
				transform.postion.y + cameraFront.y,
				transform.postion.z + cameraFront.z };

		}
		if (mouseWheel < 0) {          //ホイールが－方向に回転していたら
			transform.postion = {
			transform.postion.x - cameraFront.x,
				transform.postion.y - cameraFront.y,
				transform.postion.z - cameraFront.z };
		}
	}

	return true;
}

//カメラの固定モード実行方法
bool CameraManager::CameraModeFixed(float stepTime)
{
	switch (cameraView)
	{
	case Top:
	{
		transform.postion = topView->position;
		transform.rotation = topView->rotation;

		break;
	}
	case Back:
	{
		transform.postion = backView->position;
		transform.rotation = backView->rotation;
		break;
	}
	case Left:
	{
		transform.postion = leftView->position;
		transform.rotation = leftView->rotation;
		break;
	}
	case Right:
	{
		transform.postion = rightView->position;
		transform.rotation = rightView->rotation;
		break;
	}
	default:
	{
		break;
	}
	}


	return true;
}

//カメラの追跡モードの実行方法（追跡ターゲットを事前に設置することが必要）
//*追跡ターゲットを設置していない場合は直接固定モードに移行
bool CameraManager::CameraModeFollow(float stepTime)
{




	return true;
}

//カメラの座標を貰う
VECTOR CameraManager::GetCameraPosition()
{
	return transform.postion;
}

//カメラの角度を貰う
VECTOR CameraManager::GetCameraRotation()
{
	return VGet(
		(float)transform.rotation.x * 180 / PI,
		(float)transform.rotation.y * 180 / PI,
		(float)transform.rotation.z * 180 / PI
	);
}

//カメラの向き角度を貰う
VECTOR CameraManager::GetCameraFront()
{
	return GetCameraFrontVector();
}

//カメラマネジャーの実体を貰う
CameraManager * CameraManager::GetCameraManagerInstance()
{
	if (_instance == NULL)
	{
		_instance = new CameraManager();
	}
	return _instance;
}

CameraManager::~CameraManager()
{

}