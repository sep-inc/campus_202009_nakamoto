#include "Input.h"
#include <conio.h>

/*=============================================*/
/*　　　　　　　　　入力関数     　　　　　　　*/
/*=============================================*/
int Input::GetKey()
{
	if (_kbhit() != 0) {
		return _getch();
	}
	return -1;
}

