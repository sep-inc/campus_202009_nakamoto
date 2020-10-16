#include "ShogiSelectScene.h"
#include "../../Game/ShogiGame.h"
#include "../../../System/Input.h"
#include "../../../System/Drawer.h"

/*===================*/
/*　コンストラクタ   */
/*===================*/
ShogiSelectScene::ShogiSelectScene(ShogiPlayerType* first_, ShogiPlayerType* second_) :
	m_FirstMovePlayer { nullptr },
	m_SecondMovePlayer{ nullptr }
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
		m_DrawStr = "先攻の棋士の種類を選択してください\n";
		SelectPlayer(m_FirstMovePlayer);
	}
	else if (*m_SecondMovePlayer == ShogiPlayerType::TYPE_UNKNOWN) {
		m_DrawStr = "後攻の棋士の種類を選択してください\n";
		SelectPlayer(m_SecondMovePlayer);
	}
	else if (IsConfirm() == true) {
		//  ゲームシーンに遷移
		m_EndScene = true;

	}
}


/*=================================================*/
/*　　　　　　　PCかNPCを選択する関数   　　　　　 */
/*=================================================*/
void ShogiSelectScene::SelectPlayer(ShogiPlayerType* player_)
{
	// どちらが選ばれているかを保存する変数
	static bool is_pc = true;

	int key = Input::GetKey();

	// もし↑キーならPCが選ばれている
	if (key == KEY_UP) is_pc = true;
	// もし↓キーなら
	else if (key == KEY_DOWN) is_pc = false;
	// もしSpaceキーなら現在の情報を保存する
	else if (key == KEY_SPACE) {
		*player_ = is_pc ? ShogiPlayerType::TYPE_PC : ShogiPlayerType::TYPE_NPC;

		is_pc = true;
		m_DrawStr = "";
		system("cls");
		return;
	}

	// 出力用
	m_DrawStr += "十字キーで選択  Spaceで確定\n";
	if (is_pc) {
		m_DrawStr += "->プレイヤー    \n";
		m_DrawStr += "  コンピューター\n";
	}
	else {
		m_DrawStr += "  プレイヤー    \n";
		m_DrawStr += "->コンピューター\n";
	}
}


/*======================================================================*/
/*　先手後手の棋士情報選択後、情報を確定させるかどうかを選択させる関数  */
/*======================================================================*/

bool ShogiSelectScene::IsConfirm()
{

	// 確定かどうかを保存する変数
	static bool confirm = true;
	std::string first;
	std::string second;
	first  = *m_FirstMovePlayer  == ShogiPlayerType::TYPE_PC ? "プレイヤー\n" : "コンピューター\n";
	second = *m_SecondMovePlayer == ShogiPlayerType::TYPE_PC ? "プレイヤー\n" : "コンピューター\n";

	// キー入力
	int key = Input::GetKey();

	// もし↑キーならはいが選ばれている
	if (key == KEY_UP) confirm = true;
	// もし↓キーならいいえが選ばれている
	else if (key == KEY_DOWN) confirm = false;
	// もしSpaceキーなら
	else if (key == KEY_SPACE) {
		// 確定かどうかを調べる
		if (confirm) {
			// 確定ならtrueを返す
			return true;
		}
		else {
			// 確定じゃないならリセットする
			*m_FirstMovePlayer  = ShogiPlayerType::TYPE_UNKNOWN;
			*m_SecondMovePlayer = ShogiPlayerType::TYPE_UNKNOWN;
			m_DrawStr = "";
			system("cls");
			return false;
		}
	}

	// 出力用
	m_DrawStr += "\r                                    \r";
	m_DrawStr  = "先攻 -> " + first;
	m_DrawStr += "\r                                    \r";
	m_DrawStr += "後攻 -> " + second;
	m_DrawStr += "選択を確定してよろしいですか？\n";
	m_DrawStr += "十字キーで選択  Spaceで確定\n";
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

