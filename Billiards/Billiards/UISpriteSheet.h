#pragma once
#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "UI.h"

class UISpriteSheet :public UI
{
public:
	UISpriteSheet(char * fileName, int allNum, int XNum, int YNum, int XSize, int YSize);
	~UISpriteSheet();

	bool Draw();

	bool Update(float stepTime);

	//画像のサイズ（分割後の）を貰う
	VECTOR2DINT GetSpriteSize();

	VECTOR2DINT GetUISize();

	VECTOR2D GetPositionInWindow();

	//中心描画するため、中心の位置を設置する
	void SetCenterPoint(int x, int y);

	//画像の中心座標（ローカル中心座標）を貰う
	VECTOR2DINT GetSrpiteCenter();


private:
	int * spriteSheet;
	float animationTimer;
	float animationSpaceTime;
	int animationIndex;
	int animationNum;

	VECTOR2DINT spriteSize;

	VECTOR2DINT spriteCenter;

	void InitSpriteSheet();
};

	
#endif // !SPRITESHEET_H