#include "ObjectBase.h"
#include "GrobalObject.h"

void ObjectBase::Select()
{
	while (true)
	{
		// ‰¡²‚ğ‘I‚Ô
		m_SelectX = SelectHorizontal();
		if (m_SelectX == -1) continue;

		// c²‚ğ‘I‚Ô
		m_SelectY = SelectVertical();
		if (m_SelectY == -1) continue;

		// ’u‚¯‚é‚©‚ğ’²‚×‚é
		if (g_Grid.Select(m_SelectX, m_SelectY, m_ObjectType) == true) {
			break;
		}
	}
}