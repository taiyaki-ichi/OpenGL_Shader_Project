#pragma once
#include<Windows.h>
#include<string>
#include<optional>

namespace window
{
	//ウィンドウの制裁
	//失敗したらnullptrが返ってくる
	std::optional<HWND> create(std::string&& windowName, float windowWidth, float windowHeight);
}