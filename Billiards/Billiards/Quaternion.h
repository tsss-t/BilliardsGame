#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

#include "DxLib.h"

//クォータニオン構造体
class Quaternion
{
public:

	double t;   //real
	double x;   //x
	double y;   //y
	double z;   //z

	void InitQuaternion();
private:
};
//クォータニオンの計算
Quaternion operator*(Quaternion q1, Quaternion q2);

//回転クォータニオン
Quaternion CreateRotationQuaternion(double radian, VECTOR Axis);

//位置クォータニオン
Quaternion CreateXYZToQuaternion(double PosX, double PosY, double PosZ);

//クォータニオンから回転行列へ
MATRIX QuaternionToMatrix(Quaternion q);

#endif // !QUATERNION_H