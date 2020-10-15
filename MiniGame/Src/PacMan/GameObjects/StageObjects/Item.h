#ifndef ITEM_H_
#define ITEM_H_

#include "StageObject.h"

namespace PacMan
{
	/*
		アイテムクラス
	*/
	class Item : public StageObject
	{
	public:
		/*
			コンストラクタ
		*/
		Item();

		/*
			デストラクタ
		*/
		~Item();

		/*
			描画関数
		*/
		void Draw() override;

		/*
			自身のオブジェクトの種類を返す関数
		*/
		virtual inline ObjectType GetObjectType() const { return ObjectType::TYPE_ITEM; }


	private:
		// インスタンスの数を保存する変数
		static int m_InstanceNum;

		int m_Id;

	};
}


#endif