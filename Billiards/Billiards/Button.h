#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include "Sprite.h"

typedef enum _EButtonType
{
	SpriteType,
	LabelType,
	LabelSpriteType
} EButtonType;

class Button :public UI
{
public:

	void InitButton();

	Button(Sprite *sprite);
	Button(Sprite * sprite, float drawPriority);
	Button(Sprite * sprite, float updatePriority, float drawPriority);
	Button(Label *label);
	Button(Label *label, Sprite *sprite);
	Button(Label * label, Sprite * sprite, float drawPriority);
	Button(Label * label, Sprite * sprite, float updatePriority, float drawPriority);
	~Button();

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
	Sprite * buttonSprite;
	Label * buttonLabel;

	VECTOR2DINT buttonSize;
	VECTOR2DINT buttonCenter;

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