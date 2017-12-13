/*
Created By Hosein Ghahremanzadeh 5/24/2017
A cross platform window creation lib.
*/

#ifndef WINDOW_HANLE
#define WINDOW_HANLE

namespace WindowHandler_Lib
{
	class WindowHandle
	{
	public:
		const void* handle;

		WindowHandle() = delete;
		WindowHandle(const void* i_handle) : handle(i_handle) {};
	};
}
#endif
