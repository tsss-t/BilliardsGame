#pragma once
#ifndef UI_H
#define UI_H

#include "GameObjectBase.h"

enum TweenType
{
	Once,
	Loop,
	PingPong
};




typedef struct _STransform2D
{
	VECTOR2D position;
	float angle;
	VECTOR2D scale;
}STransform2D;

typedef struct _SFlickerInfo
{
	bool isFlicker;
	float flickerSpace;
	float alphaFrom;
	float alphaTo;
	float alphaNow;
	bool isFlickerAdd;
	float flickerTimer;
	TweenType flickerType;

}FlickerInfo;

typedef struct _SMovingInfo
{
	bool isMoving;
	float movingTime;
	VECTOR2D pointFrom;
	VECTOR2D pointTo;
	bool isMoveTo;
	float moveTimer;
	TweenType moveType;
}MovingInfo;

class UI :public GameObjectBase
{
public:


	virtual bool Update(float stepTime);
	virtual bool Draw();

	virtual bool IsGUI();

	//ゲームオブジェクトの状態推移処理順番を変更
	virtual void SetUpdatePriority(int updatePriority);

	//ゲームオブジェクトの描画処理順番を変更
	virtual void SetDrawPriority(int drawPriority);

	//UIの位置を設置
	virtual void SetPosition(float x, float y);

	//UIの位置を設置
	virtual void SetPosition(VECTOR2D vector2d);

	//UIの方向を設置
	virtual void SetRotation(float angle);

	//UIの拡張倍数を設置
	virtual void SetScale(float x, float y);

	//UIの拡張倍数を設置
	virtual void SetScale(VECTOR2D scale);

	//UIの位置データを貰う
	virtual VECTOR2D GetPosition();

	//UIの方向データを貰う
	virtual float GetRotation();

	//UIのサイズデータを貰う
	virtual VECTOR2DINT GetUISize();

	//UIの拡張倍数データを貰う
	virtual VECTOR2D GetScale();

	//UIはスクリーン中の位置データを貰う
	virtual VECTOR2D GetPositionInWindow();

	//UIの明暗変化を設置
	virtual void SetTweenColor(float flickerSpace, TweenType type = Once);

	//UIの明暗変化を設置
	virtual void SetTweenColor(float flickerSpace, int alphaFrom, int alphaTo, TweenType type = Once);

	//UIの移動動作を設置
	virtual void SimpleMove(float moveTime, VECTOR2D pointFrom, VECTOR2D pointTo, TweenType type);

	//UIの動作を設置（draw&update）
	void SetEnable(bool enable);
	bool IsEnabled();
	UI();
	~UI();

private:

protected:

	bool enable;

	_STransform2D * transform;

	//明暗変化関連
	_SFlickerInfo * flickerInfo;

	//移動関連
	_SMovingInfo * movingInfo;
};


#endif // !UI_H