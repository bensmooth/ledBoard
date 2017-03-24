#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <deque>
#include <cmath>
#include <limits>
#include <memory>
#include <cassert>
#include <random>
#include "IRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"
#include "BoardState.h"
#include "ImageFile.h"

using namespace std;
using namespace Pix;

const Color DEAD_CELL_COLOR;

inline uint8_t Psycho(double t)
{
	static constexpr auto PI = std::acos(-1);
	return ((cos(t * PI / 180.0) + 1.0) / 2.0) * std::numeric_limits<uint8_t>::max();
}

enum class TerminationReason
{
	Unknown = 0,
	AllDead,
	Cycling,
	Timeout
};

const char* to_string(TerminationReason reason)
{
	switch(reason)
	{
		case TerminationReason::AllDead:
			return "AllDead";
		case TerminationReason::Cycling:
			return "Cycling";
		case TerminationReason::Timeout:
			return "Timeout";
		default:
			return "Unknown";
	}
}

// Returns the number of iterations that happen before the simulation stops or cycles.
TerminationReason RunLife(IRenderTarget* renderTarget, const BoardState& initialState, uint32_t& outIterationCount)
{
	FrameTimer timer(30.0);
	double elapsed = 0.0;
	TerminationReason terminationReason = TerminationReason::Unknown;

	ImageBuffer image(18, 18);
	BoardState currentState = initialState;

	int previousIndex = 0;
	int newIndex = 1;

	outIterationCount = 0;
	bool stopSimulation = false;
	chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
	uint64_t totalFrameCount = 0;
	std::deque<BoardState> previousStates;

	while (!stopSimulation)
	{
		timer.StartFrame();

		elapsed = (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime).count()) / 1000.0;
		Color currentColor;
		currentColor.Set(Psycho(elapsed * 10.0), Psycho(elapsed * 20.0), Psycho(elapsed * 50.0));

		// Current color should never be all black!
		assert(currentColor != DEAD_CELL_COLOR);

		if (totalFrameCount % 10 == 0 && !stopSimulation)
		{
			BoardState newState;
			BoardState::TakeStep(currentState, newState);

			previousIndex = (previousIndex + 1) % 2;
			newIndex = (newIndex + 1) % 2;
			outIterationCount++;

			size_t aliveCellCount = newState.CountAlive();
			if (aliveCellCount == 0)
			{
				terminationReason = TerminationReason::AllDead;
				stopSimulation = true;
			}

			previousStates.push_back(currentState);
			if (std::find(previousStates.cbegin(), previousStates.cend(), newState) != previousStates.cend())
			{
				stopSimulation = true;
				terminationReason = TerminationReason::Cycling;
			}

			currentState = newState;
		}

		currentState.ToImage(image, currentColor.Inverted(), currentColor);
		renderTarget->Render(image);
		totalFrameCount++;

		timer.EndFrame();
	}

	return terminationReason;
}

int main(int argc, char* argv[])
{
	BoardState initialState;

	try
	{
		IRenderTargetPtr renderTarget = IRenderTarget::GetDefaultRenderer(argv[0], 18, 18);

		bool continueLooping = true;

		while (continueLooping)
		{
			if (argc == 1)
			{
				uint64_t seed = FrameTimer::GetMilliseconds();
				cout << "Seeded with " << seed << endl;
				initialState.Randomize(seed);
			}
			else if (argc == 2)
			{
				ImageBuffer image(18, 18);
				ImageFile::Read(argv[1], image);

				initialState.FromImage(image, DEAD_CELL_COLOR);
				continueLooping = false;
			}
			else
			{
				cerr << "Usage: " << argv[0] << " <path to file containing initial state>" << endl;
				return -1;
			}

			uint32_t iterations;
			TerminationReason reason = RunLife(renderTarget.get(), initialState, iterations);
			cout << "Ran for " << iterations << " iterations until life ended because of " << to_string(reason) << endl;
		}
	}
	catch (const exception& ex)
	{
		cerr << "Something bad happened " << ex.what() << endl;
	}

	return 0;
}
