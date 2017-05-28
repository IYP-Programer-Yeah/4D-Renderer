#include "../FS Lib/FS Lib.hpp"
#include "../WindowHandler Lib/WindowHandler Lib.hpp"
#include "Defs.h"
#include <iostream>

int main()
{
    WindowHandler_Lib::WindowHandler wh;
	//wh.hint_window(WindowHandler_Lib::WindowHandler::WH_RESIZABLE, WindowHandler_Lib::WindowHandler::HFalse);
	bool window_created = wh.create_window(0, 0, 500, 500, std::string("hello"));
    wh.show_window(WindowHandler_Lib::WindowHandler::SM_SHOWNA);
	while (window_created)
	{
		wh.get_event();
		std::cout << "hello\n";
	}
	return 0;
}
