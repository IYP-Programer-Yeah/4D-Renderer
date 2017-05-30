#include "../FS Lib/FS Lib.hpp"
#include "../WindowHandler Lib/IWindowHandler Lib.hpp"
#include "Defs.h"
#include <iostream>

#if defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
    WindowHandler_Lib::IWindowHandler *wh = WindowHandler_Lib::creat_window_handler();
	bool window_created = wh->create_window(0, 0, 500, 500, std::string("hello"));
    wh->show_window(WindowHandler_Lib::IWindowHandler::SM_HIDE);
	while (window_created)
	{
		wh->get_event();
		std::cout << "hello\n";
	}
	return 0;
}
