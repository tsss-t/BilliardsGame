#include "Mathematics.h"

// Catmull-Rom �a�g��ʹ�ä���ָ���Σ���� Pos1 �� Pos2 ���a�g�������ˤ�ȡ�ä���
void CatmullRom(
	// Catmull-Rom �a�g��ʹ�ä������ˣ�( ������Ȥ���ʹ�ä���� )
	VECTOR *Pos0,

	// Catmull-Rom �a�g��ʹ�ä������ˣ�
	VECTOR *Pos1,

	// Catmull-Rom �a�g��ʹ�ä������ˣ�
	VECTOR *Pos2,

	// Catmull-Rom �a�g��ʹ�ä������ˣ�( ������Ȥ���ʹ�ä���� )
	VECTOR *Pos3,

	// ȡ�ä������ˤ�λ��
	// ( 0.0f:p1������   0.0f��1.0f���g:p1��p2���g���a�g����   1.0f:p2������ )
	float DestPosRate,

	// Ӌ��Y�������ˤ���뤹������Υ��ɥ쥹
	VECTOR *DestPos
)
{
	VECTOR v0;
	VECTOR v1;
	float  t2;
	float  t3;

	// Catmull-Rom �a�g��ʹ�ä��ơ�Pos1 �� Pos2 ���a�g���ˤ��������

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

// �������Ф��g�� Catmull-Rom ��ʹ�ä����a�g�����������Ф�ȡ�ä���
void GetCatmullRomPosList(
	// �a�g���Ф��������Ф����^���ɥ쥹
	VECTOR *InPos,

	// InPos �����ˤ���
	int PosNum,

	// һ�����g���a�g���ˤ���
	int DivNum,

	// �Y�������ˤ��{�����������Ф����^���ɥ쥹
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

	// ����Ŀ�����ˤ�������ϣ���Ŀ�����ˤ��飰��Ŀ�����ˤη����
	// ����Ŀ�����ˤ����ƄӤ������ˤȤ���
	SPos.x = InPos[0].x + (InPos[0].x - InPos[1].x) / 2.0f;
	SPos.y = InPos[0].y + (InPos[0].y - InPos[1].y) / 2.0f;
	SPos.z = InPos[0].z + (InPos[0].z - InPos[1].z) / 2.0f;

	// ��������ˤ�������������һ��ǰ�����ˤ�����������ˤη����
	// ��������ˤ����ƄӤ������ˤȤ���
	EPos.x = InPos[PosNum - 1].x + (InPos[PosNum - 1].x - InPos[PosNum - 2].x) / 2.0f;
	EPos.y = InPos[PosNum - 1].y + (InPos[PosNum - 1].y - InPos[PosNum - 2].y) / 2.0f;
	EPos.z = InPos[PosNum - 1].z + (InPos[PosNum - 1].z - InPos[PosNum - 2].z) / 2.0f;

	// Catmull-Rom �a�g��ʹ�ä���ȫ�����g���a�g���ˤ��������
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

// GetCatmullRomPosList �˶ɤ���InPos �����ˤ������ȡ�һ�����g���a�g���ˤ���������
// �Y�����{�����������Ф˱�Ҫ��Ҫ������ȡ�ä���
//     ���ꂎ : �Y�����{�����������Ф˱�Ҫ��Ҫ����
int GetCatmullRomPosNum(
	// InPos �����ˤ���
	int PosNum,

	// һ�����g���a�g���ˤ���
	int DivNum
)
{
	// �������ˤ����ϡ������g����������һ�Ĥ������g���a�g���ˤ�����������������ˡ�
	return (PosNum - 1) * DivNum + 1;
}

// ����С�����ͤΉ����΂���ָ���΂��˽��Ť���I����Ф�
//     ���ꂎ : �����΂���ָ���΂����_�������ɤ���
//              ( true : ָ���΂����_����  false : ָ���΂����_���Ƥ��ʤ� )
bool ParamChangeFloat(
	// ��������Ή����Υ��ɥ쥹
	float *Param,

	// Ŀ�ˤȤ��낎
	float TargetParam,

	// ���Ƥ�����r�g
	float StepTime,

	// ���Ή仯�ٶ�
	float Speed
)
{
	// �����΂���Ŀ�ˤȤ��낎���С�������ɤ����ǄI�����
	if (*Param < TargetParam)
	{
		// Ŀ�ˤ΂����С�������Ϥω����΂��ˉ仯������㤹��
		*Param += Speed * StepTime;

		// Ŀ�ˤ΂����_���Ƥ��뤫�ɤ������ж�
		if (*Param >= TargetParam)
		{
			// �_���Ƥ����������Ŀ�ˤ΂�����뤷�� true �򷵤�
			*Param = TargetParam;
			return true;
		}
	}
	else
	{
		// Ŀ�ˤ΂����С�������Ϥω����΂�����仯����p�㤹��
		*Param -= Speed * StepTime;

		// Ŀ�ˤ΂����_���Ƥ��뤫�ɤ������ж�
		if (*Param <= TargetParam)
		{
			// �_���Ƥ����������Ŀ�ˤ΂�����뤷�� true �򷵤�
			*Param = TargetParam;
			return true;
		}
	}

	// ������������ޤ�Ŀ�ˤ΂����_���Ƥ��ʤ��Ȥ������ȤʤΤ� false �򷵤�
	return false;
}


// ����С�����ͤΉ����˴��뤵��Ƥ���ǶȤ�ָ���νǶȤ˽��Ť���I����Ф�
// ( Ŀ�ˤȤ���ǶȤȉ����˴��뤵��Ƥ���ǶȤβ 2.0f * �� ���ڤǤ����Ҫ������ )
//     ���ꂎ : �����νǶȤ�ָ���νǶȤ��_�������ɤ���
//              ( true : ָ���νǶȤ��_����  false : ָ���νǶȤ��_���Ƥ��ʤ� )
bool ParamChangeAngle(
	// ��������Ή����Υ��ɥ쥹
	float *Param,

	// Ŀ�ˤȤ���Ƕ�
	float TargetParam,

	// ���Ƥ�����r�g
	float StepTime,

	// �ǶȤΉ仯�ٶ�
	float Speed
)
{
	float RelateAngle;

	// Ŀ�ˤȤ���ǶȤȉ����νǶȤȤβ�����
	RelateAngle = TargetParam - *Param;

	// �ǶȤβ�����������ϤΈ��ϤϽǶȤβ�����뷽�����ܞ������
	if (RelateAngle < -DX_PI_F)
	{
		RelateAngle += DX_TWO_PI_F;
	}
	else
		if (RelateAngle > DX_PI_F)
		{
			RelateAngle -= DX_TWO_PI_F;
		}

	// �ǶȤβ�򣰤˽��Ť���
	if (ParamChangeFloat(&RelateAngle, 0.0f, StepTime, Speed))
	{
		// �ǶȤβ���ˤʤä���Ŀ�ˤȤ���ǶȤˤʤ�Ȥ������ȤʤΤ�
		// ������Ŀ�ˤνǶȤ���뤷�� true �򷵤�
		*Param = TargetParam;
		return true;
	}

	// Ŀ�ˤνǶȤ���ǶȤβ����������Τ��¤����ǶȤȤ���
	*Param = TargetParam - RelateAngle;

	// �ޤ�Ŀ�ˤνǶȤ��_���Ƥ��ʤ��Τ� false �򷵤�
	return false;
}

// ָ���ι��줫�������ǛQ����������ȡ�ä���( ����С���ゎ )
//     ���ꂎ : ������ǛQ��������
float GetRandomFloat(
	// ���
	float MaxF,

	// ��С��
	float MinF
)
{
	return GetRand(10000) * (MaxF - MinF) / 10000.0f + MinF;
}

// ָ���ι��줫�������ǛQ����������ȡ�ä���( ������ )
//     ���ꂎ : ������ǛQ��������
int GetRandomInt(
	// ���
	int MaxI,

	// ��С��
	int MinI
)
{
	return GetRand(MaxI - MinI) + MinI;
}

// ָ���ι��줫�������ǛQ����������ȡ�ä���( ����С���ゎ )
//     ���ꂎ : ������ǛQ��������
float GetRandomFloatS(
	// ��󂎤���С���������ä�������Υ��ɥ쥹
	SMaxMinF *MaxMinF
)
{
	return GetRandomFloat(MaxMinF->MaxF, MaxMinF->MinF);
}

// ָ���ι��줫�������ǛQ����������ȡ�ä���( ������ )
//     ���ꂎ : ������ǛQ��������
int GetRandomIntS(
	// ��󂎤���С���������ä�������Υ��ɥ쥹
	SMaxMinI *MaxMinI
)
{
	return GetRandomInt(MaxMinI->MaxI, MaxMinI->MinI);
}



