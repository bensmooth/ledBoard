#include "Image.h"

namespace Pix
{
	IImage::IImage(uint32_t width, uint32_t height)
	{
		m_width = width;
		m_height = height;
	}

	IImage::~IImage()
	{
	}

	uint32_t IImage::GetWidth() const
	{
		return m_width;
	}

	uint32_t IImage::GetHeight() const
	{
		return m_height;
	}

	bool IImage::PointIsInBounds(uint32_t x, uint32_t y) const
	{
		if (x < m_width)
		{
			if (y < m_height)
			{
				return true;
			}
		}

		return false;
	}


	ImageBuffer::ImageBuffer(uint32_t width, uint32_t height)
		: IImage(width, height)
	{
		m_image.resize(boost::extents[width][height]);
	}

	ImageBuffer::~ImageBuffer()
	{
	}

	const Color& ImageBuffer::At(uint32_t x, uint32_t y) const
	{
		return m_image[x][y];
	}

	Color& ImageBuffer::At(uint32_t x, uint32_t y)
	{
		return m_image[x][y];
	}
}
