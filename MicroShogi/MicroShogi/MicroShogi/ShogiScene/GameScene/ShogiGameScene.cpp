#include "ShogiGameScene.h"
#include "../../Game/ShogiGame.h"
#include "../../ShogiObject/ShogiPlayer/PC/ShogiPlayerPC.h"
#include "../../ShogiObject/ShogiPlayer/NPC/ShogiPlayerNPC.h"


/*===================*/
/*　コンストラクタ   */
/*===================*/
ShogiGameScene::ShogiGameScene(const ShogiPlayerType* first_, const ShogiPlayerType* second_, MoveTrun* whoseWin_):
	m_ShogiPlayer{nullptr}, m_WhoseWin{ whoseWin_ }, m_TrunCount{0}
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
	m_TrunCount++;

	// 奇数なら先手の更新
	if (m_TrunCount % 2 == 1) {
		if (m_ShogiPlayer[(int)MoveTrun::MOVE_FIRST]) m_ShogiPlayer[(int)MoveTrun::MOVE_FIRST]->Update();
	}
	// 偶数なら後手の更新
	else {
		if (m_ShogiPlayer[(int)MoveTrun::MOVE_SECOND]) m_ShogiPlayer[(int)MoveTrun::MOVE_SECOND]->Update();
	}

	// 王が取られていたらそのターン行動していた側の勝利
	if (m_Board->KingWasTake() == true) {
		*m_WhoseWin = m_TrunCount % 2 == 1 ? MoveTrun::MOVE_FIRST : MoveTrun::MOVE_SECOND;
		ShogiGame::GetInstance().ChangeScene(ShogiSceneList::SCENE_RESULT);
	}
}


/*=====================*/
/*　    描画関数       */
/*=====================*/
void ShogiGameScene::Draw()
{
	if (m_Board) {
		if (m_TrunCount % 2 == 1) {
			// 先手ターンなら後手を描画
			m_Board->Draw(MoveTrun::MOVE_SECOND);
		}
		else {
			// 後手ターンなら先手を描画
			m_Board->Draw(MoveTrun::MOVE_FIRST);
		}
	}
}
