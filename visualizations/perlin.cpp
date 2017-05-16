#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <limits>
#include <memory>
#include "FilesystemRenderTarget.h"
#include "SDLRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"

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

	double elapsed = 0.0;

	chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
	uint64_t frameCount = 0;

	try
	{
		IRenderTargetPtr renderTarget = IRenderTarget::GetDefaultRenderer(argv[0], LED_DIMENSION, LED_DIMENSION);

		ImageBuffer backbuffer(LED_DIMENSION, LED_DIMENSION);
		FrameTimer timer(60.0);

		while (true)
		{
			timer.StartFrame();

			chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();
			elapsed = (chrono::duration_cast<chrono::milliseconds>(currentTime - startTime).count()) / 1000.0;
			Color current;
			//current.Set(Psycho(elapsed * 10.0), Psycho(elapsed * 20.0), Psycho(elapsed * 50.0));

			for (int x = 0; x < backbuffer.GetWidth(); x++)
			{
				for (int y = 0; y < backbuffer.GetHeight(); y++)
				{
					backbuffer.At(x, y) = current;
				}
			}

			renderTarget->Render(backbuffer);
			frameCount++;

			timer.EndFrame();
		}
	}
	catch (const exception& ex)
	{
		cerr << "Something bad happened at t=" << elapsed << " - " << ex.what() << endl;
	}

	if (elapsed > 0.0)
	{
		cout << "Average FPS: " << ((double)frameCount / elapsed) << endl;
	}

	return 0;
}
