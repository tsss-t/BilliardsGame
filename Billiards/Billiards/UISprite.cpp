#include "UISprite.h"

#pragma region 初期化
void UISprite::InitSprite()
{
	this->spriteHandle = 0;

	offset = { 0.0f, 0.0f };
	spriteDrawCenter = { 0,0 };
	spriteCenter = { 0,0 };
	spriteSize = { 0,0 };

	enable = true;
}

UISprite::UISprite() :UI::UI()
{
	InitSprite();
}

UISprite::UISprite(int spriteHandle)
{
	InitSprite();
	this->spriteHandle = spriteHandle;
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;
}

UISprite::UISprite(char* fileName)
{
	InitSprite();
	this->spriteHandle = LoadGraph(fileName);
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;
}

UISprite::UISprite(int spriteHandle, int drawPriority)
{
	InitSprite();
	this->spriteHandle = spriteHandle;
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;

	SetPriority(PRIORITY_MAX / 2, drawPriority);
}

UISprite::UISprite(char * fileName, int drawPriority)
{
	InitSprite();
	this->spriteHandle = LoadGraph(fileName);
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;

	SetPriority(PRIORITY_MAX / 2, drawPriority);
}

UISprite::UISprite(int spriteHandle, int updatePriority, int drawPriority)
{
	InitSprite();
	this->spriteHandle = spriteHandle;
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;

	SetPriority(updatePriority, drawPriority);

}

UISprite::UISprite(char * fileName, int updatePriority, int drawPriority)
{
	InitSprite();
	this->spriteHandle = LoadGraph(fileName);
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;

	SetPriority(updatePriority, drawPriority);

}

UISprite::~UISprite()
{

}
#pragma endregion

bool UISprite::Update(float stepTime)
{
	UI::Update(stepTime);
	return true;
}

bool UISprite::Draw()
{
	if (enable)
	{
		UI::Draw();
		if (flickerInfo->isFlicker)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, flickerInfo->alphaNow);
		}
		DrawRotaGraph3F(
			transform->position.x + offset.x, transform->position.y + offset.y,
			spriteDrawCenter.x, spriteDrawCenter.y,
			transform->scale.x, transform->scale.y,
			transform->angle, spriteHandle,
			true);
	}
	return true;
}

bool UISprite::Draw(float process)
{
	if (enable)
	{
		UI::Draw();
		if (flickerInfo->isFlicker)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, flickerInfo->alphaNow);
		}
		DrawRectGraph(
			transform->position.x + offset.x, transform->position.y + offset.y,
			0, 0,
			spriteSize.x*process, spriteSize.y,
			spriteHandle,
			true, false);
	}
	return true;
}

//画像ハンドルデータを貰う
int UISprite::GetSpriteHandle()
{
	return spriteHandle;
}

//中心点について描画するため、中心の位置を設置する
void UISprite::SetDrawCenterPoint(int x, int y)
{
	this->spriteDrawCenter.x = x;
	this->spriteDrawCenter.y = y;
}

VECTOR2DINT UISprite::GetSpriteSize()
{
	return{ (int)(spriteSize.x * transform->scale.x),(int)(spriteSize.y *transform->scale.y) };
}

VECTOR2D UISprite::GetPositionInWindow()
{
	return{ transform->position.x - spriteDrawCenter.x*transform->scale.x, transform->position.y - spriteDrawCenter.y*transform->scale.y };
}

//画像のサイズを貰う
VECTOR2DINT UISprite::GetUISize()
{
	return{ (int)(spriteSize.x * transform->scale.x),(int)(spriteSize.y *transform->scale.y) };

}


VECTOR2DINT UISprite::GetSrpiteCenter()
{
	return{ spriteDrawCenter.x, spriteDrawCenter.y };
}

//画像ハンドルデータのみ変更、中心やサイズそのまま
void UISprite::ChangeSpriteSimple(int handle)
{
	if (this->spriteHandle != handle)
	{
		this->spriteHandle = handle;
	}
}

//画像ハンドルデータのみ変更、中心やサイズそのまま
void UISprite::ChangeSpriteSimple(char * fileName)
{
	this->spriteHandle = LoadGraph(fileName);
}

//画像ハンドルデータ変更及び中心やサイズ再算出
void UISprite::ChangeSpriteReload(int handle)
{
	if (this->spriteHandle != handle)
	{
		this->spriteHandle = handle;
	}
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;
}

//画像ハンドルデータ変更及び中心やサイズ再算出
void UISprite::ChangeSpriteReload(char * fileName)
{
	this->spriteHandle = LoadGraph(fileName);
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;
}

void UISprite::SetOffset(float x, float y)
{
	this->offset.x = x;
	this->offset.y = y;
}







