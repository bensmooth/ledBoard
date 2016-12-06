#include <iostream>
#include <thread>
#include <limits>
#include <memory>
#include "FilesystemRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"
#include "FontRenderer.h"
#include "fonts/Prototype15Font.h"
#include "fonts/TomThumbFont.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


using namespace std;
using namespace Pix;

constexpr auto LED_DIMENSION = 18;


using PropertyTree = boost::property_tree::ptree;


struct TeamInfo
{
	Color primaryColor;
	Color secondaryColor;

	uint8_t score;

	std::string teamName;
};

ostream& operator<< (ostream& stream, const TeamInfo& teamInfo)
{
	stream << teamInfo.teamName << ": " << to_string(teamInfo.score);

	return stream;
}

struct GameInfo
{
	void Populate(const PropertyTree& ptree)
	{
		awayTeam.score = ptree.get<uint8_t>("ats", 0);
		awayTeam.teamName = ptree.get<string>("atn") + " " + ptree.get<string>("atv");

		homeTeam.score = ptree.get<uint8_t>("hts", 0);
		homeTeam.teamName = ptree.get<string>("htn") + " " + ptree.get<string>("htv");

		// TODO: Based on the team name, map it to an enum for each team...then use it to produce colors.
		homeTeam.primaryColor = Color(0, 0, 0);
		homeTeam.secondaryColor = Color(0, 255, 0);
		awayTeam.primaryColor = Color(0, 0, 0);
		awayTeam.secondaryColor = Color(255, 0, 0);
	}

	TeamInfo homeTeam;
	TeamInfo awayTeam;
};

ostream& operator<< (ostream& stream, const GameInfo& gameInfo)
{
	stream << gameInfo.awayTeam << " at " << gameInfo.homeTeam;

	return stream;
}


string indent(int level) {
  string s; 
  for (int i=0; i<level; i++) s += "  ";
  return s; 
} 

void printTree (boost::property_tree::ptree &pt, int level) {
  if (pt.empty()) {
    cout << "\""<< pt.data()<< "\"";
  }

  else {
    if (level) cout << endl; 

    cout << indent(level) << "{" << endl;     

    for (boost::property_tree::ptree::iterator pos = pt.begin(); pos != pt.end();) {
      cout << indent(level+1) << "\"" << pos->first << "\": "; 

      printTree(pos->second, level + 1); 
      ++pos; 
      if (pos != pt.end()) {
        cout << ","; 
      }
      cout << endl;
    } 

   cout << indent(level) << " }";
  }

  return; 
}

vector<GameInfo> LoadJson(const std::string& filePath)
{
	vector<GameInfo> gameInfo;

	PropertyTree json;
	boost::property_tree::read_json(filePath, json);

// 	printTree(json, 0);

	const PropertyTree& games = json.get_child("games");

	for (const auto& current : games)
	{
		GameInfo info;

		info.Populate(current.second);

		cout << info << endl;
		gameInfo.push_back(info);
	}

	return gameInfo;
}


void RenderGame(const GameInfo& game, Image& renderTarget)
{
	const TeamInfo& team1 = game.homeTeam;
	const TeamInfo& team2 = game.awayTeam;

	for (int x = 0; x < renderTarget.GetWidth(); x++)
	{
		for (int y = 0; y < renderTarget.GetHeight(); y++)
		{
			Color currentColor;
			if (x < (renderTarget.GetWidth() / 2))
			{
				// Left team.
				currentColor = team1.primaryColor;
			}
			else
			{
				// Right team.
				currentColor = team2.primaryColor;
			}

			renderTarget.At(x, y) = currentColor;
		}
	}

	int32_t scoreY = 3;
	FontRenderer::RenderText<Prototype15Font>(to_string(team1.score), renderTarget, team1.secondaryColor, -1, scoreY, RenderMode::FixedPitch);
	FontRenderer::RenderText<Prototype15Font>(to_string(team2.score), renderTarget, team2.secondaryColor, LED_DIMENSION / 2, scoreY, RenderMode::FixedPitch);

	FontRenderer::RenderText<TomThumbFont>(team1.teamName.substr(0, 2), renderTarget, team1.secondaryColor, 1, 0, RenderMode::FixedPitch);
	FontRenderer::RenderText<TomThumbFont>(team2.teamName.substr(0, 2), renderTarget, team2.secondaryColor, LED_DIMENSION / 2 + 1, 0, RenderMode::FixedPitch);
}


int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		cerr << "Usage: " << argv[0] << endl;
		return -1;
	}

	vector<GameInfo> games = LoadJson("RegularSeasonScoreboardv3Trimmed.jsonp");

	// Find the game we are interested in.
	size_t currentGameIndex = -1;
	for (size_t i = 0; i < games.size(); i++)
	{
		const GameInfo& game = games[i];
		if ((game.homeTeam.teamName == "Minnesota wild") || (game.awayTeam.teamName == "Minnesota wild"))
		{
			currentGameIndex = i;
		}
	}

	if (currentGameIndex == -1)
	{
		cout << "Selecting first game." << endl;
		currentGameIndex = 0;
	}

	cout << "Showing game: " << games[currentGameIndex] << endl;

// 	TeamInfo team1;
// 	team1.primaryColor.Set(0, 79, 48);
// 	team1.secondaryColor.Set(241, 179, 16);
// 	team1.score = 5;
// 	team1.teamName = "Minnesota Wild";
// 
// 	TeamInfo team2;
// 	team2.primaryColor.Set(198, 12, 48);
// 	team2.secondaryColor.Set(255, 255, 255);
// 	team2.score = 2;
// 	team2.teamName = "Chicago Blackhawks";

	try
	{
		IRenderTargetPtr renderTarget = IRenderTarget::GetDefaultRenderer(argv[0], LED_DIMENSION, LED_DIMENSION);

		Image backbuffer(LED_DIMENSION, LED_DIMENSION);
		FrameTimer timer(1.0);

		while (true)
		{
			timer.StartFrame();

			RenderGame(games[currentGameIndex], backbuffer);

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
