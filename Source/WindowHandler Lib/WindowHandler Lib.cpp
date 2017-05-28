/*
Created By Hosein Ghahremanzadeh 5/24/2017
This is a simple library to access data from files.
*/

/*
*todo:
*	1-implementaton of the rest of the hints
*	2-handle hinstance on windows
*	3-get attribute
*	4-window creation for windows can be enhanced to support parent window
*/

#define _WINDOW_HANLER_LIB_DLL_EXPORTS
#include "WindowHandler Lib.hpp"
namespace WindowHandler_Lib
{
#if defined(_WIN32) || defined(__WIN32__)
	LRESULT CALLBACK default_wnd_proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hWnd, Msg, wParam, lParam);//return default reaction
	}
#endif

	void WindowHandler::set_title_value(std::string i_title)
	{
		title = i_title;
#if defined(_WIN32) || defined(__WIN32__)
		wnd_class.lpszClassName = title.c_str();//kind safe
#endif
	}

	WindowHandler::WindowHandler() : pfd ()
	{
#if defined(_WIN32) || defined(__WIN32__)
		//init pfd
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

		//init window class
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.lpfnWndProc = NULL;
		wnd_class.cbClsExtra = NULL;
		wnd_class.cbWndExtra = NULL;
		wnd_class.hInstance = NULL;//
		wnd_class.hCursor = LoadCursor(NULL, IDC_ARROW); //set the cursor to arrow
		wnd_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //clear the window with white
		wnd_class.lpszMenuName = NULL;//no menu
		wnd_class.lpfnWndProc = default_wnd_proc;
/*#ifndef _M_X64 //if 32bit
		Main_Windows.WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCEA(IDI_ICON1)); //set the icon 32bit
#else          //if 64bit
		Main_Windows.WndClass.hIcon = LoadIcon(hInstance, (LPCSTR)MAKEINTRESOURCEA(IDI_ICON1)); //set the icon 64bit
#endif*/
		
		//init window style
		wnd_style = WS_OVERLAPPEDWINDOW;
#else
		resizable = GLFW_TRUE;
		maximized = GLFW_FALSE;
		red_bits = 8;
		green_bits = 8;
		blue_bits = 8;
		alpha_bits = 8;
		depth_bits = 24;
		stencil_bits = 8;
		accum_red_bits = 0;
		accum_green_bits = 0;
		accum_blue_bits = 0;
		accum_alpha_bits = 0;
		aux_buffers = 0;
		stereo = GLFW_FALSE;
		doublebuffer = GLFW_TRUE;
		client_api = GLFW_OPENGL_API;
		context_creation_api = GLFW_NATIVE_CONTEXT_API;
#endif
	}
	void WindowHandler::hint_window(WindowHints window_hint, std::uint64_t hint_value)
	{
		switch (window_hint)
		{
		case WH_RESIZABLE:
#if defined(_WIN32) || defined(__WIN32__)
			wnd_style = (hint_value) ? (wnd_style | WS_THICKFRAME) : (wnd_style & !WS_THICKFRAME);
#else
			resizable = (hint) ? GLFW_TRUE : GLFW_FALSE;
#endif
			break;
#if defined(_WIN32) || defined(__WIN32__)
		case WH_MINIMIZED:
			wnd_style = (hint_value) ? (wnd_style | WS_MINIMIZE) : (wnd_style & !WS_MINIMIZE);
			break;
#endif
		case WH_MAXIMIZED:
#if defined(_WIN32) || defined(__WIN32__)
			wnd_style = (hint_value) ? (wnd_style | WS_MAXIMIZE) : (wnd_style & !WS_MAXIMIZE);
#else
#endif
			break;
		case WH_RED_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cRedBits = hint_value;
#else
#endif
			break;
		case WH_GREEN_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cGreenBits = hint_value;
#else
#endif
			break;
		case WH_BLUE_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cBlueBits = hint_value;
#else
#endif
			break;
		case WH_ALPHA_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cAlphaBits = hint_value;
#else
#endif
			break;
		case WH_DEPTH_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cDepthBits = hint_value;
#else
#endif
			break;
		case WH_STENCIL_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cStencilBits = hint_value;
#else
#endif
			break;
		case WH_ACCUM_RED_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cAccumRedBits = hint_value;
#else
#endif
			break;
		case WH_ACCUM_GREEN_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cAccumGreenBits = hint_value;
#else
#endif
			break;
		case WH_ACCUM_BLUE_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cAccumBlueBits = hint_value;
#else
#endif
			break;
		case WH_ACCUM_ALPHA_BITS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cAccumAlphaBits = hint_value;
#else
#endif
			break;
		case WH_AUX_BUFFERS:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.cAuxBuffers = hint_value;
#else
#endif
			break;
		case WH_STEREO:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.dwFlags = (hint_value) ? (hint_value == HTrue ? ((pfd.dwFlags & !PFD_STEREO_DONTCARE) | PFD_STEREO): ((pfd.dwFlags & !PFD_STEREO) | PFD_STEREO_DONTCARE)) : (pfd.dwFlags & !(PFD_STEREO | PFD_STEREO_DONTCARE));//mutually exclusive
#else
#endif
			break;
		case WH_DOUBLEBUFFER:
#if defined(_WIN32) || defined(__WIN32__)
			pfd.dwFlags = (hint_value) ? (hint_value == HTrue ? ((pfd.dwFlags & !PFD_DOUBLEBUFFER_DONTCARE) | PFD_DOUBLEBUFFER) : ((pfd.dwFlags & !PFD_DOUBLEBUFFER) | PFD_DOUBLEBUFFER_DONTCARE)) : (pfd.dwFlags & !(PFD_DOUBLEBUFFER | PFD_DOUBLEBUFFER_DONTCARE));//mutually exclusive
#else
#endif
			break;
		default:
			break;
		}
#else
		glfwWindowHint(window_hint, hint_value);
#endif
	}

	bool WindowHandler::create_window(int x, int y, int w, int h, std::string i_title)
	{
		set_title_value(i_title);
#if defined(_WIN32) || defined(__WIN32__)
		RegisterClass(&wnd_class);
		hwnd = CreateWindow(i_title.c_str(), i_title.c_str(), wnd_style, x, y, w, h, NULL, NULL, NULL, NULL);
#else
#endif
		if (hwnd == NULL)
			return false;
		return true;
	}

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
			glfwIconifyWindow(hwnd);
			break;
		case HIDE:
			glfwHideWindow(hwnd);
			break;
		case RESTORE:
			glfwRestoreWindow(hwnd);
			break;
		case SHOW:
			glfwShowWindow(hwnd);
			glfwFocusWindow(hwnd);
			break;
		case SHOWMAXIMIZED:
			glfwShowWindow(hwnd);
			glfwFocusWindow(hwnd);
			break;
		case SHOWMINIMIZED:
			glfwIconifyWindow(hwnd);
			glfwShowWindow(hwnd);
			glfwFocusWindow(hwnd);
			break;
		case SHOWMINNOACTIVE:
			glfwIconifyWindow(hwnd);
			glfwShowWindow(hwnd);
			break;
		case SHOWNA:
			glfwShowWindow(hwnd);
			break;
		case SHOWNOACTIVATE:
			glfwRestoreWindow(hwnd);
			glfwShowWindow(hwnd);
			break;
		case SHOWNORMAL:
			glfwRestoreWindow(hwnd);
			glfwShowWindow(hwnd);
			glfwFocusWindow(hwnd);
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
		glfwDestroyWindow(hwnd);
