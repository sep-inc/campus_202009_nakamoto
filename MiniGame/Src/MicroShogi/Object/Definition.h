#ifndef DEFINITION_H_
#define DEFINITION_H_

#include <cstdint>

#define CURSOR_FLASH_TIME 20

// ボードの横幅
#define BOARD_WIDTH  4
// ボードの縦幅
#define BOARD_HEIGHT 5
// 枠付きボードの横幅
#define BOARD_FRAME_WIDTH  (BOARD_WIDTH  * 2 + 2)
// 枠付きボードの縦幅
#define BOARD_FRAME_HEIGHT (BOARD_HEIGHT * 2 + 2)
// 枠付きのボードの左端
#define BOARD_FRAME_MIN_X 1
// 枠付きのボードの右端
#define BOARD_FRAME_MAX_X (BOARD_FRAME_WIDTH  - 1)
// 枠付きのボードの上
#define BOARD_FRAME_MIN_Y  1
// 枠付きのボードの下
#define BOARD_FRAME_MAX_Y (BOARD_FRAME_HEIGHT - 1)
// 文字サイズ
#define CHAR_SIZE 4

/**
* @enum Enum
* 先手後手の列挙
*/
enum class AttackTurn : uint8_t
{
	ATTACK_FIRST,	// 先手
	ATTACK_SECOND,	// 後手
	ATTACK_NONE,
};

/**
* @enum Enum
* 棋士のタイプ
*/
enum class ShogiPlayerType : unsigned char
{
	TYPE_UNKNOWN,	 
	TYPE_PC,		// プレイヤーキャラクター
	TYPE_NPC,		// ノンプレイヤーキャラクター
};

/**
* @enum Enum
* ゲームのシーン
*/
enum class ShogiSceneList : unsigned char
{
	SCENE_UNKNOWN,
	SCENE_SELECT,	// セレクトシーン
	SCENE_GAME,		// ゲームシーン
	SCENE_RESULT,	// 結果シーン
};

/**
* @enum Enum
* 駒の種類
*/
enum class PieceType : uint8_t
{
	PIECE_KING,			// 王
	PIECE_GOLDGENERAL,	// 金
	PIECE_KNIGHT,		// 桂
	PIECE_PAWN,			// 歩
	PIECE_EMPTY,
};

#endif