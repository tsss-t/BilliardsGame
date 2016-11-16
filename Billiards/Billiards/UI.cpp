#include "UI.h"



UI::UI()
{
	this->enable = true;
	this->transform = new _STransform2D();

	this->transform->position = { 0, 0 };
	this->transform->angle = 0.0f;
	this->transform->scale = { 1,1 };

	this->SetPriority(PRIORITY_MAX / 2, PRIORITY_MAX / 2);

	flickerInfo = new FlickerInfo();
	flickerInfo->isFlicker = false;
	flickerInfo->flickerSpace = 0.0f;
	flickerInfo->alphaFrom = 0.0f;
	flickerInfo->alphaTo = 0.0f;
	flickerInfo->alphaNow = 255.0f;
	flickerInfo->flickerTimer = 0.0f;
	flickerInfo->isFlickerAdd = true;
	flickerInfo->flickerType = Once;

	movingInfo = new MovingInfo();
	movingInfo->isMoving = false;
	movingInfo->movingTime = 0.0f;
	movingInfo->pointFrom = { 0,0 };
	movingInfo->pointTo = { 0,0 };
	movingInfo->isMoveTo = true;
	movingInfo->moveTimer = 0.0f;
	movingInfo->moveType = Once;
}

UI::~UI()
{
	delete this->transform;
	delete this->flickerInfo;
}



bool UI::Update(float stepTime)
{
	//明暗変化
	if (flickerInfo->isFlicker)
	{
		switch (flickerInfo->flickerType)
		{
		case Once: {
			if (flickerInfo->flickerTimer > flickerInfo->flickerSpace)
			{
				flickerInfo->isFlicker = false;
				flickerInfo->flickerTimer = 0;
			}
			flickerInfo->alphaNow = flickerInfo->alphaFrom + (flickerInfo->alphaTo - flickerInfo->alphaFrom)* flickerInfo->flickerTimer / flickerInfo->flickerSpace;
			break;
		}
		case Loop: {
			if (flickerInfo->flickerTimer > flickerInfo->flickerSpace)
			{
				flickerInfo->flickerTimer = 0;
			}
			flickerInfo->alphaNow = flickerInfo->alphaFrom + (flickerInfo->alphaTo - flickerInfo->alphaFrom)* flickerInfo->flickerTimer / flickerInfo->flickerSpace;
			break;
		}
		case PingPong: {
			if (flickerInfo->flickerTimer > flickerInfo->flickerSpace)
			{
				flickerInfo->isFlickerAdd = !flickerInfo->isFlickerAdd;
				flickerInfo->flickerTimer = 0;
			}
			if (flickerInfo->isFlickerAdd)
			{
				flickerInfo->alphaNow = flickerInfo->alphaFrom + (flickerInfo->alphaTo - flickerInfo->alphaFrom)* flickerInfo->flickerTimer / flickerInfo->flickerSpace;
			}
			else
			{
				flickerInfo->alphaNow = flickerInfo->alphaTo - (flickerInfo->alphaTo - flickerInfo->alphaFrom)* flickerInfo->flickerTimer / flickerInfo->flickerSpace;
			}
			break;
		}
		default: {
			break;
		}
		}
		if (flickerInfo->flickerTimer <= flickerInfo->flickerSpace)
		{
			flickerInfo->flickerTimer += stepTime;
		}
	}
	//Move
	if (movingInfo->isMoving)
	{
		switch (movingInfo->moveType)
		{
		case Once: {
			if (movingInfo->moveTimer > movingInfo->movingTime)
			{
				movingInfo->isMoving = false;
				movingInfo->moveTimer = 0;
			}
			transform->position.x += (movingInfo->pointTo.x - movingInfo->pointFrom.x)* stepTime / movingInfo->movingTime;
			transform->position.y += (movingInfo->pointTo.y - movingInfo->pointFrom.y)* stepTime / movingInfo->movingTime;
			break;
		}
		case Loop: {
			if (movingInfo->moveTimer > movingInfo->movingTime)
			{
				transform->position.x = movingInfo->pointFrom.x;
				transform->position.y = movingInfo->pointFrom.y;
				movingInfo->moveTimer = 0;
			}
			transform->position.x += (movingInfo->pointTo.x - movingInfo->pointFrom.x)* stepTime / movingInfo->movingTime;
			transform->position.y += (movingInfo->pointTo.y - movingInfo->pointFrom.y)* stepTime / movingInfo->movingTime;
			break;
		}
		case PingPong: {
			if (movingInfo->moveTimer > movingInfo->movingTime)
			{
				movingInfo->isMoveTo = !movingInfo->isMoveTo;
				movingInfo->moveTimer = 0;
				if (movingInfo->isMoveTo)
				{
					transform->position.x = movingInfo->pointFrom.x;
					transform->position.y = movingInfo->pointFrom.y;
				}
				else
				{
					transform->position.x = movingInfo->pointTo.x;
					transform->position.y = movingInfo->pointTo.y;
				}
			}
			if (movingInfo->isMoveTo)
			{
				transform->position.x += (movingInfo->pointTo.x - movingInfo->pointFrom.x)* stepTime / movingInfo->movingTime;
				transform->position.y += (movingInfo->pointTo.y - movingInfo->pointFrom.y)* stepTime / movingInfo->movingTime;
			}
			else
			{
				transform->position.x -= (movingInfo->pointTo.x - movingInfo->pointFrom.x)* stepTime / movingInfo->movingTime;
				transform->position.y -= (movingInfo->pointTo.y - movingInfo->pointFrom.y)* stepTime / movingInfo->movingTime;
			}
			break;
		}
		default: {

			break;
		}
		}
		if (movingInfo->moveTimer <= movingInfo->movingTime)
		{
			movingInfo->moveTimer += stepTime;
		}
	}

	return true;
}

