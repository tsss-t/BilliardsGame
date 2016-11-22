#include "UIButton.h"
#include "InputSystem.h"


void UIButton::InitButton()
{
	this->isEventEnable = false;

	buttonType = LabelSpriteType;
	this->buttonCenter = { 0,0 };
	this->buttonSize = { 0,0 };

	this->normalColorHandle = GetColor(255, 255, 255);
	this->hoverColorHandle = GetColor(225, 200, 150);
	this->pressColorHandle = GetColor(183, 163, 123);
	this->disabledColorHandle = GetColor(128, 128, 128);
}

UIButton::UIButton(UISprite *sprite)
{
	InitButton();
	this->normalSpriteHandle = sprite->GetSpriteHandle();
	this->hoverSpriteHandle = normalSpriteHandle;
	this->pressSpriteHandle = normalSpriteHandle;
	this->disabledSpriteHandle = normalSpriteHandle;

	this->buttonSprite = sprite;
	this->buttonCenter = sprite->GetSrpiteCenter();
	this->buttonSize = sprite->GetSpriteSize();

	this->buttonType = SpriteType;
}
UIButton::UIButton(UISprite *sprite, float drawPriority)
{
	InitButton();
	this->normalSpriteHandle = sprite->GetSpriteHandle();
	this->hoverSpriteHandle = normalSpriteHandle;
	this->pressSpriteHandle = normalSpriteHandle;
	this->disabledSpriteHandle = normalSpriteHandle;

	this->buttonSprite = sprite;
	this->buttonCenter = sprite->GetSrpiteCenter();
	this->buttonSize = sprite->GetSpriteSize();

	this->buttonType = SpriteType;

	SetPriority(PRIORITY_MAX / 2, drawPriority);
}
UIButton::UIButton(UISprite *sprite, float updatePriority, float drawPriority)
{
	InitButton();
	this->normalSpriteHandle = sprite->GetSpriteHandle();
	this->hoverSpriteHandle = normalSpriteHandle;
	this->pressSpriteHandle = normalSpriteHandle;
	this->disabledSpriteHandle = normalSpriteHandle;

	this->buttonSprite = sprite;
	this->buttonCenter = sprite->GetSrpiteCenter();
	this->buttonSize = sprite->GetSpriteSize();

	this->buttonType = SpriteType;

	SetPriority(updatePriority, drawPriority);
}
UIButton::UIButton(UILabel *label)
{
	InitButton();
	this->buttonLabel = label;
	this->buttonType = LabelType;

}
UIButton::UIButton(UILabel *label, float drawPriority)
{
	InitButton();
	this->buttonLabel = label;
	this->buttonType = LabelType;

	SetPriority(PRIORITY_MAX / 2, drawPriority);
}
UIButton::UIButton(UILabel *label, UISprite *sprite)
{
	InitButton();

	this->normalSpriteHandle = sprite->GetSpriteHandle();
	this->hoverSpriteHandle = normalSpriteHandle;
	this->pressSpriteHandle = normalSpriteHandle;
	this->disabledSpriteHandle = normalSpriteHandle;

	this->buttonSprite = sprite;
	this->buttonLabel = label;
	this->buttonCenter = sprite->GetSrpiteCenter();
	this->buttonSize = sprite->GetSpriteSize();
}
UIButton::UIButton(UILabel *label, UISprite *sprite, float drawPriority)
{
	InitButton();

	this->normalSpriteHandle = sprite->GetSpriteHandle();
	this->hoverSpriteHandle = normalSpriteHandle;
	this->pressSpriteHandle = normalSpriteHandle;
	this->disabledSpriteHandle = normalSpriteHandle;

	this->buttonSprite = sprite;
	this->buttonLabel = label;
	this->buttonCenter = sprite->GetSrpiteCenter();
	this->buttonSize = sprite->GetSpriteSize();
	SetPriority(PRIORITY_MAX / 2, drawPriority);
}
UIButton::UIButton(UILabel *label, UISprite *sprite, float updatePriority, float drawPriority)
{
	InitButton();

	this->normalSpriteHandle = sprite->GetSpriteHandle();
	this->hoverSpriteHandle = normalSpriteHandle;
	this->pressSpriteHandle = normalSpriteHandle;
	this->disabledSpriteHandle = normalSpriteHandle;

	this->buttonSprite = sprite;
	this->buttonLabel = label;
	this->buttonCenter = sprite->GetSrpiteCenter();
	this->buttonSize = sprite->GetSpriteSize();
	SetPriority(updatePriority, drawPriority);
}

