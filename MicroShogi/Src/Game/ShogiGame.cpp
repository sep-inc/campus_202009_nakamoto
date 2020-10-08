#include "ShogiGame.h"
#include "../Scene/SelectScene/ShogiSelectScene.h"
#include "../Scene/GameScene/ShogiGameScene.h"
#include "../Scene/ResultScene/ShogiResultScene.h"

/*===================*/
/*　コンストラクタ   */
/*===================*/
ShogiGame::ShogiGame() :
	m_CurrentScene    {nullptr                        },
	m_FirstMovePlayer { ShogiPlayerType::TYPE_UNKNOWN },
	m_SecondMovePlayer{ ShogiPlayerType::TYPE_UNKNOWN },
	m_WhoseWin        { AttackTurn::ATTACK_FIRST          }
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
	switch (scene_)
	{
	case ShogiSceneList::SCENE_SELECT:
		SAFE_DELETE(m_CurrentScene);
		m_FirstMovePlayer  = ShogiPlayerType::TYPE_UNKNOWN;
		m_SecondMovePlayer = ShogiPlayerType::TYPE_UNKNOWN;
		m_CurrentScene     = new ShogiSelectScene(&m_FirstMovePlayer, &m_SecondMovePlayer);
		system("cls");
		break;

	case ShogiSceneList::SCENE_GAME:
		SAFE_DELETE(m_CurrentScene);
		m_CurrentScene = new ShogiGameScene(&m_FirstMovePlayer, &m_SecondMovePlayer, &m_WhoseWin);
		system("cls");
		break;

	case ShogiSceneList::SCENE_RESULT:
		SAFE_DELETE(m_CurrentScene);
		m_CurrentScene = new ShogiResultScene(&m_WhoseWin);
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
	if (m_CurrentScene) m_CurrentScene->Update();
}


/*=====================*/
/*　    描画関数       */
/*=====================*/
void ShogiGame::Draw()
{
	if (m_CurrentScene) m_CurrentScene->Draw();
}
