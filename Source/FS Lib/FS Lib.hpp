/*
Created By Hosein Ghahremanzadeh 5/9/2017
This is a simple library to access data from files.
*/

#ifndef FS_LIB
#define FS_LIB

#if defined(_WIN32) || defined(__WIN32__)
	#ifdef FS_LIB_DLL_EXPORTS
		#define FS_LIB_DLL_EXPORT __declspec(dllexport)
	#else
		#define FS_LIB_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define FS_LIB_DLL_EXPORT
#endif

#include <vector>
#include <cstdint>
#include <string>

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
		FS_LIB_DLL_EXPORT File();
		FS_LIB_DLL_EXPORT File(const std::string& i_path);//trys to open the file, and reads data, if wasnt able to open the file just sets the path
		FS_LIB_DLL_EXPORT File(const File& i_file);
		FS_LIB_DLL_EXPORT File(File&& i_file);
		FS_LIB_DLL_EXPORT ~File();
		FS_LIB_DLL_EXPORT File& operator= (const File& i_file);
		FS_LIB_DLL_EXPORT File& operator= (File&& i_file);
		FS_LIB_DLL_EXPORT bool save() const;//uses the current path to save the file, if the file doesnt exist dont try saving it, use save as
		FS_LIB_DLL_EXPORT bool save_as(const std::string& i_path);//save the file to a new path, changes current path
		FS_LIB_DLL_EXPORT bool file_exists();//checks if the path is valid
		FS_LIB_DLL_EXPORT bool add_data(const void* src, std::size_t size, std::size_t at = 0);//adds data to the file data of given size at given point
		FS_LIB_DLL_EXPORT bool read_data(void* src, std::size_t size, std::size_t at = 0) const;//reads data of given size at givven point
		FS_LIB_DLL_EXPORT const std::uint8_t* access_data(std::size_t at = 0) const;//direct access to data at given point, this is the const version
		FS_LIB_DLL_EXPORT std::uint8_t* access_data(std::size_t at = 0);//direct access to data at given point
		FS_LIB_DLL_EXPORT std::size_t size();//return the size of data, not the actual file
		FS_LIB_DLL_EXPORT std::string get_current_path();//returns current file path
	};
}

#endif
