#ifndef SELECT_SCENE_H_
#define SELECT_SCENE_H_

#include "SceneBase.h"
#include "../MiniGameDifinition.h"

class SelectScene : public SceneBase
{
public:
	SelectScene(GameList* selectGame_);

	~SelectScene(){}

	void Update() override;

	void Draw() override;

	inline SceneList GetScene() const { return SceneList::SCENE_SELECT; }

private:
	bool SelectGame(GameList* game_);

private:
	GameList* m_SelectGame;

};

#endif