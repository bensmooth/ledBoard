#pragma once

#include <array>
#include "Image.h"


namespace Pix
{

// From: http://www.dafont.com/visitor.font


// From: http://robey.lag.net/2010/01/23/tiny-monospace-font.html
class TomThumbFont
{
public:
	// The number of pixels after each letter.
	static constexpr uint16_t SpacingPixels()
	{
		return 1;
	}

	typedef std::array<std::array<bool, 3>, 5> FontBitmapType;

	static constexpr FontBitmapType GetCharacterBitmap(char c)
	{
		switch (c)
		{
		case 'A':
			return FontBitmapType
			{{
				{0, 1, 0},
				{1, 0, 1},
				{1, 1, 1},
				{1, 0, 1},
				{1, 0, 1}
			}};
		case 'B':
			return FontBitmapType
			{{
				{1, 1, 0},
				{1, 0, 1},
				{1, 1, 0},
				{1, 0, 1},
				{1, 1, 0}
			}};
		case 'C':
			return FontBitmapType
			{{
				{0, 1, 1},
				{1, 0, 0},
				{1, 0, 0},
				{1, 0, 0},
				{0, 1, 1}
			}};
		case 'D':
			return FontBitmapType
			{{
				{1, 1, 0},
				{1, 0, 1},
				{1, 0, 1},
				{1, 0, 1},
				{1, 1, 0}
			}};
		case 'E':
			return FontBitmapType
			{{
				{1, 1, 1},
				{1, 0, 0},
				{1, 1, 1},
				{1, 0, 0},
				{1, 1, 1}
			}};
		case 'F':
			return FontBitmapType
			{{
				{1, 1, 1},
				{1, 0, 0},
				{1, 1, 1},
				{1, 0, 0},
				{1, 0, 0}
			}};
		case 'G':
			return FontBitmapType
			{{
				{0, 1, 1},
				{1, 0, 0},
				{1, 1, 1},
				{1, 0, 1},
				{0, 1, 1}
			}};
		case 'H':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 0, 1},
				{1, 1, 1},
				{1, 0, 1},
				{1, 0, 1}
			}};
		case 'I':
			return FontBitmapType
			{{
				{1, 1, 1},
				{0, 1, 0},
				{0, 1, 0},
				{0, 1, 0},
				{1, 1, 1}
			}};
		case 'J':
			return FontBitmapType
			{{
				{0, 0, 1},
				{0, 0, 1},
				{0, 0, 1},
				{1, 0, 1},
				{0, 1, 0}
			}};
		case 'K':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 0, 1},
				{1, 1, 0},
				{1, 0, 1},
				{1, 0, 1}
			}};
		case 'L':
			return FontBitmapType
			{{
				{1, 0, 0},
				{1, 0, 0},
				{1, 0, 0},
				{1, 0, 0},
				{1, 1, 1}
			}};
		case 'M':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 1, 1},
				{1, 1, 1},
				{1, 0, 1},
				{1, 0, 1}
			}};
		case 'N':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 1, 1},
				{1, 1, 1},
				{1, 1, 1},
				{1, 0, 1}
			}};
		case 'O':
			return FontBitmapType
			{{
				{0, 1, 0},
				{1, 0, 1},
				{1, 0, 1},
				{1, 0, 1},
				{0, 1, 0}
			}};
		case 'P':
			return FontBitmapType
			{{
				{1, 1, 0},
				{1, 0, 1},
				{1, 1, 0},
				{1, 0, 0},
				{1, 0, 0}
			}};
		case 'Q':
			return FontBitmapType
			{{
				{0, 1, 0},
				{1, 0, 1},
				{1, 0, 1},
				{1, 1, 1},
				{0, 1, 1}
			}};
		case 'R':
			return FontBitmapType
			{{
				{1, 1, 0},
				{1, 0, 1},
				{1, 1, 1},
				{1, 1, 0},
				{1, 0, 1}
			}};
		case 'S':
			return FontBitmapType
			{{
				{0, 1, 1},
				{1, 0, 0},
				{0, 1, 0},
				{0, 0, 1},
				{1, 1, 0}
			}};
		case 'T':
			return FontBitmapType
			{{
				{1, 1, 1},
				{0, 1, 0},
				{0, 1, 0},
				{0, 1, 0},
				{0, 1, 0}
			}};
		case 'U':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 0, 1},
				{1, 0, 1},
				{1, 0, 1},
				{0, 1, 1}
			}};
		case 'V':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 0, 1},
				{1, 0, 1},
				{0, 1, 0},
				{0, 1, 0}
			}};
		case 'W':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 0, 1},
				{1, 1, 1},
				{1, 1, 1},
				{1, 0, 1}
			}};
		case 'X':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 0, 1},
				{0, 1, 0},
				{1, 0, 1},
				{1, 0, 1}
			}};
		case 'Y':
			return FontBitmapType
			{{
				{1, 0, 1},
				{1, 0, 1},
				{0, 1, 0},
				{0, 1, 0},
				{0, 1, 0}
			}};
		case 'Z':
			return FontBitmapType
			{{
				{1, 1, 1},
				{0, 0, 1},
				{0, 1, 0},
				{1, 0, 0},
				{1, 1, 1}
			}};
		case ' ':
			return FontBitmapType
			{{
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0}
			}};
		case '.':
			return FontBitmapType
			{{
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0},
				{0, 1, 0}
			}};
		case '!':
			return FontBitmapType
			{{
				{0, 1, 0},
				{0, 1, 0},
				{0, 1, 0},
				{0, 0, 0},
				{0, 1, 0}
			}};
		case '?':
			return FontBitmapType
			{{
				{1, 1, 1},
				{0, 0, 1},
				{0, 1, 0},
				{0, 0, 0},
				{0, 1, 0}
			}};
		case '+':
			return FontBitmapType
			{{
				{0, 0, 0},
				{0, 1, 0},
				{1, 1, 1},
				{0, 1, 0},
				{0, 0, 0}
			}};
		case '-':
			return FontBitmapType
			{{
				{0, 0, 0},
				{0, 0, 0},
				{1, 1, 1},
				{0, 0, 0},
				{0, 0, 0}
			}};
		default:
			return FontBitmapType
			{{
				{1, 1, 1},
				{1, 1, 1},
				{1, 1, 1},
				{1, 1, 1},
				{1, 1, 1}
			}};
		}
	}
};

class FontRenderer
{
public:
	template<typename FontType>
	static void RenderText(const std::string& text, Image& destination, const Color& color, uint16_t x, uint16_t y)
	{
		for (size_t i = 0; i < text.size(); i++)
		{
			auto bitmap = FontType::GetCharacterBitmap(text[i]);

			RenderCharacter(bitmap, destination, color, x, y);

			x += bitmap[0].size() + FontType::SpacingPixels();
		}
	}

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