UIButton::~UIButton()
{
	delete buttonSprite;
	delete buttonLabel;
}

bool UIButton::Update(float stepTime)
{
	if (enable)
	{
		switch (buttonType)
		{
		case SpriteType:
		{
			buttonSprite->Update(stepTime);

			transform->position.x = buttonSprite->GetPosition().x;
			transform->position.y = buttonSprite->GetPosition().y;
			transform->angle = buttonSprite->GetRotation();
			transform->scale.x = buttonSprite->GetScale().x;
			transform->scale.y = buttonSprite->GetScale().y;

			if (IsSelected())
			{
				if (normalSpriteHandle != hoverSpriteHandle)
				{
					ChangeSpriteSimple(hoverSpriteHandle);
				}
				if (IsClicked())
				{
					OnClick();
				}
			}
			else
			{
				if (normalSpriteHandle != hoverSpriteHandle)
				{
					ChangeSpriteSimple(normalSpriteHandle);
				}
			}

			break;
		}
		case LabelType:
		{
			buttonLabel->Update(stepTime);

			transform->position.x = buttonLabel->GetPosition().x;
			transform->position.y = buttonLabel->GetPosition().y;
			transform->angle = buttonLabel->GetRotation();
			transform->scale.x = buttonLabel->GetScale().x;
			transform->scale.y = buttonLabel->GetScale().y;

			if (IsSelected())
			{
				if (normalColorHandle != hoverColorHandle)
				{
					ChangeColorSimple(hoverColorHandle);
				}
				if (IsClicked())
				{
					OnClick();
				}
			}
			else
			{
				if (normalColorHandle != hoverColorHandle)
				{
					ChangeColorSimple(normalColorHandle);
				}
			}
			break;
		}
		case LabelSpriteType:
		{
			buttonSprite->Update(stepTime);
			buttonLabel->Update(stepTime);

			transform->position.x = buttonSprite->GetPosition().x;
			transform->position.y = buttonSprite->GetPosition().y;
			transform->angle = buttonSprite->GetRotation();
			transform->scale.x = buttonSprite->GetScale().x;
			transform->scale.y = buttonSprite->GetScale().y;
			if (IsSelected())
			{
				if (normalSpriteHandle != hoverSpriteHandle)
				{
					ChangeSpriteSimple(hoverSpriteHandle);
				}
				if (normalColorHandle != hoverColorHandle)
				{
					ChangeColorSimple(hoverColorHandle);
				}
				if (IsClicked())
				{
					OnClick();
				}
			}
			else
			{
				if (normalSpriteHandle != hoverSpriteHandle)
				{
					ChangeSpriteSimple(normalSpriteHandle);
				}
				if (normalColorHandle != hoverColorHandle)
				{
					ChangeColorSimple(normalColorHandle);
				}
			}
			break;
		}
		default:
			break;
		}
	}
	return true;
}

bool UIButton::Draw()
{
	if (enable)
	{
		switch (buttonType)
		{
		case SpriteType:
		{
			buttonSprite->Draw();

			break;
		}
		case LabelType:
		{
			buttonLabel->Draw();
			break;
		}
		case LabelSpriteType:
		{
			buttonSprite->Draw();
			buttonLabel->Draw();
			break;
		}
		default:
			break;
		}
	}
	return true;
}

//ボタンの位置を設置
void UIButton::SetPosition(float x, float y)
{
	UI::SetPosition(x, y);
	switch (buttonType)
	{
	case SpriteType:
	{
		buttonSprite->SetPosition(x, y);
		break;
	}
	case LabelType:
	{
		buttonLabel->SetPosition(x, y);
		break;
	}
	case LabelSpriteType:
	{
		buttonLabel->SetPosition(x, y);
		buttonSprite->SetPosition(x, y);
		break;
	}
	default:
		break;
	}
}

