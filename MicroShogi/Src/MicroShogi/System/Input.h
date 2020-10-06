#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>

#define KEY_UP		72	
#define KEY_DOWN	80
#define KEY_RIGHT	77
#define KEY_LEFT	75
#define KEY_SPACE	32

/**
* @enum Enum
* 入力につかうキー情報
*/
enum class KeyList : int
{
	R_KEY       = 'R',
	C_KEY       = 'C',
	SPACE_KEY   = VK_SPACE,
	UP_KEY      = VK_UP,
	DOWN_KEY    = VK_DOWN,
	ESC_KEY     = VK_ESCAPE,
	CONTROL_KEY = VK_CONTROL,
};

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

	/**
	* @brief       入力関数
	* @param[in]   key_　KeyListに列挙されているキー情報
	* @return bool 押されていたらtrueを返す
	* @details     引数のキーが押されている間trueを返す
	*/
	static bool GetKey(KeyList key_);

};

#endif