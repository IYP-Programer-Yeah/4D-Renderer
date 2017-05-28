/*
Created By Hosein Ghahremanzadeh 5/24/2017
This is a simple library to access data from files.
*/

/*
*todo:
*	1-implementaton of the rest of the hints
*	2-handle hinstance on windows
*	3-get attribute
*
*/

#define _WINDOW_HANLER_LIB_DLL_EXPORTS
#include "WindowHandler Lib.hpp"
namespace WindowHandler_Lib
{

	void WindowHandler::set_title_value(std::string i_title)
	{
		title = i_title;
#if defined(_WIN32) || defined(__WIN32__)
		wnd_class.lpszClassName = title.c_str();//kind safe
#endif
	}



	WindowHandler::WindowHandler() : pfd ()
	{
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
/*#ifndef _M_X64 //if 32bit
		Main_Windows.WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCEA(IDI_ICON1)); //set the icon 32bit
#else          //if 64bit
		Main_Windows.WndClass.hIcon = LoadIcon(hInstance, (LPCSTR)MAKEINTRESOURCEA(IDI_ICON1)); //set the icon 64bit
#endif*/
		
		//init window style
		window_style = 0;
	}
	void WindowHandler::hint_window(WindowHints window_hint, std::uint64_t hint_value)
	{
#if defined(_WIN32) || defined(__WIN32__)
		switch (window_hint)
		{
		case RESIZABLE:
			window_style = (hint_value) ? (window_style | WS_THICKFRAME) : (window_style & !WS_THICKFRAME);
			break;
		case MINIMIZED:
			window_style = (hint_value) ? (window_style | WS_MINIMIZE) : (window_style & !WS_MINIMIZE);
			break;
		case MAXIMIZED:
			window_style = (hint_value) ? (window_style | WS_MAXIMIZE) : (window_style & !WS_MAXIMIZE);
			break;
		case RED_BITS:
			pfd.cRedBits = hint_value;
			break;
		case GREEN_BITS:
			pfd.cGreenBits = hint_value;
			break;
		case BLUE_BITS:
			pfd.cBlueBits = hint_value;
			break;
		case ALPHA_BITS:
			pfd.cAlphaBits = hint_value;
			break;
		case DEPTH_BITS:
			pfd.cDepthBits = hint_value;
			break;
		case STENCIL_BITS:
			pfd.cStencilBits = hint_value;
			break;
		case ACCUM_RED_BITS:
			pfd.cAccumRedBits = hint_value;
			break;
		case ACCUM_GREEN_BITS:
			pfd.cAccumGreenBits = hint_value;
			break;
		case ACCUM_BLUE_BITS:
			pfd.cAccumBlueBits = hint_value;
			break;
		case ACCUM_ALPHA_BITS:
			pfd.cAccumAlphaBits = hint_value;
			break;
		case AUX_BUFFERS:
			pfd.cAuxBuffers = hint_value;
			break;
		case STEREO:
			pfd.dwFlags = (hint_value) ? (hint_value == HTrue ? ((pfd.dwFlags & !PFD_STEREO_DONTCARE) | PFD_STEREO): ((pfd.dwFlags & !PFD_STEREO) | PFD_STEREO_DONTCARE)) : (pfd.dwFlags & !(PFD_STEREO | PFD_STEREO_DONTCARE));//mutually exclusive
			break;
		case DOUBLEBUFFER:
			pfd.dwFlags = (hint_value) ? (hint_value == HTrue ? ((pfd.dwFlags & !PFD_DOUBLEBUFFER_DONTCARE) | PFD_DOUBLEBUFFER) : ((pfd.dwFlags & !PFD_DOUBLEBUFFER) | PFD_DOUBLEBUFFER_DONTCARE)) : (pfd.dwFlags & !(PFD_DOUBLEBUFFER | PFD_DOUBLEBUFFER_DONTCARE));//mutually exclusive
			break;
		default:
			break;
		}
#else
		glfwWindowHint(window_hint, hint_value);
#endif
	}

	void WindowHandler::create_window(int x, int y, int w, int h, std::string i_title)
	{
		
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
