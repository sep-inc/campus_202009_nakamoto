#include "ShogiGame.h"
#include "../Scene/SelectScene/ShogiSelectScene.h"
#include "../Scene/GameScene/ShogiGameScene.h"
#include "../Scene/ResultScene/ShogiResultScene.h"
#include "../../Utility/SafeDelete.h"

/*===================*/
/*　コンストラクタ   */
/*===================*/
ShogiGame::ShogiGame() :
	m_CurrentScene    {nullptr                        },
	m_FirstMovePlayer { ShogiPlayerType::TYPE_UNKNOWN },
	m_SecondMovePlayer{ ShogiPlayerType::TYPE_UNKNOWN },
	m_WhoseWin        { AttackTurn::ATTACK_FIRST      },
	m_Continue{ false }
{ 
	m_CurrentScene = new ShogiSelectScene(&m_FirstMovePlayer, &m_SecondMovePlayer);
}


/*===================*/
/*　　デストラクタ   */
/*===================*/
ShogiGame::~ShogiGame()
{
	SAFE_DELETE(m_CurrentScene);
}


/*===========================*/
/*　引数付きコンストラクタ   */
/*===========================*/
void ShogiGame::ChangeScene(ShogiSceneList scene_)
{
	// 現在のsceneを参照
	switch (scene_)
	{
		// セレクトシーンならゲームシーンに遷移
	case ShogiSceneList::SCENE_SELECT:
		SAFE_DELETE(m_CurrentScene);

		m_CurrentScene = new ShogiGameScene(&m_FirstMovePlayer, &m_SecondMovePlayer, &m_WhoseWin);
		system("cls");
		break;

	case ShogiSceneList::SCENE_GAME:
		SAFE_DELETE(m_CurrentScene);
		m_CurrentScene = new ShogiResultScene(&m_WhoseWin, &m_IsEnd, &m_Continue);
		system("cls");
		break;

	case ShogiSceneList::SCENE_RESULT:
		SAFE_DELETE(m_CurrentScene);

		if (!m_IsEnd) {
			if (m_Continue) {
				m_CurrentScene = new ShogiGameScene(&m_FirstMovePlayer, &m_SecondMovePlayer, &m_WhoseWin);
			}
			else {
				m_FirstMovePlayer = ShogiPlayerType::TYPE_UNKNOWN;
				m_SecondMovePlayer = ShogiPlayerType::TYPE_UNKNOWN;
				m_CurrentScene = new ShogiSelectScene(&m_FirstMovePlayer, &m_SecondMovePlayer);
			}
		}
		system("cls");
		break;

	default:
		break;
	}
}


/*=====================*/
/*　    更新関数       */
/*=====================*/
void ShogiGame::Update()
{
	if (!m_CurrentScene) return;

	m_CurrentScene->Update();
	
	if (m_CurrentScene->EndScene() == true) {
		this->ChangeScene(m_CurrentScene->GetScene());
	}
}


/*=====================*/
/*　    描画関数       */
/*=====================*/
void ShogiGame::Draw()
{
	if (m_CurrentScene) m_CurrentScene->Draw();
}
