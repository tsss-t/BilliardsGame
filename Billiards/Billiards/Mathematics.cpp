#include "Mathematics.h"

// Catmull-Rom 補間を使用して指定の４点の Pos1 ～ Pos2 を補間する座標を取得する
void CatmullRom(
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
)
{
	VECTOR v0;
	VECTOR v1;
	float  t2;
	float  t3;

	// Catmull-Rom 補間を使用して、Pos1 ～ Pos2 の補間座標を算出する

	v0.x = (Pos2->x - Pos0->x) / 2.0f;
	v0.y = (Pos2->y - Pos0->y) / 2.0f;
	v0.z = (Pos2->z - Pos0->z) / 2.0f;

	v1.x = (Pos3->x - Pos1->x) / 2.0f;
	v1.y = (Pos3->y - Pos1->y) / 2.0f;
	v1.z = (Pos3->z - Pos1->z) / 2.0f;

	t2 = DestPosRate * DestPosRate;
	t3 = t2 * DestPosRate;

	DestPos->x = (2 * Pos1->x - 2 * Pos2->x + v0.x + v1.x) * t3 +
		(-3 * Pos1->x + 3 * Pos2->x - 2 * v0.x - v1.x) * t2 +
		v0.x * DestPosRate + Pos1->x;

	DestPos->y = (2 * Pos1->y - 2 * Pos2->y + v0.y + v1.y) * t3 +
		(-3 * Pos1->y + 3 * Pos2->y - 2 * v0.y - v1.y) * t2 +
		v0.y * DestPosRate + Pos1->y;

	DestPos->z = (2 * Pos1->z - 2 * Pos2->z + v0.z + v1.z) * t3 +
		(-3 * Pos1->z + 3 * Pos2->z - 2 * v0.z - v1.z) * t2 +
		v0.z * DestPosRate + Pos1->z;
}

// 座標配列の間を Catmull-Rom を使用して補間した座標配列を取得する
void GetCatmullRomPosList(
	// 補間を行う座標配列の先頭アドレス
	VECTOR *InPos,

	// InPos の座標の数
	int PosNum,

	// 一座標間の補間座標の数
	int DivNum,

	// 結果の座標を格納する座標配列の先頭アドレス
	VECTOR *DestPos
)
{
	VECTOR  SPos;
	VECTOR  EPos;
	VECTOR *Pos[4];
	VECTOR *dp;
	int     i;
	int     j;
	int     num;
	float   sm;

	// ０番目の座標の制御点は１番目の座標から０番目の座標の方向へ
	// ０番目の座標から移動した座標とする
	SPos.x = InPos[0].x + (InPos[0].x - InPos[1].x) / 2.0f;
	SPos.y = InPos[0].y + (InPos[0].y - InPos[1].y) / 2.0f;
	SPos.z = InPos[0].z + (InPos[0].z - InPos[1].z) / 2.0f;

	// 最後の座標の制御点は最後の一つ前の座標から最後の座標の方向へ
	// 最後の座標から移動した座標とする
	EPos.x = InPos[PosNum - 1].x + (InPos[PosNum - 1].x - InPos[PosNum - 2].x) / 2.0f;
	EPos.y = InPos[PosNum - 1].y + (InPos[PosNum - 1].y - InPos[PosNum - 2].y) / 2.0f;
	EPos.z = InPos[PosNum - 1].z + (InPos[PosNum - 1].z - InPos[PosNum - 2].z) / 2.0f;

	// Catmull-Rom 補間を使用して全座標間の補間座標を算出する
	dp = DestPos;
	num = PosNum - 1;
	sm = 1.0f / DivNum;
	for (i = 0; i < num; i++)
	{
		VECTOR v0;
		VECTOR v1;
		float  t2;
		float  t3;
		float  t;
		VECTOR par1;
		VECTOR par2;

		Pos[0] = i - 1 <  0 ? &SPos : &InPos[i - 1];
		Pos[1] = &InPos[i];
		Pos[2] = &InPos[i + 1];
		Pos[3] = i + 2 >= PosNum ? &EPos : &InPos[i + 2];

		v0.x = (Pos[2]->x - Pos[0]->x) / 2.0f;
		v0.y = (Pos[2]->y - Pos[0]->y) / 2.0f;
		v0.z = (Pos[2]->z - Pos[0]->z) / 2.0f;

		v1.x = (Pos[3]->x - Pos[1]->x) / 2.0f;
		v1.y = (Pos[3]->y - Pos[1]->y) / 2.0f;
		v1.z = (Pos[3]->z - Pos[1]->z) / 2.0f;

		par1.x = 2 * Pos[1]->x - 2 * Pos[2]->x + v0.x + v1.x;
		par1.y = 2 * Pos[1]->y - 2 * Pos[2]->y + v0.y + v1.y;
		par1.z = 2 * Pos[1]->z - 2 * Pos[2]->z + v0.z + v1.z;

		par2.x = -3 * Pos[1]->x + 3 * Pos[2]->x - 2 * v0.x - v1.x;
		par2.y = -3 * Pos[1]->y + 3 * Pos[2]->y - 2 * v0.y - v1.y;
		par2.z = -3 * Pos[1]->z + 3 * Pos[2]->z - 2 * v0.z - v1.z;

		t = 0.0f;
		for (j = 0; j < DivNum; j++, dp++, t += sm)
		{
			t2 = t  * t;
			t3 = t2 * t;
			dp->x = par1.x * t3 + par2.x * t2 + v0.x * t + Pos[1]->x;
			dp->y = par1.y * t3 + par2.y * t2 + v0.y * t + Pos[1]->y;
			dp->z = par1.z * t3 + par2.z * t2 + v0.z * t + Pos[1]->z;
		}
	}
	*dp = InPos[PosNum - 1];
}

