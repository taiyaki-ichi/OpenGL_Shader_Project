#pragma once
#include<string>
#include<optional>

namespace utility
{
	//�t�@�C����ǂݍ���string�^�ŕԂ�
	std::optional<std::string> read_file(const std::string& fileName);
}