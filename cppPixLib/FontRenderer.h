#pragma once

#include <array>
#include "Image.h"


namespace Pix
{

class FontRenderer
{
public:
	template<typename FontType>
	static void RenderText(const std::string& text, Image& destination, const Color& color, int32_t x, int32_t y)
	{
		for (size_t i = 0; i < text.size(); i++)
		{
			auto bitmap = FontType::GetCharacterBitmap(text[i]);

			RenderCharacter(bitmap, destination, color, x, y);

			x += FontType::LetterWidth + FontType::SpacingPixels;
		}
	}

	template<typename Character>
	static void RenderCharacter(Character character, Image& destination, const Color& color, int32_t x, uint32_t y)
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
