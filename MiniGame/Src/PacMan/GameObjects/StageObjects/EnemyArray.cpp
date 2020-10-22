#include "EnemyArray.h"

PacMan::EnemyArray::EnemyArray(Stage* stage_) :
	m_Enemy{ nullptr }
{
	if (!m_Enemy[0])m_Enemy[0] = new CharacterEnemy(stage_, 20, EnemyPersonalityList::PERSONALITY_A);
	if (!m_Enemy[1])m_Enemy[1] = new CharacterEnemy(stage_, 30, EnemyPersonalityList::PERSONALITY_B);
	if (!m_Enemy[2])m_Enemy[2] = new CharacterEnemy(stage_, 30, EnemyPersonalityList::PERSONALITY_C);

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
