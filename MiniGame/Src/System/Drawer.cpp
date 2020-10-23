#include "Drawer.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

/*=============================================*/
/*    引数resouce_をバッファに書き込む関数     */
/*                                             */
/* 文字列が格納され出力されるので改行コードも  */
/* 含め渡す必要がある                          */
/*=============================================*/
void Drawer::SetDrawBuffer(std::string resouce_)
{
	// バッファにコピーする
	m_StrDrawBuffer = resouce_;

	
}

void Drawer::SetDrawBuffer(int x_, int y_, const char* str_)
{
	strcpy_s(m_DrawBuffer[y_][x_], str_);
}


/*=======================================*/
/*　　　　バッファをクリアする関数     　*/
/*=======================================*/
void Drawer::ClearBuffer()
{
	// コマンドラインに出力されている文字を消す
	//system("cls");

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });

	memset(m_DrawBuffer, 0, sizeof(m_DrawBuffer));

	// バッファをリセットする
	m_StrDrawBuffer = "\0";
}


/*=====================================*/
/*　　　  バッファを描画する関数  　   */
/*=====================================*/
void Drawer::DrawBuffer()
{
	for (int y = 0; y < 15; ++y) {
		for (int x = 0; x < 30; ++x) {
			if (m_DrawBuffer[y][x] == " ") {

			}
			m_StrDrawBuffer += m_DrawBuffer[y][x];
		}
		m_StrDrawBuffer += "\n";
	}

	// バッファに格納している文字列を出力す
	std::cout << m_StrDrawBuffer << std::endl;
}
