#include "FrameTimer.h"
#include <thread>

using namespace std;

namespace Pix
{
	int64_t FrameTimer::GetMilliseconds()
	{
		auto duration = chrono::high_resolution_clock::now().time_since_epoch();
		return (chrono::duration_cast<chrono::milliseconds>(duration)).count();
	}

	FrameTimer::FrameTimer(double expectedFramesPerSecond)
		: m_expectedMillisecondsPerFrame(1000.0 / expectedFramesPerSecond)
	{
	}

	void FrameTimer::StartFrame()
	{
		m_currentFrameStartTick = GetMilliseconds();
	}

	void FrameTimer::EndFrame()
	{
		int64_t duration = m_currentFrameStartTick + m_expectedMillisecondsPerFrame - GetMilliseconds();
		this_thread::sleep_for(chrono::milliseconds(duration));
	}
}
