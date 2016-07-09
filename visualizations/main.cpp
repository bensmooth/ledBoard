#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <limits>
#include "FilesystemRenderTarget.h"
#include "Image.h"

using namespace std;
using namespace Pix;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <out filename>" << endl;
		return -1;
	}

	static constexpr auto PI = std::acos(-1);


	FilesystemRenderTarget renderTarget(argv[1]);
	Image backbuffer(18, 18);

	auto startTime = std::chrono::steady_clock::now();

	while (true)
	{
		auto currentTime = std::chrono::steady_clock::now();
		double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime).count();

		uint8_t r = ((std::cos(elapsed * PI / 180.0) + 1.0) / 2.0) * std::numeric_limits<uint8_t>::max();

		Color current;
		current.Set(r, 0, 0);

		for (int x = 0; x < backbuffer.GetWidth(); x++)
		{
			for (int y = 0; y < backbuffer.GetHeight(); y++)
			{
				backbuffer.At(x, y) = current;
			}
		}

		this_thread::sleep_for(chrono::milliseconds(30));
	}

	return 0;
}
