#include "ItemManager.h"

PacMan::ItemManager::ItemManager() :
	m_Item{ nullptr }
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (!m_Item[i])m_Item[i] = new Item();
	}
}

PacMan::ItemManager::~ItemManager()
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		SAFE_DELETE(m_Item[i]);
	}
}

void PacMan::ItemManager::Init()
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		SAFE_DELETE(m_Item[i]);
	}
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (!m_Item[i])m_Item[i] = new Item();
	}
}

void PacMan::ItemManager::Draw()
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i])m_Item[i]->Draw();
	}
}

bool PacMan::ItemManager::Empty()
{
	// 一つでもアイテムが残っていたらfalseを返す
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i]) return false;
	}

	return true;
}
