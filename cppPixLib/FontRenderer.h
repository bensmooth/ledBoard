#pragma once

#include <array>
#include "Image.h"


namespace Pix
{

enum class RenderMode
{
	FixedPitch,
	ProportionalPitch
};

class FontRenderer
{
public:
	// Renders a string onto an image.  Returns the actual width of the rendered string in pixels.
	template<typename FontType>
	static int32_t RenderText(const std::string& text, Image& destination, const Color& color, int32_t x, int32_t y, RenderMode renderMode)
	{
		int32_t renderedWidth = 0;

		for (size_t i = 0; i < text.size(); i++)
		{
			auto bitmap = FontType::GetCharacterBitmap(text[i]);

			uint32_t actualCharacterWidth = RenderCharacter(bitmap, destination, color, x, y);

			renderedWidth = x;

			if ((renderMode == RenderMode::FixedPitch) || (actualCharacterWidth == 0))
			{
				x += FontType::LetterWidth + FontType::SpacingPixels;
			}
			else
			{
				x += actualCharacterWidth + FontType::SpacingPixels;
			}
		}

		return renderedWidth;
	}

	// Renders a character to an image.  Returns the actual width of the character that was rendered.
	template<typename Character>
	static uint32_t RenderCharacter(Character character, Image& destination, const Color& color, int32_t x, uint32_t y)
	{
		uint32_t actualWidth = 0;

		for (uint32_t yf = 0; yf < character.size(); yf++)
		{
			for (uint32_t xf = 0; xf < character[0].size(); xf++)
			{
				if (character[yf][xf])
				{
					actualWidth = std::max(actualWidth, xf + 1);

					uint32_t actualX = xf + x;
					uint32_t actualY = yf + y;

					if (destination.PointIsInBounds(actualX, actualX))
					{
						destination.At(actualX, actualY) = color;
					}
				}
			}
		}

		return actualWidth;
	}
};

}
