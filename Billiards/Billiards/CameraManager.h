#pragma once
#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "DxLib.h"
#include "Quaternion.h"
#include "GameObject.h"

#define PI 3.141592654

typedef enum _ECameraMode
{
	FreeMode,
	FollowMode,
	FixedMode
} ECameraMode;
typedef enum _ECameraView
{
	Top,
	Back,
	Left,
	Right
}ECameraView;

typedef struct _STransformCamera
{
	VECTOR position;
	VECTOR rotation;
}STransformCamera;

class CameraManager
{
public:

	typedef struct _SCameraView
	{
		VECTOR position;
		VECTOR rotation;
	}SCameraView;

	//カメラの位置を設置
	bool SetCameraPos(VECTOR position);

	//カメラの角度を設置
	// Elur角度使用
	bool SetCameraRotElur(VECTOR rotation);

	//カメラの角度を設置
	//　角度の値使用
	bool SetCameraRot(VECTOR rotation);

	//カメラの位置と角度を一緒に設定
	// Elur角度使用
	bool SetCameraPR(VECTOR position, VECTOR rotation);

	bool SetCameraPRElur(VECTOR position, VECTOR rotation);

	//カメラ追跡のターゲット（ゲームオブジェクトのみ）を設置
	void SetCamaraTarget(GameObject * gameObject);

	void SetCamaraViewPR(ECameraView view, VECTOR position, VECTOR rotation);

	//カメラを目標に注目
	bool CameraLookAt(VECTOR targetPosition);

	//カメラ状態更新
	bool CameraUpdate(float stepTime);

	//カメラのモードを変更
	void ChangeCameraMode(ECameraMode mode);

	//カメラの方位を変更
	void ChangeCameraView(ECameraView view);

	//カメラの座標を貰う
	VECTOR GetCameraPosition();

	//カメラの角度を貰う
	VECTOR GetCameraRotation();

	//カメラの向き角度を貰う
	VECTOR GetCameraFront();

	//カメラマネジャーの実体を貰う
	static CameraManager * GetCameraManagerInstance();

	~CameraManager();

private:

	static CameraManager * _instance;

	_ECameraMode cameraMode;

	_ECameraView cameraView;

	_SCameraView * topView;

	_SCameraView * backView;

	_SCameraView * leftView;

	_SCameraView * rightView;

	STransformCamera transform;

	GameObject * targetGameObject;

	//カメラのフリーモード実行方法
	bool CameraModeFree(float stepTime);

	//カメラの固定モード実行方法
	bool CameraModeFixed(float stepTime);

	//カメラの追跡モードの実行方法（追跡ターゲットを事前に設置することが必要）
	//*追跡ターゲットを設置していない場合は直接固定モードに移行
	bool CameraModeFollow(float stepTime);

	CameraManager();
};
#endif // !CAMERAMANAGER_H