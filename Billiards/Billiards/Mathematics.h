#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include "DxLib.h"

// ָ���ι��줫�������˂���Q������I���ʹ�ä������( ����С������ )
typedef struct _SMaxMinF
{
	// ���
	float MaxF;

	// ��С��
	float MinF;
} SMaxMinF;

// ָ���ι��줫�������˂���Q������I���ʹ�ä������( ������ )
typedef struct _SMaxMinI
{
	// ���
	int MaxI;

	// ��С��
	int MinI;
} SMaxMinI;

// Catmull-Rom �a�g��ʹ�ä���ָ���Σ���� Pos1 �� Pos2 ���a�g�������ˤ�ȡ�ä���
extern void CatmullRom(
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
);

// �������Ф��g�� Catmull-Rom ��ʹ�ä����a�g�����������Ф�ȡ�ä���
extern void GetCatmullRomPosList(
	// �a�g���Ф��������Ф����^���ɥ쥹
	VECTOR *InPos,

	// InPos �����ˤ���
	int PosNum,

	// һ�����g���a�g���ˤ���
	int DivNum,

	// �Y�������ˤ��{�����������Ф����^���ɥ쥹
	VECTOR *DestPos
);

// GetCatmullRomPosList �˶ɤ���InPos �����ˤ������ȡ�һ�����g���a�g���ˤ���������
// �Y�����{�����������Ф˱�Ҫ��Ҫ������ȡ�ä���
//     ���ꂎ : �Y�����{�����������Ф˱�Ҫ��Ҫ����
extern int GetCatmullRomPosNum(
	// InPos �����ˤ���
	int PosNum,

	// һ�����g���a�g���ˤ���
	int DivNum
);

// ����С�����ͤΉ����΂���ָ���΂��˽��Ť���I����Ф�
//     ���ꂎ : �����΂���ָ���΂����_�������ɤ���
//              ( true : ָ���΂����_����  false : ָ���΂����_���Ƥ��ʤ� )
extern bool ParamChangeFloat(
	// ��������Ή����Υ��ɥ쥹
	float *Param,

	// Ŀ�ˤȤ��낎
	float TargetParam,

	// ���Ƥ�����r�g
	float StepTime,

	// ���Ή仯�ٶ�
	float Speed
);

// ����С�����ͤΉ����˴��뤵��Ƥ���ǶȤ�ָ���νǶȤ˽��Ť���I����Ф�
// ( Ŀ�ˤȤ���ǶȤȉ����˴��뤵��Ƥ���ǶȤβ 2.0f * �� ���ڤǤ����Ҫ������ )
//     ���ꂎ : �����νǶȤ�ָ���νǶȤ��_�������ɤ���
//              ( true : ָ���νǶȤ��_����  false : ָ���νǶȤ��_���Ƥ��ʤ� )
extern bool ParamChangeAngle(
	// ��������Ή����Υ��ɥ쥹
	float *Param,

	// Ŀ�ˤȤ���Ƕ�
	float TargetParam,

	// ���Ƥ�����r�g
	float StepTime,

	// �ǶȤΉ仯�ٶ�
	float Speed
);

// ָ���ι��줫�������ǛQ����������ȡ�ä���( ����С���ゎ )
//     ���ꂎ : ������ǛQ��������
extern float GetRandomFloat(
	// ���
	float MaxF,

	// ��С��
	float MinF
);

// ָ���ι��줫�������ǛQ����������ȡ�ä���( ������ )
//     ���ꂎ : ������ǛQ��������
extern int GetRandomInt(
	// ���
	int MaxI,

	// ��С��
	int MinI
);

// ָ���ι��줫�������ǛQ����������ȡ�ä���( ����С���ゎ )
//     ���ꂎ : ������ǛQ��������
extern float GetRandomFloatS(
	// ��󂎤���С���������ä�������Υ��ɥ쥹
	SMaxMinF *MaxMinF
);

// ָ���ι��줫�������ǛQ����������ȡ�ä���( ������ )
//     ���ꂎ : ������ǛQ��������
extern int GetRandomIntS(
	// ��󂎤���С���������ä�������Υ��ɥ쥹
	SMaxMinI *MaxMinI
);


#endif


