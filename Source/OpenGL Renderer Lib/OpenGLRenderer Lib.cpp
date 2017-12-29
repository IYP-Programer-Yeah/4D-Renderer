/*
 Created By Alireza Arvandi 5/30/2017
 A cross platform openGL renderer lib.
 */

#include "OpenGLRenderer Lib.hpp"
#include "OpenGLHandle.hpp"
#include "../../Includes/GL/glew.h"
#include "../FS Lib/FS Lib.hpp"

namespace OpenGLRenderer_Lib
{
	bool OpenGLRenderer::load_shader(const std::string v_shader_path, const std::string f_shader_path)
	{
		GLint result = GL_FALSE;


		GLuint program_id = glCreateProgram();//creat program


		GLuint last_error = glGetError();


		FS_Lib::File v_shader_file(v_shader_path.c_str());
		if (!v_shader_file.file_exists())
			return false;


		const char* v_shader_data = (char*)v_shader_file.access_data(0);
		size_t v_shader_data_size = v_shader_file.size();

		GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);					
		GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex_shader_id, 1, &v_shader_data, (int*)&v_shader_data_size);			
		glCompileShader(vertex_shader_id);																	



		glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
		char log[1000];
		size_t length;
		if (result == GL_FALSE)
		{
			glGetShaderInfoLog(vertex_shader_id, 1000, (int*)&length, log);				
			return false;
		}

		glAttachShader(program_id, vertex_shader_id);			

		FS_Lib::File f_shader_file(f_shader_path);

		if (f_shader_file.file_exists())
		{
			const char* f_shader_data = (char*)f_shader_file.access_data(0);
			size_t f_shader_data_size = f_shader_file.size();
			glShaderSource(fragment_shader_id, 1, &f_shader_data, (int*)&f_shader_data_size);
			glCompileShader(fragment_shader_id);
			glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);


			if (result == GL_FALSE)
			{
				glGetShaderInfoLog(fragment_shader_id, 1000, (int*)&length, log);
				return false;
			}

			glAttachShader(program_id, fragment_shader_id);
		}

		glBindAttribLocation(program_id, 0, "vert_coord");
		glBindFragDataLocation(program_id, 0, "color");

		glLinkProgram(program_id);
		glGetProgramiv(program_id, GL_LINK_STATUS, &result);

		if (result == GL_FALSE)
		{
			glGetProgramInfoLog(program_id, 1000, (int*)&length, log); //get the log
			return false;
		}

		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);

		this->program_id = program_id;

		return true;
	}

	void OpenGLRenderer::init()
	{
		OpenGLSession this_session(opengl_handle);
		GLuint res = glewInit();
		if (GLEW_OK != res)
			exit(0);
	
		load_shader("../../../Source/OpenGL Renderer Lib/Shaders/VS00.vert", "../../../Source/OpenGL Renderer Lib/Shaders/FS00.frag");
		
		float data[] = { -1.0, -1.0,
						-1.0, 1.0,
						1.0, -1.0,
						1.0, 1.0};

		glGenVertexArrays(1, &VAO_ID);//make a new VAO
		glBindVertexArray(VAO_ID);//bind vao
		glGenBuffers(1, &VBO_ID);//make a new buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);//binde vbo
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8, data, GL_STATIC_DRAW);//send data to vbo
		glEnableVertexAttribArray(0);//set the index 0
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);//set position first pos: 0-Vert_Pos_Size
		glBindVertexArray(0);//unbind vao

		g_location = glGetUniformLocation(program_id, "g");


		glViewport(0, 0, 1024, 728);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(0.0f);
		glDepthFunc(GL_GREATER);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}

	OpenGLRenderer::OpenGLRenderer(const WindowHandler_Lib::WindowHandle &window_handle) : opengl_handle(window_handle) {}
	void OpenGLRenderer::render()
	{
		unsigned int indices[] = { 3, 1, 2, 1, 0, 2 };
		static uint8_t color = 0;
		color++;
		OpenGLSession this_session(opengl_handle);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program_id);
		glBindVertexArray(VAO_ID);
		glUniform1f(g_location, float(color) / 255.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
		auto err = glGetError();
		glBindVertexArray(0);



		opengl_handle.swap_buffers();
	}
}
