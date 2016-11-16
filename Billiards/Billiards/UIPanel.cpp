#include "UIPanel.h"

void UIPanel::PanelInit()
{
	*updateList = NULL;
	*drawList = NULL;

}

UIPanel::UIPanel()
{
	PanelInit();
}
UIPanel::UIPanel(int drawPriority)
{
	PanelInit();
	this->SetPriority(PRIORITY_MAX / 2, drawPriority);
}

UIPanel::UIPanel(int updatePriority, int drawPriority)
{
	PanelInit();
	this->SetPriority(updatePriority, drawPriority);
}
UIPanel::UIPanel(float x, float y, int drawPriority)
{
	PanelInit();
	this->transform->position = { x,y };
	this->SetPriority(PRIORITY_MAX / 2, drawPriority);
}

UIPanel::UIPanel(float x, float y, int updatePriority, int drawPriority)
{
	PanelInit();
	this->transform->position = { x,y };
	this->SetPriority(updatePriority, drawPriority);
}

UIPanel::UIPanel(VECTOR2D position, int drawPriority)
{
	PanelInit();
	this->transform->position = position;
	this->SetPriority(PRIORITY_MAX / 2, drawPriority);
}

UIPanel::UIPanel(VECTOR2D position, int updatePriority, int drawPriority)
{
	PanelInit();
	this->transform->position = position;
	this->SetPriority(updatePriority, drawPriority);
}



bool UIPanel::AddUI(UI * ui)
{
	SUIListPoint * tempPoint = new SUIListPoint();
	tempPoint->ui = ui;
	tempPoint->nextUIListPoint = addUIList;
	addUIList = tempPoint;
	if (!run)
	{
		return RefreshUIList();
	}
	return true;
}

bool UIPanel::DeleteUI(UI * ui)
{
	SUIListPoint * tempPoint = new SUIListPoint();
	tempPoint->ui = ui;
	tempPoint->nextUIListPoint = delUIList;
	delUIList = tempPoint;
	if (!run)
	{
		return RefreshUIList();
	}
	return true;
}

bool UIPanel::RefreshUIList()
{
	UI * ui;
	SUIListPoint * nextUIPoint;
	GameObjectBase * tempUI;
	VECTOR2D position;
#pragma region <追加するゲームオブジェクトのリスト>に登録されているゲームオブジェクトをリストに追加する
	if (addUIList != NULL)
	{
		ui = addUIList->ui;
		while (true)
		{
			// <追加するゲームオブジェクトのリスト>の次のゲームオブジェクトのアドレスを保持しておく
			nextUIPoint = addUIList->nextUIListPoint;

			// 状態推移処理のリストに追加する
			ui->goInfo->updateNext = updateList[ui->goInfo->goBaseInfo->updatePriority];
			updateList[ui->goInfo->goBaseInfo->updatePriority] = ui;

			// 描画処理のリストに追加する
			ui->goInfo->drawNext = drawList[ui->goInfo->goBaseInfo->drawPriority];
			drawList[ui->goInfo->goBaseInfo->drawPriority] = ui;
			position = ui->GetPosition();
			ui->SetPosition(this->transform->position.x + position.x, this->transform->position.y + position.y);
			uiList.push_back(ui);

			delete addUIList;
			addUIList = nextUIPoint;
			if (addUIList == NULL)
			{
				break;
			}
			else
			{
				ui = addUIList->ui;
			}
		}
		addUIList = NULL;
	}
#pragma endregion 
#pragma region <削除するゲームオブジェクトのリスト>に登録されているゲームオブジェクトをリストから外す
	if (delUIList != NULL)
	{
		ui = delUIList->ui;
		while (true)
		{
			// <削除するゲームオブジェクトのリスト>の次のゲームオブジェクトのアドレスを保持しておく
			nextUIPoint = delUIList->nextUIListPoint;

			// 外すゲームオブジェクトが状態推移処理のゲームオブジェクトのリストの先頭かをチェック
			if (updateList[ui->goInfo->goBaseInfo->updatePriority] == ui)
			{
				updateList[ui->goInfo->goBaseInfo->updatePriority] = ui->goInfo->updateNext;

				for (vector <GameObjectBase*>::iterator iter = uiList.begin(); iter != uiList.end();)
				{
					if ((*iter) == ui)
					{
						iter = uiList.erase(iter);
					}
					else
					{
						iter++;
					}
				}
			}
			else
			{
				// 状態推移処理のゲームオブジェクトのリストの先頭ではなかったら
				// 状態推移処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
				tempUI = updateList[ui->goInfo->goBaseInfo->updatePriority];

				while (true)
				{
					// リストの終端に来てしまった場合はループを抜ける
					if (tempUI->goInfo->updateNext == NULL)
					{
						break;
					}
					// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
					if (tempUI->goInfo->updateNext == ui)
					{
						tempUI->goInfo->updateNext = ui->goInfo->updateNext;
						for (vector <GameObjectBase*>::iterator iter = uiList.begin(); iter != uiList.end();)
						{
							if ((*iter) == ui)
							{
								iter = uiList.erase(iter);
							}
							else
							{
								iter++;
							}
						}
						break;
					}
					tempUI = tempUI->goInfo->updateNext;
				}
			}

			// 外すゲームオブジェクトが描画処理のゲームオブジェクトのリストの先頭かをチェック
			if (drawList[ui->goInfo->goBaseInfo->drawPriority] == ui)
			{
				// 先頭だった場合は先頭を外すゲームオブジェクトの次のゲームオブジェクトにする
				drawList[ui->goInfo->goBaseInfo->drawPriority] = ui->goInfo->drawNext;
			}
			else
			{
				// 描画処理のゲームオブジェクトのリストの先頭ではなかったら
				// 描画処理のゲームオブジェクトのリストから外すゲームオブジェクトを検索
				tempUI = drawList[ui->goInfo->goBaseInfo->drawPriority];

				while (true)
				{
					// リストの終端に来てしまった場合はループを抜ける
					if (tempUI->goInfo->drawNext == NULL)
					{
						break;
					}
					// 削除対象のゲームオブジェクトを発見した場合はリストから外してループから抜ける
					if (tempUI->goInfo->drawNext == ui)
					{
						tempUI->goInfo->drawNext = ui->goInfo->drawNext;
						break;
					}
					tempUI = tempUI->goInfo->drawNext;
				}
			}
			delete delUIList;
			delUIList = nextUIPoint;
			if (delUIList == NULL)
			{
				break;
			}
			else
			{
				ui = delUIList->ui;
			}
		}
		delUIList = NULL;
	}
#pragma endregion
	return true;
}

bool UIPanel::Draw()
{
	if (enable)
	{
		GameObjectBase * goBase;
		run = true;
		for (int i = 0; i < PRIORITY_MAX; i++)
		{
			for (goBase = drawList[i]; goBase != NULL; goBase = goBase->goInfo->drawNext)
			{
				if (!goBase->Draw())
				{
					return false;
				}
			}
		}
		run = false;
	}
	return true;
}

bool UIPanel::Update(float stepTime)
{
	if (enable)
	{
		GameObjectBase * goBase;
		run = true;
		for (int i = 0; i < PRIORITY_MAX; i++)
		{
			for (goBase = updateList[i]; goBase != NULL; goBase = goBase->goInfo->updateNext)
			{
				if (!goBase->Update(stepTime))
				{
					return false;
				}
			}
		}
		run = false;
		RefreshUIList();
	}

	return true;
}

vector<GameObjectBase*> UIPanel::getObjectList()
{
	return uiList;
}

UIPanel::~UIPanel()
{
}
