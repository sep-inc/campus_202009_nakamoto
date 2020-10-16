#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>

#define KEY_UP		72	
#define KEY_DOWN	80
#define KEY_RIGHT	77
#define KEY_LEFT	75
#define KEY_SPACE	32
#define KEY_ENTER   13
#define KEY_ESC     27
#define KEY_1       49
#define KEY_2       50
#define KEY_3       51

/**
* @brief   インプットクラス
* @details 入力を管理するクラス
*/
class Input
{
public:
	/**
	* @brief       入力関数
	* @return int  ASCIIコード表に対応する10進数が返る
	* @details     入力された文字のASCIIコード表に対応する10進数を返す
	*/
	static int GetKey();

};

#endif