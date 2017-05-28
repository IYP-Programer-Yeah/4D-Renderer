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
		PIXELFORMATDESCRIPTOR pfd;
		WNDCLASS wnd_class;
		DWORD window_style;
#else
        GLFWwindow* hwnd;
        int resizable = GLFW_TRUE;
        int maximized = GLFW_FALSE;
        int red_bits = 8;
        int green_bits = 8;
        int blue_bits = 8;
        int alpha_bits = 8;
        int depth_bits = 24;
        int stencil_bits = 8;
        int accum_red_bits = 0;
        int accum_green_bits = 0;
        int accum_blue_bits = 0;
        int accum_alpha_bits = 0;
        int aux_buffers = 0;
        int stereo = GLFW_FALSE;
        int doublebuffer = GLFW_TRUE;
        int client_api = GLFW_OPENGL_API;
        int context_creation_api = GLFW_NATIVE_CONTEXT_API;
#endif
		void set_title_value(std::string i_title);
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
		enum WindowHints
		{
#if defined(_WIN32) || defined(__WIN32__)
			RESIZABLE,
			MINIMIZED,
			MAXIMIZED,
			RED_BITS,
			GREEN_BITS,
			BLUE_BITS,
			ALPHA_BITS,
			DEPTH_BITS,
			STENCIL_BITS,
			ACCUM_RED_BITS,
			ACCUM_GREEN_BITS,
			ACCUM_BLUE_BITS,
			ACCUM_ALPHA_BITS,
			AUX_BUFFERS,
			STEREO,
			DOUBLEBUFFER,
#else
			RESIZABLE = GLFW_RESIZABLE,
			MAXIMIZED = GLFW_MAXIMIZED,
			RED_BITS = GLFW_RED_BITS,
			GREEN_BITS = GLFW_GREEN_BITS,
			BLUE_BITS = GLFW_BLUE_BITS,
			ALPHA_BITS = GLFW_ALPHA_BITS,
			DEPTH_BITS = GLFW_DEPTH_BITS,
			STENCIL_BITS = GLFW_STENCIL_BITS,
			ACCUM_RED_BITS = GLFW_ACCUM_RED_BITS,
			ACCUM_GREEN_BITS = GLFW_ACCUM_GREEN_BITS,
			ACCUM_BLUE_BITS = GLFW_ACCUM_BLUE_BITS,
			ACCUM_ALPHA_BITS = GLFW_ACCUM_ALPHA_BITS,
			AUX_BUFFERS = GLFW_AUX_BUFFERS,
			STEREO = GLFW_STEREO,
			DOUBLEBUFFER = GLFW_DOUBLEBUFFER,
			CLIENT_API = GLFW_CLIENT_API,
			CONTEXT_CREATION_API = GLFW_CONTEXT_CREATION_API
#endif
		};

		enum HintValues
		{
			HFalse = false,
			HTrue = true,
			HDontCare
		};

		_WINDOW_HANLER_LIB_DLL_EXPORT WindowHandler();
		_WINDOW_HANLER_LIB_DLL_EXPORT void hint_window(WindowHints window_hint, std::uint64_t hint_value);
		_WINDOW_HANLER_LIB_DLL_EXPORT void create_window(int x, int y, int w, int h, std::string i_title);//create the window
		_WINDOW_HANLER_LIB_DLL_EXPORT void show_window(WindowShowMode window_show_mode);//show the window, behavior differes between windows and the rest of the platforms
		_WINDOW_HANLER_LIB_DLL_EXPORT void close_window();//close the windows
		_WINDOW_HANLER_LIB_DLL_EXPORT WindowHandle get_handle();//gets a handle to windows
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_width();
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_height();
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_location_x();
		_WINDOW_HANLER_LIB_DLL_EXPORT int get_location_y();
		_WINDOW_HANLER_LIB_DLL_EXPORT std::string get_title();
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_width(int width);//only accessable after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_height(int height);//only accessable after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_location_x(int x);//only accessable after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_location_y(int y);//only accessable after window creation
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_title(std::string i_title);//only accessable after window creation

#if defined(_WIN32) || defined(__WIN32__)
		_WINDOW_HANLER_LIB_DLL_EXPORT void set_wnd_proc(WNDPROC wnd);//single wnd proc on windows
#else

#endif
	};
}
#endif
