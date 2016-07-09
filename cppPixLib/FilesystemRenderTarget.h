#pragma once
#include "IRenderTarget.h"
#include <string>

namespace Pix
{
	class FilesystemRenderTarget : public IRenderTarget
	{
	public:
		FilesystemRenderTarget(const std::string& targetFilename);
		~FilesystemRenderTarget() override;

		void Render(const Image& image) override;

	private:
		std::string m_targetFilename;
	};
}
