#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Drawer.h"
#include "Input.h"

//! 描画クラス
extern Drawer g_Drawer;

//! 入力クラス
extern Input g_Input;

//! ゲームを終了するかどうかを保存する変数
extern bool g_Quit;

#endif