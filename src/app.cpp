#include"app.hpp"
#include"app/func.hpp"
#include<iostream>
#include"app/handle.hpp"
#include<Windows.h>
#include<glew.h>
#include"app/time_keeper.hpp"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")

namespace graphic
{
	app::app(const std::string& name, float w, float h,float fps)
		:m_is_running{ false }
		, m_handle{nullptr}
		, m_time_keeper{nullptr}
	{
		auto hwnd = create_window(name, w, h);

		if (!hwnd)
			std::cout << "failed window_create";
		//ウィンドウ生成成功
		else
		{
			auto pair = init_opengl(hwnd.value());
			if (!pair)
				std::cout << "failed init_opengl";
			//opengl初期化成功
			else {
				auto flag = glewInit();
				if (flag != GLEW_OK)
					std::cout << "failed glewInit";

				//glewも初期化成功
				else {
					m_is_running = true;
					m_handle = new handle{ hwnd.value(),pair.value().first,pair.value().second };
				}
			}
		}

		m_time_keeper = std::unique_ptr<time_keeper>{ new time_keeper{fps} };
	}

	std::unique_ptr<app> app::create(const std::string& name, float w, float h,float fps)
	{
		return std::unique_ptr<app>{ new app{ name,w,h ,fps } };
	}
	bool app::loop()
	{
		m_time_keeper->adjust();
		return process_message();
	}
	void app::begin_drawing()
	{
		if (m_handle)
			wglMakeCurrent(m_handle->m_hdc, m_handle->m_hglrc);
	}
	void app::finish_drawing()
	{
		if (m_handle)
		{
			glFlush();
			SwapBuffers(m_handle->m_hdc);
			wglMakeCurrent(NULL, NULL);
		}
	}
	

	app::~app()
	{
		if (m_handle) {
			shutdown(m_handle->m_hwnd, m_handle->m_hdc, m_handle->m_hglrc);
			delete m_handle;
		}
	}
}