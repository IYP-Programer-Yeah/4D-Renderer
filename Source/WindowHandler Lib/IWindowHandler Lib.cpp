/*
Created By Hosein Ghahremanzadeh 5/29/2017
A cross platform window creation lib.
*/

#define IWINDOW_HANLER_LIB_DLL_EXPORTS
#include "IWindowHandler Lib.hpp"
#include "WindowHandler Lib.hpp"
#include "WindowHandle.hpp"

namespace WindowHandler_Lib
{
	IWindowHandler* creat_window_handler()
	{
		return new WindowHandler();
	}
	void delete_window_handler(IWindowHandler* window_handler)
	{
		delete window_handler;
	}
}
