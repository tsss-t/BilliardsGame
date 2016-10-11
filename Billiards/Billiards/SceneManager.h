#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include "Scene.h"

using namespace std;

typedef struct _SSceneData
{
	string sceneName;
	Scene scene;
} SSceneData;

class SceneManager
{
public:
	static Scene * nowPlayScene;
	static SSceneData sceneList[];
	static void LoadSceneLevel(int sceneID);
	static void LoadSceneLevel(string sceneName);


	~SceneManager();
private:
	SceneManager();
};

#endif // !SCENEMANAGER_H
