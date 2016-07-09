#pragma once
#include "Image.h"

namespace Pix
{
	// Represents a target that an image can be rendered to.
	class IRenderTarget
	{
	public:
		virtual ~IRenderTarget() {}

		// Renders the given image on the target.
		virtual void Render(const Image& image) = 0;
	};
}
