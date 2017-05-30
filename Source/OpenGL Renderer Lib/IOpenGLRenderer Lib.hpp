/*
 Created By Alireza Arvandi 5/30/2017
 A cross platform openGL renderer lib.
 */

#ifndef IOPENGL_RENDERER_LIB
#define IOPENGL_RENDERER_LIB

#if defined(_WIN32) || defined(__WIN32__)
    #ifdef IOPENGL_RENDERER_LIB_DLL_EXPORTS
        #define IOPENGL_RENDERER_LIB_DLL_EXPORT __declspec(dllexport)
    #else
        #define IOPENGL_RENDERER_LIB_DLL_EXPORT  __declspec(dllimport)
    #endif
#else
    #define IOPENGL_RENDERER_LIB_DLL_EXPORT
#endif

namespace OpenGLRenderer_Lib
{
    class IOpenGLRenderer
    {
        
    };
	IOPENGL_RENDERER_LIB_DLL_EXPORT IOpenGLRenderer* create_opengl_renderer();
	IOPENGL_RENDERER_LIB_DLL_EXPORT void delete_opengl_renderer(IOpenGLRenderer* window_handler);

}

#endif
