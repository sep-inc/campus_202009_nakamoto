#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "SceneBase.h"
#include "../MiniGameDifinition.h"

/*
	�~�j�Q�[���̃V�[�����Ǘ�����N���X
*/
class SceneManager
{
public:
	/*
		�R���X�g���N�^
	*/
	SceneManager();

	/*
		�f�X�g���N�^
	*/
	~SceneManager();
	
	
	void Update();

	void Draw();


private:
	SceneBase* m_Scene;

	GameList m_SelectGame;
	
};

#endif