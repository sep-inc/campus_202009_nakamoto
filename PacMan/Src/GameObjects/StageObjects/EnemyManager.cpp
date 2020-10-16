#include "EnemyManager.h"

PacMan::EnemyManager::EnemyManager(Stage* stage_) :
	m_Enemy{ nullptr }
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (!m_Enemy[i])m_Enemy[i] = new Enemy(stage_);
	}
}

PacMan::EnemyManager::~EnemyManager()
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		SAFE_DELETE(m_Enemy[i]);
	}
}

void PacMan::EnemyManager::Init()
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (m_Enemy[i])m_Enemy[i]->Init();
	}
}

void PacMan::EnemyManager::Update()
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (m_Enemy[i])m_Enemy[i]->Update();
	}
}

void PacMan::EnemyManager::Draw()
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (m_Enemy[i])m_Enemy[i]->Draw();
	}
}
