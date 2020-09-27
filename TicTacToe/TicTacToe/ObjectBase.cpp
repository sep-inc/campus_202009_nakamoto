#include "ObjectBase.h"
#include "GrobalObject.h"

void ObjectBase::Select()
{
	while (true)
	{
		// ������I��
		m_SelectX = SelectHorizontal();
		if (m_SelectX == -1) continue;

		// �c����I��
		m_SelectY = SelectVertical();
		if (m_SelectY == -1) continue;

		// �u���邩�𒲂ׂ�
		if (g_Grid.Select(m_SelectX, m_SelectY, m_ObjectType) == true) {
			break;
		}
	}
}