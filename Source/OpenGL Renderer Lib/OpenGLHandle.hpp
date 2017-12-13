/*
 Created By Hosein Ghahremanzadeh 12/12/2017
 A cross platform openGL renderer lib.
 */

#ifndef OPENGL_HANDLE
#define OPENGL_HANDLE

#include "../WindowHandler Lib/WindowHandle.hpp"

#ifdef MS_WINDOWS_ENV
#	include <Windows.h>
#else
#endif

namespace OpenGLRenderer_Lib
{
    class OpenGLHandle
    {
		const void* handle;
		const void* window_handle;
	public:
		OpenGLHandle() = delete;
		OpenGLHandle(const OpenGLHandle&) = delete;
		OpenGLHandle(const OpenGLHandle&&) = delete;
		OpenGLHandle& operator= (const OpenGLHandle&) = delete;
		OpenGLHandle& operator= (const OpenGLHandle&&) = delete;

		OpenGLHandle(const WindowHandler_Lib::WindowHandle &window_handle);
		~OpenGLHandle();
		const void* get_handle() const;
		const void* get_window_handle() const;

		void swap_buffers() const;
	};

	class OpenGLSession
	{
		const OpenGLHandle* oepngl_handle;
	public:
		OpenGLSession(const OpenGLHandle &handle) : oepngl_handle(&handle)
		{
#ifdef MS_WINDOWS_ENV
			wglMakeCurrent((const HDC)(handle.get_window_handle()), (const HGLRC)(oepngl_handle->get_handle()));
#else
#endif
		}
		~OpenGLSession()
		{
#ifdef MS_WINDOWS_ENV
			wglMakeCurrent(NULL, NULL);
#else
#endif
		}

	};
}

#endif
