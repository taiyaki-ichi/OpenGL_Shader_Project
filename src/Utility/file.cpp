#include"file.hpp"
#include<fstream>
#include<iostream>

namespace utility
{
	std::optional<std::string> read_file(const std::string& fileName)
	{
		std::ifstream file{ fileName };
		if (!file) {
			std::cout << "faild read_file (file name: " << fileName << ")\n";
			return std::nullopt;
		}
		else
			return std::string{ std::istreambuf_iterator<char>{file},std::istreambuf_iterator<char>{} };
	}

}