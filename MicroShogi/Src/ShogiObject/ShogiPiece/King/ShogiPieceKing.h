#ifndef SHOGIPIECEKING_H_
#define SHOGIPIECEKING_H_

#include "../ShogiPieceBase.h"

/**
* @brief �y��z���N���X
*/
class ShogiPieceKing : public ShogiPieceBase
{
public:
	/**
	* @brief   �R���X�g���N�^
	*/
	ShogiPieceKing();

	/**
	* @brief   �f�X�g���N�^
	*/
	~ShogiPieceKing() {}


	/**
	* @brief ���g�̋�̏���Ԃ��֐�
	* @return  const ShogiPiece�@���g�̋�̎��
	*/
	inline const ShogiPiece GetShogiPiece() const override { return ShogiPiece::PIECE_KING; }

	/**
	* @brief ��̕`��ɕK�v�ȃ��\�[�X��Ԃ��֐�
	* @param[in] id_ ��肩���̏��
	* @return  const char* ��̕`��p�����񂪕Ԃ�
	*/
	virtual const char* GetResouce(MoveTrun id_) const override;

private:
	//! �ړ��\�͈͂�ۑ�����ϐ�
	static const bool m_MovableRange[4][3];

};

#endif