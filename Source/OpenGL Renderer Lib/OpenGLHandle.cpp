/*
Created By Hosein Ghahremanzadeh 12/12/2017
A cross platform openGL renderer lib.
*/

#include "Defs.h"
#include "OpenGLHandle.hpp"

#ifdef MS_WINDOWS_ENV
#	include <Windows.h>
#else
#endif

namespace OpenGLRenderer_Lib
{
	OpenGLHandle::OpenGLHandle(const WindowHandler_Lib::WindowHandle &window_handle) :
#ifdef MS_WINDOWS_ENV
																						window_handle(window_handle.handle),
																						handle(wglCreateContext((const HDC)(window_handle.handle)))
#else
																						handle(this->window_handle)
#endif
	{
	}

	OpenGLHandle::~OpenGLHandle()
	{
#ifdef MS_WINDOWS_ENV
		wglDeleteContext((HGLRC)handle);
#else
#endif
	}

	const void* OpenGLHandle::get_handle() const
	{
		return handle;
	}

	const void* OpenGLHandle::get_window_handle() const
	{
		return window_handle;
	}

	void OpenGLHandle::swap_buffers() const
	{
		SwapBuffers((const HDC)window_handle);
	}
}
