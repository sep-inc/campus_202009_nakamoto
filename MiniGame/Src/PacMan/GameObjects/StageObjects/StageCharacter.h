#ifndef STAGE_CHARACTER_H_
#define STAGE_CHARACTER_H_

#include "StageObject.h"
#include "../Stage.h"

namespace PacMan
{
	/*
	ステージに置くキャラクターの規定クラス
*/
	class StageCharacter : public StageObject
	{
	public:
		StageCharacter(Stage* stage_);

		virtual ~StageCharacter() {}

		/*
			初期化関数
		*/
		virtual void Init() = 0;

		/*
			更新関数
		*/
		virtual void Update() = 0;

		/*
			描画関数
		*/
		virtual void Draw() = 0;

		/*
			自身のオブジェクトの種類を返す関数
		*/
		virtual inline ObjectType GetObjectType() const = 0;

	protected:
		// ステージクラスへのポインタ変数
		Stage* m_RefStage;

	};
}



#endif