#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "SceneBase.h"
#include "../Game.h"
#include "../MiniGameDifinition.h"

/*
	ゲームシーン
*/
class GameScene : public SceneBase
{
public:
	/*
		コンストラクタ
	*/
	GameScene(GameList game_);

	/*
		デストラクタ
	*/
	~GameScene();

	/*
		更新関数
	*/
	void Update() override;

	/*
		描画関数
	*/
	void Draw() override;

	/*
		現在のシーンを取得する関数
	*/
	inline SceneList GetScene() const { return SceneList::SCENE_GAME; }

private:
	// ゲームクラスのポインタ
	Game* m_Game;

};

#endif