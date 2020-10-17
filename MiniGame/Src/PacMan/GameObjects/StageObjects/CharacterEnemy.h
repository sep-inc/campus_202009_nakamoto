#ifndef ENEMY_H_
#define ENEMY_H_

#include "../StageObjects/StageCharacter.h"

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
		CharacterEnemy(Stage* stage_);


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

		/*
			自身の周りで移動できる方向と数をかえす関数
		*/
		void AbleMoveAround(IVec2 pos_, IVec2* outVecArray_, int* ableMoveNum_);

	private:
		// フレーム数をカウントする変数
		int m_Timer;

		// 現在の移動方向を保存する変数
		IVec2 m_Direction;
		
	};
}


#endif