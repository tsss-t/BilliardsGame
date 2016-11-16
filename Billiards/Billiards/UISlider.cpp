#include "UISlider.h"

void UISlider::InitSlider()
{
	this->transform->position = { 0, 0 };
	this->transform->angle = 0;
	this->transform->scale = { 1,1 };

	this->sliderSize = { 0,0 };
	this->process = 1.0f;
}

UISlider::UISlider(int frontHandle, int backHandle)
{
	InitSlider();
	this->spBack = new UISprite(backHandle);
	this->spFront = new UISprite(frontHandle);
	sliderSize = spBack->GetSpriteSize();
}
UISlider::UISlider(int frontHandle, int backHandle, int drawPriority)
{
	InitSlider();
	this->spBack = new UISprite(backHandle, drawPriority);
	this->spFront = new UISprite(frontHandle, drawPriority);
	sliderSize = spBack->GetSpriteSize();

	this->SetPriority(PRIORITY_MAX/2, drawPriority);
}
UISlider::UISlider(int frontHandle, int backHandle, int drawPriority, int updatePriority)
{
	InitSlider();
	this->spBack = new UISprite(backHandle, drawPriority, updatePriority);
	this->spFront = new UISprite(frontHandle, drawPriority, updatePriority);

	sliderSize = spBack->GetSpriteSize();

	this->SetPriority(updatePriority, drawPriority);
}
UISlider::UISlider(char * frontSpriteName, char * backSpriteName)
{
	InitSlider();
	this->spBack = new UISprite(backSpriteName);
	this->spFront = new UISprite(frontSpriteName);
	sliderSize = spBack->GetSpriteSize();
}
UISlider::UISlider(char * frontSpriteName, char * backSpriteName, int drawPriority)
{
	InitSlider();
	this->spBack = new UISprite(backSpriteName, drawPriority);
	this->spFront = new UISprite(frontSpriteName, drawPriority);
	sliderSize = spBack->GetSpriteSize();
	SetPriority(PRIORITY_MAX / 2, drawPriority);
}
UISlider::UISlider(char * frontSpriteName, char * backSpriteName, int drawPriority, int updatePriority)
{
	InitSlider();
	this->spBack = new UISprite(backSpriteName, drawPriority, updatePriority);
	this->spFront = new UISprite(frontSpriteName, drawPriority, updatePriority);
	sliderSize = spBack->GetSpriteSize();
	this->SetPriority(updatePriority, drawPriority);

}




bool UISlider::Update(float stepTime)
{
	this->spBack->Update(stepTime);
	this->spFront->Update(stepTime);
	return true;
}
bool UISlider::Draw()
{
	this->spBack->Draw();
	this->spFront->Draw(this->process);

	return true;
}
void UISlider::SetPosition(float x, float y)
{
	UI::SetPosition(x, y);
	this->spBack->SetPosition(x, y);
	this->spFront->SetPosition(x, y);
}
void UISlider::SetPosition(VECTOR2D vector2d)
{
	UI::SetPosition(vector2d);
	this->spBack->SetPosition(vector2d);
	this->spFront->SetPosition(vector2d);
}
void UISlider::SetRotation(float angle)
{
	UI::SetRotation(angle);
	this->spBack->SetRotation(angle);
	this->spFront->SetRotation(angle);
}
void UISlider::SetScale(float x, float y)
{
	UI::SetScale(x,y);
	this->spBack->SetScale(x, y);
	this->spFront->SetScale(x, y);
}
void UISlider::SetScale(VECTOR2D scale)
{
	UI::SetScale(scale);
	this->spBack->SetScale(scale);
	this->spFront->SetScale(scale);
}
void UISlider::SetTweenColor(float flickerSpace, TweenType type)
{
}
void UISlider::SetTweenColor(float flickerSpace, int alphaFrom, int alphaTo, TweenType type)
{
}
void UISlider::SetProccess(float process)
{
	this->process = process;
}
void UISlider::SetFrontSpriteOffset(float x, float y)
{
	this->spFront->SetOffset(x, y);
}
VECTOR2D UISlider::GetPositionInWindow()
{
	return{ this->transform->position.x, this->transform->position.y };
}
VECTOR2DINT UISlider::GetUISize()
{
	return spBack->GetUISize();
}
UISlider::~UISlider()
{
	delete spFront;
	delete spBack;
}

