#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include "DxLib.h"

// 指定の範囲からランダムに値を決定する処理で使用する情報( 浮動小数点型 )
typedef struct _SMaxMinF
{
	// 最大値
	float MaxF;

	// 最小値
	float MinF;
} SMaxMinF;

// 指定の範囲からランダムに値を決定する処理で使用する情報( 整数型 )
typedef struct _SMaxMinI
{
	// 最大値
	int MaxI;

	// 最小値
	int MinI;
} SMaxMinI;

// Catmull-Rom 補間を使用して指定の４点の Pos1 ～ Pos2 を補間する座標を取得する
extern void CatmullRom(
	// Catmull-Rom 補間で使用する座標０( 制御点として使用される )
	VECTOR *Pos0,

	// Catmull-Rom 補間で使用する座標１
	VECTOR *Pos1,

	// Catmull-Rom 補間で使用する座標２
	VECTOR *Pos2,

	// Catmull-Rom 補間で使用する座標３( 制御点として使用される )
	VECTOR *Pos3,

	// 取得する座標の位置
	// ( 0.0f:p1の座標   0.0fと1.0fの間:p1とp2の間の補間座標   1.0f:p2の座標 )
	float DestPosRate,

	// 計算結果の座標を代入する変数のアドレス
	VECTOR *DestPos
);

// 座標配列の間を Catmull-Rom を使用して補間した座標配列を取得する
extern void GetCatmullRomPosList(
	// 補間を行う座標配列の先頭アドレス
	VECTOR *InPos,

	// InPos の座標の数
	int PosNum,

	// 一座標間の補間座標の数
	int DivNum,

	// 結果の座標を格納する座標配列の先頭アドレス
	VECTOR *DestPos
);

// GetCatmullRomPosList に渡す「InPos の座標の数」と「一座標間の補間座標の数」から
// 結果を格納する座標配列に必要な要素数を取得する
//     戻り値 : 結果を格納する座標配列に必要な要素数
extern int GetCatmullRomPosNum(
	// InPos の座標の数
	int PosNum,

	// 一座標間の補間座標の数
	int DivNum
);

// 浮動小数点型の変数の値を指定の値に近づける処理を行う
//     戻り値 : 変数の値が指定の値に達したかどうか
//              ( true : 指定の値に達した  false : 指定の値に達していない )
extern bool ParamChangeFloat(
	// 操作対象の変数のアドレス
	float *Param,

	// 目標とする値
	float TargetParam,

	// 推移させる時間
	float StepTime,

	// 値の変化速度
	float Speed
);

// 浮動小数点型の変数に代入されている角度を指定の角度に近づける処理を行う
// ( 目標とする角度と変数に代入されている角度の差が 2.0f * π 以内である必要がある )
//     戻り値 : 変数の角度が指定の角度に達したかどうか
//              ( true : 指定の角度に達した  false : 指定の角度に達していない )
extern bool ParamChangeAngle(
	// 操作対象の変数のアドレス
	float *Param,

	// 目標とする角度
	float TargetParam,

	// 推移させる時間
	float StepTime,

	// 角度の変化速度
	float Speed
);

// 指定の範囲からランダムで決定した値を取得する( 浮動小数点値 )
//     戻り値 : ランダムで決定した値
extern float GetRandomFloat(
	// 最大値
	float MaxF,

	// 最小値
	float MinF
);

// 指定の範囲からランダムで決定した値を取得する( 整数値 )
//     戻り値 : ランダムで決定した値
extern int GetRandomInt(
	// 最大値
	int MaxI,

	// 最小値
	int MinI
);

// 指定の範囲からランダムで決定した値を取得する( 浮動小数点値 )
//     戻り値 : ランダムで決定した値
extern float GetRandomFloatS(
	// 最大値と最小値の情報が入った構造体のアドレス
	SMaxMinF *MaxMinF
);

// 指定の範囲からランダムで決定した値を取得する( 整数値 )
//     戻り値 : ランダムで決定した値
extern int GetRandomIntS(
	// 最大値と最小値の情報が入った構造体のアドレス
	SMaxMinI *MaxMinI
);


#endif


