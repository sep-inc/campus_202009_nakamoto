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
	// �X�V
	ActionStateList tmp = m_AI->Update(m_EnemyPos, m_Parameter, m_RefStage);

	// �����A�N�V�������ς���Ă�����
	if (tmp != m_CurrentAction) {
		switch (tmp)
		{
		case ActionStateList::ACTION_SAUNTERING:
			// �p�j
			m_AI = EnemyAISauntering::GetInstance();
			break;
		case ActionStateList::ACTION_DEFEND:
			// ���
			m_AI = EnemyAIDeffend::GetInstance();
			break;
		case ActionStateList::ACTION_CHASE:
			// �ǂ�������
			m_AI = EnemyAIChase::GetInstance();
			break;
		default:
			break;
		}
	}

	// �A�N�V�������X�V
	m_CurrentAction = tmp;

}
