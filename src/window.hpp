#pragma once
#include<Windows.h>
#include<string>
#include<optional>

namespace window
{
	//�E�B���h�E�̐���
	//���s������nullptr���Ԃ��Ă���
	std::optional<HWND> create(std::string&& windowName, float windowWidth, float windowHeight);
}