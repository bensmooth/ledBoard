#pragma once
#include "Image.h"

namespace Pix
{
	class ImageFile
	{
	public:
		static void Read(const std::string& inFilename, Image& out);
		static void Write(const Image& image, const std::string& outFilename);
		static size_t GetExpectedFilesize(const Image& image);
	};
}
