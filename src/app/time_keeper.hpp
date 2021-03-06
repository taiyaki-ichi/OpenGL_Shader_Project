#pragma once

namespace graphic
{
	//fps制御用
	class time_keeper
	{
		unsigned int m_now_time;
		const unsigned int m_delta_time;

	public:
		time_keeper(float fps);
		~time_keeper() = default;

		//経過を調整
		void adjust();
	};
}