#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include "Sprite.h"

class Slider :public UI
{
public:

	Slider(int frontHandle, int backHandle);
	Slider(int frontHandle, int backHandle, int drawPriority);
	Slider(int frontHandle, int backHandle, int drawPriority, int updatePriority);
	Slider(char * frontSpriteName, char * backSpriteName);
	Slider(char * frontSpriteName, char * backSpriteName, int drawPriority);
	Slider(char * frontSpriteName, char * backSpriteName, int drawPriority, int updatePriority);

	bool Update(float stepTime);
	bool Draw();

	//ボタンの位置を設置
	void SetPosition(float x, float y);

	//ボタンの位置を設置
	void SetPosition(VECTOR2D vector2d);

	//ボタンの方向を設置
	void SetRotation(float angle);

	//ボタンの拡張倍数を設置
	void SetScale(float x, float y);

	//ボタンの拡張倍数を設置
	void SetScale(VECTOR2D scale);

	//ボタンの明暗変化を設置
	void SetTweenColor(float flickerSpace, TweenType type = Once);

	//ボタンの明暗変化を設置
	void SetTweenColor(float flickerSpace, int alphaFrom, int alphaTo, TweenType type = Once);


	void SetProccess(float process);

	void SetFrontSpriteOffset(float x, float y);

	~Slider();

private:
	Sprite * spBack;
	Sprite * spFront;

	float process;

	VECTOR2DINT sliderSize;
	void InitSlider();
};




#endif // !SLIDER_H