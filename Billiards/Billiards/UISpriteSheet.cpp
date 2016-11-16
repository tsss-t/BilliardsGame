#include "UISpriteSheet.h"


void UISpriteSheet::InitSpriteSheet()
{
	this->animationTimer = 0.0f;
	this->animationSpaceTime = 0.0f;
	this->animationIndex = 0;
	this->animationNum = 0;

	spriteCenter = { 0,0 };
	spriteSize = { 0,0 };
}
UISpriteSheet::UISpriteSheet(char* fileName, int allNum,
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

UISpriteSheet::~UISpriteSheet()
{
	delete[] spriteSheet;
}
bool UISpriteSheet::Update(float stepTime)
{
	if (enable)
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
	}
	return true;
}
bool UISpriteSheet::Draw()
{
	if (enable)
	{
		UI::Draw();
		if (flickerInfo->isFlicker)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, flickerInfo->alphaNow);
		}
		DrawRotaGraph3F(
			transform->position.x, transform->position.y,
			spriteCenter.x, spriteCenter.y,
			transform->scale.x, transform->scale.y,
			transform->angle, spriteSheet[animationIndex],
			true);
	}
	return true;
}

void UISpriteSheet::SetCenterPoint(int x, int y)
{
	this->spriteCenter.x = x;
	this->spriteCenter.y = y;
}

VECTOR2DINT UISpriteSheet::GetSpriteSize()
{
	return{ spriteSize.x,spriteSize.y };
}

VECTOR2DINT UISpriteSheet::GetUISize()
{
	return{ spriteSize.x,spriteSize.y };
}

VECTOR2D UISpriteSheet::GetPositionInWindow()
{
	return{ this->transform->position.x, this->transform->position.y };
}

VECTOR2DINT UISpriteSheet::GetSrpiteCenter()
{
	return{ spriteCenter.x, spriteCenter.y };
}

