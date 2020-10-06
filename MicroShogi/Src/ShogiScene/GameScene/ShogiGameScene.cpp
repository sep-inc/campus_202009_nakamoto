#include "ShogiGameScene.h"
#include "../../Game/ShogiGame.h"
#include "../../ShogiObject/ShogiPlayer/PC/ShogiPlayerPC.h"
#include "../../ShogiObject/ShogiPlayer/NPC/ShogiPlayerNPC.h"


/*===================*/
/*　コンストラクタ   */
/*===================*/
ShogiGameScene::ShogiGameScene(const ShogiPlayerType* first_, const ShogiPlayerType* second_, MoveTrun* whoseWin_) :
	m_ShogiPlayer{ nullptr }, m_WhoseWin{ whoseWin_ }, CurrentTurn{ MoveTrun::MOVE_FIRST }
{
	m_Board = new ShogiBoard();

	// ゲームクラスからもらった先手と後手の情報をもとに先手と後手の情報を初期化する
	if (*first_ == ShogiPlayerType::TYPE_PC) {
		m_ShogiPlayer[static_cast<unsigned __int8>(MoveTrun::MOVE_FIRST)] = new ShogiPlayerPC(m_Board, MoveTrun::MOVE_FIRST);
	}
	else {
		m_ShogiPlayer[static_cast<unsigned __int8>(MoveTrun::MOVE_FIRST)] = new ShogiPlayerNPC(m_Board, MoveTrun::MOVE_FIRST);
	}
	
	if (*second_ == ShogiPlayerType::TYPE_PC) {
		m_ShogiPlayer[static_cast<unsigned __int8>(MoveTrun::MOVE_SECOND)] = new ShogiPlayerPC(m_Board, MoveTrun::MOVE_SECOND);
	}
	else {
		m_ShogiPlayer[static_cast<unsigned __int8>(MoveTrun::MOVE_SECOND)] = new ShogiPlayerNPC(m_Board, MoveTrun::MOVE_SECOND);
	}

}


/*=========================*/
/*　　　　デストラクタ     */
/*=========================*/
ShogiGameScene::~ShogiGameScene()
{
	SAFE_DELETE(m_ShogiPlayer[static_cast<unsigned __int8>(MoveTrun::MOVE_FIRST)]);
	SAFE_DELETE(m_ShogiPlayer[static_cast<unsigned __int8>(MoveTrun::MOVE_SECOND)]);
	SAFE_DELETE(m_Board);

}


/*=====================*/
/*　    更新関数       */
/*=====================*/
void ShogiGameScene::Update()
{
	// 現在のターンの棋士の更新を行う
	if (m_ShogiPlayer[(int)CurrentTurn]) m_ShogiPlayer[(int)CurrentTurn]->Update();

	// 王が取られていたらそのターン行動していた側の勝利
	if (m_Board->KingWasTake() == true) {
		*m_WhoseWin = CurrentTurn;
		// リザルトシーンに切り替える
		ShogiGame::GetInstance().ChangeScene(ShogiSceneList::SCENE_RESULT);
	}

	// ターンを切り替える
	CurrentTurn = (CurrentTurn == MoveTrun::MOVE_FIRST) ? MoveTrun::MOVE_SECOND : MoveTrun::MOVE_FIRST;
}


/*=====================*/
/*　    描画関数       */
/*=====================*/
void ShogiGameScene::Draw()
{
	if (m_Board) m_Board->Draw();
}
