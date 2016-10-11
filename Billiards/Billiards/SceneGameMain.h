#ifndef SceneGameMain_H
#define SceneGameMain_H

#include "Scene.h"
#include "BiliardsTable.h"

class SceneGameMain :public Scene
{
public:
	static SceneGameMain *GetSceneInstance();
	BilliardsTable billiardTable;
	~SceneGameMain();
	bool SceneUpdate(float stepTime);
	bool SceneDraw(void);
	
private:
	static SceneGameMain * sceneGameMain;
	SceneGameMain();
};


#endif // !SceneGameMain_H