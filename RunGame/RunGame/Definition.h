#ifndef DEFINITION_H_
#define DEFINITION_H_

// 重力
#define GRAVITY           0.07
// 初速度
#define INITIAL_VELOCITY  0.6

// プレイヤー速度
#define PLAYER_SPEED      0.2
// プレイヤー初期X座標
#define PLAYER_INIT_POS_X 1.0
// プレイヤーの横幅
#define PLAYER_WIDTH      1
// プレイヤーの縦幅
#define PLAYER_HEIGHT     2

// ゴール地点
#define GOAL_POS          300.0

// ブロックのサイズ(正方形)
#define BLCOK_SIZE        1
// ステージの横の長さ
#define STAGE_WIDTH       320
// ステージの縦の長さ
#define STAGE_HEIGHT      10

// ステージの横の描画範囲
#define DRAW_RANGE_WIDTH  11
// ステージの縦の描画範囲
#define DRAW_RANGE_HEIGHT 10


//! ゲームが終了したかどうかを保存する変数
extern bool g_GameEnd;

//! ゲームをクリアしたかどうかを保存する変数
extern bool g_GameClear;

#endif