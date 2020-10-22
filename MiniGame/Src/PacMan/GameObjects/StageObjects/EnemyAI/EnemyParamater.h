#ifndef ENEMY_ENEMY_PARAMETER_H_
#define ENEMY_ENEMY_PARAMETER_H_

#include "../../../../Utility/IVec2.h"
#include <vector>

enum class EnemyPersonalityList
{
	PERSONALITY_A,
	PERSONALITY_B,
	PERSONALITY_C,
};

enum class ActionStateList
{
	ACTION_SAUNTERING,	// 徘徊
	ACTION_DEFEND,		// アイテムを守る
	ACTION_CHASE,		// 追いかける

	ACTION_NUM,
};

struct EnemyParameter
{
	// エネミーの更新速度
	int m_Speed;

	// 現在の移動方向を保存する変数
	IVec2 m_Direction;

	// エネミーの性格
	EnemyPersonalityList m_Personality;

	std::vector<IVec2> m_TraceList;
};

#endif