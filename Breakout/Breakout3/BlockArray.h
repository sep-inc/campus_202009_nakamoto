﻿#ifndef BLOCKARRAY_H_
#define BLOCKARRAY_H_

/****************************************************
	header
*****************************************************/

/*
	ブロックの配列を管理するクラス
*/
class BlockArray
{
public:
	/****************************************************
		コンストラクタ
	*****************************************************/
	BlockArray();

	/****************************************************
		デストラクタ
	*****************************************************/
	~BlockArray()
	{}

	/****************************************************
		ブロックの更新
	*****************************************************/
	void StepUpdate();

	/****************************************************
		ブロックの描画
	*****************************************************/
	void Draw();
	
private:
	/****************************************************
		全てのブロックが壊れているかを判定する関数
	*****************************************************/
	bool AllBlocksBroken();

};

#endif