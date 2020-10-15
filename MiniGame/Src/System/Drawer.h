#ifndef DRAWER_H_
#define DRAWER_H_

#include <string>

/**
* @brief   �`��N���X
*/
class Drawer
{
public:
	static Drawer& GetInstance() {
		static Drawer instance;
		return instance;
	}

	/**
	* @brief �ȒP�Ȑ����i�`����֐��j
	* @param[in] resouce_ �`�悷�郊�\�[�X(������)
	* @details �ڍׂȐ���
	*/
	void SetDrawBuffer(std::string resouce_);

	void SetDrawBuffer(int x_, int y_, const char* str_);

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


private:
	char m_DrawBuffer[30][20][10];

	//! �A���p�`��o�b�t�@
	std::string m_StrDrawBuffer;

};

#endif