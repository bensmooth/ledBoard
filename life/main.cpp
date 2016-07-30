#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cmath>
#include <limits>
#include <memory>
#include <cassert>
#include "IRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"
#include <ImageFile.h>

using namespace std;
using namespace Pix;

constexpr auto LED_DIMENSION = 18;
constexpr uint32_t GRID_WIDTH = LED_DIMENSION;
constexpr uint32_t GRID_HEIGHT = LED_DIMENSION;

const Color DEAD_CELL_COLOR;


inline uint32_t AlwaysPositiveModulo(int32_t a, int32_t b)
{
	return (a % b + b) % b;
}

bool CellIsAlive(const Image& grid, int32_t x, int32_t y)
{
	// Avoid dumb modulo of negative values.
	x = AlwaysPositiveModulo(x, LED_DIMENSION);
	y = AlwaysPositiveModulo(y, LED_DIMENSION);
	return DEAD_CELL_COLOR != grid.At(x, y);
}

uint8_t CountNeighbors(const Image& grid, int32_t x, int32_t y)
{
	uint8_t count = 0;

	for (int32_t dx = -1; dx <= 1; dx++)
	{
		for (int32_t dy = -1; dy <= 1; dy++)
		{
			// Skip center.
			if (dx != 0 || dy != 0)
			{
				int32_t currentX = x + dx;
				int32_t currentY = y + dy;
				if (CellIsAlive(grid, currentX, currentY))
				{
					count++;
				}
			}
		}
	}

	return count;
}

inline uint8_t Psycho(double t)
{
	static constexpr auto PI = std::acos(-1);
	return ((cos(t * PI / 180.0) + 1.0) / 2.0) * std::numeric_limits<uint8_t>::max();
}


uint32_t TakeStep(const Color& aliveColor, const Color& deadColor, const Image& oldGrid, Image& newGrid)
{
	uint32_t aliveCellCount = 0;

	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			uint8_t neighbourCount = CountNeighbors(oldGrid, x, y);

			if (neighbourCount < 2)
			{
				// Any live cell with fewer than two live neighbours dies, as if caused by under-population.
				newGrid.At(x, y) = deadColor;
			}
			else if (neighbourCount == 3)
			{
				// Any cell with exactly three live neighbours becomes a live cell if it wasn't already.
				aliveCellCount++;
				newGrid.At(x, y) = aliveColor;
			}
			else if (neighbourCount > 3)
			{
				// Any live cell with more than three live neighbours dies, as if by over-population.
				aliveCellCount++;
				newGrid.At(x, y) = deadColor;
			}
			else if (neighbourCount == 2 && CellIsAlive(oldGrid, x, y))
			{
				// Any live cell with two live neighbours lives on to the next generation.
				aliveCellCount++;
				newGrid.At(x, y) = aliveColor;
			}
			else
			{
				newGrid.At(x, y) = deadColor;
			}
		}
	}

	return aliveCellCount;
}


int main(int argc, char* argv[])
{
	Image initialState(GRID_WIDTH, GRID_HEIGHT);

	if (argc == 1)
	{
		// TODO: Make this the random mode...
	}
	else if (argc == 2)
	{
		ImageFile::Read(argv[1], initialState);
	}
	else
	{
		cerr << "Usage: " << argv[0] << " <path to file containing initial state>" << endl;
		return -1;
	}

	double elapsed = 0.0;

	chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
	uint64_t totalFrameCount = 0;

	try
	{
		IRenderTargetPtr renderTarget = IRenderTarget::GetDefaultRenderer(argv[0], GRID_WIDTH, GRID_HEIGHT);

		Image grids[2] =
		{
			Image(initialState),
			Image(GRID_WIDTH, GRID_HEIGHT)
		};

		int previousIndex = 0;
		int newIndex = 1;

		FrameTimer timer(30.0);

		uint32_t iterationCount = 0;
		bool stopSimulation = false;

		while (true)
		{
			timer.StartFrame();

			elapsed = (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime).count()) / 1000.0;
			Color currentColor;
			currentColor.Set(Psycho(elapsed * 10.0), Psycho(elapsed * 20.0), Psycho(elapsed * 50.0));

			// Current color should never be all black!
			assert(currentColor != DEAD_CELL_COLOR);

			if (totalFrameCount % 10 == 0 && !stopSimulation)
			{
				uint32_t aliveCellCount = TakeStep(currentColor, DEAD_CELL_COLOR, grids[previousIndex], grids[newIndex]);

				previousIndex = (previousIndex + 1) % 2;
				newIndex = (newIndex + 1) % 2;
				iterationCount++;

				if (aliveCellCount == 0)
				{
					cout << "Ended simulation after " << iterationCount << " iterations." << endl;
					stopSimulation = true;
				}
			}
			else
			{
				// If we don't take a step, we redraw the existing board with the new current color.
				for (int y = 0; y < GRID_HEIGHT; y++)
				{
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						if (CellIsAlive(grids[previousIndex], x, y))
						{
							grids[previousIndex] = currentColor;
						}
					}
				}
			}

			renderTarget->Render(grids[previousIndex]);
			totalFrameCount++;

			timer.EndFrame();
		}
	}
	catch (const exception& ex)
	{
		cerr << "Something bad happened at t=" << elapsed << " - " << ex.what() << endl;
	}

	if (elapsed > 0.0)
	{
		cout << "Average FPS: " << ((double)totalFrameCount / elapsed) << endl;
	}

	return 0;
}
