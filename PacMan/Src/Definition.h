#ifndef DIFINITION_H_
#define DIFINITION_H_

// セーフデリート
#define SAFE_DELETE(p) { if (p != nullptr) { delete (p); (p) = nullptr; }}

// 単体テスト用
#define PLAYER_ON
#define ENEMY_ON
#define ITEM_ON

// ステージの横幅
#define STAGE_WIDTH  13

// ステージの縦幅
#define STAGE_HEIGHT 13

// プレイヤーの初期値
#define PLAYER_INIT_POS_X 3
#define PLAYER_INIT_POS_Y 6

// 敵の数
#define ENEMY_NUM 3

// アイテムの数
#define ITEM_NUM  5

// 敵の速度　20 -> 20フレームに一度行動する
#define ENEMY_SPEED 20


// オブジェクトの識別
enum class ObjectType : int
{
	TYPE_EMPTY,		// 空
	TYPE_WALL,		// 壁
	TYPE_PLAYER,	// プレイヤー
	TYPE_ENEMY,		// 敵
	TYPE_ITEM,		// アイテム
};


#endif