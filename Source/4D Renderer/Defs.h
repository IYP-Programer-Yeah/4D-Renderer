#ifndef _4D_RENDERER_DEFS_
#define _4D_RENDERER_DEFS_
#ifdef _MSC_VER
	#define CurrentDirectory(x) ("../../../" x)
#elseifdef __APPLE__
    #define CurrentDirectory(x) ("../../../" x)
#else
	#define CurrentDirectory(x) (x)
#endif

#endif