//ボタンの位置を設置
void UIButton::SetPosition(VECTOR2D vector2d)
{
	UI::SetPosition(vector2d);
	switch (buttonType)
	{
	case SpriteType:
	{
		buttonSprite->SetPosition(vector2d);
		break;
	}
	case LabelType:
	{
		buttonLabel->SetPosition(vector2d);
		break;
	}
	case LabelSpriteType:
	{
		buttonLabel->SetPosition(vector2d);
		buttonSprite->SetPosition(vector2d);
		break;
	}
	default:
		break;
	}
}

//ボタンの方向を設置
void UIButton::SetRotation(float angle)
{
	UI::SetRotation(angle);
	switch (buttonType)
	{
	case SpriteType:
	{
		buttonSprite->SetRotation(angle);
		break;
	}
	case LabelType:
	{
		buttonLabel->SetRotation(angle);
		break;
	}
	case LabelSpriteType:
	{
		buttonLabel->SetRotation(angle);
		buttonSprite->SetRotation(angle);
		break;
	}
	default:
		break;
	}
}

//ボタンの拡張倍数を設置
void UIButton::SetScale(float x, float y)
{
	UI::SetScale(x, y);
	switch (buttonType)
	{
	case SpriteType:
	{
		buttonSprite->SetScale(x, y);
		break;
	}
	case LabelType:
	{
		buttonLabel->SetScale(x, y);
		break;
	}
	case LabelSpriteType:
	{
		buttonLabel->SetScale(x, y);
		buttonSprite->SetScale(x, y);
		break;
	}
	default:
		break;
	}
}

//ボタンの拡張倍数を設置
void UIButton::SetScale(VECTOR2D scale)
{
	UI::SetScale(scale);
	switch (buttonType)
	{
	case SpriteType:
	{
		buttonSprite->SetScale(scale);
		break;
	}
	case LabelType:
	{
		buttonLabel->SetScale(scale);
		break;
	}
	case LabelSpriteType:
	{
		buttonLabel->SetScale(scale);
		buttonSprite->SetScale(scale);
		break;
	}
	default:
		break;
	}
}

//ボタンの明暗変化を設置
void UIButton::SetTweenColor(float flickerSpace, TweenType type)
{
	switch (buttonType)
	{
	case SpriteType:
	{
		buttonSprite->SetTweenColor(flickerSpace, type);
		break;
	}
	case LabelType:
	{
		buttonLabel->SetTweenColor(flickerSpace, type);
		break;
	}
	case LabelSpriteType:
	{
		buttonLabel->SetTweenColor(flickerSpace, type);
		buttonSprite->SetTweenColor(flickerSpace, type);
		break;
	}
	default:
		break;
	}
}

//ボタンの明暗変化を設置
void UIButton::SetTweenColor(float flickerSpace, int alphaFrom, int alphaTo, TweenType type)
{
	switch (buttonType)
	{
	case SpriteType:
	{
		buttonSprite->SetTweenColor(flickerSpace, alphaFrom, alphaTo, type);
		break;
	}
	case LabelType:
	{
		buttonLabel->SetTweenColor(flickerSpace, alphaFrom, alphaTo, type);
		break;
	}
	case LabelSpriteType:
	{
		buttonLabel->SetTweenColor(flickerSpace, alphaFrom, alphaTo, type);
		buttonSprite->SetTweenColor(flickerSpace, alphaFrom, alphaTo, type);
		break;
	}
	default:
		break;
	}
}

//ボタンの移動動作を設置
void UIButton::SimpleMove(float moveTime, VECTOR2D pointFrom, VECTOR2D pointTo, TweenType type)
{
	switch (buttonType)
	{
	case SpriteType:
	{
		buttonSprite->SimpleMove(moveTime, pointFrom, pointTo, type);
		break;
	}
	case LabelType:
	{
		buttonLabel->SimpleMove(moveTime, pointFrom, pointTo, type);
		break;
	}
	case LabelSpriteType:
	{
		buttonLabel->SimpleMove(moveTime, pointFrom, pointTo, type);
		buttonSprite->SimpleMove(moveTime, pointFrom, pointTo, type);
		break;
	}
	default:
		break;
	}
}

