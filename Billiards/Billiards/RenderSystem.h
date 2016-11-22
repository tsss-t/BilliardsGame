#pragma once
#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "System.h"

class RenderSystem
{
public:

	static RenderSystem *GetRenderSystemInstance();

	void Render3D();

	void Render2D();

	~RenderSystem();

private:

	static RenderSystem * _instance;

	// アンチエイリアスレンダリング用の描画対象にできるグラフィックハンドル
	int    antialiasScreenHandle;

	RenderSystem();

};



#endif // !RENDERSYSTEM_H
