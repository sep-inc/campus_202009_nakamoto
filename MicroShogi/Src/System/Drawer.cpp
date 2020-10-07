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
	m_DrawBuffer = resouce_;
}


/*=======================================*/
/*　　　　バッファをクリアする関数     　*/
/*=======================================*/
void Drawer::ClearBuffer()
{
	// コマンドラインに出力されている文字を消す
	//system("cls");

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });

	// バッファをリセットする
	m_DrawBuffer = "\0";
}


/*=====================================*/
/*　　　  バッファを描画する関数  　   */
/*=====================================*/
void Drawer::DrawBuffer()
{
	// バッファに格納している文字列を出力す
	std::cout << m_DrawBuffer << std::endl;
}
