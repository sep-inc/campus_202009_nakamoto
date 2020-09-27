#include "Drawer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*=============================================*/
/*    引数resouce_をバッファに書き込む関数     */
/*                                             */
/* 文字列が格納され出力されるので改行コードも  */
/* 含め渡す必要がある                          */
/*=============================================*/
void Drawer::SetDrawBuffer(const char* resouce_)
{
	// バッファにコピーする
	strcpy_s(m_DrawBuffer, resouce_);
}

/****************************************/
/*       バッファをクリアする関数       */
/****************************************/
void Drawer::ClearBuffer()
{
	// コマンドラインに出力されている文字を消す
	system("cls");
	// バッファをリセットする
	memset(m_DrawBuffer, '0', sizeof(m_DrawBuffer));
}

/****************************************/
/*       バッファを描画する関数         */
/****************************************/
void Drawer::DrawBuffer()
{
	// バッファに格納している文字列を出力する
	printf("%s", m_DrawBuffer);
}
