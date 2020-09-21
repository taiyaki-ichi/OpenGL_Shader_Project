#pragma once
#include<Windows.h>

namespace graphic
{
	struct handle
	{
		HWND m_hwnd;
		HDC m_hdc;
		HGLRC m_hglrc;
	};
}