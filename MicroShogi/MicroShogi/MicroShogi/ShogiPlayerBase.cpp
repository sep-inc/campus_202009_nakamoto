#include "ShogiPlayerBase.h"

/*=============*/
/*　更新関数   */
/*=============*/
void ShogiPlayerBase::Update()
{
	while (true)
	{
		if (SelectSource() == false) continue;

		if (SelectDest() == true) break;
	}
}
