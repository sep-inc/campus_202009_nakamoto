#include "SceneManager.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "../Utility/SafeDelete.h"
#include <Windows.h>

SceneManager::SceneManager() :
	m_Scene{ nullptr }
{
	m_Scene = new SelectScene(&m_SelectGame);
}

SceneManager::~SceneManager()
{
	SAFE_DELETE(m_Scene);
}

void SceneManager::Update()
{
	if (!m_Scene)return;

	m_Scene->Update();

	if (m_Scene->SceneEnd() == true)
	{
		switch (m_Scene->GetScene())
		{
		case SceneList::SCENE_SELECT:

			SAFE_DELETE(m_Scene);

			system("cls");
			if (m_SelectGame == GameList::GAME_UNKNOWN) exit(1);

			m_Scene = new GameScene(m_SelectGame);
			break;
		case SceneList::SCENE_GAME:

			system("cls");
			m_Scene = new SelectScene(&m_SelectGame);
			break;
			
		default:
			break;
		}
	}
	
}

void SceneManager::Draw()
{
	if(m_Scene)m_Scene->Draw();
}
