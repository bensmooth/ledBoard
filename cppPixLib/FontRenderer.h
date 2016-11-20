#pragma once

#include <array>
#include "Image.h"


namespace Pix
{

// From: http://www.dafont.com/visitor.font
class VisitorFont
{
public:
	// The number of pixels after each letter.
	static constexpr uint16_t SpacingPixels()
	{
		return 1;
	}

	static constexpr auto A()
	{
		return std::array<std::array<bool, 3>, 5>
			{{
				{0, 1, 0},
				{1, 0, 1},
				{1, 1, 1},
				{1, 0, 1},
				{1, 0, 1}
			}};
	}
};

class FontRenderer
{
public:
	static void RenderText(const std::string& text, Image& destination, uint16_t x, uint16_t y);

	template<typename Character>
	static void RenderCharacter(Character character, Image& destination, const Color& color, uint16_t x, uint16_t y)
	{
		for (uint32_t yf = 0; yf < character.size(); yf++)
		{
			for (uint32_t xf = 0; xf < character[0].size(); xf++)
			{
				if (character[yf][xf])
				{
					uint32_t actualX = xf + x;
					uint32_t actualY = yf + y;

					if (destination.PointIsInBounds(actualX, actualX))
					{
						destination.At(actualX, actualY) = color;
					}
				}
			}
		}
	}
};

}
