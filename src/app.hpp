#pragma once
#include<memory>
#include<string>

namespace graphic
{
	struct handle;

	//ウィンドウの管理openglの初期化、glewの初期化
	class app
	{
		bool m_is_running;
		handle* m_handle;

		app(const std::string& windowName, float windowWidth, float windowHeight);
	public:
		//インターフェース
		static std::unique_ptr<app> create(const std::string& windowName, float windowWidth, float windowHeight);

		//メインループ
		bool loop();

		void begin_drawing();
		void finish_drawing();

		~app();
	};
}