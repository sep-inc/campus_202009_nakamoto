#include "EnemyAIController.h"
#include "EnemyAIChase.h"
#include "EnemyAIDefend.h"
#include "EnemyAISauntering.h"

PacMan::EnemyAIController::EnemyAIController(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	m_AI{ nullptr }, m_EnemyPos{ enemyPos_ }, m_Parameter{ enemyParam_ }, m_RefStage{ stage_ }, m_CurrentAction{ ActionStateList::ACTION_SAUNTERING }
{
	m_AI = EnemyAISauntering::GetInstance();
}


ActionStateList m_CurrentAction;
void PacMan::EnemyAIController::Update()
{
	// 更新
	ActionStateList tmp = m_AI->Update(m_EnemyPos, m_Parameter, m_RefStage);

	// もしアクションが変わっていたら
	if (tmp != m_CurrentAction) {
		switch (tmp)
		{
		case ActionStateList::ACTION_SAUNTERING:
			// 徘徊
			m_AI = EnemyAISauntering::GetInstance();
			break;
		case ActionStateList::ACTION_DEFEND:
			// 守備
			m_AI = EnemyAIDeffend::GetInstance();
			break;
		case ActionStateList::ACTION_CHASE:
			// 追いかける
			m_AI = EnemyAIChase::GetInstance();
			break;
		default:
			break;
		}
	}

	// アクションを更新
	m_CurrentAction = tmp;

}
