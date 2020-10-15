#ifndef ENEMY_H_
#define ENEMY_H_

#include "../StageObjects/StageCharacter.h"

namespace PacMan
{
	/*
		エネミークラス
	*/
	class Enemy : public StageCharacter
	{
	public:
		/*
			コンストラクタ
		*/
		Enemy(Stage* stage_);


		/*
			デストラクタ
		*/
		~Enemy() {}

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
		// フレーム数をカウントする変数
		int m_Timer;

	};
}


#endif