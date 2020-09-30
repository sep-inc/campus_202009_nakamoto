#include "Input.h"
#include <conio.h>
#include <Windows.h>

/*=============================================*/
/*�@�@�@�@�@�@�@�@�@���͊֐�     �@�@�@�@�@�@�@*/
/*=============================================*/
int Input::GetKey()
{
	return _getch();
}

/*=============================================*/
/*�@�@�@�@WindowsApi���͊֐�     �@�@�@�@�@�@�@*/
/*=============================================*/
bool Input::GetKey(KeyList key_)
{
	return GetAsyncKeyState(static_cast<int>(key_)) & 0x8000;
}

