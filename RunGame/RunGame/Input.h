#ifndef INPUT_H_
#define INPUT_H_

/**
* @enum Enum
* 入力につかうキー情報
*/
enum class KeyList : int
{
	R_KEY = 'R',
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
	int GetKey();

	/**
	* @brief       入力関数
	* @param[in]   key_　KeyListに列挙されているキー情報
	* @return bool 押されていたらtrueを返す
	* @details     引数のキーが押されている間trueを返す
	*/
	bool GetKey(KeyList key_);
	
};

#endif