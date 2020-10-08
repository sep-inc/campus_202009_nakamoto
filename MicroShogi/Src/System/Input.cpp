#include "Input.h"
#include <conio.h>
#include <Windows.h>

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

/*=============================================*/
/*　　　　WindowsApi入力関数     　　　　　　　*/
/*=============================================*/
bool Input::GetKey(KeyList key_)
{
	return GetAsyncKeyState(static_cast<int>(key_)) & 0x8000;
}

