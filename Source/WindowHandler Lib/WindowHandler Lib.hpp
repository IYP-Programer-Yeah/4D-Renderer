/*
Created By Hosein Ghahremanzadeh 5/24/2017
A cross platform window creation lib.
*/

#ifndef WINDOW_HANLER_LIB
#define WINDOW_HANLER_LIB

#include "WindowHandle.hpp"
#include "IWindowHandler Lib.hpp"
#include "Defs.h"

#include <string>
#ifdef MS_WINDOWS_ENV
#	include <Windows.h>
#else
#	include "../../Includes/GLFW/glfw3.h"
#endif

namespace WindowHandler_Lib
{
	struct GLFWHints
	{
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
	};

	class WindowHandler : public IWindowHandler
	{
        static int32_t default_wnd_proc(void* user_ptr);
#if defined(_WIN32) || defined(__WIN32__)
        static LRESULT CALLBACK wnd_proc_handler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#else
        static int64_t call_wnd_proc(GLFWwindow* hwnd, WindowHandler* &window_handler);
        static void pos_event_handler (GLFWwindow *, int, int);
        static void size_event_handler (GLFWwindow *, int, int);
        static void close_event_handler (GLFWwindow *);
        static void refresh_event_handler (GLFWwindow *);
        static void focus_event_handler (GLFWwindow *, int);
        static void iconify_event_handler (GLFWwindow *, int);
        static void buffersize_event_handler (GLFWwindow *, int, int);
        static bool init_glfw();
#endif
        std::string title;
		EventHandlerCallback wnd_proc;
		void* user_ptr;
#if defined(_WIN32) || defined(__WIN32__)
		HWND hwnd;
		PIXELFORMATDESCRIPTOR pfd;
		WNDCLASS wnd_class;
		DWORD wnd_style;
		std::string class_name;
		inline void init_pfd();
		inline void init_wnd_class();
#else
        GLFWwindow* hwnd;
		GLFWHints glfw_hints;
#endif
		inline void init_wnd_hints();
	public:
		WindowHandler();
        ~WindowHandler();
		void hint_window(WindowHints window_hint, std::uint64_t hint_value);//hint attributes including pixel formats
		bool create_window(int x, int y, int w, int h, const std::string &i_title);//create the window
		void show_window(WindowShowMode window_show_mode);//show the window, behavior differes between Windows and the rest of the platforms
		void close_window();//close the window
		WindowHandle get_handle();//gets a handle to window, applys pixel format on Windows
		int get_width();//only valid after window creation
		int get_height();//only valid after window creation
		int get_location_x();//only valid after window creation
		int get_location_y();//only valid after window creation
		std::string get_title();//only valid after window creation
		void set_width(int width);//only valid after window creation
		void set_height(int height);//only valid after window creation
		void set_location_x(int x);//only valid after window creation
		void set_location_y(int y);//only valid after window creation
		void set_title(const std::string &i_title);//only valid after window creation
		void peek_event();//doesnt wait for the event
		void get_event();//waits for the event
		void set_wnd_proc(EventHandlerCallback i_wnd_proc);
		void set_user_ptr(void* i_user_ptr);
	};
}
#endif
