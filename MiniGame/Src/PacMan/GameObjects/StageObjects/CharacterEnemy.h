#ifndef ENEMY_H_
#define ENEMY_H_

#include "../StageObjects/StageCharacter.h"
#include "EnemyAI/EnemyParamater.h"
#include "EnemyAI/EnemyAIController.h"

namespace PacMan
{
	/*
		エネミークラス
	*/
	class CharacterEnemy : public StageCharacter
	{
	public:
		/*
			コンストラクタ
		*/
		CharacterEnemy(Stage* stage_, int speed_, EnemyPersonalityList personality_);


		/*
			デストラクタ
		*/
		~CharacterEnemy() {}

		/*
			初期化関数
			ゲーム開始時に一度だけ呼び出す
		*/
		void Init() override;

		/*
			更新関数
		*/
		void Update() override;

		/*
			描画関数
			描画クラスのバッファにセットする
		*/
		void Draw() override;

		/*
			自身の種類を返す関数
		*/
		virtual inline ObjectType GetObjectType()const override { return ObjectType::TYPE_ENEMY; }


	private:
		/*
			移動関数
		*/
		void Move();

	private:

		int m_Timer;

		// エネミーのパラメーターをまとめた構造体
		EnemyParameter m_Param;

		EnemyAIController m_AI;
	};
}


#endif