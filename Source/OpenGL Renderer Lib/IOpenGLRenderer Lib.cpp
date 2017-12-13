/*
 Created By Alireza Arvandi 5/30/2017
 A cross platform openGL renderer lib.
 */

#define IOPENGL_RENDERER_LIB_DLL_EXPORTS

#include "IOpenGLRenderer Lib.hpp"
#include "OpenGLRenderer Lib.hpp"
#include "../WindowHandler Lib/WindowHandle.hpp"

namespace OpenGLRenderer_Lib
{
	IOPENGL_RENDERER_LIB_DLL_EXPORT IOpenGLRenderer* create_opengl_renderer(const WindowHandler_Lib::WindowHandle &window_handle)
	{
		return new OpenGLRenderer(window_handle);
	}
	IOPENGL_RENDERER_LIB_DLL_EXPORT void delete_opengl_renderer(IOpenGLRenderer* window_handler)
	{
		delete window_handler;
	}
}
