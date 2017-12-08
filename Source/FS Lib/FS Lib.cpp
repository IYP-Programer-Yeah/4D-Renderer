/*
Created By Hosein Ghahremanzadeh 5/9/2017
This is a simple library to access data from files.
*/

#define FS_LIB_DLL_EXPORTS
#include "FS Lib.hpp"
#include <stdexcept>
#include <fstream>


namespace FS_Lib
{
	File::File() : path(), data(), file_read_or_saved(false) {}

	File::File(const std::string& i_path) : path(i_path), data(), file_read_or_saved(read_data_from_file()) {}

	File::File(const File& i_file) : path(i_file.path), data(i_file.data) {}

	File::File(File&& i_file) : path(std::move(i_file.path)), data(std::move(i_file.data)) {}

	File::~File() {}

	File& File::operator= (const File& i_file)
	{
		path = i_file.path;
		data = i_file.data;
		return *this;
	}

	File& File::operator= (File&& i_file)
	{
		path = std::move(i_file.path);
		data = std::move(i_file.data);
		return *this;
	}

	bool File::save() const
	{
		return write_data_to_file();
	}

	bool File::save_as(const std::string& i_path)
	{
		path = i_path;
		file_read_or_saved = write_data_to_file();
		return file_read_or_saved;
	}

	bool File::file_exists()
	{
		return file_read_or_saved;
	}

	bool File::add_data(const void* i_data, std::size_t size, std::size_t at)
	{
		if (at <= data.size())
		{
			data.insert(data.begin() + at, reinterpret_cast<const std::uint8_t*>(i_data), reinterpret_cast<const std::uint8_t*>(i_data) + size);
			return true;
		}
		return false;
	}

	bool File::read_data(void* i_data, std::size_t size, std::size_t at) const
	{
		if ((at + size) <= data.size())
		{
			memcpy(i_data, &data[at], size);
			return true;
		}
		return false;
	}

	const std::uint8_t* File::access_data(std::size_t at) const
	{
		if (at < data.size())
			return &data[at];
		else
			return nullptr;
	}

	std::uint8_t* File::access_data(std::size_t at)
	{
		if (at < data.size())
			return &data[at];
		else
			return nullptr;
	}

	std::size_t File::size()
	{
		return data.size();
	}

	std::string File::get_current_path()
	{
		return path;
	}

	bool File::read_data_from_file()
	{
		std::fstream file(path.c_str(), std::ios::binary | std::ios::in | std::ios::ate);//seek to the end to read the size
		if (!file.is_open())
			return false;

		std::ios::pos_type end = file.tellp();
		if (end == std::ios::pos_type(-1))
			return false;

		data = std::vector<std::uint8_t>(static_cast<std::size_t>(end));

		try
		{
			file.seekp(std::ios::beg);//seek back to beging
			if (data.size() > 0)
				file.read(reinterpret_cast<char*>(&data[0]), data.size());
		}
		catch (std::exception e)
		{
			data.clear();//clear the data so the size will be 0
			return false;
		}
		return true;
	}

	bool File::write_data_to_file() const
	{
		std::fstream file(path.c_str(), std::ios::binary | std::ios::out);
		if (!file.is_open())
			return false;

		try
		{
			if (data.size() > 0)
				file.write(reinterpret_cast<const char*>(&data[0]), data.size());
		}
		catch (std::exception e)
		{
			return false;
		}
		return true;
	}
}