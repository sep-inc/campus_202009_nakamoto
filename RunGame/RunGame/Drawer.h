#ifndef DRAWER_H_
#define DRAWER_H_

#include "Definition.h"
#include <string>

/**
* @brief   �`��N���X
*/
class Drawer
{
public:
	/**
	* @brief   �R���X�g���N�^
	* @details �K�v�ȏ�������������
	*/
	Drawer() :
		m_DrawBuffer{ "\0" }
	{}

	/**
	* @brief   �f�X�g���N�^
	*/
	~Drawer() {}

	/**
	* @brief �ȒP�Ȑ����i�`����֐��j
	* @param[in] resouce_ �`�悷�郊�\�[�X(������)
	* @details �ڍׂȐ���
	*/
	void SetDrawBuffer(std::string resouce_);

	/**
	* @brief   �o�b�t�@�̃N���A
	* @details �������܂�Ă���o�b�t�@���N���A����
	*/
	void ClearBuffer();

	/**
	* @brief   �`��֐�
	* @details �o�b�t�@��`�悷��
	*/
	void DrawBuffer();

private:
	//! �`��o�b�t�@
	std::string m_DrawBuffer;

};
#endif