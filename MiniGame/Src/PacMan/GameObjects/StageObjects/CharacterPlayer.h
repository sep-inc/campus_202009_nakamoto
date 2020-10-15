#ifndef PLAYER_H_
#define PLAYER_H_

#include "StageCharacter.h"

namespace PacMan
{
	/*
		プレイヤークラス
	*/
	class CharacterPlayer : public StageCharacter
	{
	public:
		/*
			コンストラクタ
		*/
		CharacterPlayer(Stage* stage_);

		/*
			デストラクタ
		*/
		~CharacterPlayer() {}

		/*
			初期化関数
			ゲーム開始時に1度呼ぶ
		*/
		void Init() override;

		/*
			更新関数
			1フレームに1度呼ぶ
		*/
		void Update() override;

		/*
			描画関数
			描画ステップ時に
			1フレーム1度呼ぶ
		*/
		void Draw() override;

		// 自身のオブジェクトの種類を返す関数
		virtual inline ObjectType GetObjectType()const override { return ObjectType::TYPE_PLAYER; }


	private:
		/*
			移動関数
		*/
		void Move();

	};
}


#endif