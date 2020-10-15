#include "GrobalObject.h"



	// ゲームが終了したかどうかを保存する変数
	bool g_IsGameOver;

	// 誰の番なのかを保存する変数
	TicTacToe::ObjectType g_WhosTurn;

	// 誰が勝利したか保存する変数
	TicTacToe::ObjectType g_WhosWon;



// グリッド
TicTacToe::Grid g_Grid;