#include "ImageFile.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>
#include "Exception.h"

namespace Pix
{
	using Coordinate = std::pair<uint32_t, uint32_t>;

	// Converts a set of coordinates into an index.
	inline size_t CoordinatesToIndex(Coordinate coords, uint32_t imageWidth)
	{
		size_t index = coords.second * imageWidth;
		if (coords.second % 2 == 0)
		{
			index += coords.first;
		}
		else
		{
			index += imageWidth - 1 - coords.first;
		}

		return index;
	}

	inline Coordinate IndexToCoordinates(size_t index, uint32_t imageWidth)
	{
		uint32_t x = index % imageWidth;
		uint32_t y = index / imageWidth;

		// Odd rows go backwards
		if (y % 2 == 1)
		{
			x = imageWidth - 1 - x;
		}

		return Coordinate(x, y);
	}

	// Given an RGB tuple and coordinates, converts the RGB tuple into an RBG tuple if necessary.
	void FormatPixel(Color& rgb, Coordinate coords, uint32_t imageHeight)
	{
		// The hardware requires us to use RGB instead of RBG for the last row.
		if (coords.second != (imageHeight - 1))
		{
			auto temp = rgb.Green();
			rgb.Green() = rgb.Blue();
			rgb.Blue() = temp;
		}
	}


	void ImageFile::Read(const std::string& inFilename, IImage& out)
	{
		size_t expectedFileSize = GetExpectedFilesize(out);
		size_t actualFileSize = boost::filesystem::file_size(inFilename);

		if (expectedFileSize != actualFileSize)
		{
			throw Exception("Actual file size does not match expected file size.");
		}

		std::ifstream instream(inFilename, std::ios::binary | std::ios::in);

		if (instream.bad())
		{
			throw Exception("Unable to open input file: " + inFilename);
		}

		uint32_t imageWidth = out.GetWidth();
		uint32_t imageHeight = out.GetHeight();
		size_t pixels = imageWidth * imageHeight;

		for (size_t i = 0; i < pixels; i++)
		{
			Color currentColor;
			currentColor.Read(instream);

			Coordinate coord = IndexToCoordinates(i, imageWidth);
			FormatPixel(currentColor, coord, imageHeight);
			out.At(coord.first, coord.second) = currentColor;
		}
	}

	void ImageFile::Write(const IImage& image, const std::string& outFilename)
	{
		uint32_t imageWidth = image.GetWidth();
		uint32_t imageHeight = image.GetHeight();
		size_t fileSize = GetExpectedFilesize(image);
		std::stringstream buffer;

		// Write to buffer with a stream.
		size_t pixels = imageWidth * imageHeight;

		for (size_t i = 0; i < pixels; i++)
		{
			Coordinate coords = IndexToCoordinates(i, imageWidth);
			Color currentPixel = image.At(coords.first, coords.second);
			FormatPixel(currentPixel, coords, imageHeight);
			currentPixel.Write(buffer);
		}

		// Write buffer.
		std::ofstream outstream(outFilename, std::ios::out | std::ios::binary);
		if (outstream.bad())
		{
			throw Exception("Unable to open file " + outFilename);
		}

		outstream.write(buffer.str().c_str(), fileSize);
	}

	size_t ImageFile::GetExpectedFilesize(const IImage& image)
	{
		return image.GetWidth() * image.GetHeight() * 3;
	}
}
