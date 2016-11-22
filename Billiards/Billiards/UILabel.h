#pragma once
#ifndef LABEL_H
#define LABEL_H

#include "UI.h"


class UILabel:public UI
{
public:
	//ラベルの初期化
	UILabel();
	UILabel(char * string, int handle);
	UILabel(char * string, char * FontName, int Size, int Thinck, int FontType);
	~UILabel();

	bool Draw();
	bool Update(float stepTime);

	//色を動的変化
	void SetTweenColor(float flickerSpace, TweenType type);
	void SetTweenColor(float flickerSpace, int formAlpha, int toAlpha,TweenType type);

	//フォントのサイズを変更
	bool ChangeFontSize(int size);

	//ラベルの表示を変更
	void SetString(char * string);

	//ラベル表示する文字列を貰う
	char* GetString();

	//ラベルの位置補正値を設置する
	void SetOffset(float x, float y);

	//ラベルの色を変更
	void SetLabelColor(int color);

private:

	int fontHandle;

	char* string;
	char* fontName;
	int fontColor;
	int fontSize;
	int fontThick;
	int fontType;

	VECTOR2D offset;

	void InitLabel();
};



#endif // !LABEL_H