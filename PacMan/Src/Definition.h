#ifndef DIFINITION_H_
#define DIFINITION_H_

// �Z�[�t�f���[�g
#define SAFE_DELETE(p) { if (p != nullptr) { delete (p); (p) = nullptr; }}

// �P�̃e�X�g�p
#define PLAYER_ON
#define ENEMY_ON
#define ITEM_ON

// �X�e�[�W�̉���
#define STAGE_WIDTH  13

// �X�e�[�W�̏c��
#define STAGE_HEIGHT 13

// �v���C���[�̏����l
#define PLAYER_INIT_POS_X 3
#define PLAYER_INIT_POS_Y 6

// �G�̐�
#define ENEMY_NUM 3

// �A�C�e���̐�
#define ITEM_NUM  5

// �G�̑��x�@20 -> 20�t���[���Ɉ�x�s������
#define ENEMY_SPEED 20


// �I�u�W�F�N�g�̎���
enum class ObjectType : int
{
	TYPE_EMPTY,		// ��
	TYPE_WALL,		// ��
	TYPE_PLAYER,	// �v���C���[
	TYPE_ENEMY,		// �G
	TYPE_ITEM,		// �A�C�e��
};


#endif