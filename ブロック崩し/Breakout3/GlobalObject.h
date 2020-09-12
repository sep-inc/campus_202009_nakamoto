#ifndef GLOBALOBJECT_H_
#define GLOBALOBJECT_H_

/****************************************************
	header
*****************************************************/
#include "Ball.h"
#include "Wall.h"
#include "Block.h"
#include "Paddle.h"

/****************************************************
	define
*****************************************************/

/*------------ ステージ -----------------*/
// ステージの横幅
#define STAGE_WIDTH  17

// ステージの高さ
#define STAGE_HEIGHT 26

// ステージの左端
#define STAGE_MIN_X 0

// ステージの右端
#define STAGE_MAX_X 15

// ステージの上
#define STAGE_MIN_Y 0

// ステージの下
#define STAGE_MAX_Y 24

/*------------ ボール -------------------*/
// 初期X座標
#define BALL_INIT_POS_X  7.5f

// 初期Y座標
#define BALL_INIT_POS_Y  19.5f

// ボールの半径
#define BALL_RADIUS		 0.5f

// ボールの速度(1/60フレーム)
#define BALL_SPEED		 0.5f

// 初期のボールの角度
#define BALL_INIT_ANGLE  60.0f


/*------------ ブロック -------------------*/
// 左上ブロックの初期値
#define BLOCK_INIT_X  4

// 左上ブロックの初期値
#define BLOCK_INIT_Y  4

// ブロック1個の横幅
#define BLOCK_WIDTH   1

// ブロック1個の縦幅
#define BLOCK_HEIGHT  1

// ブロックのX軸の数
#define BLOCK_NUM_X   7

// ブロックのY軸の数
#define BLOCK_NUM_Y   3


/*------------ パドル -------------------*/
// パドルのX座標の初期値
#define PADDLE_INIT_X 7.0f

// パドルのY座標の初期値
#define PADDLE_INIT_Y 21.0f

// パドルの速度(1/60フレーム)
#define PADDLE_SPEED  0.5f

// パドルの横幅
#define PADDLE_WIDTH  3

// パドルの縦幅
#define PADDLE_HEIGHT 1

/*------------ 壁 -------------------*/
// 左壁
#define WALL_MIN_X  1

// 右壁
#define WALL_MAX_X  14

// 上壁
#define WALL_MIN_Y  1

// 下壁
#define WALL_MAX_Y  23

// 壁の横幅
#define WALL_WIDTH  15

// 壁の縦幅
#define WALL_HEIGHT 24

/****************************************************
	extern
*****************************************************/

// [ボール]オブジェクのトインスタンス
extern Ball g_Ball;

// [壁]オブジェクトのインスタンス
extern Wall g_Wall;

// [ブロック]オブジェクトのインスタンス
extern Block g_Block[BLOCK_NUM_Y][BLOCK_NUM_X];

// [パドル]オブジェクトのインスタンス
extern Paddle g_Paddle;

// ゲーム終了フラグ
// trueならゲーム終了
extern bool g_IsGameOver;


#endif