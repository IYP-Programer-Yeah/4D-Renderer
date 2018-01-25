/*
 Created By Alireza Arvandi 5/30/2017
 A cross platform openGL renderer lib.
 */

#ifndef OPENGL_RENDERER_LIB
#define OPENGL_RENDERER_LIB


#include "Defs.h"
#include "IOpenGLRenderer Lib.hpp"
#include "OpenGLHandle.hpp"
#include "../WindowHandler Lib/WindowHandle.hpp"
#include "../../Includes/GL/glew.h"

#include <string>

namespace OpenGLRenderer_Lib
{
    class OpenGLRenderer : public IOpenGLRenderer
    {
		GLuint program_id;

		GLuint VAO_ID;
		GLuint VBO_ID;
		GLuint RBO_ID;
		GLuint FBO_ID;

		GLuint g_location;
		GLuint texture_id;
		uint32_t *indices;

		const OpenGLHandle opengl_handle;
		bool load_shader(const std::string v_shader_path, const std::string f_shader_path);
	public:
		OpenGLRenderer() = delete;
		OpenGLRenderer(const WindowHandler_Lib::WindowHandle &window_handle);
		void render();
		void init();
	};
}

#endif