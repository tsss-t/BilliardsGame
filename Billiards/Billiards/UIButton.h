#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "UILabel.h"
#include "UISprite.h"

typedef enum _EButtonType
{
	SpriteType,
	LabelType,
	LabelSpriteType
} EButtonType;

class UIButton :public UI
{
public:

	void InitButton();

	UIButton(UISprite *sprite);
	UIButton(UISprite * sprite, float drawPriority);
	UIButton(UISprite * sprite, float updatePriority, float drawPriority);
	UIButton(UILabel *label);
	UIButton(UILabel * label, float drawPriority);
	UIButton(UILabel *label, UISprite *sprite);
	UIButton(UILabel * label, UISprite * sprite, float drawPriority);
	UIButton(UILabel * label, UISprite * sprite, float updatePriority, float drawPriority);
	~UIButton();

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

	//ボタンの移動動作を設置
	void SimpleMove(float moveTime, VECTOR2D pointFrom, VECTOR2D pointTo, TweenType type);

	//ボタンのクリック事件を設置
	void SetClickEvent(void(*callBack)());

	//ボタンのクリックを起用するかどうか
	void SetEventEnable(bool isEnable);

	//ボタンのサイズを貰う
	VECTOR2DINT GetUISize();

	VECTOR2D GetPositionInWindow();

	//Sprite/labelの切り替えの設定
	void SetNormalSpriteHandle(int handle);
	void SetHoverSpriteHandle(int handle);
	void SetPressSpriteHandle(int handle);
	void SetDisabledSpriteHandle(int handle);

	void SetNormalLabelColor(int color);
	void SetHoverLabelColor(int color);
	void SetPressColor(int color);
	void SetDisabledColor(int color);


private:
	int normalSpriteHandle;
	int hoverSpriteHandle;
	int pressSpriteHandle;
	int disabledSpriteHandle;

	int normalColorHandle;
	int hoverColorHandle;
	int pressColorHandle;
	int disabledColorHandle;


	_EButtonType buttonType;
	UISprite * buttonSprite;
	UILabel * buttonLabel;

	VECTOR2DINT buttonSize;
	VECTOR2DINT buttonCenter;

	bool isEventEnable;

	void(*onClick)();

	//画像を変更する
	void ChangeSpriteSimple(int spriteHandle);

	//ラベルの色を変更する
	void ChangeColorSimple(int color);

	//ボタンの選択状態（hover）を設置
	bool IsSelected();

	//ボタンは押したのか
	bool IsClicked();

	//ボタンを押した後の処理
	void OnClick();
};
#endif // !BUTTON_H