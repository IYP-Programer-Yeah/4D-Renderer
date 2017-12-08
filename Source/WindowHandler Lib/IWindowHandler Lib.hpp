/*
Created By Hosein Ghahremanzadeh 5/29/2017
A cross platform window creation lib.
*/

#ifndef IWINDOW_HANLER_LIB
#define IWINDOW_HANLER_LIB

#include <string>
#include "WindowHandle.hpp"
#include "Defs.h"

#ifdef MS_WINDOWS_ENV
#	ifdef IWINDOW_HANLER_LIB_DLL_EXPORTS
#		define IWINDOW_HANLER_LIB_DLL_EXPORT __declspec(dllexport)
#	else
#		define IWINDOW_HANLER_LIB_DLL_EXPORT  __declspec(dllimport)
#	endif
#else
    #define IWINDOW_HANLER_LIB_DLL_EXPORT
#endif

namespace WindowHandler_Lib
{
	struct IWindowHandler
	{
		enum WindowShowMode
		{
			SM_MINIMIZED,
			SM_MAXIMIZED,
			SM_HIDE,
			SM_RESTORE,
			SM_SHOW,
			SM_SHOWDEFAULT,
			SM_SHOWMAXIMIZED,
			SM_SHOWMINIMIZED,
			SM_SHOWMINNOACTIVE,
			SM_SHOWNA,
			SM_SHOWNOACTIVATE,
			SM_SHOWNORMAL
		};
		enum WindowHints
		{
			WH_SUPPORT_OPENGL,
			WH_CONTEXT_CREATION_API,
			WH_RESIZABLE,
			WH_MINIMIZED,
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
			HV_FALSE = false,
			HV_TRUE = true,
			HV_DONTCARE
		};
        virtual ~IWindowHandler() = default;
		virtual void hint_window(WindowHints window_hint, std::uint64_t hint_value) = 0;//hint attributes including pixel formats
		virtual bool create_window(int x, int y, int w, int h, const std::string &i_title) = 0;//create the window
		virtual void show_window(WindowShowMode window_show_mode) = 0;//show the window, behavior differes between Windows and the rest of the platforms
		virtual void close_window() = 0;//close the window
		virtual WindowHandle get_handle() = 0;//gets a handle to window, applys pixel format on Windows
		virtual int get_width() = 0;//only valid after window creation
		virtual int get_height() = 0;//only valid after window creation
		virtual int get_location_x() = 0;//only valid after window creation
		virtual int get_location_y() = 0;//only valid after window creation
		virtual std::string get_title() = 0;//only valid after window creation
		virtual void set_width(int width) = 0;//only valid after window creation
		virtual void set_height(int height) = 0;//only valid after window creation
		virtual void set_location_x(int x) = 0;//only valid after window creation
		virtual void set_location_y(int y) = 0;//only valid after window creation
		virtual void set_title(const std::string &i_title) = 0;//only valid after window creation
		virtual void peek_event() = 0;//doesnt wait for the event
		virtual void get_event() = 0;//waits for the event
		virtual void set_wnd_proc(EventHandlerCallback i_wnd_proc) = 0;
		virtual void set_user_ptr(void* i_user_ptr) = 0;
	};
	IWINDOW_HANLER_LIB_DLL_EXPORT IWindowHandler* cdecl creat_window_handler();
	IWINDOW_HANLER_LIB_DLL_EXPORT void cdecl delete_window_handler(IWindowHandler* window_handler);
}
#endif
