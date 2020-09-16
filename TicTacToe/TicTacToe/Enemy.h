#ifndef ENEMY_H_
#define ENEMY_H_

#include "ObjectBase.h"

class Enemy : public ObjectBase
{
	// エネミーのステップ項目
	enum class EnemyStep : unsigned char
	{
		STEP_INIT,		// 初期化ステップ
		STEP_UPDATE,	// 更新ステップ
		STEP_RELEASE,	// 解放ステップ
	};


public:
	// コンストラクタ
	Enemy():
		ObjectBase(ObjectType::TYPE_ENEMY),
		m_CurrentStep(EnemyStep::STEP_INIT)
	{}

	// デストラクタ
	~Enemy(){}


	// ステップの更新関数
	void StepUpdate() override;


private:
	// どのマスに置くかを選ぶ関数
	void Select() override;

	// どのマスの横軸に置くかを決める関数
	__int8 SelectHorizontal() override;

	// どのマスの縦軸に置くかを決める関数
	__int8 SelectVertical() override;


private:
	// 現在のステップを保存する変数
	EnemyStep m_CurrentStep;

};

#endif