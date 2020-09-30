#ifndef STAGE_H_
#define STAGE_H_

#include "Definition.h"
#include "Vec2.h"

/**
* @brief �X�e�[�W�N���X
*/
class Stage
{
public:
	/**
	* @brief   �R���X�g���N�^
	* @details �K�v�ȏ�������������
	*/
	Stage() :
		m_Stage{ 0 },
		m_Draw_Range_Min{ 0 },
		m_Draw_Range_Max{ 0 }
	{}

	/**
	* @brief   �f�X�g���N�^
	*/
	~Stage(){}

	/**
	* @brief   �������֐�
	* @details �Q�[���̏���������1�x�����Ă�
	*/
	void Init();

	/**
	* @brief   �`��֐��֐�
	* @details �X�e�[�W�ɕۑ�����
	*/
	void Draw();
 
	/**
	* @brief   �����蔻��֐��֐�
	* @details �v���C���[�̉E�̕ӂƃu���b�N�̍��̕ӂƂ̓����蔻��
	*/

	/**
	* @brief     �v���C���[�̉E�̕ӂƃu���b�N�̍��̕ӂƂ̓����蔻����s���֐�
	* @param[in] pos_    �v���C���[�̍��W
	* @param[in] width_  ����
	* @param[in] height_ �c��
	* @return  bool �������Ă�����True��Ԃ�
	*/
	bool HitPlyaerAndBlockLeftEdge(Vec2 pos_, __int8 width_, __int8 height_);

	/**
	* @brief     �v���C���[�̉��̕ӂƃu���b�N�̏�̕ӂƂ̓����蔻����s���֐�
	* @param[in]  pos_        �v���C���[�̍��W
	* @param[in]  width_      ����
	* @param[in]  height_     �c��
	* @param[out] contactPos_ ��������Y���̍��W��Ԃ�
	* @return  bool �������Ă�����True��Ԃ�
	*/
	bool HitPlayerAndBlockTopEdge(Vec2 pos_, __int8 width_, __int8 height_, float* contactPos_);
	
	/**
	* @brief      �X�e�[�W�ɃZ�b�g����֐�
	* @param[in]  pos_     ���W
	*/
	void SetStage(Vec2 pos_);

private:
	//! �X�e�[�W��ۑ�����ϐ�
	int m_Stage[STAGE_HEIGHT][STAGE_WIDTH];

	//! �`��͈͂̍��[��ۑ�����ϐ�
	int m_Draw_Range_Min;

	//! �`��͈͂̉E�[��ۑ�����ϐ�
	int m_Draw_Range_Max;

};

#endif