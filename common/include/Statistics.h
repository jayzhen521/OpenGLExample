#pragma once

#include <sys/utime.h>

class Statistics
{
protected:
	Statistics();

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();

private:
	long long m_frameTime;
	long long m_startTime;
	int m_frameCount;
	int m_fps;

};