#ifndef STAGE_H_
#define STAGE_H_

#include "../PacManDefinition.h"
#include "../../Utility/IVec2.h"
#include "StageObjects/ItemArray.h"

namespace PacMan
{
	// �X�e�[�W���������N���X
	class Stage
	{
	public:
		/*
			�R���X�g���N�^
		*/
		Stage();

		/*
			�f�X�g���N�^
		*/
		~Stage();

		/*
			�������֐�
		*/
		void Init();

		/*
			�`��֐�
		*/
		void Draw();

		/*
			�I�u�W�F�N�g�������_���ɔz�u����֐�
		*/
		void SetRandomPlacementObject(StageObject* stageObject_);

		/*
			�����ɐݒ肵�����W�ɂǂ̃I�u�W�F�N�g������̂���Ԃ��֐�
		*/
		const ObjectType GetStageObject(IVec2 pos_) const { return m_Stage[pos_.m_Y][pos_.m_X]; }

		/*
			�A�C�e���Ɠ������Ă��邩�𒲂ׂ�֐�
			�������Ă����ꍇ�A�C�e��������
		*/
		bool HitItem(IVec2 pos_);

		/*
			�I�u�W�F�N�g�̈ړ���X�e�[�W�ɃZ�b�g����֐�

			moveSource_ �ړ���
			moveDest_   �ړ���
			type_       �I�u�W�F�N�g�̎��
		*/
		void SetStage(IVec2 moveSource_, IVec2 moveDest_, PacMan::ObjectType type_);

		/*
			�A�C�e�������݂��邩�ǂ�����Ԃ��֐�
		*/
		bool EmptyItem();

		/*
			�v���C���[�ƃG�l�~�[�������������ǂ�����Ԃ��֐�
		*/
		bool HitPlayerAndEnemy()const { return m_IsGameOver; }

	private:
		// �������p�̋�̃X�e�[�W�f�[�^
		static const int m_BlankStage[STAGE_HEIGHT][STAGE_WIDTH];

		// �X�e�[�W�̏���ۑ�����ϐ�
		PacMan::ObjectType m_Stage[STAGE_HEIGHT][STAGE_WIDTH];

		ItemArray* m_ItemArray;

		// �v���C���[�ƓG�������������ǂ�����ۑ�����ϐ�
		bool m_IsGameOver;

	};
}

#endif