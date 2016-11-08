#include "Sprite.h"

#pragma region 初期化
void Sprite::InitSprite()
{
	this->spriteHandle = 0;

	offset = { 0.0f, 0.0f };

	spriteCenter = { 0,0 };
	spriteSize = { 0,0 };
}

Sprite::Sprite() :UI::UI()
{
	InitSprite();
}

Sprite::Sprite(int spriteHandle)
{
	InitSprite();
	this->spriteHandle = spriteHandle;
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;
}

Sprite::Sprite(char* fileName)
{
	InitSprite();
	this->spriteHandle = LoadGraph(fileName);
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;
}

Sprite::Sprite(int spriteHandle, int drawPriority)
{
	InitSprite();
	this->spriteHandle = spriteHandle;
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;

	SetPriority(PRIORITY_MAX / 2, drawPriority);
}

Sprite::Sprite(char * fileName, int drawPriority)
{
	InitSprite();
	this->spriteHandle = LoadGraph(fileName);
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;

	SetPriority(PRIORITY_MAX/2, drawPriority);
}

Sprite::Sprite(int spriteHandle, int updatePriority, int drawPriority)
{
	InitSprite();
	this->spriteHandle = spriteHandle;
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;

	SetPriority(updatePriority, drawPriority);

}

Sprite::Sprite(char * fileName, int updatePriority, int drawPriority)
{
	InitSprite();
	this->spriteHandle = LoadGraph(fileName);
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;

	SetPriority(updatePriority, drawPriority);

}

Sprite::~Sprite()
{

}
#pragma endregion

bool Sprite::Update(float stepTime)
{
	UI::Update(stepTime);
	return true;
}

bool Sprite::Draw()
{
	UI::Draw();
	if (flickerInfo->isFlicker)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, flickerInfo->alphaNow);
	}
	DrawRotaGraph3F(
		transform->postion.x+offset.x, transform->postion.y+offset.y,
		spriteCenter.x, spriteCenter.y,
		transform->scale.x, transform->scale.y,
		transform->angle, spriteHandle,
		true);
	return true;
}

bool Sprite::Draw(float process)
{
	UI::Draw();
	if (flickerInfo->isFlicker)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, flickerInfo->alphaNow);
	}
	DrawRectGraph(
		transform->postion.x + offset.x, transform->postion.y + offset.y,
		0,0,
		spriteSize.x*process,spriteSize.y,
		spriteHandle,
		true,false);
	return true;
}

//画像ハンドルデータを貰う
int Sprite::GetSpriteHandle()
{
	return spriteHandle;
}

//中心描画するため、中心の位置を設置する
void Sprite::SetCenterPoint(int x, int y)
{
	this->spriteCenter.x = x;
	this->spriteCenter.y = y;
}

//画像の中心座標（ローカル中心座標）を貰う
VECTOR2DINT Sprite::GetSpriteSize()
{
	return{ spriteSize.x,spriteSize.y };
}

//画像のサイズを貰う
VECTOR2DINT Sprite::GetSrpiteCenter()
{
	return{ spriteCenter.x, spriteCenter.y };
}

//画像ハンドルデータのみ変更、中心やサイズそのまま
void Sprite::ChangeSpriteSimple(int handle)
{
	if (this->spriteHandle != handle)
	{
		this->spriteHandle = handle;
	}
}

//画像ハンドルデータのみ変更、中心やサイズそのまま
void Sprite::ChangeSpriteSimple(char * fileName)
{
	this->spriteHandle = LoadGraph(fileName);
}

//画像ハンドルデータ変更及び中心やサイズ再算出
void Sprite::ChangeSpriteReload(int handle)
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
void Sprite::ChangeSpriteReload(char * fileName)
{
	this->spriteHandle = LoadGraph(fileName);
	GetGraphSize(spriteHandle, &spriteSize.x, &spriteSize.y);
	spriteCenter.x = spriteSize.x / 2;
	spriteCenter.y = spriteSize.y / 2;
}

void Sprite::SetOffset(float x, float y)
{
	this->offset.x = x;
	this->offset.y = y;
}





