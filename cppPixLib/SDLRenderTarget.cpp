#include "SDLRenderTarget.h"
#include "Exception.h"
#include <SDL2/SDL.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

using namespace SDL2pp;

namespace Pix
{
	SDLRenderTarget::SDLRenderTarget(const std::string& windowTitle, int32_t windowWidth, int32_t windowHeight)
		: m_windowWidth(windowWidth), m_windowHeight(windowHeight)
	{
		m_sdl.reset(new SDL(SDL_INIT_VIDEO));
		m_window.reset(new Window(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN));\
		m_renderer.reset(new Renderer(*m_window, -1, SDL_RENDERER_ACCELERATED));
	}

	SDLRenderTarget::~SDLRenderTarget()
	{
	}

	void SDLRenderTarget::Render(const Image& image)
	{
		uint32_t imageWidth = image.GetWidth();
		uint32_t imageHeight = image.GetHeight();
		uint32_t pixelWidth = m_windowWidth / imageWidth;
		uint32_t pixelHeight = m_windowHeight / imageHeight;

		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if ((event.type == SDL_QUIT) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)))
			{
				throw Exception("User requested to quit.");
			}
		}

		m_renderer->SetDrawColor(0, 0, 0);
		m_renderer->Clear();

		for (uint32_t x = 0; x < imageWidth; x++)
		{
			uint32_t pixelX = pixelWidth * x;

			for (uint32_t y = 0; y < imageHeight; y++)
			{
				const Color& color = image.At(x, y);
				m_renderer->SetDrawColor(color.Red(), color.Green(), color.Blue());

				uint32_t pixelY = pixelHeight * y;
				m_renderer->FillRect(pixelX, pixelY, pixelX + pixelWidth, pixelY + pixelHeight);
			}
		}

		m_renderer->Present();
	}
}
