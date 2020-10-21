#include "ItemArray.h"

PacMan::ItemArray::ItemArray() :
	m_Item{ nullptr }
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (!m_Item[i])m_Item[i] = new Item();
	}
}

PacMan::ItemArray::~ItemArray()
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		SAFE_DELETE(m_Item[i]);
	}
}

void PacMan::ItemArray::Init()
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		SAFE_DELETE(m_Item[i]);
	}
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (!m_Item[i])m_Item[i] = new Item();
	}
}

void PacMan::ItemArray::Draw()
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i])m_Item[i]->Draw();
	}
}

bool PacMan::ItemArray::Empty()
{
	// 一つでもアイテムが残っていたらfalseを返す
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i]) return false;
	}

	return true;
}

int PacMan::ItemArray::GetItemTotalNum() const
{
	int ret_num = 0;
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i]) ret_num++;
	}
	return ret_num;
}
