#ifndef GROBALOBJECT
#define GROBALOBJECT

#include "ObjectType.h"
#include "Player.h"
#include "Enemy.h"
#include "Grid.h"

// ゲームが終了したかどうかを保存する変数
extern bool g_IsGameOver;

// 誰の番なのかを保存する変数
extern ObjectType g_WhosTurn;

// 誰が勝利したか保存する変数
extern ObjectType g_WhosWon;

// グリッド
extern TicTacToe::Grid g_Grid;


#endif