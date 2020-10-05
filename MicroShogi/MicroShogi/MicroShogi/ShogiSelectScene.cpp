#include "ShogiSelectScene.h"
#include "ShogiGame.h"
#include "Input.h"
#include "Drawer.h"

/*===================*/
/*　コンストラクタ   */
/*===================*/
ShogiSelectScene::ShogiSelectScene(ShogiPlayerType* first_, ShogiPlayerType* second_) :
	m_FirstMovePlayer { nullptr },
	m_SecondMovePlayer{ nullptr },
	m_Onece           { true    }
{
	m_FirstMovePlayer  = first_;
	m_SecondMovePlayer = second_;
}


/*=====================*/
/*　    更新関数       */
/*=====================*/
void ShogiSelectScene::Update()
{

	if (*m_FirstMovePlayer == ShogiPlayerType::TYPE_UNKNOWN) {
		m_DrawStr = "先手を選択してください\n";
		SelectPlayer(m_FirstMovePlayer);
	}
	else if (*m_SecondMovePlayer == ShogiPlayerType::TYPE_UNKNOWN) {
		m_DrawStr = "後手を選択してください\n";
		SelectPlayer(m_SecondMovePlayer);
	}
	else if (IsConfirm() == true) {
		//  ゲームシーンに遷移
		ShogiGame::GetInstance().ChangeScene(ShogiSceneList::SCENE_GAME);
	}
}


/*=================================================*/
/*　　　　　　　PCかNPCを選択する関数   　　　　　 */
/*=================================================*/
void ShogiSelectScene::SelectPlayer(ShogiPlayerType* player_)
{
	// どちらが選ばれているかを保存する変数
	static bool is_pc = true;

	if (m_Onece) {
		// 出力用
		m_DrawStr += "↑↓キーで選ぶ  Spaceで確定\n";
		if (is_pc) {
			m_DrawStr += "->PC\n";
			m_DrawStr += "  NPC\n";
		}
		else {
			m_DrawStr += "  PC\n";
			m_DrawStr += "->NPC\n";
		}

		m_Onece = false;
		return;
	}

	int key = Input::GetKey();

	// もし↑キーならPCが選ばれている
	if (key == 72) is_pc = true;
	// もし↓キーなら
	else if (key == 80) is_pc = false;
	// もしSpaceキーなら現在の情報を保存する
	else if (key == 32) {
		*player_ = is_pc ? ShogiPlayerType::TYPE_PC : ShogiPlayerType::TYPE_NPC;
		m_Onece = true;
	}

	// 出力用
	m_DrawStr += "↑↓キーで選ぶ  Spaceで確定\n";
	if (is_pc) {
		m_DrawStr += "->PC\n";
		m_DrawStr += "  NPC\n";
	}
	else {
		m_DrawStr += "  PC\n";
		m_DrawStr += "->NPC\n";
	}
}


/*======================================================================*/
/*　先手後手の棋士情報選択後、情報を確定させるかどうかを選択させる関数  */
/*======================================================================*/

bool ShogiSelectScene::IsConfirm()
{

	// 確定かどうかを保存する変数
	static bool confirm = true;

	if (m_Onece) {
		m_DrawStr = "↑↓キーで選ぶ  Spaceで確定\n";
		if (confirm) {
			m_DrawStr += "->はい\n";
			m_DrawStr += "  いいえ\n";
		}
		else {
			m_DrawStr += "  はい\n";
			m_DrawStr += "->いいえ\n";
		}

		m_Onece = false;
		return false;
	}


	// キー入力
	int key = Input::GetKey();

	// もし↑キーならはいが選ばれている
	if (key == 72) confirm = true;
	// もし↓キーならいいえが選ばれている
	else if (key == 80) confirm = false;
	// もしSpaceキーなら
	else if (key == 32) {
		// 確定かどうかを調べる
		if (confirm) {
			// 確定ならtrueを返す
			return true;
		}
		else {
			// 確定じゃないならリセットする
			*m_FirstMovePlayer  = ShogiPlayerType::TYPE_UNKNOWN;
			*m_SecondMovePlayer = ShogiPlayerType::TYPE_UNKNOWN;
			m_Onece = true;
			return false;
		}
	}

	// 出力用
	m_DrawStr = "↑↓キーで選ぶ  Spaceで確定\n";
	if (confirm) {
		m_DrawStr += "->はい\n";
		m_DrawStr += "  いいえ\n";
	}
	else {
		m_DrawStr += "  はい\n";
		m_DrawStr += "->いいえ\n";
	}
	
	return false;
}


/*=====================*/
/*　    描画関数       */
/*=====================*/
void ShogiSelectScene::Draw()
{
	// 描画クラスに文字列を送る
	Drawer::GetInstance().SetDrawBuffer(m_DrawStr);
}

