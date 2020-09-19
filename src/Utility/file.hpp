#pragma once
#include<string>
#include<optional>

namespace utility
{
	//ファイルを読み込みstring型で返す
	std::optional<std::string> read_file(const std::string& fileName);
}