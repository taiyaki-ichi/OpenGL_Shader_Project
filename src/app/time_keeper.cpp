#include"time_keeper.hpp"
#include<Windows.h>
#include"func.hpp"

namespace graphic
{
	time_keeper::time_keeper(float fps)
		:m_delta_time{ static_cast<unsigned long>(1000.f / fps) }
		, m_now_time{get_time()}
	{}

	void time_keeper::adjust()
	{
		sleep(m_now_time, m_delta_time);
		m_now_time = get_time();
	}
}