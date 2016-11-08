#include "Label.h"


void Label::InitLabel()
{
	offset = { 0.0f, 0.0f };
	this->string = "";
	this->fontName = "ＭＳ ゴシック";
	this->fontSize = 25;
	this->fontThick = 9;
	this->fontType = DX_FONTTYPE_NORMAL;
	this->fontColor = GetColor(255, 255, 255);
}

Label::Label()
{
	InitLabel();
	fontHandle = CreateFontToHandle(fontName, fontSize, fontThick, fontType);

}
Label::Label(char * string, int handle)
{
	InitLabel();
	this->fontHandle = handle;
}
Label::Label(char * string, char * fontName, int size, int thinck, int fontType)
{
	InitLabel();
	if (fontName == NULL)
	{
		fontName = "ＭＳ ゴシック";
	}
	this->string = string;
	this->fontName = fontName;
	this->fontSize = size;
	this->fontThick = thinck;
	this->fontType = fontType;
	fontHandle = CreateFontToHandle(this->fontName, fontSize, fontThick, this->fontType);
}

bool Label::Update(float stepTime)
{
	UI::Update(stepTime);
	return true;
}

bool Label::Draw()
{
	UI::Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flickerInfo->alphaNow);
	DrawStringToHandle(this->transform->postion.x + offset.x, this->transform->postion.y + offset.y, string, fontColor, fontHandle);
	return true;
}

//色を動的変化
void Label::SetTweenColor(float flickerSpace, TweenType type = Once)
{
	UI::SetTweenColor(flickerSpace, type);
}

//色を動的変化
void Label::SetTweenColor(float flickerSpace, int alphaFrom, int alphaTo, TweenType type = Once)
{
	UI::SetTweenColor(flickerSpace, alphaFrom, alphaTo, type);
}

//フォントを変更
bool Label::ChangeFontSize(int size)
{
	DeleteFontToHandle(fontHandle);
	fontSize = size;
	fontHandle = CreateFontToHandle(fontName, fontSize, fontThick, fontType);
	return true;
}

//ラベルの表示を変更
void Label::SetString(char * string)
{
	this->string = string;
}

//ラベル表示する文字列を貰う
char * Label::GetString()
{
	return string;
}

//ラベルの位置補正値を設置する
void Label::SetOffset(float x, float y)
{
	this->offset.x = x;
	this->offset.y = y;
}

//ラベルの色を変更
void Label::ChangeLabelColor(int color)
{
	this->fontColor = color;
}


Label::~Label()
{
	DeleteFontToHandle(fontHandle);
}