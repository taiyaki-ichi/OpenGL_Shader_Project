#pragma once

#pragma comment(lib, "OpenGL32.lib")

#include<Windows.h>
#include<string>
#include<optional>

namespace windows
{
	//ウィンドウの制裁
	//失敗したらnullptrが返ってくる
	std::optional<HWND> create_window(std::string&& windowName, float windowWidth, float windowHeight);

	//OpenGLの初期化
	//HWNDを要求
	std::optional<std::pair<HDC, HGLRC>> init_opengl(HWND hwnd);

	//終了処理
	void shutdown(HWND, HDC, HGLRC);

}