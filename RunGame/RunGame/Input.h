#ifndef INPUT_H_
#define INPUT_H_

/**
* @enum Enum
* ���͂ɂ����L�[���
*/
enum class KeyList : int
{
	R_KEY = 'R',
};

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
	int GetKey();

	/**
	* @brief       ���͊֐�
	* @param[in]   key_�@KeyList�ɗ񋓂���Ă���L�[���
	* @return bool ������Ă�����true��Ԃ�
	* @details     �����̃L�[��������Ă����true��Ԃ�
	*/
	bool GetKey(KeyList key_);
	
};

#endif