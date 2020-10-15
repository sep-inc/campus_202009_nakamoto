#include "PlayerBase.h"


/*====================*/
/*　 コンストラクタ   */
/*====================*/
MicroShogi::PlayerBase::PlayerBase(AttackTurn id_) :
	m_ref_shogi_board{ nullptr },
	m_attack_turn{ id_ },
	m_souce_pos{ 0,0 },
	m_dest_pos{ 0,0 },
	SelectedMoveSource{ false }
{}


/*=============*/
/*　更新関数   */
/*=============*/
bool MicroShogi::PlayerBase::Update()
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