#endif
	}

	WindowHandle WindowHandler::get_handle()
	{
		return WindowHandle(hwnd);
	}

#if defined(_WIN32) || defined(__WIN32__)
	void WindowHandler::set_wnd_proc(WNDPROC i_wnd_proc)
	{
		wnd_class.lpfnWndProc = i_wnd_proc;
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
		glfwGetWindowSize(hwnd, &w, &h);
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
		glfwGetWindowSize(hwnd, &w, &h);
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
		glfwGetWindowPos(hwnd, &x, &y);
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
		glfwGetWindowPos(hwnd, &x, &y);
		return y;
#endif
	}

	std::string WindowHandler::get_title()
	{
		return title;
	}

	void WindowHandler::set_width(int width)
	{
#if defined(_WIN32) || defined(__WIN32__)
		SetWindowPos(hwnd, HWND_TOP, 0, 0, width, get_height(), SWP_NOZORDER | SWP_NOMOVE);
#else
		glfwSetWindowSize(hwnd, width, get_height());
#endif
	}

	void WindowHandler::set_height(int height)
	{
#if defined(_WIN32) || defined(__WIN32__)
		SetWindowPos(hwnd, HWND_TOP, get_width(), height, 0, 0, SWP_NOZORDER | SWP_NOMOVE);
#else
		glfwSetWindowSize(hwnd, get_width(), height);
#endif
	}

	void WindowHandler::set_location_x(int x)
	{
#if defined(_WIN32) || defined(__WIN32__)
		SetWindowPos(hwnd, HWND_TOP, x, get_location_y(), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
#else
		glfwSetWindowPos(hwnd, x, get_location_y());
#endif
	}

	void WindowHandler::set_location_y(int y)
	{
#if defined(_WIN32) || defined(__WIN32__)
		SetWindowPos(hwnd, HWND_TOP, get_location_x(), y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
#else
		glfwSetWindowPos(hwnd, get_location_y(), y);
#endif
	}

	void WindowHandler::set_title(std::string i_title)
	{
		set_title_value(i_title);
#if defined(_WIN32) || defined(__WIN32__)
		SetWindowText(hwnd, title.c_str());
#else
		glfwSetWindowTitle(hwnd, title.c_str());
#endif
	}
}
