#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>

#define KEY_UP		72	
#define KEY_DOWN	80
#define KEY_RIGHT	77
#define KEY_LEFT	75
#define KEY_SPACE	32

/**
* @brief   �C���v�b�g�N���X
* @details ���͂��Ǘ�����N���X
*/
class Input
{
public:
	/**
	* @brief       ���͊֐�
	* @return int  ASCII�R�[�h�\�ɑΉ�����10�i�����Ԃ�
	* @details     ���͂��ꂽ������ASCII�R�[�h�\�ɑΉ�����10�i����Ԃ�
	*/
	static int GetKey();

};

#endif