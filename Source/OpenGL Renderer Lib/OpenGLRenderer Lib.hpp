/*
 Created By Alireza Arvandi 5/30/2017
 A cross platform openGL renderer lib.
 */

#ifndef OPENGL_RENDERER_LIB
#define OPENGL_RENDERER_LIB

#include "IOpenGLRenderer Lib.hpp"
#include "OpenGLHandle.hpp"
#include "../WindowHandler Lib/WindowHandle.hpp"

namespace OpenGLRenderer_Lib
{
    class OpenGLRenderer : public IOpenGLRenderer
    {
		const OpenGLHandle opengl_handle;
	public:
		OpenGLRenderer() = delete;
		OpenGLRenderer(const WindowHandler_Lib::WindowHandle &window_handle);
		void render();
	};
}

#endif