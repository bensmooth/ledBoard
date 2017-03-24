#include "FilesystemRenderTarget.h"
#include "ImageFile.h"

namespace Pix
{
	FilesystemRenderTarget::FilesystemRenderTarget(const std::string& targetFilename)
	{
		m_targetFilename = targetFilename;
	}

	FilesystemRenderTarget::~FilesystemRenderTarget()
	{
	}

	void FilesystemRenderTarget::Render(const IImage& image)
	{
		ImageFile::Write(image, m_targetFilename);
	}
}
