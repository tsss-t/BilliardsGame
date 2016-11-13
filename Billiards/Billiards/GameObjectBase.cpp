#include "GameObjectBase.h"
#include "SceneManager.h"

GameObjectBase::GameObjectBase()
{
	goInfo = (SGameObjectInfo *)calloc(1, sizeof(SGameObjectInfo));
	goInfo->goBaseInfo = (SGameObjectBaseInfo *)calloc(1, sizeof(SGameObjectBaseInfo));
	this->goInfo->goBaseInfo->drawPriority = PRIORITY_MAX / 2;
	this->goInfo->goBaseInfo->updatePriority = PRIORITY_MAX / 2;
}

GameObjectBase::~GameObjectBase()
{
	delete goInfo->goBaseInfo;
	delete goInfo;
}

//ゲームオブジェクトの状態推移処理順番を変更
void GameObjectBase::SetUpdatePriority(int updatePriority)
{
	if (updatePriority != goInfo->goBaseInfo->updatePriority)
	{
		if (updatePriority > PRIORITY_MAX - 1)
		{
			if (!SceneManager::GetNowPlayScene()->AdjustGameObjectUpdatePriority(this, PRIORITY_MAX - 1))
			{
				goInfo->goBaseInfo->updatePriority = PRIORITY_MAX - 1;
			}
		}
		else if (updatePriority < 0)
		{
			if (!SceneManager::GetNowPlayScene()->AdjustGameObjectUpdatePriority(this, 0))
			{
				goInfo->goBaseInfo->updatePriority = 0;
			}
		}
		else
		{
			if (!SceneManager::GetNowPlayScene()->AdjustGameObjectUpdatePriority(this, updatePriority))
			{
				goInfo->goBaseInfo->updatePriority = updatePriority;
			}
		}
	}
}

//ゲームオブジェクトの描画処理順番を変更
void GameObjectBase::SetDrawPriority(int drawPriority)
{
	if (drawPriority != goInfo->goBaseInfo->drawPriority)
	{
		if (drawPriority > PRIORITY_MAX - 1)
		{
			if (!SceneManager::GetNowPlayScene()->AdjustGameObjectDrawPriority(this, PRIORITY_MAX - 1))
			{
				goInfo->goBaseInfo->updatePriority = PRIORITY_MAX - 1;
			}
		}
		else if (drawPriority < 0)
		{
			if (!SceneManager::GetNowPlayScene()->AdjustGameObjectDrawPriority(this, 0))
			{
				goInfo->goBaseInfo->updatePriority = 0;
			}
		}
		else
		{
			if (!SceneManager::GetNowPlayScene()->AdjustGameObjectDrawPriority(this, drawPriority))
			{
				goInfo->goBaseInfo->updatePriority = drawPriority;
			}
		}
	}
}

bool GameObjectBase::IsRigidBody()
{
	return false;
}


bool GameObjectBase::IsGUI()
{
	return false;
}

VECTOR2D GameObjectBase::GetPositionInWindow()
{
	return{ 0,0 };
}

btRigidBody * GameObjectBase::GetRigidBody()
{
	return nullptr;
}

VECTOR2DINT GameObjectBase::GetUISize()
{
	return VECTOR2DINT();
}

void GameObjectBase::SetPriority(int updatePriority, int drawPriority)
{
	if (updatePriority < 0)
	{
		this->goInfo->goBaseInfo->updatePriority = 0;
	}
	else if (updatePriority >= PRIORITY_MAX)
	{
		this->goInfo->goBaseInfo->updatePriority = PRIORITY_MAX - 1;
	}
	else
	{
		this->goInfo->goBaseInfo->updatePriority = updatePriority;
	}

	if (drawPriority < 0)
	{
		this->goInfo->goBaseInfo->drawPriority = 0;
	}
	else if (drawPriority >= PRIORITY_MAX)
	{
		this->goInfo->goBaseInfo->drawPriority = PRIORITY_MAX - 1;
	}
	else
	{
		this->goInfo->goBaseInfo->drawPriority = drawPriority;
	}
	this->goInfo->goBaseInfo->updatePriority = drawPriority;
}