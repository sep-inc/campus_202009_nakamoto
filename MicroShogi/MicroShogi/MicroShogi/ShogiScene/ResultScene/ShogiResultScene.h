#ifndef SHOGI_RESULT_SCENE_H_
#define SHOGI_RESULT_SCENE_H_

#include "../ShogiSceneBase.h"
#include "../../ShogiObject/Definition.h"

/**
* @brief 将棋のリザルトシーン
*/
class ShogiResultScene : public ShogiSceneBase
{
	/**
	* @enum Enum
	* 結果出力後どのシーンに遷移するかのメニューリスト
	*/
	enum class ResultMenuList : unsigned char
	{
		MENU_SELECT,		// 選択シーン
		MENU_CONTINUE,		// もう一度
		MENU_END,			// ゲーム終了
	};
public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	ShogiResultScene(const MoveTrun* whoseWin_);

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

private:
	/**
	* @brief   続けるかどうかを選択させる関数
	*/
	bool SelectContinue();

private:
	//! 現在どの項目が選択されているかを保存する変数
	ResultMenuList m_CurrentSelectMenu;

	//! 誰が勝利したかを文字列で保存する変数
	std::string m_WhoseWin;

	//! 一度だけ行いたい処理を管理するための変数
	bool m_Onece;

};

#endif