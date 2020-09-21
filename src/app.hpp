#pragma once
#include<memory>
#include<string>

namespace graphic
{
	struct handle;
	class time_keeper;

	//ウィンドウの管理openglの初期化、glewの初期化
	class app
	{
		bool m_is_running;
		handle* m_handle;
		std::unique_ptr<time_keeper> m_time_keeper;

		app(const std::string& windowName, float windowWidth, float windowHeight,float fps);
	public:
		//インターフェース
		static std::unique_ptr<app> create(const std::string& windowName, float windowWidth, float windowHeight, float fps = 60.f);

		//メインループ
		bool loop();

		void begin_drawing();
		void finish_drawing();

		~app();
	};
}