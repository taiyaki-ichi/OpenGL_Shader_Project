#pragma once
#include<memory>
#include<string>

namespace graphic
{
	struct handle;
	class time_keeper;

	//�E�B���h�E�̊Ǘ�opengl�̏������Aglew�̏�����
	class app
	{
		bool m_is_running;
		handle* m_handle;
		std::unique_ptr<time_keeper> m_time_keeper;

		app(const std::string& windowName, float windowWidth, float windowHeight,float fps);
	public:
		//�C���^�[�t�F�[�X
		static std::unique_ptr<app> create(const std::string& windowName, float windowWidth, float windowHeight, float fps = 60.f);

		//���C�����[�v
		bool loop();

		void begin_drawing();
		void finish_drawing();

		~app();
	};
}