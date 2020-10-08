#include "ShogiPlayerBase.h"


/*====================*/
/*　 コンストラクタ   */
/*====================*/
ShogiPlayerBase::ShogiPlayerBase(ShogiBoard* board_, MoveTrun id_) :
	m_RefBoard	{ board_ },
	m_Id		{ id_	 },
	m_MoveSource{ 0,0	 },
	SelectedMoveSource{ false }
{}


/*=============*/
/*　更新関数   */
/*=============*/
bool ShogiPlayerBase::Update()
{
	static bool selected = false;

	if (SelectedMoveSource == false) {
		SelectedMoveSource = SelectSource();
	}
	else if (SelectDest(&selected) == false) {
		if (selected == true) {
			SelectedMoveSource = false;
		}
	}
	else {
		SelectedMoveSource = false;
		return true;
	}

	return false;
}
