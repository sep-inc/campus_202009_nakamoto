#ifndef DEFINITION_H_
#define DEFINITION_H_

// �d��
#define GRAVITY           0.07
// �����x
#define INITIAL_VELOCITY  0.6

// �v���C���[���x
#define PLAYER_SPEED      0.2
// �v���C���[����X���W
#define PLAYER_INIT_POS_X 1.0
// �v���C���[�̉���
#define PLAYER_WIDTH      1
// �v���C���[�̏c��
#define PLAYER_HEIGHT     2

// �S�[���n�_
#define GOAL_POS          300.0

// �u���b�N�̃T�C�Y(�����`)
#define BLCOK_SIZE        1
// �X�e�[�W�̉��̒���
#define STAGE_WIDTH       320
// �X�e�[�W�̏c�̒���
#define STAGE_HEIGHT      10

// �X�e�[�W�̉��̕`��͈�
#define DRAW_RANGE_WIDTH  11
// �X�e�[�W�̏c�̕`��͈�
#define DRAW_RANGE_HEIGHT 10


//! �Q�[�����I���������ǂ�����ۑ�����ϐ�
extern bool g_GameEnd;

//! �Q�[�����N���A�������ǂ�����ۑ�����ϐ�
extern bool g_GameClear;

#endif