#ifndef _4D_RENDERER_DEFS_
#define _4D_RENDERER_DEFS_

#ifdef _MSC_VER
	#ifdef _DEBUG
		#define CurrentDirectory(x) ("../../../" x)
	#else
		#define CurrentDirectory(x) ("" x)
	#endif
#elif defined(__APPLE__)
	#ifdef DEBUG
		#define CurrentDirectory(x) ("../../../" x)
	#else
		#define CurrentDirectory(x) ("" x)
	#endif
#else
	#define CurrentDirectory(x) ("" x)
#endif

#endif
