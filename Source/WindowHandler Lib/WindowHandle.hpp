/*
Created By Hosein Ghahremanzadeh 5/24/2017
A cross platform window creation lib.
*/

#ifndef _WINDOW_HANLE_
#define _WINDOW_HANLE_

#if defined(_WIN32) || defined(__WIN32__)
	#include <Windows.h>
#else
    #include "../../Includes/GLFW/glfw3.h"
#endif

namespace WindowHandler_Lib
{
	class WindowHandle
	{
#if defined(_WIN32) || defined(__WIN32__)
		HDC hdc;
#else
		GLFWwindow* hwnd;
#endif
	public:
		WindowHandle
#if defined(_WIN32) || defined(__WIN32__)
		(HDC i_hdc)
		{
			hdc = i_hdc;
		}
#else
		(GLFWwindow* i_hwnd)
		{
			hwnd = i_hwnd;
		}
#endif
	};
}
#endif
