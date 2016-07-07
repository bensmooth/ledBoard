#include "Image.h"

namespace Pix
{
	Image::Image(uint32_t width, uint32_t height)
	{
		m_image.resize(boost::extents[width][height]);
		m_width = width;
		m_height = height;
	}

	Image::~Image()
	{
	}

	uint32_t Image::GetWidth() const
	{
		return m_width;
	}

	uint32_t Image::GetHeight() const
	{
		return m_height;
	}

	const Color& Image::At(uint32_t x, uint32_t y) const
	{
		return m_image[x][y];
	}

	Color& Image::At(uint32_t x, uint32_t y)
	{
		return m_image[x][y];
	}
}
