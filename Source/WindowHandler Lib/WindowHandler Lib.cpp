/*
Created By Hosein Ghahremanzadeh 5/24/2017
A cross platform window creation lib.
*/

/*
*todo:
*	1-implementaton of the rest of the hints
*	2-handle hinstance on windows
*	3-get attribute
*	4-window creation for windows can be enhanced to support parent window
*/
#include <string>
#include "WindowHandle.hpp"
#include "WindowHandler Lib.hpp"
#include "Defs.h"

#ifdef MS_WINDOWS_ENV
#	include <Windows.h>
#	define WINDOW_HANLDER_CLASS_NAME_ID "WHLIB:InstanceID="
#else
#	include "../../Includes/GLFW/glfw3.h"
#endif

namespace WindowHandler_Lib
{
#ifdef MS_WINDOWS_ENV
	static const DWORD gdi_show_mode_map[] = { SW_MINIMIZE, SW_MAXIMIZE, SW_HIDE, SW_RESTORE, SW_SHOW, SW_SHOWDEFAULT, SW_SHOWMAXIMIZED, SW_SHOWMINIMIZED, SW_SHOWMINNOACTIVE, SW_SHOWNA, SW_SHOWNOACTIVATE, SW_SHOWNORMAL };
#endif

    int32_t WindowHandler::default_wnd_proc(void* user_ptr)
    {
        return 0;
    }

#ifdef MS_WINDOWS_ENV
	LRESULT CALLBACK WindowHandler::wnd_proc_handler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_NCCREATE)
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>((reinterpret_cast<CREATESTRUCT*>(lparam))->lpCreateParams));
		int32_t result;
		WindowHandler* window_handler = reinterpret_cast<WindowHandler*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (window_handler != NULL)
		{
			EventHandlerCallback wnd_proc = window_handler->wnd_proc;
			result = wnd_proc(window_handler->user_ptr);
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);//return default reaction
	}
#else
	int64_t WindowHandler::call_wnd_proc(GLFWwindow* hwnd, WindowHandler* &window_handler)
    {
		window_handler = reinterpret_cast<WindowHandler*>(glfwGetWindowUserPointer(hwnd));
        return window_handler->wnd_proc(window_handler->user_ptr);
    }
    
    void WindowHandler::pos_event_handler (GLFWwindow * hwnd, int, int)
    {
		WindowHandler* window_handler;
        std::int64_t result = call_wnd_proc(hwnd, window_handler);
    }
    
    void WindowHandler::size_event_handler (GLFWwindow * hwnd, int, int)
    {
		WindowHandler* window_handler;
		std::int64_t result = call_wnd_proc(hwnd, window_handler);
	}
    
    void WindowHandler::close_event_handler (GLFWwindow * hwnd)
    {
		WindowHandler* window_handler;
		std::int64_t result = call_wnd_proc(hwnd, window_handler);
		if (window_handler && result == 0)
			window_handler->close_window();
	}
    
    void WindowHandler::refresh_event_handler (GLFWwindow * hwnd)
    {
		WindowHandler* window_handler;
		std::int64_t result = call_wnd_proc(hwnd, window_handler);
    }
    
    void WindowHandler::focus_event_handler (GLFWwindow * hwnd, int)
    {
		WindowHandler* window_handler;
		std::int64_t result = call_wnd_proc(hwnd, window_handler);
    }
    
    void WindowHandler::iconify_event_handler (GLFWwindow * hwnd, int)
    {
		WindowHandler* window_handler;
		std::int64_t result = call_wnd_proc(hwnd, window_handler);
    }
    
    void WindowHandler::buffersize_event_handler (GLFWwindow * hwnd, int, int)
    {
		WindowHandler* window_handler;
		std::int64_t result = call_wnd_proc(hwnd, window_handler);
    }
    
	bool WindowHandler::init_glfw()
	{
		static bool glfw_initialized = false;
		if (!glfw_initialized)
			glfw_initialized = glfwInit();
		return glfw_initialized;
	}
