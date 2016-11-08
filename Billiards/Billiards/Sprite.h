#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include "UI.h"

class Sprite:public UI
{
public:

	int spriteHandle;

	Sprite();
	Sprite(int spriteHandle);
	Sprite(char * fileName);

	Sprite(int spriteHandle,int drawPriority);
	Sprite(char * fileName,int drawPriority);
	Sprite(int spriteHandle,int updatePriority, int drawPriority);
	Sprite(char * fileName, int updatePriority, int drawPriority);

	~Sprite();

	bool Update(float stepTime);

	bool Draw();

	bool Draw(float process);

	//画像ハンドルデータを貰う
	int GetSpriteHandle();

	//中心描画するため、中心の位置を設置する
	void SetCenterPoint(int x, int y);

	//画像の中心座標（ローカル中心座標）を貰う
	VECTOR2DINT GetSrpiteCenter();

	//画像のサイズを貰う
	VECTOR2DINT GetSpriteSize();
	
	//画像ハンドルデータのみ変更、中心やサイズそのまま
	void ChangeSpriteSimple(int handle);

	//画像ハンドルデータのみ変更、中心やサイズそのまま
	void ChangeSpriteSimple(char* fileName);

	//画像ハンドルデータ変更及び中心やサイズ再算出
	void ChangeSpriteReload(int handle);

	//画像ハンドルデータ変更及び中心やサイズ再算出
	void ChangeSpriteReload(char* fileName);

	void SetOffset(float x,float y);

private:
	VECTOR2DINT spriteSize;

	VECTOR2DINT spriteCenter;

	VECTOR2D offset;

	void InitSprite();
};

#endif // !SPRITE_H