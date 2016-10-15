#pragma once

#include <bitset>
#include <Image.h>

namespace Pix
{
	class BoardState
	{
	private:
		static constexpr auto LED_DIMENSION = 18;
		static constexpr uint32_t GRID_WIDTH = LED_DIMENSION;
		static constexpr uint32_t GRID_HEIGHT = LED_DIMENSION;

		// Contains the entire state of the board in a bitmap.
		typedef std::bitset<GRID_HEIGHT * GRID_WIDTH> State;

	public:
		BoardState();

		~BoardState();

		// Generates a new random state based on the given seed.
		void Randomize(uint64_t seed);

		// Takes in an image of the correct dimensions, and converts it to a state.
		void FromImage(const Image& image, Color deadColor);

		// Writes the current state to an image.
		void ToImage(Image& image, Color deadColor, Color aliveColor);

		bool Get(uint32_t x, uint32_t y) const;
		void Set(uint32_t x, uint32_t y, bool value);

		// Counts the number of alive neighbors a cell has.
		uint8_t CountNeighbors(int32_t x, int32_t y) const;

		// Returns the number of cells that are alive.
		size_t CountAlive() const;

		// Takes a step forward in the simulation.
		static void TakeStep(const BoardState& currentState, BoardState& newState);

	private:
		static uint32_t GetIndex(uint32_t x, uint32_t y);

		State m_lifeState;
	};
}
