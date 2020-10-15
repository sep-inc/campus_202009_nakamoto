#include "EnemyArray.h"

PacMan::EnemyArray::EnemyArray(Stage* stage_) :
	m_Enemy{ nullptr }
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (!m_Enemy[i])m_Enemy[i] = new CharacterEnemy(stage_);
	}
}

PacMan::EnemyArray::~EnemyArray()
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		SAFE_DELETE(m_Enemy[i]);
	}
}

void PacMan::EnemyArray::Init()
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (m_Enemy[i])m_Enemy[i]->Init();
	}
}

void PacMan::EnemyArray::Update()
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (m_Enemy[i])m_Enemy[i]->Update();
	}
}

void PacMan::EnemyArray::Draw()
{
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (m_Enemy[i])m_Enemy[i]->Draw();
	}
}
