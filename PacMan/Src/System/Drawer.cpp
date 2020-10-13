#include "Drawer.h"
#include "../Definition.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

/*=============================================*/
/*    ����resouce_���o�b�t�@�ɏ������ފ֐�     */
/*                                             */
/* �����񂪊i�[����o�͂����̂ŉ��s�R�[�h��  */
/* �܂ߓn���K�v������                          */
/*=============================================*/
void Drawer::SetDrawBuffer(std::string resouce_)
{
	// �o�b�t�@�ɃR�s�[����
	m_StrDrawBuffer = resouce_;

	
}

void Drawer::SetDrawBuffer(int x_, int y_, const char* str_)
{
	strcpy_s(m_DrawBuffer[y_][x_], str_);
}


/*=======================================*/
/*�@�@�@�@�o�b�t�@���N���A����֐�     �@*/
/*=======================================*/
void Drawer::ClearBuffer()
{
	// �R�}���h���C���ɏo�͂���Ă��镶��������
	//system("cls");

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });

	// �o�b�t�@�����Z�b�g����
	m_StrDrawBuffer = "\0";
}


/*=====================================*/
/*�@�@�@  �o�b�t�@��`�悷��֐�  �@   */
/*=====================================*/
void Drawer::DrawBuffer()
{
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			m_StrDrawBuffer += m_DrawBuffer[y][x];
		}
		m_StrDrawBuffer += "\n";
	}

	// �o�b�t�@�Ɋi�[���Ă��镶������o�͂�
	std::cout << m_StrDrawBuffer << std::endl;
}
