#include "SceneGameMain.h"

SceneGameMain *SceneGameMain::sceneGameMain = NULL;

SceneGameMain::SceneGameMain()
{

	AddToScene(&billiardTable);
}
SceneGameMain * SceneGameMain::GetSceneInstance()
{
	if (sceneGameMain == NULL)
	{
		sceneGameMain = new SceneGameMain();
	}
	return sceneGameMain;
}

SceneGameMain::~SceneGameMain()
{
	delete &billiardTable;
}

bool SceneGameMain::SceneUpdate(float stepTime)
{
	return Scene::SceneUpdate(stepTime);
}

bool SceneGameMain::SceneDraw(void)
{
	return Scene::SceneDraw();
}