#endif

#ifdef MS_WINDOWS_ENV
	void WindowHandler::init_pfd()
	{
		pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			1,
			0,
			0, 0, 0, 0,
			32,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0 };
	}

	void WindowHandler::init_wnd_class()
	{
		//init window class
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		class_name = (std::string(WINDOW_HANLDER_CLASS_NAME_ID) + std::to_string(size_t(this)));
		wnd_class.lpszClassName = class_name.c_str();
		wnd_class.lpfnWndProc = NULL;
		wnd_class.cbClsExtra = NULL;
		wnd_class.cbWndExtra = NULL;
		wnd_class.hInstance = NULL;//
		wnd_class.hCursor = LoadCursor(NULL, IDC_ARROW); //set the cursor to arrow
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)); //clear the window with white
		wnd_class.lpszMenuName = NULL;//no menu
		wnd_class.lpfnWndProc = wnd_proc_handler;
		/*#ifndef _M_X64 //if 32bit
		Main_Windows.WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCEA(IDI_ICON1)); //set the icon 32bit
		#else          //if 64bit
		Main_Windows.WndClass.hIcon = LoadIcon(hInstance, (LPCSTR)MAKEINTRESOURCEA(IDI_ICON1)); //set the icon 64bit
		#endif*/
	}


#else
#endif

	void WindowHandler::init_wnd_hints()
	{
#ifdef MS_WINDOWS_ENV
		init_pfd();
		init_wnd_class();
		//init window style
		wnd_style = WS_OVERLAPPEDWINDOW;
#else
		glfw_hints.wh_resizable = GLFW_TRUE;
		glfw_hints.wh_maximized = GLFW_FALSE;
		glfw_hints.wh_red_bits = 8;
		glfw_hints.wh_green_bits = 8;
		glfw_hints.wh_blue_bits = 8;
		glfw_hints.wh_alpha_bits = 8;
		glfw_hints.wh_depth_bits = 24;
		glfw_hints.wh_stencil_bits = 8;
		glfw_hints.wh_accum_red_bits = 0;
		glfw_hints.wh_accum_green_bits = 0;
		glfw_hints.wh_accum_blue_bits = 0;
		glfw_hints.wh_accum_alpha_bits = 0;
		glfw_hints.wh_aux_buffers = 0;
		glfw_hints.wh_stereo = GLFW_FALSE;
		glfw_hints.wh_doublebuffer = GLFW_TRUE;
		glfw_hints.wh_client_api = GLFW_OPENGL_API;
		glfw_hints.wh_context_creation_api = GLFW_NATIVE_CONTEXT_API;
#endif
	}

	WindowHandler::WindowHandler()
	{
		user_ptr = NULL;
		wnd_proc = default_wnd_proc;
#ifdef MS_WINDOWS_ENV
#else
		init_glfw();
#endif
		init_wnd_hints();
	}
    
    WindowHandler::~WindowHandler()
    {
        close_window();
    }

	void WindowHandler::hint_window(WindowHints window_hint, std::uint64_t hint_value)
	{
		switch (window_hint)
		{
		case WH_SUPPORT_OPENGL:
#ifdef MS_WINDOWS_ENV
#else
            glfw_hints.wh_client_api = (hint_value == HV_TRUE) ? GLFW_OPENGL_API : GLFW_NO_API;
#endif
			break;
		case WH_CONTEXT_CREATION_API:
#ifdef MS_WINDOWS_ENV
#else
#endif
			break;
		case WH_RESIZABLE:
#ifdef MS_WINDOWS_ENV
			wnd_style = (hint_value == HV_TRUE) ? (wnd_style | WS_THICKFRAME) : (wnd_style & !WS_THICKFRAME);
#else
			glfw_hints.wh_resizable = (hint_value == HV_TRUE) ? GLFW_TRUE : GLFW_FALSE;
#endif
			break;
		case WH_MINIMIZED:
#ifdef MS_WINDOWS_ENV
			wnd_style = (hint_value == HV_TRUE) ? (wnd_style | WS_MINIMIZE) : (wnd_style & !WS_MINIMIZE);
#else
#endif
			break;
		case WH_MAXIMIZED:
#ifdef MS_WINDOWS_ENV
			wnd_style = (hint_value == HV_TRUE) ? (wnd_style | WS_MAXIMIZE) : (wnd_style & !WS_MAXIMIZE);
#else
			glfw_hints.wh_maximized = (hint_value == HV_TRUE) ? GLFW_TRUE : GLFW_FALSE;
#endif
			break;
		case WH_RED_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cRedBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_red_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_GREEN_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cGreenBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_green_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_BLUE_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cBlueBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_blue_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_ALPHA_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cAlphaBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_alpha_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_DEPTH_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cDepthBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_depth_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_STENCIL_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cStencilBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_stencil_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_ACCUM_RED_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cAccumRedBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_accum_red_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_ACCUM_GREEN_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cAccumGreenBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_accum_green_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_ACCUM_BLUE_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cAccumBlueBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_accum_blue_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_ACCUM_ALPHA_BITS:
#ifdef MS_WINDOWS_ENV
			pfd.cAccumAlphaBits = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_accum_alpha_bits = static_cast<int>(hint_value);
#endif
			break;
		case WH_AUX_BUFFERS:
#ifdef MS_WINDOWS_ENV
			pfd.cAuxBuffers = static_cast<BYTE>(hint_value);
#else
			glfw_hints.wh_aux_buffers = static_cast<int>(hint_value);
#endif
			break;
		case WH_STEREO:
#ifdef MS_WINDOWS_ENV
			pfd.dwFlags = (hint_value != HV_FALSE) ? (hint_value == HV_TRUE ? ((pfd.dwFlags & !PFD_STEREO_DONTCARE) | PFD_STEREO) : ((pfd.dwFlags & !PFD_STEREO) | PFD_STEREO_DONTCARE)) : (pfd.dwFlags & !(PFD_STEREO | PFD_STEREO_DONTCARE));//mutually exclusive
#else
			glfw_hints.wh_stereo = (hint_value) ? GLFW_TRUE : GLFW_FALSE;
#endif
			break;
		case WH_DOUBLEBUFFER:
#ifdef MS_WINDOWS_ENV
			pfd.dwFlags = (hint_value != HV_FALSE) ? (hint_value == HV_TRUE ? ((pfd.dwFlags & !PFD_DOUBLEBUFFER_DONTCARE) | PFD_DOUBLEBUFFER) : ((pfd.dwFlags & !PFD_DOUBLEBUFFER) | PFD_DOUBLEBUFFER_DONTCARE)) : (pfd.dwFlags & !(PFD_DOUBLEBUFFER | PFD_DOUBLEBUFFER_DONTCARE));//mutually exclusive
#else
			glfw_hints.wh_doublebuffer = (hint_value == HV_TRUE) ? GLFW_TRUE : GLFW_FALSE;
#endif
			break;
		default:
			break;
		}
	}

	bool WindowHandler::create_window(std::int64_t x, std::int64_t y, std::int64_t w, std::int64_t h, const std::string &i_title)
	{
		title = i_title;
#ifdef MS_WINDOWS_ENV
		RegisterClass(&wnd_class);
		hwnd = CreateWindow(wnd_class.lpszClassName, i_title.c_str(), wnd_style, x, y, w, h, NULL, NULL, NULL, this);
#else
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, glfw_hints.wh_resizable);
		glfwWindowHint(GLFW_MAXIMIZED, glfw_hints.wh_maximized);
		glfwWindowHint(GLFW_RED_BITS, glfw_hints.wh_red_bits);
		glfwWindowHint(GLFW_GREEN_BITS, glfw_hints.wh_green_bits);
		glfwWindowHint(GLFW_BLUE_BITS, glfw_hints.wh_blue_bits);
		glfwWindowHint(GLFW_ALPHA_BITS, glfw_hints.wh_alpha_bits);
		glfwWindowHint(GLFW_DEPTH_BITS, glfw_hints.wh_depth_bits);
		glfwWindowHint(GLFW_STENCIL_BITS, glfw_hints.wh_stencil_bits);
		glfwWindowHint(GLFW_ACCUM_RED_BITS, glfw_hints.wh_accum_red_bits);
		glfwWindowHint(GLFW_ACCUM_GREEN_BITS, glfw_hints.wh_accum_green_bits);
		glfwWindowHint(GLFW_ACCUM_BLUE_BITS, glfw_hints.wh_accum_blue_bits);
		glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, glfw_hints.wh_accum_alpha_bits);
		glfwWindowHint(GLFW_AUX_BUFFERS, glfw_hints.wh_aux_buffers);
		glfwWindowHint(GLFW_STEREO, glfw_hints.wh_stereo);
		glfwWindowHint(GLFW_DOUBLEBUFFER, glfw_hints.wh_doublebuffer);
		glfwWindowHint(GLFW_CLIENT_API, glfw_hints.wh_client_api);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API, glfw_hints.wh_context_creation_api);
		hwnd = glfwCreateWindow(static_cast<int>(w), static_cast<int>(h), i_title.c_str(), NULL, NULL);
        glfwSetWindowUserPointer(hwnd, this);
        glfwSetWindowPosCallback(hwnd, pos_event_handler);
        glfwSetWindowSizeCallback(hwnd, size_event_handler);
        glfwSetWindowCloseCallback(hwnd, close_event_handler);
        glfwSetWindowRefreshCallback(hwnd, refresh_event_handler);
        glfwSetWindowFocusCallback(hwnd, focus_event_handler);
        glfwSetWindowIconifyCallback(hwnd, iconify_event_handler);
        glfwSetFramebufferSizeCallback(hwnd, buffersize_event_handler);
