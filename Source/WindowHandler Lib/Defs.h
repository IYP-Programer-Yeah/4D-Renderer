/*
Created By Hosein Ghahremanzadeh 5/30/2017
A cross platform window creation lib.
*/
#ifndef WINDOW_HANDLER_DEFS
#define WINDOW_HANDLER_DEFS

#if defined(_WIN32) || defined(__WIN32__)
#	define MS_WINDOWS_ENV
#endif

#include <cstdint>
namespace WindowHandler_Lib
{
	typedef std::int32_t(*EventHandlerCallback)(void*);
}
#endif
