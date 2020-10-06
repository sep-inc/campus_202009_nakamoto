#ifndef DEFINITION_H_
#define DEFINITION_H_

// セーフデリート
#define SAFE_DELETE(p) {delete p; p = nullptr;}
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
enum class MoveTrun : unsigned char
{
	MOVE_FIRST,		// 先手
	MOVE_SECOND,	// 後手
	MOVE_NON,
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
	SCENE_SELECT,	// セレクトシーン
	SCENE_GAME,		// ゲームシーン
	SCENE_RESULT,	// 結果シーン
};

/**
* @enum Enum
* 駒の種類
*/
enum class ShogiPiece : unsigned char
{
	PIECE_EMPTY,
	PIECE_KING,		// 王
	PIECE_GOLD,		// 金
	PIECE_KNIGHT,	// 桂
	PIECE_PAWN,		// 歩
};

#endif