#pragma once

namespace graphic
{
	//fps����p
	class time_keeper
	{
		unsigned int m_now_time;
		const unsigned int m_delta_time;

	public:
		time_keeper(float fps);
		~time_keeper() = default;

		//�o�߂𒲐�
		void adjust();
	};
}