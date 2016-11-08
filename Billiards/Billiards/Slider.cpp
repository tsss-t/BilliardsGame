#include "Slider.h"

void Slider::InitSlider()
{
	this->transform->postion = { 0, 0 };
	this->transform->angle = 0;
	this->transform->scale = { 1,1 };

	this->sliderSize = { 0,0 };
	this->process = 1.0f;
}

Slider::Slider(int frontHandle, int backHandle)
{
	InitSlider();
	this->spBack = new Sprite(backHandle);
	this->spFront = new Sprite(frontHandle);
	this->spBack->SetCenterPoint(0, 0);
	this->spFront->SetCenterPoint(0, 0);
	sliderSize = spBack->GetSpriteSize();
}
Slider::Slider(int frontHandle, int backHandle, int drawPriority)
{
	InitSlider();
	this->spBack = new Sprite(backHandle, drawPriority);
	this->spFront = new Sprite(frontHandle, drawPriority);
	this->spBack->SetCenterPoint(0, 0);
	this->spFront->SetCenterPoint(0, 0);
	sliderSize = spBack->GetSpriteSize();

	this->SetPriority(PRIORITY_MAX/2, drawPriority);
}
Slider::Slider(int frontHandle, int backHandle, int drawPriority, int updatePriority)
{
	InitSlider();
	this->spBack = new Sprite(backHandle, drawPriority, updatePriority);
	this->spFront = new Sprite(frontHandle, drawPriority, updatePriority);
	this->spBack->SetCenterPoint(0, 0);
	this->spFront->SetCenterPoint(0, 0);

	sliderSize = spBack->GetSpriteSize();

	this->SetPriority(updatePriority, drawPriority);
}
Slider::Slider(char * frontSpriteName, char * backSpriteName)
{
	InitSlider();
	this->spBack = new Sprite(backSpriteName);
	this->spFront = new Sprite(frontSpriteName);
	this->spBack->SetCenterPoint(0, 0);
	this->spFront->SetCenterPoint(0, 0);
	sliderSize = spBack->GetSpriteSize();
}
Slider::Slider(char * frontSpriteName, char * backSpriteName, int drawPriority)
{
	InitSlider();
	this->spBack = new Sprite(backSpriteName, drawPriority);
	this->spFront = new Sprite(frontSpriteName, drawPriority);
	this->spBack->SetCenterPoint(0, 0);
	this->spFront->SetCenterPoint(0, 0);
	sliderSize = spBack->GetSpriteSize();
}
Slider::Slider(char * frontSpriteName, char * backSpriteName, int drawPriority, int updatePriority)
{
	InitSlider();
	this->spBack = new Sprite(backSpriteName, drawPriority, updatePriority);
	this->spFront = new Sprite(frontSpriteName, drawPriority, updatePriority);
	this->spBack->SetCenterPoint(0, 0);
	this->spFront->SetCenterPoint(0, 0);
	sliderSize = spBack->GetSpriteSize();
}




bool Slider::Update(float stepTime)
{
	this->spBack->Update(stepTime);
	this->spFront->Update(stepTime);
	return true;
}
bool Slider::Draw()
{
	this->spBack->Draw();
	this->spFront->Draw(this->process);

	return true;
}
void Slider::SetPosition(float x, float y)
{
	this->spBack->SetPosition(x, y);
	this->spFront->SetPosition(x, y);

}
void Slider::SetPosition(VECTOR2D vector2d)
{
	this->spBack->SetPosition(vector2d);
	this->spFront->SetPosition(vector2d);
}
void Slider::SetRotation(float angle)
{
	this->spBack->SetRotation(angle);
	this->spFront->SetRotation(angle);
}
void Slider::SetScale(float x, float y)
{
	this->spBack->SetScale(x, y);
	this->spFront->SetScale(x, y);
}
void Slider::SetScale(VECTOR2D scale)
{
	this->spBack->SetScale(scale);
	this->spFront->SetScale(scale);
}
void Slider::SetTweenColor(float flickerSpace, TweenType type)
{
}
void Slider::SetTweenColor(float flickerSpace, int alphaFrom, int alphaTo, TweenType type)
{
}
void Slider::SetProccess(float process)
{
	this->process = process;
}
void Slider::SetFrontSpriteOffset(float x, float y)
{
	this->spFront->SetOffset(x, y);
}
Slider::~Slider()
{
	delete spFront;
	delete spBack;
}

