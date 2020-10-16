#ifndef SHOGI_RESULT_SCENE_H_
#define SHOGI_RESULT_SCENE_H_

#include "../ShogiSceneBase.h"
#include "../../Object/Definition.h"

/**
* @brief 将棋のリザルトシーン
*/
class ShogiResultScene : public ShogiSceneBase
{
	enum class ResultMenuList: unsigned char
	{
		MENU_SELECT,
		MENU_CONTINUE,
		MENU_END,
		MENU_MAX,
	};

public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	ShogiResultScene(const AttackTurn* whoseWin_, bool* gameEnd_, bool* contine_);

	/**
	* @brief   デストラクタ
	*/
	~ShogiResultScene(){}

	/**
	* @brief   更新関数
	* @details リザルトシーンの更新
	*/
	void Update() override;

	/**
	* @brief   描画関数
	* @details リザルトシーンの描画処理を行う
	*/
	void Draw() override;

	inline const ShogiSceneList GetScene() const override { return ShogiSceneList::SCENE_RESULT; }


private:
	/**
	* @brief   続けるかどうかを選択させる関数
	*/
	bool SelectContinue();

private:
	//! 誰が勝利したかを文字列で保存する変数
	std::string m_WhoseWin;

	//! 次に遷移するシーンの情報を保存する変数
	ShogiSceneList m_NextScene;

	__int8 CurrentSelectMenu;

	//! セレクト
	std::string SelectStr;
	std::string ContinueStr;
	std::string EndStr;

	bool* m_GameEnd;
	bool* m_Continue;

};

#endif