#pragma once
#include <cstdint>

namespace Pix
{
	// Controls how often the renderer is called.  Attempts to keep things renderering at a specified FPS.
	class FrameTimer
	{
	public:
		// Analagous to GetTickCount()...but may go backwards?
		int64_t GetMillseconds();

		FrameTimer(double expectedFramesPerSecond);

		// Should be called before doing work for each frame.
		void StartFrame();

		// Sleeps for the correct amount of time, so that you will hit your desired FPS.
		void EndFrame();

	private:
		int64_t m_expectedMillisecondsPerFrame;
		int64_t m_currentFrameStartTick;
	};
}
