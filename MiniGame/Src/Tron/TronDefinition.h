#ifndef TRON_DEFINITION_H_
#define TRON_DEFINITION_H_

// ステージの横幅
#define TRON_STAGE_WIDTH   19
// ステージの縦幅
#define TRON_STAGE_HEIGHT  12

// 壁ありのステージの横幅
#define MAP_WIDTH  (TRON_STAGE_WIDTH  + 2)
// 壁ありのステージの縦幅
#define MAP_HEIGHT (TRON_STAGE_HEIGHT + 2)

namespace Tron
{
	/**
* @enum Enum
* オブジェクトのタイプ
*/
	enum class ObjectType : unsigned char
	{
		TYPE_EMPTY,
		TYPE_PLAYRE,
		TYPE_ENEMY,
		TYPE_WALL,
	};

	/**
	* @enum Enum
	* 向きを表すための列挙
	*/
	enum class Direction : unsigned char
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
	};
}


//! ゲームが終了したかどうかを保存する変数
extern bool g_IsGameEnd;


#endif