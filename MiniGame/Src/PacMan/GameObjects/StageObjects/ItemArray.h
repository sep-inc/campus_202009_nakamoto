#ifndef ITEM_ARRAY_H_
#define ITEM_ARRAY_H_

#include "Item.h"
#include "../../../Utility/SafeDelete.h"

namespace PacMan
{
	class ItemArray
	{
	public:
		ItemArray();

		~ItemArray();
		
		void Init();

		void Draw();

		void Destory(int idx_) { SAFE_DELETE(m_Item[idx_]); }

		inline Item* GetItem(int idx_) { return m_Item[idx_]; }

		bool Empty();

	private:
		Item* m_Item[ITEM_NUM];

	};
}


#endif