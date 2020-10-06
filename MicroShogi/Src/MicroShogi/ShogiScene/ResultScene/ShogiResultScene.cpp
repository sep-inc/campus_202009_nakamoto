#include "ShogiResultScene.h"
#include "../../Game/ShogiGame.h"
#include "../../System/Drawer.h"
#include "../../System/Input.h"

/*===================*/
/*　コンストラクタ   */
/*===================*/
ShogiResultScene::ShogiResultScene(const MoveTrun* whoseWin_):
	m_CurrentSelectMenu{ ResultMenuList::MENU_CONTINUE },
	m_WhoseWin {"\0"						   },
	m_Onece    {true                           }
{
	switch (*whoseWin_)
	{
	case MoveTrun::MOVE_FIRST:
		m_WhoseWin = "先手の勝利です！\n\n";
		break;

	case MoveTrun::MOVE_SECOND:
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
	m_DrawStr = m_WhoseWin;

	// 続けるかどうかを選択する
	if (SelectContinue() == true) {

		switch (m_CurrentSelectMenu)
		{
		case ResultMenuList::MENU_SELECT:
			ShogiGame::GetInstance().ChangeScene(ShogiSceneList::SCENE_SELECT);
			break;

		case ResultMenuList::MENU_CONTINUE:
			ShogiGame::GetInstance().ChangeScene(ShogiSceneList::SCENE_GAME);
			break;

		case ResultMenuList::MENU_END:
			exit(0);
			break;

		default:
			break;
		}

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
	// 何が選択されているかを保存する変数
	static __int8 menu;

	if (m_Onece) {
		// 出力用
		m_DrawStr += "↑↓キーで選ぶ  Spaceで確定\n";
		if (m_CurrentSelectMenu == ResultMenuList::MENU_SELECT) {
			m_DrawStr += "->セレクト\n";
			m_DrawStr += "  もう一度\n";
			m_DrawStr += "  終了\n";
		}
		else if (m_CurrentSelectMenu == ResultMenuList::MENU_CONTINUE) {
			m_DrawStr += "　セレクト\n";
			m_DrawStr += "->もう一度\n";
			m_DrawStr += "  終了\n";
		}
		else {
			m_DrawStr += "  セレクト\n";
			m_DrawStr += "  もう一度\n";
			m_DrawStr += "->終了\n";
		}

		m_Onece = false;
		return false;
	}

	int key = Input::GetKey();

	// もし↑キーなら
	if (key == 72) menu--;
	// もし↓キーなら
	else if (key == 80) menu++;
	// もしSpaceキーなら現在の情報を保存する
	else if (key == 32) return true;

	// 最小値を下回ったら戻す
	if (menu < static_cast<unsigned __int8>(ResultMenuList::MENU_SELECT)) menu = static_cast<unsigned __int8>(ResultMenuList::MENU_SELECT);
	// 最大値を上回ったら戻す
	if (menu > static_cast<unsigned __int8>(ResultMenuList::MENU_END))    menu = static_cast<unsigned __int8>(ResultMenuList::MENU_END);

	m_CurrentSelectMenu = static_cast<ResultMenuList>(menu);

	// 出力用
	m_DrawStr += "↑↓キーで選ぶ  Spaceで確定\n";
	if (m_CurrentSelectMenu == ResultMenuList::MENU_SELECT) {
		m_DrawStr += "->セレクト\n";
		m_DrawStr += "  もう一度\n";
		m_DrawStr += "  終了\n";
	}
	else if (m_CurrentSelectMenu == ResultMenuList::MENU_CONTINUE){
		m_DrawStr += "　セレクト\n";
		m_DrawStr += "->もう一度\n";
		m_DrawStr += "  終了\n";
	}
	else {
		m_DrawStr += "  セレクト\n";
		m_DrawStr += "  もう一度\n";
		m_DrawStr += "->終了\n";
	}

	return false;
}
