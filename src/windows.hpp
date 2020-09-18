#pragma once

#pragma comment(lib, "OpenGL32.lib")

#include<Windows.h>
#include<string>
#include<optional>

namespace windows
{
	//�E�B���h�E�̐���
	//���s������nullptr���Ԃ��Ă���
	std::optional<HWND> create_window(std::string&& windowName, float windowWidth, float windowHeight);

	//OpenGL�̏�����
	//HWND��v��
	std::optional<std::pair<HDC, HGLRC>> init_opengl(HWND hwnd);

	//�I������
	void shutdown(HWND, HDC, HGLRC);

}