bool UI::Draw()
{
	return true;
}

bool UI::IsGUI()
{
	return true;
}

void UI::SetUpdatePriority(int updatePriority)
{
	GameObjectBase::SetUpdatePriority(updatePriority);
}

void UI::SetDrawPriority(int drawPriority)
{
	GameObjectBase::SetDrawPriority(drawPriority);
}

void UI::SetPosition(float x, float y)
{
	this->transform->position = { x,y };
}

void UI::SetPosition(VECTOR2D position)
{
	this->transform->position = position;
}


void UI::SetRotation(float angle)
{
	this->transform->angle = angle;
}

void UI::SetScale(float x, float y)
{
	this->transform->scale = { x,y };
}

void UI::SetScale(VECTOR2D scale)
{
	this->transform->scale = scale;
}


VECTOR2D UI::GetPosition()
{
	return this->transform->position;
}

float UI::GetRotation()
{
	return this->transform->angle;
}

VECTOR2DINT UI::GetUISize()
{
	return VECTOR2DINT();
}

VECTOR2D UI::GetScale()
{
	return this->transform->scale;
}

VECTOR2D UI::GetPositionInWindow()
{
	VECTOR2D vector;
	vector.x = transform->position.x;
	vector.y = transform->position.y;
	return vector;
}

void UI::SetTweenColor(float flickerSpace, TweenType type)
{
	if (flickerSpace > 0)
	{
		flickerInfo->alphaFrom = 0;
		flickerInfo->alphaTo = 255;
		flickerInfo->alphaNow = 0;
		flickerInfo->isFlicker = true;
		flickerInfo->flickerSpace = flickerSpace;
		flickerInfo->flickerType = type;
	}
	else
	{
		flickerInfo->alphaFrom = 0;
		flickerInfo->alphaTo = 255;
		flickerInfo->alphaNow = 0;
		flickerInfo->isFlicker = false;
		flickerInfo->flickerSpace = 0.0f;
		flickerInfo->flickerType = Once;
	}
}

void UI::SetTweenColor(float flickerSpace, int alphaFrom, int alphaTo, TweenType type)
{
	if (flickerSpace > 0)
	{
		flickerInfo->alphaFrom = alphaFrom;
		flickerInfo->alphaTo = alphaTo;
		flickerInfo->alphaNow = alphaFrom;
		flickerInfo->isFlicker = true;
		flickerInfo->flickerSpace = flickerSpace;
		flickerInfo->flickerType = type;
	}
	else
	{
		flickerInfo->alphaFrom = 0;
		flickerInfo->alphaTo = 255;
		flickerInfo->alphaNow = 0;
		flickerInfo->isFlicker = false;
		flickerInfo->flickerSpace = 0;
		flickerInfo->flickerType = Once;
	}
}

void UI::SimpleMove(float movingTime, VECTOR2D pointFrom, VECTOR2D pointTo, TweenType type)
{
	if (movingTime > 0)
	{
		movingInfo->pointFrom = pointFrom;
		movingInfo->pointTo = pointTo;
		movingInfo->isMoving = true;
		movingInfo->movingTime = movingTime;
		movingInfo->moveType = type;
	}
	else
	{
		movingInfo->pointFrom = { 0,0 };
		movingInfo->pointTo = { 0,0 };
		movingInfo->isMoving = false;
		movingInfo->movingTime = 0;
		movingInfo->moveType = Once;
	}
}

void UI::SetEnable(bool enable)
{
	this->enable = enable;
}

bool UI::IsEnabled()
{
	return enable;
}
