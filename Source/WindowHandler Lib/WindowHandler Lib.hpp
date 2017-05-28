/*
Created By Hosein Ghahremanzadeh 5/24/2017
A cross platform window creation lib.
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
		PIXELFORMATDESCRIPTOR pfd;
		WNDCLASS wnd_class;
		DWORD wnd_style;
		void init_pfd();
		void init_wnd_class();
#else
        GLFWwindow* hwnd;
        int wh_resizable;
        int wh_maximized;
		int wh_red_bits;
        int wh_green_bits;
        int wh_blue_bits;
        int wh_alpha_bits;
        int wh_depth_bits;
		int wh_stencil_bits;
		int wh_accum_red_bits;
		int wh_accum_green_bits;
        int wh_accum_blue_bits;
		int wh_accum_alpha_bits;
        int wh_aux_buffers;
        int wh_stereo;
		int wh_doublebuffer;
		int wh_client_api;
		int wh_context_creation_api;
#endif
		void init_wnd_hints();
		void set_title_value(std::string i_title);
	public:
		enum WindowShowMode//not all the values availble for all the platforms
		{
#if defined(_WIN32) || defined(__WIN32__)
			SM_MINIMIZED = SW_MINIMIZE,
			SM_MAXIMIZED = SW_MAXIMIZE,
			SM_HIDE = SW_HIDE,
			SM_RESTORE = SW_RESTORE,
			SM_SHOW = SW_SHOW,
			SM_SHOWDEFAULT = SW_SHOWDEFAULT,//only for windows
			SM_SHOWMAXIMIZED = SW_SHOWMAXIMIZED,
			SM_SHOWMINIMIZED = SW_SHOWMINIMIZED,
			SM_SHOWMINNOACTIVE = SW_SHOWMINNOACTIVE,
			SM_SHOWNA = SW_SHOWNA,
			SM_SHOWNOACTIVATE = SW_SHOWNOACTIVATE,
			SM_SHOWNORMAL = SW_SHOWNORMAL
#else
			SM_MINIMIZED,
			SM_MAXIMIZED,
			SM_HIDE,
			SM_RESTORE,
			SM_SHOW,
			SM_SHOWMAXIMIZED,
			SM_SHOWMINIMIZED,
			SM_SHOWMINNOACTIVE,
			SM_SHOWNA,
			SM_SHOWNOACTIVATE,
			SM_SHOWNORMAL
#endif

		};
		enum WindowHints
		{
#if defined(_WIN32) || defined(__WIN32__)
			WH_MINIMIZED,
#else
			WH_CLIENT_API,
			WH_CONTEXT_CREATION_API,
#endif
			WH_RESIZABLE,
			WH_MAXIMIZED,
			WH_RED_BITS,
			WH_GREEN_BITS,
			WH_BLUE_BITS,
			WH_ALPHA_BITS,
			WH_DEPTH_BITS,
			WH_STENCIL_BITS,
			WH_ACCUM_RED_BITS,
			WH_ACCUM_GREEN_BITS,
			WH_ACCUM_BLUE_BITS,
			WH_ACCUM_ALPHA_BITS,
			WH_AUX_BUFFERS,
			WH_STEREO,
			WH_DOUBLEBUFFER,
		};

		enum HintValues
		{
			HFalse = false,
			HTrue = true,
			HDontCare
		};

		_WINDOW_HANLER_LIB_DLL_EXPORT WindowHandler();
		_WINDOW_HANLER_LIB_DLL_EXPORT void hint_window(WindowHints window_hint, std::uint64_t hint_value);//hint attributes including pixel formats
		_WINDOW_HANLER_LIB_DLL_EXPORT bool create_window(int x, int y, int w, int h, std::string i_title);//create the window
		_WINDOW_HANLER_LIB_DLL_EXPORT void show_window(WindowShowMode window_show_mode);//show the window, behavior differes between Windows and the rest of the platforms
		_WINDOW_HANLER_LIB_DLL_EXPORT void close_window();//close the window
		_WINDOW_HANLER_LIB_DLL_EXPORT WindowHandle get_handle();//gets a handle to window, applys pixel format on Windows
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_width();//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_height();//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_location_x();//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_location_y();//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT std::string get_title();//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_width(int width);//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_height(int height);//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_location_x(int x);//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_location_y(int y);//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_title(std::string i_title);//only accessible after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void peek_event();//doesnt wait for the event
		_WINDOW_HANLER_LIB_DLL_EXPORT void get_event();//waits for the event

#if defined(_WIN32) || defined(__WIN32__)
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_wnd_proc(WNDPROC wnd);//single wnd proc on windows
#else

#endif
	};
}
#endif
