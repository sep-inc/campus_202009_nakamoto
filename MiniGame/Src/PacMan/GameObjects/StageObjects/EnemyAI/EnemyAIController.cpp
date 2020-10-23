#include "EnemyAIController.h"
#include "EnemyAIChase.h"
#include "EnemyAIDefend.h"
#include "EnemyAISauntering.h"

PacMan::EnemyAIController::EnemyAIController(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	m_AI{ nullptr },  m_CurrentAction{ ActionStateList::ACTION_SAUNTERING }
{
	m_AI[(int)ActionStateList::ACTION_SAUNTERING] = new EnemyAISauntering(enemyPos_, enemyParam_, stage_);
	m_AI[(int)ActionStateList::ACTION_CHASE]	  = new EnemyAIChase(enemyPos_, enemyParam_, stage_);
	m_AI[(int)ActionStateList::ACTION_DEFEND]	  = new EnemyAIDeffend(enemyPos_, enemyParam_, stage_);

	m_AI[(int)m_CurrentAction]->Init();
}

PacMan::EnemyAIController::~EnemyAIController()
{
	for (int i = 0; i < (int)ActionStateList::ACTION_NUM; ++i)
	{
		SAFE_DELETE(m_AI[i]);
	}
}


void PacMan::EnemyAIController::Update()
{
	// 更新
	ActionStateList next_action = m_AI[(int)m_CurrentAction]->Update();

	// もしアクションが変わっていたら
	if (next_action != m_CurrentAction) {

		// アクションを更新
		m_CurrentAction = next_action;
		m_AI[(int)m_CurrentAction]->Init();
	}
}
