/*
Created By Hosein Ghahremanzadeh 5/24/2017
This is a simple library to access data from files.
*/

#ifndef _WINDOW_HANLER_LIB_
#define _WINDOW_HANLER_LIB_

#if defined(_WIN32) || defined(__WIN32__)
	#ifdef _WINDOW_HANLER_LIB_DLL_EXPORTS
		#define _WINDOW_HANLER_LIB_DLL_EXPORT __declspec(dllexport)
	#else
		#define _WINDOW_HANLER_LIB_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define _WINDOW_HANLER_LIB_DLL_EXPORT
#endif

#include "WindowHandle.hpp"
#include <string>

namespace WindowHandler_Lib
{
	class WindowHandler
    {
        std::string title;
#if defined(_WIN32) || defined(__WIN32__)
		HWND hwnd;
		WNDPROC wnd_proc;
		PIXELFORMATDESCRIPTOR pfd;
		WNDCLASS wnd_class;
#else
		GLFWwindow* hwnd;
#endif
	public:
		enum WindowShowMode//not all the values availble for all the platforms
		{
#if defined(_WIN32) || defined(__WIN32__)
			MINIMIZE = SW_MINIMIZE,
			MAXIMIZE = SW_MAXIMIZE,
			HIDE = SW_HIDE,
			RESTORE = SW_RESTORE,
			SHOW = SW_SHOW,
			SHOWDEFAULT = SW_SHOWDEFAULT,//only for windows
			SHOWMAXIMIZED = SW_SHOWMAXIMIZED,
			SHOWMINIMIZED = SW_SHOWMINIMIZED,
			SHOWMINNOACTIVE = SW_SHOWMINNOACTIVE,
			SHOWNA = SW_SHOWNA,
			SHOWNOACTIVATE = SW_SHOWNOACTIVATE,
			SHOWNORMAL = SW_SHOWNORMAL
#else
			MINIMIZE,
			MAXIMIZE,
			HIDE,
			RESTORE,
			SHOW,
			SHOWMAXIMIZED,
			SHOWMINIMIZED,
			SHOWMINNOACTIVE,
			SHOWNA,
			SHOWNOACTIVATE,
			SHOWNORMAL
#endif

		};
		_WINDOW_HANLER_LIB_DLL_EXPORT void create_window(int x, int y, int w, int h, std::string name);//create the window
		_WINDOW_HANLER_LIB_DLL_EXPORT void show_window(WindowShowMode window_show_mode);//show the window, behavior differes between windows and the rest of the platforms
		_WINDOW_HANLER_LIB_DLL_EXPORT void close_window();//close the windows
		_WINDOW_HANLER_LIB_DLL_EXPORT WindowHandle get_handle();//gets a handle to windows
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_width();
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_height();
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_location_x();
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_location_y();
		_WINDOW_HANLER_LIB_DLL_EXPORT std::string get_title();
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_width(int width);
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_height(int height);
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_location_x(int x);
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_location_y(int y);
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_title(std::string title);

#if defined(_WIN32) || defined(__WIN32__)
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_wnd_proc(WNDPROC wnd);//single wnd proc on windows
#else

#endif
	};
}
#endif
