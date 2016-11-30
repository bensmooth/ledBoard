#include <iostream>
#include <thread>
#include <limits>
#include <memory>
#include "FilesystemRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"
#include "FontRenderer.h"
#include "fonts/Prototype15Font.h"
#include "fonts/Visitor12Font.h"
#include "fonts/TomThumbFont.h"

using namespace std;
using namespace Pix;

constexpr auto LED_DIMENSION = 18;


struct TeamInfo
{
	Color primaryColor;
	Color secondaryColor;

	uint8_t score;

	std::string stateAbbreviation;
};


// TODO: Make this happen if stuff happens in the game.
// FontRenderer::RenderText<TomThumbFont>("BULL", backbuffer, fore, 1, 3, RenderMode::FixedPitch);
// FontRenderer::RenderText<TomThumbFont>("SHIT", backbuffer, fore, 1, 9, RenderMode::FixedPitch);
// Color temp = back;
// back = fore;
// fore = temp;


int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		cerr << "Usage: " << argv[0] << endl;
		return -1;
	}

	TeamInfo team1;
	team1.primaryColor.Set(0, 80, 24);
	team1.secondaryColor.Set(241, 179, 16);
	team1.score = 5;
	team1.stateAbbreviation = "MN";

	TeamInfo team2;
	team2.primaryColor.Set(198, 12, 48);
	team2.secondaryColor.Set(255, 255, 255);
	team2.score = 2;
	team2.stateAbbreviation = "IL";

	try
	{
		IRenderTargetPtr renderTarget = IRenderTarget::GetDefaultRenderer(argv[0], LED_DIMENSION, LED_DIMENSION);

		Image backbuffer(LED_DIMENSION, LED_DIMENSION);
		FrameTimer timer(1.0);

		while (true)
		{
			timer.StartFrame();

			for (int x = 0; x < backbuffer.GetWidth(); x++)
			{
				for (int y = 0; y < backbuffer.GetHeight(); y++)
				{
					Color currentColor;
					if (x < (LED_DIMENSION / 2))
					{
						// Left team.
						currentColor = team1.primaryColor;
					}
					else
					{
						// Right team.
						currentColor = team2.primaryColor;
					}

					backbuffer.At(x, y) = currentColor;
				}
			}

			int32_t scoreY = 3;
			FontRenderer::RenderText<Prototype15Font>(to_string(team1.score), backbuffer, team1.secondaryColor, -1, scoreY, RenderMode::FixedPitch);
			FontRenderer::RenderText<Prototype15Font>(to_string(team2.score), backbuffer, team2.secondaryColor, LED_DIMENSION / 2, scoreY, RenderMode::FixedPitch);

			FontRenderer::RenderText<Visitor12Font>(team1.stateAbbreviation, backbuffer, team1.secondaryColor,
				0, 0, RenderMode::FixedPitch);
			FontRenderer::RenderText<Visitor12Font>(team2.stateAbbreviation, backbuffer, team2.secondaryColor,
				LED_DIMENSION / 2, 0, RenderMode::FixedPitch);

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
