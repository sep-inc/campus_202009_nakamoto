#include "ShogiResultScene.h"
#include "../../Game/ShogiGame.h"
#include "../../System/Drawer.h"
#include "../../System/Input.h"

/*===================*/
/*　コンストラクタ   */
/*===================*/
ShogiResultScene::ShogiResultScene(const AttackTurn* whoseWin_) :
	m_WhoseWin{ "\0" }, CurrentSelectMenu{ 0 }, m_NextScene{ ShogiSceneList::SCENE_SELECT }
{
	switch (*whoseWin_)
	{
	case AttackTurn::ATTACK_FIRST:
		m_WhoseWin = "先手の勝利です！\n\n";
		break;

	case AttackTurn::ATTACK_SECOND:
		m_WhoseWin = "後手の勝利です！\n\n";
		break;
	default:
		break;
	}
}


/*=====================*/
/*　    更新関数       */
/*=====================*/
void ShogiResultScene::Update()
{
	// 結果を書き込む
	m_DrawStr   = m_WhoseWin;
	SelectStr   = "  セレクト\n";
	ContinueStr = "  もう一度\n";
	EndStr      = "  終了\n";

	// 続けるかどうかを選択する
	if (SelectContinue() == true) {
		// 終了が選ばれたらプログラムを終了させる
		if (m_NextScene == ShogiSceneList::SCENE_UNKNOWN) {
			exit(0);
		}

		// 選択されたシーンへ遷移する
		ShogiGame::GetInstance().ChangeScene(m_NextScene);
	}
	
}


/*=====================*/
/*　    描画関数       */
/*=====================*/
void ShogiResultScene::Draw()
{
	Drawer::GetInstance().SetDrawBuffer(m_DrawStr);
}


/*=================================================*/
/*　選択した場所に移動可能かどうかを判定する関数   */
/*=================================================*/
bool ShogiResultScene::SelectContinue()
{
	int key = Input::GetKey();

	// もし↑キーなら
	if (key == KEY_UP) CurrentSelectMenu--;
	// もし↓キーなら
	else if (key == KEY_DOWN) CurrentSelectMenu++;
	// もしSpaceキーなら現在の情報を保存する
	else if (key == KEY_SPACE) return true;

	// 最小値を下回ったら戻す
	if (CurrentSelectMenu < 0) CurrentSelectMenu = 0;
	// 最大値を上回ったら戻す
	if (CurrentSelectMenu > 2) CurrentSelectMenu = 2;

	if (CurrentSelectMenu      == (__int8)ResultMenuList::MENU_SELECT)	 { m_NextScene = ShogiSceneList::SCENE_SELECT;  }
	else if (CurrentSelectMenu == (__int8)ResultMenuList::MENU_CONTINUE) { m_NextScene = ShogiSceneList::SCENE_GAME;    }
	else if (CurrentSelectMenu == (__int8)ResultMenuList::MENU_END)		 { m_NextScene = ShogiSceneList::SCENE_UNKNOWN; }

	// 出力用
	m_DrawStr += "↑↓キーで選ぶ  Spaceで確定\n";

	if (CurrentSelectMenu      == (__int8)ResultMenuList::MENU_SELECT)   { SelectStr = "->セレクト\n";   }
	else if (CurrentSelectMenu == (__int8)ResultMenuList::MENU_CONTINUE) { ContinueStr = "->もう一度\n"; }
	else if (CurrentSelectMenu == (__int8)ResultMenuList::MENU_END)      { EndStr = "->終了\n";          }

	m_DrawStr += SelectStr + ContinueStr + EndStr;

	return false;
}
