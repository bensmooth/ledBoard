#include <iostream>
#include <thread>
#include <limits>
#include <memory>
#include "FilesystemRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"
#include "FontRenderer.h"

using namespace std;
using namespace Pix;

constexpr auto LED_DIMENSION = 18;


int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		cerr << "Usage: " << argv[0] << endl;
		return -1;
	}

	try
	{
		IRenderTargetPtr renderTarget = IRenderTarget::GetDefaultRenderer(argv[0], LED_DIMENSION, LED_DIMENSION);

		Image backbuffer(LED_DIMENSION, LED_DIMENSION);
		FrameTimer timer(60.0);

		Color back, fore;
		back.Set(0, 0, 0);
		fore.Set(0, 0, 255);

		while (true)
		{
			timer.StartFrame();

			for (int x = 0; x < backbuffer.GetWidth(); x++)
			{
				for (int y = 0; y < backbuffer.GetHeight(); y++)
				{
					backbuffer.At(x, y) = back;
				}
			}

			FontRenderer::RenderText<TomThumbFont>("ABCD", backbuffer, fore, 1, 0);
			FontRenderer::RenderText<TomThumbFont>("EFGH", backbuffer, fore, 1, 6);
			FontRenderer::RenderText<TomThumbFont>("IJKL", backbuffer, fore, 1, 12);

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
