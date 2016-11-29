#include <iostream>
#include <thread>
#include <limits>
#include <memory>
#include "FilesystemRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"
#include "FontRenderer.h"
#include "fonts/Prototype15Font.h"

typedef Pix::Prototype15Font ActiveFont;

using namespace std;
using namespace Pix;

constexpr auto LED_DIMENSION = 18;


int32_t RenderString(const std::string& text, Image& destination, const Color& color, int32_t x, int32_t y)
{
	return FontRenderer::RenderText<ActiveFont>(text, destination, color, x, y, RenderMode::ProportionalPitch);
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return -1;
	}

	string toBeDisplayed = argv[1];

	try
	{
		IRenderTargetPtr renderTarget = IRenderTarget::GetDefaultRenderer(argv[0], LED_DIMENSION, LED_DIMENSION);

		Image backbuffer(LED_DIMENSION, LED_DIMENSION);
		FrameTimer timer(10.0);

		Color back, fore;
		back.Set(0, 0, 0);
		fore.Set(0, 0, 255);

		int32_t textX = LED_DIMENSION;
		int32_t textY = (LED_DIMENSION / 2) - (ActiveFont::LetterHeight / 2);

		int32_t xVel = -1;

		// Get the total width of the string.
		int32_t travelDistance = RenderString(toBeDisplayed, backbuffer, fore, 0, 0);
		travelDistance += 2 * LED_DIMENSION;
		int32_t frameCount = -travelDistance / xVel;

		while (frameCount --> 0)
		{
			timer.StartFrame();

			for (int x = 0; x < backbuffer.GetWidth(); x++)
			{
				for (int y = 0; y < backbuffer.GetHeight(); y++)
				{
					backbuffer.At(x, y) = back;
				}
			}

			RenderString(toBeDisplayed, backbuffer, fore, textX, textY);
			textX += xVel;

			renderTarget->Render(backbuffer);

			timer.EndFrame();
		}
	}
	catch (const exception& ex)
	{
		cerr << "Something bad happened - " << ex.what() << endl;
	}

	return 0;
}
