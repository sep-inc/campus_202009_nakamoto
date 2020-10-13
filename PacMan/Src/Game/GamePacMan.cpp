#include "GamePacMan.h"
#include "../GameObjects/StageObjects/Player.h"
#include "../GameObjects/StageObjects/Enemy.h"
#include "../GameObjects/StageObjects/Item.h"

GamePacMan::GamePacMan() :
	m_Stage{ nullptr }, m_Enemy{ nullptr }, m_CurrentStep{ GamePacManStep::STEP_INIT }
{
	m_Stage = new Stage();

#ifdef PLAYER_ON
	m_Player = new Player(m_Stage);
#endif

#ifdef ENEMY_ON
	for (int i = 0; i < ENEMY_NUM; ++i) {
		m_Enemy[i] = new Enemy(m_Stage);
	}
#endif

#ifdef ITEM_ON
	for (int i = 0; i < ITEM_NUM; ++i) {
		m_Item[i] = new Item(m_Stage);
	}
#endif

}

void GamePacMan::Update()
{
	switch (m_CurrentStep)
	{
	case GamePacMan::GamePacManStep::STEP_INIT:

		if (m_Player) m_Player->Init();
		
		for (int i = 0; i < ENEMY_NUM; ++i) {
			if (m_Enemy[i]) {
				m_Stage->SetRandomPlacementObject(m_Enemy[i]);
			}
		}

		for (int i = 0; i < ITEM_NUM; ++i) {
			if (m_Item[i]) {
				m_Stage->SetRandomPlacementObject(m_Item[i]);
			}
		}

		m_CurrentStep = GamePacManStep::STEP_UPDATE;
		break;
	case GamePacMan::GamePacManStep::STEP_UPDATE:

		if (m_Player) m_Player->Update();

		for (int i = 0; i < ENEMY_NUM; ++i) {
			if (m_Enemy[i]) m_Enemy[i]->Update();
		}

		break;
	case GamePacMan::GamePacManStep::STEP_RELEASE:
		break;
	default:
		break;
	}
}

void GamePacMan::Draw()
{
	m_Stage->Draw();

	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i]) {
			m_Item[i]->Draw();
		}
	}

	if (m_Player) m_Player->Draw();

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (m_Enemy[i]) m_Enemy[i]->Draw();
	}
}
