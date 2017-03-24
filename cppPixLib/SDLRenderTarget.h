#pragma once
#include <memory>
#include "IRenderTarget.h"

namespace SDL2pp
{
	class SDL;
	class Window;
	class Renderer;
}

namespace Pix
{
	class SDLRenderTarget : public IRenderTarget
	{
	public:
		SDLRenderTarget(const std::string& windowTitle, int32_t windowWidth, int32_t windowHeight);
		~SDLRenderTarget() override;

		void Render(const IImage& image) override;

	private:
		std::unique_ptr<SDL2pp::SDL> m_sdl;
		std::unique_ptr<SDL2pp::Window> m_window;
		std::unique_ptr<SDL2pp::Renderer> m_renderer;
		int32_t m_windowWidth;
		int32_t m_windowHeight;
	};
}
