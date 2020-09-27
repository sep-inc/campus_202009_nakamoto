#ifndef INPUT_H_
#define INPUT_H_

/**
* @brief   インプットクラス
* @details 入力を管理するクラス
*/
class Input
{
public:
	/**
	* @brief       入力関数
	* @details     入力された文字のASCIIコード表に対応する10進数を返す関数
	* @return int  ASCIIコード表に対応する10進数が返る
	*/
	int GetKey();

};

#endif