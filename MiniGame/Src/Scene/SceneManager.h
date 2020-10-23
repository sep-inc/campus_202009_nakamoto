#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "SceneBase.h"
#include "../MiniGameDifinition.h"

/*
	ミニゲームのシーンを管理するクラス
*/
class SceneManager
{
public:
	/*
		コンストラクタ
	*/
	SceneManager();

	/*
		デストラクタ
	*/
	~SceneManager();
	
	
	void Update();

	void Draw();


private:
	SceneBase* m_Scene;

	GameList m_SelectGame;
	
};

#endif