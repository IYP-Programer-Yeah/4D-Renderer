/*
 Created By Alireza Arvandi 5/30/2017
 A cross platform openGL renderer lib.
 */

#include "OpenGLRenderer Lib.hpp"
#include "OpenGLHandle.hpp"
#include "../../Includes/GL/glew.h"
#include "../FS Lib/FS Lib.hpp"
#include <cmath>

#define PI  3.14159265359f

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
		glBindAttribLocation(program_id, 1, "normal");
		glBindAttribLocation(program_id, 2, "texture_coord");
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


		//glViewport(0, 0, 1024, 728);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(0.0f);

		glDepthFunc(GL_GREATER);

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);


		g_location = glGetUniformLocation(program_id, "g");

		texture_id;
		glGenTextures(1, &texture_id);

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

		uint8_t *texture = new uint8_t[1024*1024*3];
		for (int i = 0; i < 1024; i++)
			for (int j = 0; j < 1024; j++)
				for (int k = 0; k < 3; k++)
					texture[(i * 1024 + j) * 3 + k] = (i*k)%255;// (i*j / 8192 + k*i / 24);

		glProgramUniform1i(program_id, glGetUniformLocation(program_id, "tex2d"), 0);

		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

		uint32_t count = 101 * 101 + 2;
		float *sphere = new float[count*8];
		indices = new uint32_t[200 * 100 * 3];

		for (int i = 0; i < 101; i++)
			for (int j = 0; j < 101; j++)
			{
				sphere[(i * 101 + j) * 8] = std::cos((PI*i) / 100.0f);
				sphere[(i * 101 + j) * 8 + 1] = std::sin((PI*j) / 100.0f * 2) * std::sin(PI*i / 100.0f);
				sphere[(i * 101 + j) * 8 + 2] = std::cos((PI*j) / 100.0f * 2) * std::sin(PI*i / 100.0f);
				sphere[(i * 101 + j) * 8 + 3] = std::cos((PI*i) / 100.0f);
				sphere[(i * 101 + j) * 8 + 4] = std::sin((PI*j) / 100.0f * 2) * std::sin(PI*i / 100.0f);
				sphere[(i * 101 + j) * 8 + 5] = std::cos((PI*j) / 100.0f * 2) * std::sin(PI*i / 100.0f);
				sphere[(i * 101 + j) * 8 + 6] = i/100.0f;
				sphere[(i * 101 + j) * 8 + 7] = j/100.0f;
			}

		sphere[10000 * 8] = -1.0f;
		sphere[10000 * 8 + 1] = 0.0f;
		sphere[10000 * 8 + 2] = 0.0f;
		sphere[10000 * 8 + 3] = -1.0f;
		sphere[10000 * 8 + 4] = 0.0f;
		sphere[10000 * 8 + 5] = 0.0f;
		sphere[10000 * 8 + 6] = -1.0f;
		sphere[10000 * 8 + 7] = 0.5f;

		sphere[10001 * 8] = 1.0f;
		sphere[10001 * 8 + 1] = 0.0f;
		sphere[10001 * 8 + 2] = 0.0f;
		sphere[10001 * 8 + 3] = 1.0f;
		sphere[10001 * 8 + 4] = 0.0f;
		sphere[10001 * 8 + 5] = 0.0f;
		sphere[10001 * 8 + 6] = 1.0f;
		sphere[10001 * 8 + 7] = 0.5f;

		for (int i = 0; i < 99; i++)
			for (int j = 0; j < 100; j++)
			{
				indices[(i * 100 + j) * 6 + 0] = i * 101 + j;
				indices[(i * 100 + j) * 6 + 1] = i * 101 + j + 1;
				indices[(i * 100 + j) * 6 + 2] = (i + 1) * 101 + j;

				indices[(i * 100 + j) * 6 + 0 + 3] = (i + 1) * 101 + j;
				indices[(i * 100 + j) * 6 + 1 + 3] = (i + 1) * 101 + j + 1;
				indices[(i * 100 + j) * 6 + 2 + 3] = i * 101 + j + 1;
			}


		for (int j = 0; j < 100; j++)
		{
			int i = 99;
			indices[9900 * 6 + 0] = i * 101 + j;
			indices[9900 * 6 + 1] = i * 101 + j + 1;
			indices[9900 * 6 + 2] = 10001;

			i = -1;
			indices[9900 * 6 + 0 + 3] = (i + 1) * 101 + j;
			indices[9900 * 6 + 1 + 3] = (i + 1) * 101 + j + 1;
			indices[9900 * 6 + 2 + 3] = 10000;
		}

		glGenVertexArrays(1, &VAO_ID);//make a new VAO
		glBindVertexArray(VAO_ID);//bind vao
		glGenBuffers(1, &VBO_ID);//make a new buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);//binde vbo
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count * 8, sphere, GL_STATIC_DRAW);//send data to vbo
		glEnableVertexAttribArray(0);//set the index 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);//stride is 0
		glEnableVertexAttribArray(1);//set the index 0
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(2);//set the index 0
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
		glBindVertexArray(0);//unbind vao
		glDeleteBuffers(1, &VBO_ID);

		/*glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);*/


		/*glGenFramebuffers(1, &FBO_ID);

		glGenRenderbuffers(1, &RBO_ID);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO_ID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 1024);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, FBO_ID);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO_ID);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);*/

	}

	OpenGLRenderer::OpenGLRenderer(const WindowHandler_Lib::WindowHandle &window_handle) : opengl_handle(window_handle) {}
	void OpenGLRenderer::render()
	{
		static uint8_t color = 0;
		color++;
		OpenGLSession this_session(opengl_handle);

		/*glBindFramebuffer(GL_FRAMEBUFFER, FBO_ID);
		GLuint buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, buffers);*/

		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program_id);
		glBindVertexArray(VAO_ID);
		glUniform1f(g_location, float(color) / 255.0f);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 60000, GL_UNSIGNED_INT, indices);
		auto err = glGetError();
		glBindVertexArray(0);



		opengl_handle.swap_buffers();
	}
}