#endif
		if (hwnd == NULL)
			return false;
#ifdef MS_WINDOWS_ENV
#else
		set_location_x(x);
		set_location_y(y);
#endif
		return true;
	}

	void WindowHandler::show_window(WindowShowMode window_show_mode)
	{
#ifdef MS_WINDOWS_ENV
		ShowWindow(hwnd, gdi_show_mode_map[window_show_mode]);
#else
		switch (window_show_mode)
		{
		case SM_MAXIMIZED:
			glfwMaximizeWindow(hwnd);
			break;
		case SM_MINIMIZED:
			glfwIconifyWindow(hwnd);
			break;
		case SM_HIDE:
			glfwHideWindow(hwnd);
			break;
		case SM_RESTORE:
			glfwRestoreWindow(hwnd);
			break;
        case SM_SHOW:
            glfwFocusWindow(hwnd);
			glfwShowWindow(hwnd);
			break;
		case SM_SHOWMAXIMIZED:
			glfwFocusWindow(hwnd);
            glfwMaximizeWindow(hwnd);
			break;
		case SM_SHOWMINIMIZED:
            glfwFocusWindow(hwnd);
			glfwIconifyWindow(hwnd);
			break;
		case SM_SHOWMINNOACTIVE:
			glfwIconifyWindow(hwnd);
			break;
		case SM_SHOWNA:
			glfwShowWindow(hwnd);
			break;
		case SM_SHOWNOACTIVATE:
			glfwRestoreWindow(hwnd);
			break;
        case SM_SHOWNORMAL:
            glfwFocusWindow(hwnd);
			glfwRestoreWindow(hwnd);
			break;
		default:
			break;
		}
#endif
	}

	void WindowHandler::close_window()
	{
#ifdef MS_WINDOWS_ENV
		DestroyWindow(hwnd);
#else
		glfwDestroyWindow(hwnd);
#endif
	}

	WindowHandle WindowHandler::get_handle()
	{
#ifdef MS_WINDOWS_ENV
		HDC hdc = GetDC(hwnd);
		int current_pf = GetPixelFormat(hdc);
		int pf = ChoosePixelFormat(hdc, &pfd); //layer masks ignored
		if (pf != current_pf)
			SetPixelFormat(hdc, current_pf, &pfd);
		WindowHandle window_handle(&hdc);
#else
		WindowHandle window_handle(&hwnd);
#endif
		return window_handle;
	}

	std::int64_t WindowHandler::get_width()
	{
#ifdef MS_WINDOWS_ENV
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		return window_rect.right - window_rect.left;
#else
		int h, w;
		glfwGetWindowSize(hwnd, &w, &h);
		return w;
#endif
	}

	std::int64_t WindowHandler::get_height()
	{
#ifdef MS_WINDOWS_ENV
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		return window_rect.bottom - window_rect.top;
#else
		int h, w;
		glfwGetWindowSize(hwnd, &w, &h);
		return h;
#endif
	}

	std::int64_t WindowHandler::get_location_x()
	{
#ifdef MS_WINDOWS_ENV
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		return window_rect.left;
#else
		int x, y;
		glfwGetWindowPos(hwnd, &x, &y);
		return x;
#endif
	}

	std::int64_t WindowHandler::get_location_y()
	{
#ifdef MS_WINDOWS_ENV
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		return window_rect.top;
#else
		int x, y;
		glfwGetWindowPos(hwnd, &x, &y);
		return y;
#endif
	}

	std::string WindowHandler::get_title()
	{
		return title;
	}

	void WindowHandler::set_width(std::int64_t width)
	{
#ifdef MS_WINDOWS_ENV
		SetWindowPos(hwnd, HWND_TOP, 0, 0, width, get_height(), SWP_NOZORDER | SWP_NOMOVE);
#else
		glfwSetWindowSize(hwnd, static_cast<int>(width), static_cast<int>(get_height()));
#endif
	}

	void WindowHandler::set_height(std::int64_t height)
	{
#ifdef MS_WINDOWS_ENV
		SetWindowPos(hwnd, HWND_TOP, get_width(), height, 0, 0, SWP_NOZORDER | SWP_NOMOVE);
#else
		glfwSetWindowSize(hwnd, static_cast<int>(get_width()), static_cast<int>(height));
#endif
	}

	void WindowHandler::set_location_x(std::int64_t x)
	{
#ifdef MS_WINDOWS_ENV
		SetWindowPos(hwnd, HWND_TOP, x, get_location_y(), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
#else
		glfwSetWindowPos(hwnd, static_cast<int>(x), static_cast<int>(get_location_y()));
#endif
	}

	void WindowHandler::set_location_y(std::int64_t y)
	{
#ifdef MS_WINDOWS_ENV
		SetWindowPos(hwnd, HWND_TOP, get_location_x(), y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
#else
		glfwSetWindowPos(hwnd, static_cast<int>(get_location_y()), static_cast<int>(y));
#endif
	}

	void WindowHandler::set_title(const std::string &i_title)
	{
		title = i_title;
#ifdef MS_WINDOWS_ENV
		SetWindowText(hwnd, title.c_str());
#else
		glfwSetWindowTitle(hwnd, title.c_str());
#endif
	}

	void WindowHandler::peek_event()
	{
#ifdef MS_WINDOWS_ENV
		MSG msg;
		if (PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
#else
		glfwPollEvents();
#endif
	}

	void WindowHandler::get_event()
	{
#ifdef MS_WINDOWS_ENV
		MSG msg;
		if (GetMessage(&msg, hwnd, NULL, NULL))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
#else
		glfwWaitEvents();
#endif
	}

	void WindowHandler::set_wnd_proc(EventHandlerCallback i_wnd_proc)
	{
		wnd_proc = i_wnd_proc;
	}

	void WindowHandler::set_user_ptr(void* i_user_ptr)
	{
		user_ptr = i_user_ptr;
	}

}
