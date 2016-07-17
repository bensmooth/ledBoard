#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <limits>
#include "FilesystemRenderTarget.h"
#include "SDLRenderTarget.h"
#include "Image.h"

using namespace std;
using namespace Pix;

constexpr auto LED_DIMENSION = 18;

inline uint8_t Psycho(double t)
{
	static constexpr auto PI = std::acos(-1);
	return ((std::cos(t * PI / 180.0) + 1.0) / 2.0) * std::numeric_limits<uint8_t>::max();
}

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		cerr << "Usage: " << argv[0] << endl;
		return -1;
	}

	double elapsed = 0.0;

	try
	{
#ifdef __arm__
		FilesystemRenderTarget renderTarget("/dev/spi0.0");
#else
		SDLRenderTarget renderTarget(argv[0], LED_DIMENSION * 50, LED_DIMENSION * 50);
#endif

		Image backbuffer(LED_DIMENSION, LED_DIMENSION);
		auto startTime = std::chrono::steady_clock::now();

		while (true)
		{
			auto currentTime = std::chrono::steady_clock::now();
			elapsed = (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count()) / 1000.0;
			Color current;
			current.Set(Psycho(elapsed * 10.0), Psycho(elapsed * 20.0), Psycho(elapsed * 50.0));

			for (int x = 0; x < backbuffer.GetWidth(); x++)
			{
				for (int y = 0; y < backbuffer.GetHeight(); y++)
				{
					backbuffer.At(x, y) = current;
				}
			}

			renderTarget.Render(backbuffer);

			this_thread::sleep_for(chrono::milliseconds(30));
		}
	}
	catch (const exception& ex)
	{
		cerr << "Something bad happened at t=" << elapsed << " - " << ex.what() << endl;
		return -1;
	}

	return 0;
}
