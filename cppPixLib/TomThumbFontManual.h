#include <array>


namespace Pix
{

// From: http://robey.lag.net/2010/01/23/tiny-monospace-font.html
class TomThumbFont
{
public:
	typedef std::array<std::array<bool, 3>, 5> FontBitmapType;

	// The number of pixels after each letter.
	static constexpr uint16_t SpacingPixels = 1;

	static constexpr uint16_t LetterHeight = std::tuple_size<FontBitmapType>::value;

	static constexpr uint16_t LetterWidth = std::tuple_size<FontBitmapType::value_type>::value;

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

}
