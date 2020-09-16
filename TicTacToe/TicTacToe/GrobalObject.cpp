#include "GrobalObject.h"

// ゲームが終了したかどうかを保存する変数
bool g_IsGameOver = false;

// 誰の番なのかを保存する変数
ObjectType g_WhosTurn = ObjectType::TYPE_PlAYER;

// 誰が勝利したか保存する変数
ObjectType g_WhosWon = ObjectType::TYPE_EMPTY;

// プレイヤー
Player g_Player;

// エネミー
Enemy  g_Enemy;

// グリッド
Grid   g_Grid;