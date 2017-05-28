#include "../FS Lib/FS Lib.hpp"
#include "../WindowHandler Lib/WindowHandler Lib.hpp"
#include "Defs.h"
#include <iostream>

int main()
{
    WindowHandler_Lib::WindowHandler wh;
	bool window_created = wh.create_window(0, 0, 500, 500, std::string("hello"));
    wh.show_window(WindowHandler_Lib::WindowHandler::SM_SHOWNA);
	while (window_created)
	{
		std::cout << "hello\n";
	}
	return 0;
}
