#pragma once
#include "Color.h"
#include "boost/multi_array.hpp"

namespace Pix
{
	class IImage
	{
	public:
		IImage(uint32_t width, uint32_t height);
		virtual ~IImage() = 0;

		virtual const Color& At(uint32_t x, uint32_t y) const = 0;
		virtual Color& At(uint32_t x, uint32_t y) = 0;

		virtual uint32_t GetWidth() const;
		virtual uint32_t GetHeight() const;
		virtual bool PointIsInBounds(uint32_t x, uint32_t y) const;

	private:
		uint32_t m_width;
		uint32_t m_height;
	};


	// Image class that contains a 2d array of pixels.
	class ImageBuffer : public IImage
	{
	public:
		ImageBuffer(uint32_t width, uint32_t height);
		virtual ~ImageBuffer();

		const Color& At(uint32_t x, uint32_t y) const;
		Color& At(uint32_t x, uint32_t y);

	private:
		typedef boost::multi_array<Color, 2> ImageArray;
		ImageArray m_image;
	};


	// Image class that only allows reading and writing to a subsection of a parent image.
	class SubImage : public IImage
	{
	public:
		// Takes in the parent image, and the rectangle on the parent this subimage should be tied to.
		SubImage(IImage* parent, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		virtual ~SubImage();

		const Color& At(uint32_t x, uint32_t y) const;
		Color& At(uint32_t x, uint32_t y);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		bool PointIsInBounds(uint32_t x, uint32_t y) const;

	private:
		IImage* m_parent;
		uint32_t m_width;
		uint32_t m_height;
	};
}
