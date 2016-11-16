#pragma once
#ifndef PANEL_H
#define PANEL_H

#include "UI.h"

typedef struct _SUIListPoint
{
	UI * ui;
	_SUIListPoint * nextUIListPoint;
} SUIListPoint;


class UIPanel :public UI
{
public:
	void PanelInit();
	UIPanel();
	UIPanel(float x, float y ,int drawPriority);
	UIPanel(float x, float y, int updatePriority, int drawPriority);

	UIPanel(VECTOR2D position, int drawPriority);
	UIPanel(VECTOR2D position, int updatePriority, int drawPriority);

	UIPanel(int drawPriority);
	UIPanel(int updatePriority, int drawPriority);
	bool AddUI(UI * ui);
	bool DeleteUI(UI * ui);
	bool RefreshUIList();
	bool Draw();
	bool Update(float stepTime);
	vector<GameObjectBase*> getObjectList();
	~UIPanel();

private:
	// タスクの処理を実行中かどうかのフラグ
	bool run;

	vector<GameObjectBase*> uiList;

	// 状態推移処理のリストの各優先順位の先頭タスクへのポインタ
	GameObjectBase * updateList[PRIORITY_MAX];

	// 描画処理のリストの各優先順位の先頭タスクへのポインタ
	GameObjectBase * drawList[PRIORITY_MAX];

	// 追加するゲームオブジェクトのリストの先頭タスクへのポインタ
	SUIListPoint * addUIList;

	// 削除するゲームオブジェクトのリストの先頭タスクへのポインタ
	SUIListPoint * delUIList;
};

#endif // !PANEL_H