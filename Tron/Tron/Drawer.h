#ifndef DRAWER_H_
#define DRAWER_H_

#include "Definition.h"

/**
* @brief   描画クラス
*/
class Drawer
{
public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	Drawer() :
		m_DrawBuffer{ "\0" }
	{}

	/**
	* @brief   デストラクタ
	*/
	~Drawer() {}

	/**
	* @brief 簡単な説明（～する関数）
	* @param[in] resouce_ 描画するリソース(文字列)
	* @details 詳細な説明
	*/
	void SetDrawBuffer(const char* resouce_);

	/**
	* @brief   バッファのクリア
	* @details 書き込まれているバッファをクリアする
	*/
	void ClearBuffer();

	/**
	* @brief   描画関数
	* @details バッファを描画する
	*/
	void DrawBuffer();

private:
	//! 描画バッファ
	char m_DrawBuffer[MAP_HEIGHT * MAP_WIDTH * 3];

};

#endif