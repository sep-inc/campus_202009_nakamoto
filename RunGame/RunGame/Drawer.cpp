#include "Drawer.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>

/*=============================================*/
/*    ����resouce_���o�b�t�@�ɏ������ފ֐�     */
/*                                             */
/* �����񂪊i�[����o�͂����̂ŉ��s�R�[�h��  */
/* �܂ߓn���K�v������                          */
/*=============================================*/
void Drawer::SetDrawBuffer(std::string resouce_)
{
	// �o�b�t�@�ɃR�s�[����
	m_DrawBuffer = resouce_;
}


/*=======================================*/
/*�@�@�@�@�o�b�t�@���N���A����֐�     �@*/
/*=======================================*/
void Drawer::ClearBuffer()
{
	// �R�}���h���C���ɏo�͂���Ă��镶��������
	system("cls");
	// �o�b�t�@�����Z�b�g����
	m_DrawBuffer = "\0";
}


/*=====================================*/
/*�@�@�@  �o�b�t�@��`�悷��֐�  �@   */
/*=====================================*/
void Drawer::DrawBuffer()
{
	// �o�b�t�@�Ɋi�[���Ă��镶������o�͂�
	std::cout << m_DrawBuffer << std::endl;
}
