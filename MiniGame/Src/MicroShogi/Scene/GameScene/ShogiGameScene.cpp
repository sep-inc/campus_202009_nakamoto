#include "ShogiGameScene.h"
#include "../../Game/ShogiGame.h"
#include "../../Object/ShogiPlayer/PC/ShogiPlayerPC.h"
#include "../../Object/ShogiPlayer/NPC/ShogiPlayerNPC.h"
#include "../../../Utility/SafeDelete.h"

/*===================*/
/*　コンストラクタ   */
/*===================*/ 
ShogiGameScene::ShogiGameScene(const ShogiPlayerType* first_, const ShogiPlayerType* second_, AttackTurn* whoseWin_) :
	m_player{ nullptr }, m_WhoseWin{ whoseWin_ }, CurrentTurn{ AttackTurn::ATTACK_FIRST }
{
	m_board = new ShogiBoard();

	// ゲームクラスからもらった先手と後手の情報をもとに先手と後手の情報を初期化する
	if (*first_ == ShogiPlayerType::TYPE_PC) {
		m_player[static_cast<unsigned __int8>(AttackTurn::ATTACK_FIRST)] = new MicroShogi::ShogiPlayerPC(AttackTurn::ATTACK_FIRST);
	}
	else {
		m_player[static_cast<unsigned __int8>(AttackTurn::ATTACK_FIRST)] = new MicroShogi::ShogiPlayerNPC(AttackTurn::ATTACK_FIRST);
	}
	
	if (*second_ == ShogiPlayerType::TYPE_PC) {
		m_player[static_cast<unsigned __int8>(AttackTurn::ATTACK_SECOND)] = new MicroShogi::ShogiPlayerPC(AttackTurn::ATTACK_SECOND);
	}
	else {
		m_player[static_cast<unsigned __int8>(AttackTurn::ATTACK_SECOND)] = new MicroShogi::ShogiPlayerNPC(AttackTurn::ATTACK_SECOND);
	}

	m_player[(uint8_t)AttackTurn::ATTACK_FIRST]->SetBoard(m_board);
	m_player[(uint8_t)AttackTurn::ATTACK_SECOND]->SetBoard(m_board);
}


/*=========================*/
/*　　　　デストラクタ     */
/*=========================*/
ShogiGameScene::~ShogiGameScene()
{
	SAFE_DELETE(m_player[static_cast<uint8_t>(AttackTurn::ATTACK_FIRST)]);
	SAFE_DELETE(m_player[static_cast<uint8_t>(AttackTurn::ATTACK_SECOND)]);
	SAFE_DELETE(m_board);

}


/*=====================*/
/*　    更新関数       */
/*=====================*/
void ShogiGameScene::Update()
{
	bool turn_end = false;

	// 現在のターンの棋士の更新を行う
	if (m_player[(int)CurrentTurn]) {
		turn_end = m_player[(int)CurrentTurn]->Update();
	}

	// 王が取られていたらそのターン行動していた側の勝利
	if (turn_end && m_board->KingWasTake() == true) {
		*m_WhoseWin = CurrentTurn;
		// リザルトシーンに切り替える
		ShogiGame::GetInstance().ChangeScene(ShogiSceneList::SCENE_RESULT);
	}

	// ターンを切り替える
	if (turn_end)CurrentTurn = (CurrentTurn == AttackTurn::ATTACK_FIRST) ? AttackTurn::ATTACK_SECOND : AttackTurn::ATTACK_FIRST;
}


/*=====================*/
/*　    描画関数       */
/*=====================*/
void ShogiGameScene::Draw()
{
	if (m_board) m_board->Draw();
}
