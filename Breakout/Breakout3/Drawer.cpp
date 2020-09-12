/****************************************************
	header
*****************************************************/
#include "Drawer.h"
#include "GlobalObject.h"

#include <stdio.h>
#include <string.h>

/****************************************************
	�R���X�g���N�^
*****************************************************/
Drawer::Drawer()
{
	// �S�Ă�0�ŏ���������
	memset(m_ClearBuffer, 0, sizeof(m_ClearBuffer));

	// ������u���b�N���Ŗ��߂�
	for (int x = 0; x < STAGE_WIDTH; ++x) {
		m_ClearBuffer[0][x] = (__int8)ObjectType::ObjectWall;
		m_ClearBuffer[STAGE_HEIGHT - 1][x] = (__int8)ObjectType::ObjectWall;
	}

	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		m_ClearBuffer[y][0] = (__int8)ObjectType::ObjectWall;
		m_ClearBuffer[y][STAGE_WIDTH - 1] = (__int8)ObjectType::ObjectWall;
	}

}

/****************************************************
		�o�b�t�@�̃N���A�֐�
*****************************************************/
void Drawer::ClearBuffer()
{
	memcpy(&m_DrawBuffer, &m_ClearBuffer, sizeof(m_ClearBuffer));
}

/****************************************************
	�o�b�t�@�ɏ������ފ֐�
*****************************************************/
void Drawer::WriteBuffer(float posX_, float posY_, __int8 objectType_)
{
	m_DrawBuffer[(int)posY_+1][(int)posX_+1] = objectType_;
}

/****************************************************
	�o�b�t�@�ɏ������ފ֐�
*****************************************************/
void Drawer::WriteBuffer(float posX_, float posY_, float width_, float height_, __int8 objectType_)
{
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			m_DrawBuffer[(int)posY_ + y + 1][(int)posX_ + x + 1] = objectType_;
		}
	}
}

/****************************************************
		�o�b�t�@�̕`��֐�
*****************************************************/
void Drawer::DrawBuffer()
{
	char str_buffer[STAGE_HEIGHT * STAGE_WIDTH * sizeof("�@")] = { "\0" };

	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {

			switch (m_DrawBuffer[y][x])
			{
			case ObjectType::ObjectBall:
				strcat_s(str_buffer, "��");
				break;

			case ObjectType::ObjectBlock:
				strcat_s(str_buffer, "��");
				break;

			case ObjectType::ObjectPaddle:
				strcat_s(str_buffer, "�[");
				break;

			case ObjectType::ObjectWall:
				strcat_s(str_buffer, "��");
				break;

			default:
				strcat_s(str_buffer, "�@");
				break;
			}
		}
		strcat_s(str_buffer, "\n");
	}

	printf("%s", str_buffer);
}
