#pragma once
#include <memory>
#include <string>
#include "Image.h"

namespace Pix
{
	class IRenderTarget;
	using IRenderTargetPtr = std::unique_ptr<IRenderTarget>;

	// Represents a target that an image can be rendered to.
	class IRenderTarget
	{
	public:
		virtual ~IRenderTarget() {}

		// Renders the given image on the target.
		virtual void Render(const IImage& image) = 0;

		static IRenderTargetPtr GetDefaultRenderer(const std::string& windowTitle, uint32_t width, uint32_t height);
	};
}
