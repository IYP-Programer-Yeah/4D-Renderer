/*
Created By Hosein Ghahremanzadeh 5/9/2017
This is a simple library to access data from files.
*/

#ifndef _FS_LIB_
#define _FS_LIB_

#if defined(_WIN32) || defined(__WIN32__)
	#ifdef _FS_LIB_DLL_EXPORTS
		#define _FS_LIB_DLL_EXPORT __declspec(dllexport)
	#else
		#define _FS_LIB_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define _FS_LIB_DLL_EXPORT
#endif

#include <vector>
#include <cstdint>


namespace FS_Lib
{
	class File
	{
		std::string path;
		std::vector<std::uint8_t> data;
		bool file_read_or_saved;

		bool read_data_from_file();
		bool write_data_to_file() const;
	public:
		_FS_LIB_DLL_EXPORT File();
		_FS_LIB_DLL_EXPORT File(const std::string& i_path);//trys to open the file, and reads data, if wasnt able to open the file just sets the path
		_FS_LIB_DLL_EXPORT File(const File& i_file);
		_FS_LIB_DLL_EXPORT File(File&& i_file);
		_FS_LIB_DLL_EXPORT ~File();
		_FS_LIB_DLL_EXPORT File& operator= (const File& i_file);
		_FS_LIB_DLL_EXPORT File& operator= (File&& i_file);
		_FS_LIB_DLL_EXPORT bool save() const;//uses the current path to save the file, if the file doesnt exist dont try saving it, use save ass
		_FS_LIB_DLL_EXPORT bool save_as(const std::string& i_path);//save the file to a new path, changes current path
		_FS_LIB_DLL_EXPORT bool file_exists();//checks if the path is valid
		_FS_LIB_DLL_EXPORT bool add_data(void* src, std::size_t size, std::size_t at);//adds data to the file data of given size at given point
		_FS_LIB_DLL_EXPORT bool read_data(void* src, std::size_t size, std::size_t at) const;//reads data of given size at givven point
		_FS_LIB_DLL_EXPORT const std::uint8_t* access_data(std::size_t at) const;//direct access to data at given point, this is the const version
		_FS_LIB_DLL_EXPORT std::uint8_t* access_data(std::size_t at);//direct access to data at given point
		_FS_LIB_DLL_EXPORT std::size_t size();//return the size of data, not the actual file
		_FS_LIB_DLL_EXPORT std::string get_current_path();//returns current file path
	};
}

#endif