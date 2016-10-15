#include <random>
#include "BoardState.h"
#include "Exception.h"

using namespace std;

namespace Pix
{

inline uint32_t AlwaysPositiveModulo(int32_t a, int32_t b)
{
	return (a % b + b) % b;
}

BoardState::BoardState()
{
}

BoardState::~BoardState()
{
}

void BoardState::FromImage(const Image& image, Color deadColor)
{
	if (image.GetWidth() != GRID_WIDTH)
	{
		throw Exception("Incorrect image width!");
	}

	if (image.GetHeight() != GRID_HEIGHT)
	{
		throw Exception("Incorrect image height!");
	}

	for (uint32_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (uint32_t x = 0; x < GRID_WIDTH; x++)
		{
			Color currentCellColor = image.At(x, y);
			bool cellAlive = deadColor != currentCellColor;
			Set(x, y, cellAlive);
		}
	}
}

void BoardState::ToImage(Image& image, Color deadColor, Color aliveColor)
{
	if (image.GetWidth() != GRID_WIDTH)
	{
		throw Exception("Incorrect image width!");
	}

	if (image.GetHeight() != GRID_HEIGHT)
	{
		throw Exception("Incorrect image height!");
	}

	for (uint32_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (uint32_t x = 0; x < GRID_WIDTH; x++)
		{
			bool cellAlive = Get(x, y);
			image.At(x, y) = cellAlive ? aliveColor : deadColor;
		}
	}
}

void BoardState::Randomize(uint64_t seed)
{
	BoardState& randomState = *this;

	minstd_rand randomEngine;
	randomEngine.seed(seed);
	uniform_real_distribution<float> uniformDistribution(0, 1);

	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			bool value = (uniformDistribution(randomEngine) > 0.5f);
			randomState.Set(x, y, value);
		}
	}
}

uint32_t BoardState::GetIndex(uint32_t x, uint32_t y)
{
	// Avoid dumb modulo of negative values.
	x = AlwaysPositiveModulo(x, GRID_WIDTH);
	y = AlwaysPositiveModulo(y, GRID_HEIGHT);

	uint32_t index = x + y * GRID_WIDTH;
	return index;
}

uint8_t BoardState::CountNeighbors(int32_t x, int32_t y) const
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
				if (Get(currentX, currentY))
				{
					count++;
				}
			}
		}
	}

	return count;
}


size_t BoardState::CountAlive() const
{
	return m_lifeState.count();
}

void BoardState::TakeStep(const BoardState& currentState, BoardState& newState)
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			uint8_t neighbourCount = currentState.CountNeighbors(x, y);

			// Any live cell with fewer than two live neighbours dies, as if caused by under-population.
			// Any live cell with more than three live neighbours dies, as if by over-population.
			bool value = false;

			if (neighbourCount == 3)
			{
				// Any cell with exactly three live neighbours becomes a live cell if it wasn't already.
				value = true;
			}
			else if (neighbourCount == 2 && currentState.Get(x, y))
			{
				// Any live cell with two live neighbours lives on to the next generation.
				value = true;
			}

			newState.Set(x, y, value);
		}
	}
}


bool BoardState::Get(uint32_t x, uint32_t y) const
{
	return m_lifeState[GetIndex(x, y)];
}

void BoardState::Set(uint32_t x, uint32_t y, bool value)
{
	m_lifeState[GetIndex(x, y)] = value;
}

}
