#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include "UISprite.h"

class UISlider :public UI
{
public:

	UISlider(int frontHandle, int backHandle);
	UISlider(int frontHandle, int backHandle, int drawPriority);
	UISlider(int frontHandle, int backHandle, int drawPriority, int updatePriority);
	UISlider(char * frontSpriteName, char * backSpriteName);
	UISlider(char * frontSpriteName, char * backSpriteName, int drawPriority);
	UISlider(char * frontSpriteName, char * backSpriteName, int drawPriority, int updatePriority);

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

	VECTOR2D GetPositionInWindow();

	VECTOR2DINT GetUISize();

	~UISlider();

private:
	UISprite * spBack;
	UISprite * spFront;

	float process;

	VECTOR2DINT sliderSize;
	void InitSlider();
};




#endif // !SLIDER_H