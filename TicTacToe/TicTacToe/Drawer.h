#ifndef DRAWER_H_
#define DRAWER_H_

#include "ObjectType.h"
#include "GrobalObject.h"

/*
	描画クラス
*/
class Drawer
{
public:
	// コンストラクタ
	Drawer();

	// デストラクタ
	~Drawer(){}

	// 描画バッファに書き込む関数
	void SetDrawBuffer(__int8 x_, __int8 y_, ObjectType type_);

	// バッファをクリアする関数
	void ClearBuffer();

	// バッファを描画する関数
	void DrawBuffer();

private:
	// 描画用バッファ
	char m_DrawBuffer[GRID_FRAME_HEIGHT][GRID_FRAME_WIDTH][CHAR_SIZE];

	// クリア用バッファ
	char m_BlankBuffer[GRID_FRAME_HEIGHT][GRID_FRAME_WIDTH][CHAR_SIZE];
	
};

#endif