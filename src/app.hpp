#pragma once
#include<memory>
#include<string>

namespace graphic
{
	struct handle;

	//�E�B���h�E�̊Ǘ�opengl�̏������Aglew�̏�����
	class app
	{
		bool m_is_running;
		handle* m_handle;

		app(const std::string& windowName, float windowWidth, float windowHeight);
	public:
		//�C���^�[�t�F�[�X
		static std::unique_ptr<app> create(const std::string& windowName, float windowWidth, float windowHeight);

		//���C�����[�v
		bool loop();

		void begin_drawing();
		void finish_drawing();

		~app();
	};
}