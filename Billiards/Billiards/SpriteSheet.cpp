#include "SpriteSheet.h"


void SpriteSheet::InitSpriteSheet()
{
	this->animationTimer = 0.0f;
	this->animationSpaceTime = 0.0f;
	this->animationIndex = 0;
	this->animationNum = 0;

	spriteCenter = { 0,0 };
	spriteSize = { 0,0 };
}
SpriteSheet::SpriteSheet(char* fileName, int allNum,
	int XNum, int YNum,
	int XSize, int YSize)
{
	InitSpriteSheet();
	spriteSheet = new int[allNum];
	LoadDivGraph(fileName, allNum,
		XNum, YNum,
		XSize, YSize, spriteSheet);
	spriteSize.x = XSize;
	spriteSize.y = YSize;
	spriteCenter.x = XSize / 2;
	spriteCenter.y = YSize / 2;
	animationNum = allNum;
}

SpriteSheet::~SpriteSheet()
{
	delete[]spriteSheet;
}
bool SpriteSheet::Update(float stepTime)
{
	UI::Update(stepTime);
	animationTimer += stepTime;

	if (animationTimer > animationSpaceTime)
	{
		animationTimer = 0;
		animationIndex++;
		if (animationIndex == animationNum)
		{
			animationIndex = 0;
		}
	}
	return true;
}
bool SpriteSheet::Draw()
{
	UI::Draw();
	if (flickerInfo->isFlicker)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, flickerInfo->alphaNow);
	}
	DrawRotaGraph3F(
		transform->postion.x, transform->postion.y,
		spriteCenter.x, spriteCenter.y,
		transform->scale.x, transform->scale.y,
		transform->angle, spriteSheet[animationIndex],
		true);
	return true;
}

void SpriteSheet::SetCenterPoint(int x, int y)
{
	this->spriteCenter.x = x;
	this->spriteCenter.y = y;
}

VECTOR2DINT SpriteSheet::GetSpriteSize()
{
	return{ spriteSize.x,spriteSize.y };
}

VECTOR2DINT SpriteSheet::GetSrpiteCenter()
{
	return{ spriteCenter.x, spriteCenter.y };
}

