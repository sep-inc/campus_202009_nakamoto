#ifndef DRAWER_H_
#define DRAWER_H_

#include <string>

/**
* @brief   描画クラス
*/
class Drawer
{
public:
	static Drawer& GetInstance() {
		static Drawer instance;
		return instance;
	}

	/**
	* @brief 簡単な説明（～する関数）
	* @param[in] resouce_ 描画するリソース(文字列)
	* @details 詳細な説明
	*/
	void SetDrawBuffer(std::string resouce_);

	void SetDrawBuffer(int x_, int y_, const char* str_);

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


private:
	char m_DrawBuffer[15][30][22];

	//! 連結用描画バッファ
	std::string m_StrDrawBuffer;

};

#endif