#pragma once
#include "Image.h"

namespace Pix
{
	class ImageFile
	{
	public:
		static void Read(const std::string& inFilename, IImage& out);
		static void Write(const IImage& image, const std::string& outFilename);
		static size_t GetExpectedFilesize(const IImage& image);
	};
}
