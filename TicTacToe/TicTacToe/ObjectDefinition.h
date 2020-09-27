#ifndef OBJECTDEFINITION_H_
#define OBJECTDEFINITION_H_

// 横のマス目の数
#define GRID_WIDTH  3

// 縦のマス目の数
#define GRID_HEIGHT 3

// グリッドの枠の横幅
#define GRID_FRAME_WIDTH  ( GRID_WIDTH  * 2 + 2 )

// グリッドの枠の縦幅
#define GRID_FRAME_HEIGHT ( GRID_HEIGHT * 2 + 2 )

// グリッドの枠の左端
#define GRID_FRAME_MIN_X 1

// グリッドの枠の右端
#define GRID_FRAME_MAX_X ( GRID_FRAME_WIDTH - 1 )

// グリッドの枠の上
#define GRID_FRAME_MIN_Y 1

// グリッドの枠の下
#define GRID_FRAME_MAX_Y ( GRID_FRAME_HEIGHT - 1 )

// 文字サイズ
#define CHAR_SIZE 4

#endif