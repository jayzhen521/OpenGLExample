#include <sstream>

#include <time.h>

#include "Statistics.h"
#include "Util.h"

Statistics::Statistics()
{
	m_frameCount = 0;
	m_frameTime = 0;
	m_fps = 0;

	m_frameTime = m_startTime = GetCurrentTimeMillis();
}

void Statistics::CalcFPS()
{
	m_frameCount++;

	long long time = GetCurrentTimeMillis();

	if (time - m_frameTime >= 1000)
	{
		m_frameTime = time;
		m_fps = m_frameCount;
		m_frameCount = 0;
	}
}

void Statistics::RenderFPS()
{
	std::ostringstream os;
	os << "FPS: " << m_fps;
	//to do:render it to window
}

float Statistics::GetRunningTime()
{
	float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;
	return RunningTime;
}
