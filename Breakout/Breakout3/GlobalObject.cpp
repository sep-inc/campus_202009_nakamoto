/****************************************************
	header
*****************************************************/
#include "GlobalObject.h"


/****************************************************
	�O���[�o���ϐ�
*****************************************************/

// [�{�[��]�I�u�W�F�N�g�C���X�^���X
Ball g_Ball;

// [��]�I�u�W�F�N�g�C���X�^���X
Wall g_Wall;

// [�u���b�N]�I�u�W�F�N�g�C���X�^���X
Block g_Block[BLOCK_NUM_Y][BLOCK_NUM_X];

// [�p�h��]�I�u�W�F�N�g�C���X�^���X
Paddle g_Paddle;

// �Q�[���I���t���O
// true�Ȃ�Q�[���I��
bool g_IsGameOver = false;