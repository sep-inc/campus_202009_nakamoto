#include "ShogiPlayerBase.h"

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
