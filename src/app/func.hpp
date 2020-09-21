#pragma once
#include<Windows.h>
#include<glew.h>

#include<string>
#include<optional>

namespace graphic
{
	//�E�B���h�E�̍쐻
	//���s������nullopt���Ԃ��Ă���
	std::optional<HWND> create_window(const std::string& windowName, float windowWidth, float windowHeight);

	//OpenGL�̏�����
	//HWND��v��
	std::optional<std::pair<HDC, HGLRC>> init_opengl(HWND hwnd);

	//���b�Z�[�W�����݂���ꍇ�A1��������
	//�A�v���P�[�V�����̏I�����Ȃ킿�E�B���h�E���j�󂳂ꂽ�Ƃ�false
	//����ȊO��true
	bool process_message();

	//�I������
	void shutdown(HWND, HDC, HGLRC);



}