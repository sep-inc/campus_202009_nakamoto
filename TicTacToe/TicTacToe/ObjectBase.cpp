#include "ObjectBase.h"
#include "GrobalObject.h"

void TicTacToe::ObjectBase::Select()
{
	while (true)
	{
		// 横軸を選ぶ
		m_SelectX = SelectHorizontal();
		if (m_SelectX == -1) continue;

		// 縦軸を選ぶ
		m_SelectY = SelectVertical();
		if (m_SelectY == -1) continue;

		// 置けるかを調べる
		if (g_Grid.Select(m_SelectX, m_SelectY, m_ObjectType) == true) {
			break;
		}
	}
}