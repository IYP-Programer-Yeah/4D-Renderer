/*
Created By Hosein Ghahremanzadeh 5/24/2017
This is a simple library to access data from files.
*/

#define _WINDOW_HANLER_LIB_DLL_EXPORTS
#include "WindowHandler Lib.hpp"
namespace WindowHandler_Lib
{
	void WindowHandler::show_window(WindowShowMode window_show_mode)
	{
#if defined(_WIN32) || defined(__WIN32__)
		ShowWindow(hwnd, window_show_mode);
#else
		switch (window_show_mode)
		{
		case MAXIMIZE:
			break;
		case MINIMIZE:
			glfwIconifyWindow(&hwnd);
			break;
		case HIDE:
			glfwHideWindow(&hwnd);
			break;
		case RESTORE:
			glfwRestoreWindow(&hwnd);
			break;
		case SHOW:
			glfwShowWindow(&hwnd);
			glfwFocusWindow(&hwnd);
			break;
		case SHOWMAXIMIZED:
			glfwShowWindow(&hwnd);
			glfwFocusWindow(&hwnd);
			break;
		case SHOWMINIMIZED:
			glfwIconifyWindow(&hwnd);
			glfwShowWindow(&hwnd);
			glfwFocusWindow(&hwnd);
			break;
		case SHOWMINNOACTIVE:
			glfwIconifyWindow(&hwnd);
			glfwShowWindow(&hwnd);
			break;
		case SHOWNA:
			glfwShowWindow(&hwnd);
			break;
		case SHOWNOACTIVATE:
			glfwRestoreWindow(&hwnd);
			glfwShowWindow(&hwnd);
			break;
		case SHOWNORMAL:
			glfwRestoreWindow(&hwnd);
			glfwShowWindow(&hwnd);
			glfwFocusWindow(&hwnd);
			break;
		default:
			break;
		}
#endif
	}
	void WindowHandler::close_window()
	{
#if defined(_WIN32) || defined(__WIN32__)
		DestroyWindow(hwnd);
#else
		glfwDestroyWindow(&hwnd);
#endif
	}
	WindowHandle WindowHandler::get_handle()
	{
		return WindowHandle(hwnd);
	}
#if defined(_WIN32) || defined(__WIN32__)
	void WindowHandler::set_wnd_proc(WNDPROC i_wnd_proc)
	{
		wnd_proc = i_wnd_proc;
	}
#else

#endif
	int WindowHandler::get_width()
	{
#if defined(_WIN32) || defined(__WIN32__)
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		return window_rect.right - window_rect.left;
#else
		int h, w;
		glfwGetWindowSize(&hwnd, &w, &h);
		return w;
#endif
	}
	int WindowHandler::get_height()
	{
#if defined(_WIN32) || defined(__WIN32__)
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		return window_rect.bottom - window_rect.top;
#else
		int h, w;
		glfwGetWindowSize(&hwnd, &w, &h);
		return h;
#endif
	}
	int WindowHandler::get_location_x()
	{
#if defined(_WIN32) || defined(__WIN32__)
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		return window_rect.left;
#else
		int x, y;
		glfwGetWindowPos(&hwnd, &x, &y);
		return x;
#endif
	}
	int WindowHandler::get_location_y()
	{
#if defined(_WIN32) || defined(__WIN32__)
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		return window_rect.top;
#else
		int x, y;
		glfwGetWindowPos(&hwnd, &x, &y);
		return y;
#endif
	}
	std::string WindowHandler::get_title()
	{
		return title;
	}
	void WindowHandler::set_width(int width)
	{

	}
	void WindowHandler::set_height(int height)
	{
	}
	void WindowHandler::set_location_x(int x)
	{
	}
	void WindowHandler::set_location_y(int y)
	{
	}
	void WindowHandler::set_title(std::string i_title)
	{
		title = i_title;
#if defined(_WIN32) || defined(__WIN32__)
		SetWindowText(hwnd, title.c_str());
#else
		glfwSetWindowTitle(&hwnd, title.c_str());
#endif
	}
}