// GetCatmullRomPosList に渡す「InPos の座標の数」と「一座標間の補間座標の数」から
// 結果を格納する座標配列に必要な要素数を取得する
//     戻り値 : 結果を格納する座標配列に必要な要素数
int GetCatmullRomPosNum(
	// InPos の座標の数
	int PosNum,

	// 一座標間の補間座標の数
	int DivNum
)
{
	// 出力座標の数は『座標間の数』×『一つの座標間の補間座標の数』＋『最後の座標』
	return (PosNum - 1) * DivNum + 1;
}

// 浮動小数点型の変数の値を指定の値に近づける処理を行う
//     戻り値 : 変数の値が指定の値に達したかどうか
//              ( true : 指定の値に達した  false : 指定の値に達していない )
bool ParamChangeFloat(
	// 操作対象の変数のアドレス
	float *Param,

	// 目標とする値
	float TargetParam,

	// 推移させる時間
	float StepTime,

	// 値の変化速度
	float Speed
)
{
	// 変数の値が目標とする値より小さいかどうかで処理を分岐
	if (*Param < TargetParam)
	{
		// 目標の値より小さい場合は変数の値に変化値を加算する
		*Param += Speed * StepTime;

		// 目標の値に達しているかどうかの判定
		if (*Param >= TargetParam)
		{
			// 達していたら変数に目標の値を代入して true を返す
			*Param = TargetParam;
			return true;
		}
	}
	else
	{
		// 目標の値より小さい場合は変数の値から変化値を減算する
		*Param -= Speed * StepTime;

		// 目標の値に達しているかどうかの判定
		if (*Param <= TargetParam)
		{
			// 達していたら変数に目標の値を代入して true を返す
			*Param = TargetParam;
			return true;
		}
	}

	// ここに来たらまだ目標の値に達していないということなので false を返す
	return false;
}


// 浮動小数点型の変数に代入されている角度を指定の角度に近づける処理を行う
// ( 目標とする角度と変数に代入されている角度の差が 2.0f * π 以内である必要がある )
//     戻り値 : 変数の角度が指定の角度に達したかどうか
//              ( true : 指定の角度に達した  false : 指定の角度に達していない )
bool ParamChangeAngle(
	// 操作対象の変数のアドレス
	float *Param,

	// 目標とする角度
	float TargetParam,

	// 推移させる時間
	float StepTime,

	// 角度の変化速度
	float Speed
)
{
	float RelateAngle;

	// 目標とする角度と変数の角度との差を算出
	RelateAngle = TargetParam - *Param;

	// 角度の差が１８０度以上の場合は角度の差を求める方向を逆転させる
	if (RelateAngle < -DX_PI_F)
	{
		RelateAngle += DX_TWO_PI_F;
	}
	else
		if (RelateAngle > DX_PI_F)
		{
			RelateAngle -= DX_TWO_PI_F;
		}

	// 角度の差を０に近づける
	if (ParamChangeFloat(&RelateAngle, 0.0f, StepTime, Speed))
	{
		// 角度の差が０になったら目標とする角度になるということなので
		// 変数に目標の角度を代入して true を返す
		*Param = TargetParam;
		return true;
	}

	// 目標の角度から角度の差を引いたものを新しい角度とする
	*Param = TargetParam - RelateAngle;

	// まだ目標の角度に達していないので false を返す
	return false;
}

// 指定の範囲からランダムで決定した値を取得する( 浮動小数点値 )
//     戻り値 : ランダムで決定した値
float GetRandomFloat(
	// 最大値
	float MaxF,

	// 最小値
	float MinF
)
{
	return GetRand(10000) * (MaxF - MinF) / 10000.0f + MinF;
}

// 指定の範囲からランダムで決定した値を取得する( 整数値 )
//     戻り値 : ランダムで決定した値
int GetRandomInt(
	// 最大値
	int MaxI,

	// 最小値
	int MinI
)
{
	return GetRand(MaxI - MinI) + MinI;
}

// 指定の範囲からランダムで決定した値を取得する( 浮動小数点値 )
//     戻り値 : ランダムで決定した値
float GetRandomFloatS(
	// 最大値と最小値の情報が入った構造体のアドレス
	SMaxMinF *MaxMinF
)
{
	return GetRandomFloat(MaxMinF->MaxF, MaxMinF->MinF);
}

// 指定の範囲からランダムで決定した値を取得する( 整数値 )
//     戻り値 : ランダムで決定した値
int GetRandomIntS(
	// 最大値と最小値の情報が入った構造体のアドレス
	SMaxMinI *MaxMinI
)
{
	return GetRandomInt(MaxMinI->MaxI, MaxMinI->MinI);
}



