#ifndef GAME_H_
#define GAME_H_

// ゲーム更新管理クラス
class Game
{
public:
	// コンストラクタ
	Game(){}

	// デストラクタ
	~Game(){}

	// 各オブジェクトのステップ関数を呼び出す関数
	void Update();
	
};

#endif