//ボタンの選択状態（hover）を設置
bool UIButton::IsSelected()
{
	FLOAT2 mousePosition = InputSystem::GetInputSystemInstance()->GetMouseNowPosition();
	//float left = transform->position.x - buttonCenter.x;
	//float right = transform->position.x - buttonCenter.x + buttonSize.x;
	//float top = transform->position.y - buttonCenter.y;
	//float button = transform->position.y - buttonCenter.y + buttonSize.y;

	if (mousePosition.u > transform->position.x&&
		mousePosition.u<transform->position.x + buttonSprite->GetUISize().x&&
		mousePosition.v>transform->position.y&&
		mousePosition.v < transform->position.y + buttonSprite->GetUISize().y)
	{
		return true;
	}

	//if ((mousePosition.u > transform->position.x - buttonCenter.x *transform->scale.x && mousePosition.u < transform->position.x + transform->scale.x* (buttonSize.x - buttonCenter.x)) &&
	//	(mousePosition.v > transform->position.y - buttonCenter.y *transform->scale.y && mousePosition.v < transform->position.y + transform->scale.y* (buttonSize.y - buttonCenter.y)))
	//{
	//	return true;
	//}
	return false;
}

//マウスの左ボタンを押したら
bool UIButton::IsClicked()
{
	if (InputSystem::GetInputSystemInstance()->GetMouseInputButton() == MOUSE_INPUT_LEFT)
	{
		return true;
	}
	return false;
}

//ボタンを押した後の処理
void UIButton::OnClick()
{
	if (isEventEnable)
	{
		switch (buttonType)
		{
		case SpriteType:
		{
			if (hoverSpriteHandle != pressSpriteHandle)
			{
				ChangeSpriteSimple(pressSpriteHandle);
			}
			break;
		}
		case LabelType:
		{
			if (hoverColorHandle != pressColorHandle)
			{
				ChangeColorSimple(pressColorHandle);
			}
			break;
		}
		case LabelSpriteType:
		{
			if (hoverSpriteHandle != pressSpriteHandle)
			{
				ChangeSpriteSimple(pressSpriteHandle);
			}
			break;
		}
		default:
		{
			break;
		}
		}

		if (onClick != nullptr)
		{
			onClick();
		}
	}
}

void UIButton::SetEventEnable(bool isEnable)
{
	this->isEventEnable = isEnable;
}

VECTOR2DINT UIButton::GetUISize()
{
	switch (buttonType)
	{
	case SpriteType:
		return buttonSprite->GetUISize();
		break;
	case LabelType:
		return buttonLabel->GetUISize();
		break;
	case LabelSpriteType:
		return buttonSprite->GetUISize();
		break;
	default:
		break;
	}
	return VECTOR2DINT();
}

VECTOR2D UIButton::GetPositionInWindow()
{
	return{ this->transform->position.x, this->transform->position.y };
}

//画像を変更する
void UIButton::ChangeSpriteSimple(int spriteHandle)
{
	this->buttonSprite->ChangeSpriteSimple(spriteHandle);
}

//ラベルの色を変更する
void UIButton::ChangeColorSimple(int color)
{
	this->buttonLabel->SetLabelColor(color);
}

//ボタンのクリック事件を設置
void UIButton::SetClickEvent(void(*callBack)())
{
	this->onClick = callBack;
}

void UIButton::SetNormalSpriteHandle(int handle)
{
	this->normalSpriteHandle = handle;
}

//Sprite/labelの切り替えの設定
//---------↓---------
void UIButton::SetHoverSpriteHandle(int handle)
{
	this->hoverSpriteHandle = handle;
}

void UIButton::SetPressSpriteHandle(int handle)
{
	this->pressSpriteHandle = handle;
}

void UIButton::SetDisabledSpriteHandle(int handle)
{
	this->disabledSpriteHandle = handle;
}

void UIButton::SetNormalLabelColor(int color)
{
	this->normalColorHandle = color;
}

void UIButton::SetHoverLabelColor(int color)
{
	this->hoverColorHandle = color;
}

void UIButton::SetPressColor(int color)
{
	this->pressColorHandle = color;
}

void UIButton::SetDisabledColor(int color)
{
	this->disabledColorHandle = color;
}
//---------↑---------