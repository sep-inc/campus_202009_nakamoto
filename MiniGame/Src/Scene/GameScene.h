#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "SceneBase.h"
#include "../Game.h"
#include "../MiniGameDifinition.h"

/*
	�Q�[���V�[��
*/
class GameScene : public SceneBase
{
public:
	/*
		�R���X�g���N�^
	*/
	GameScene(GameList game_);

	/*
		�f�X�g���N�^
	*/
	~GameScene();

	/*
		�X�V�֐�
	*/
	void Update() override;

	/*
		�`��֐�
	*/
	void Draw() override;

	/*
		���݂̃V�[�����擾����֐�
	*/
	inline SceneList GetScene() const { return SceneList::SCENE_GAME; }

private:
	// �Q�[���N���X�̃|�C���^
	Game* m_Game;

};

#endif