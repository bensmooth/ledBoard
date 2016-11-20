#pragma once
#include "Color.h"
#include "boost/multi_array.hpp"

namespace Pix
{
	class Image
	{
	public:
		Image(uint32_t width, uint32_t height);
		virtual ~Image();

		const Color& At(uint32_t x, uint32_t y) const;
		Color& At(uint32_t x, uint32_t y);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		bool PointIsInBounds(uint32_t x, uint32_t y) const;

	private:
		typedef boost::multi_array<Color, 2> ImageArray;
		ImageArray m_image;
		uint32_t m_width;
		uint32_t m_height;
	};
}
