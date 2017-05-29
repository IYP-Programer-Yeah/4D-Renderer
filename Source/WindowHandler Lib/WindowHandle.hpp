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
		void* handle;
	public:
		WindowHandle(void* i_handle);
	};
}
#endif
