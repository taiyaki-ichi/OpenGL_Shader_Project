#include"windows.hpp"
#include<iostream>

int main()
{
	auto hwnd = windows::create_window("aaa", 800.f, 600.f);
	
	if (!hwnd) {
		std::cout << "failed window_create";
		return 0;
	}

	auto pair = windows::init_opengl(hwnd.value());
	if (!pair) {
		std::cout << "failed init_opengl";
		return 0;
	}

	while (windows::process_message()) {};

	windows::shutdown(hwnd.value(), pair.value().first, pair.value().second);

	return 0;
}