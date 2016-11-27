#include <array>


namespace Pix
{
// Generated from: tom-thumb.pil
class TomThumbFont
{

public:
	typedef std::array<std::array<bool, 4>, 6> FontBitmapType;

	// The number of pixels after each letter.
	static constexpr uint16_t SpacingPixels = 0;

	static constexpr uint16_t LetterHeight = std::tuple_size<FontBitmapType>::value;
	static constexpr uint16_t LetterWidth = std::tuple_size<FontBitmapType::value_type>::value;

	static constexpr FontBitmapType GetCharacterBitmap(char c)
	{
		switch (c)
		{
		case 'a':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 1, 0, 0},
				{0, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'b':
			return FontBitmapType
			{{
				{1, 0, 0, 0},
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'c':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{0, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'd':
			return FontBitmapType
			{{
				{0, 0, 1, 0},
				{0, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'e':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{0, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'f':
			return FontBitmapType
			{{
				{0, 0, 1, 0},
				{0, 1, 0, 0},
				{1, 1, 1, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'g':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{0, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 0, 1, 0},
				{0, 1, 0, 0},
			}};
		case 'h':
			return FontBitmapType
			{{
				{1, 0, 0, 0},
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'i':
			return FontBitmapType
			{{
				{0, 1, 0, 0},
				{0, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'j':
			return FontBitmapType
			{{
				{0, 0, 1, 0},
				{0, 0, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 0, 0},
			}};
		case 'k':
			return FontBitmapType
			{{
				{1, 0, 0, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'l':
			return FontBitmapType
			{{
				{1, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'm':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 1, 1, 0},
				{1, 1, 1, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'n':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'o':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{0, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'p':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{1, 0, 0, 0},
			}};
		case 'q':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{0, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 1, 0},
			}};
		case 'r':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{0, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{0, 0, 0, 0},
			}};
		case 's':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{0, 1, 1, 0},
				{1, 1, 0, 0},
				{0, 1, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 't':
			return FontBitmapType
			{{
				{0, 1, 0, 0},
				{1, 1, 1, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'u':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'v':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'w':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{1, 1, 1, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'x':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 0, 1, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'y':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 1, 0},
				{0, 1, 0, 0},
			}};
		case 'z':
			return FontBitmapType
			{{
				{0, 0, 0, 0},
				{1, 1, 1, 0},
				{0, 1, 1, 0},
				{1, 1, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'A':
			return FontBitmapType
			{{
				{0, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'B':
			return FontBitmapType
			{{
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'C':
			return FontBitmapType
			{{
				{0, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'D':
			return FontBitmapType
			{{
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'E':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'F':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'G':
			return FontBitmapType
			{{
				{0, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'H':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'I':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'J':
			return FontBitmapType
			{{
				{0, 0, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'K':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'L':
			return FontBitmapType
			{{
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'M':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'N':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{1, 1, 1, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'O':
			return FontBitmapType
			{{
				{0, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'P':
			return FontBitmapType
			{{
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'Q':
			return FontBitmapType
			{{
				{0, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'R':
			return FontBitmapType
			{{
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{1, 1, 0, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'S':
			return FontBitmapType
			{{
				{0, 1, 1, 0},
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'T':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'U':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'V':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'W':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'X':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 0, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case 'Y':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case 'Z':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{0, 0, 1, 0},
				{0, 1, 0, 0},
				{1, 0, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case '0':
			return FontBitmapType
			{{
				{0, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case '1':
			return FontBitmapType
			{{
				{0, 1, 0, 0},
				{1, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case '2':
			return FontBitmapType
			{{
				{1, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 1, 0, 0},
				{1, 0, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case '3':
			return FontBitmapType
			{{
				{1, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case '4':
			return FontBitmapType
			{{
				{1, 0, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 0},
			}};
		case '5':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 1, 0, 0},
				{0, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		case '6':
			return FontBitmapType
			{{
				{0, 1, 1, 0},
				{1, 0, 0, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case '7':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{0, 0, 1, 0},
				{0, 1, 0, 0},
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{0, 0, 0, 0},
			}};
		case '8':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
			}};
		case '9':
			return FontBitmapType
			{{
				{1, 1, 1, 0},
				{1, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 0, 1, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
			}};
		default:
			return FontBitmapType
			{{
				{1, 1, 1, 1},
				{1, 1, 1, 1},
				{1, 1, 1, 1},
				{1, 1, 1, 1},
				{1, 1, 1, 1},
				{1, 1, 1, 1},
			}};
		}
	}
};

}
