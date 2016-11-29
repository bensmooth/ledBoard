#include <iostream>
#include <thread>
#include <limits>
#include <memory>
#include "FilesystemRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"
#include "FontRenderer.h"
#include "fonts/Prototype15Font.h"

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
		FrameTimer timer(10.0);

		Color back, fore;
		back.Set(0, 0, 0);
		fore.Set(255, 0, 0);

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

			FontRenderer::RenderText<Prototype15Font>("BULL", backbuffer, fore, 1, 3);
			FontRenderer::RenderText<Prototype15Font>("SHIT", backbuffer, fore, 1, 9);

			Color temp = back;
			back = fore;
			fore = temp;

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
