#include "UILabel.h"


void UILabel::InitLabel()
{
	offset = { 0.0f, 0.0f };
	this->string = "";
	this->fontName = "ＭＳ ゴシック";
	this->fontSize = 25;
	this->fontThick = 9;
	this->fontType = DX_FONTTYPE_NORMAL;
	this->fontColor = GetColor(255, 255, 255);
}

UILabel::UILabel()
{
	InitLabel();
	fontHandle = CreateFontToHandle(fontName, fontSize, fontThick, fontType);

}
UILabel::UILabel(char * string, int handle)
{
	InitLabel();
	this->string = string;
	this->fontHandle = handle;
}
UILabel::UILabel(char * string, char * fontName, int size, int thinck, int fontType)
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

bool UILabel::Update(float stepTime)
{
	if (enable)
	{
		UI::Update(stepTime);
	}
	return true;
}

bool UILabel::Draw()
{
	if (enable)
	{
		UI::Draw();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, flickerInfo->alphaNow);
		DrawStringToHandle(this->transform->position.x + offset.x, this->transform->position.y + offset.y, string, fontColor, fontHandle);
	}
	return true;
}

//色を動的変化
void UILabel::SetTweenColor(float flickerSpace, TweenType type = Once)
{
	UI::SetTweenColor(flickerSpace, type);
}

//色を動的変化
void UILabel::SetTweenColor(float flickerSpace, int alphaFrom, int alphaTo, TweenType type = Once)
{
	UI::SetTweenColor(flickerSpace, alphaFrom, alphaTo, type);
}

//フォントを変更
bool UILabel::ChangeFontSize(int size)
{
	DeleteFontToHandle(fontHandle);
	fontSize = size;
	fontHandle = CreateFontToHandle(fontName, fontSize, fontThick, fontType);
	return true;
}

//ラベルの表示を変更
void UILabel::SetString(char * string)
{
	this->string = string;
}

//ラベル表示する文字列を貰う
char * UILabel::GetString()
{
	return string;
}

//ラベルの位置補正値を設置する
void UILabel::SetOffset(float x, float y)
{
	this->offset.x = x;
	this->offset.y = y;
}

//ラベルの色を変更
void UILabel::SetLabelColor(int color)
{
	this->fontColor = color;
}


UILabel::~UILabel()
{
	DeleteFontToHandle(fontHandle);
}