#ifndef GLOBALOBJECT_H_
#define GLOBALOBJECT_H_

/****************************************************
	header
*****************************************************/
#include "Ball.h"
#include "Wall.h"
#include "Block.h"
#include "Paddle.h"

/****************************************************
	define
*****************************************************/

/*------------ �X�e�[�W -----------------*/
// �X�e�[�W�̉���
#define STAGE_WIDTH  17

// �X�e�[�W�̍���
#define STAGE_HEIGHT 26

// �X�e�[�W�̍��[
#define STAGE_MIN_X 0

// �X�e�[�W�̉E�[
#define STAGE_MAX_X 15

// �X�e�[�W�̏�
#define STAGE_MIN_Y 0

// �X�e�[�W�̉�
#define STAGE_MAX_Y 24

/*------------ �{�[�� -------------------*/
// ����X���W
#define BALL_INIT_POS_X  7.5f

// ����Y���W
#define BALL_INIT_POS_Y  19.5f

// �{�[���̔��a
#define BALL_RADIUS		 0.5f

// �{�[���̑��x(1/60�t���[��)
#define BALL_SPEED		 0.5f

// �����̃{�[���̊p�x
#define BALL_INIT_ANGLE  60.0f


/*------------ �u���b�N -------------------*/
// ����u���b�N�̏����l
#define BLOCK_INIT_X  4

// ����u���b�N�̏����l
#define BLOCK_INIT_Y  4

// �u���b�N1�̉���
#define BLOCK_WIDTH   1

// �u���b�N1�̏c��
#define BLOCK_HEIGHT  1

// �u���b�N��X���̐�
#define BLOCK_NUM_X   7

// �u���b�N��Y���̐�
#define BLOCK_NUM_Y   3


/*------------ �p�h�� -------------------*/
// �p�h����X���W�̏����l
#define PADDLE_INIT_X 7.0f

// �p�h����Y���W�̏����l
#define PADDLE_INIT_Y 21.0f

// �p�h���̑��x(1/60�t���[��)
#define PADDLE_SPEED  0.5f

// �p�h���̉���
#define PADDLE_WIDTH  3

// �p�h���̏c��
#define PADDLE_HEIGHT 1

/*------------ �� -------------------*/
// ����
#define WALL_MIN_X  1

// �E��
#define WALL_MAX_X  14

// ���
#define WALL_MIN_Y  1

// ����
#define WALL_MAX_Y  23

// �ǂ̉���
#define WALL_WIDTH  15

// �ǂ̏c��
#define WALL_HEIGHT 24

/****************************************************
	extern
*****************************************************/

// [�{�[��]�I�u�W�F�N�̃g�C���X�^���X
extern Ball g_Ball;

// [��]�I�u�W�F�N�g�̃C���X�^���X
extern Wall g_Wall;

// [�u���b�N]�I�u�W�F�N�g�̃C���X�^���X
extern Block g_Block[BLOCK_NUM_Y][BLOCK_NUM_X];

// [�p�h��]�I�u�W�F�N�g�̃C���X�^���X
extern Paddle g_Paddle;

// �Q�[���I���t���O
// true�Ȃ�Q�[���I��
extern bool g_IsGameOver;


#endif