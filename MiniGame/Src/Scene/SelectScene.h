#ifndef SELECT_SCENE_H_
#define SELECT_SCENE_H_

#include "SceneBase.h"
#include "../MiniGameDifinition.h"

#include <string>

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

	const std::string m_DescriptionText;

	std::string m_BlankMenuListStr[(int)GameList::GAME_NUM + 1];
	std::string m_MenuListStr[(int)GameList::GAME_NUM + 1];

};

#endif