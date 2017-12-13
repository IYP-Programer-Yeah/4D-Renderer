/*
 Created By Alireza Arvandi 5/30/2017
 A cross platform openGL renderer lib.
 */

#include "OpenGLRenderer Lib.hpp"
#include "OpenGLHandle.hpp"
#include "../../Includes/GL/glew.h"

namespace OpenGLRenderer_Lib
{
	OpenGLRenderer::OpenGLRenderer(const WindowHandler_Lib::WindowHandle &window_handle) : opengl_handle(window_handle) {}
	void OpenGLRenderer::render()
	{
		OpenGLSession this_session(opengl_handle);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		auto err = glGetError();
		glClear(GL_COLOR_BUFFER_BIT);
		opengl_handle.swap_buffers();
	}
}
