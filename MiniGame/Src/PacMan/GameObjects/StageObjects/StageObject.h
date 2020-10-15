#ifndef STAGE_OBJECT_H_
#define STAGE_OBJECT_H_

#include "../../../Utility/IVec2.h"
#include "../../PacManDefinition.h"


namespace PacMan
{
	/*
		ステージに配置するオブジェクトの基底クラス
	*/
	class StageObject
	{
	public:
		/*
			コンストラクタ
		*/
		StageObject();

		/*
			デストラクタ
		*/
		virtual ~StageObject() {}

		/*
			描画関数
		*/
		virtual void Draw() = 0;

		/*
			自身のオブジェクトの種類を返す関数
		*/
		virtual inline ObjectType GetObjectType() const = 0;

		/*
			自身の座標をセットする関数
		*/
		inline void SetPos(IVec2 vec_) { m_Pos = vec_; }

		/*
			自身の座標を返す関数
		*/
		inline IVec2 GetPos()const { return m_Pos; }


	protected:
		// 現在の座標を保存する変数
		IVec2 m_Pos;


	};
}


#endif