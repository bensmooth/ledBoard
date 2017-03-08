#include <iostream>
#include <thread>
#include <limits>
#include <memory>
#include <string>
#include <sstream>
#include "FilesystemRenderTarget.h"
#include "Image.h"
#include "FrameTimer.h"
#include "FontRenderer.h"
#include "fonts/Prototype15Font.h"
#include "fonts/TomThumbFont.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio.hpp>


using namespace std;
using namespace Pix;

constexpr auto LED_DIMENSION = 18;

using boost::asio::ip::tcp;
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


template <class T>
vector<GameInfo> LoadJson(T& source)
{
	vector<GameInfo> gameInfo;

	PropertyTree json;
	boost::property_tree::read_json(source, json);

	const PropertyTree& games = json.get_child("games");

	for (const auto& current : games)
	{
		GameInfo info;

		info.Populate(current.second);

		gameInfo.push_back(info);
	}

	return gameInfo;
}


stringstream TryHttpGet(const string& hostname, const string& path)
{
	stringstream body;

	// Get a list of endpoints corresponding to the server name.
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(hostname, "http");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	// Try each endpoint until we successfully establish a connection.
	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint_iterator);

	// Form the request. We specify the "Connection: close" header so that the
	// server will close the socket after transmitting the response. This will
	// allow us to treat all data up until the EOF as the content.
	boost::asio::streambuf request;
	std::ostream request_stream(&request);
	request_stream << "GET " << path << " HTTP/1.0\r\n";
	request_stream << "Host: " << hostname << "\r\n";
	request_stream << "Accept: */*\r\n";
	request_stream << "Connection: close\r\n\r\n";

	// Send the request.
	boost::asio::write(socket, request);

	// Read the response status line. The response streambuf will automatically
	// grow to accommodate the entire line. The growth may be limited by passing
	// a maximum size to the streambuf constructor.
	boost::asio::streambuf response;
	boost::asio::read_until(socket, response, "\r\n");

	// Check that response is OK.
	std::istream response_stream(&response);
	std::string http_version;
	response_stream >> http_version;
	unsigned int status_code;
	response_stream >> status_code;
	std::string status_message;
	std::getline(response_stream, status_message);
	if (!response_stream || http_version.substr(0, 5) != "HTTP/")
	{
		throw runtime_error("Invalid response");
	}

	if (status_code != 200)
	{
		throw runtime_error("Response returned with status code " + to_string(status_code));
	}

	// Read the response headers, which are terminated by a blank line.
	boost::asio::read_until(socket, response, "\r\n\r\n");

	// Process the response headers.
	std::string header;
	while (std::getline(response_stream, header) && header != "\r")
	{
// 		std::cout << header << "\n";
	}

	// Write whatever content we already have to output.
	if (response.size() > 0)
	{
		body << &response;
	}

	// Read until EOF, writing data to output as we go.
	boost::system::error_code error;
	while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
	{
		body << &response;
	}

	if (error != boost::asio::error::eof)
	{
		throw boost::system::system_error(error);
	}

	return body;
}

stringstream HttpGet(const string& hostname, const string& path, uint32_t retries)
{
	const auto timeToSleepBetweenTries = std::chrono::milliseconds(1000);
	stringstream jsonStream;

	for (uint32_t i = 0; i < retries; i++)
	{
		try
		{
			jsonStream = TryHttpGet(hostname, path);
			break;
		}
		catch (const exception& ex)
		{
			cerr << "HTTP GET failed for http://" << (hostname + path) << " - " << ex.what();
			cerr << "\tRetrying..." << (i+1) << " of " << retries << endl;

			if (i == (retries - 1))
			{
				throw;
			}
			else
			{
				std::this_thread::sleep_for(timeToSleepBetweenTries);
			}
		}
	}

	return jsonStream;
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

vector<GameInfo> PopulateGamesList()
{
	const string hostname = "live.nhle.com";
	const string path = "/GameData/RegularSeasonScoreboardv3.jsonp";

	stringstream jsonStream;
	jsonStream = HttpGet(hostname, path, 10);

	// Trim to the first and last {}
	// TODO: The correct way to do this would probably be to modify our stream code in HttpGet to only get the JSON.
	string json = jsonStream.str();
	size_t firstBracket = json.find_first_of('{');
	size_t lastBracket = json.find_last_of('}');

	if ((firstBracket == string::npos) || (lastBracket == string::npos) || (firstBracket > lastBracket))
	{
		throw runtime_error("Strange JSON?");
	}

	size_t jsonLength = lastBracket - firstBracket + 1;
	jsonStream.str(json.substr(firstBracket, jsonLength));

	try
	{
		return LoadJson(jsonStream);
	}
	catch (exception)
	{
		const char* jsonDumpFilename = "games.json";
		cerr << "Failed to parse json...dumping to " << jsonDumpFilename << endl;

		try
		{
			ofstream dump(jsonDumpFilename);
			dump << jsonStream.str();
			dump.close();
		}
		catch (exception)
		{
		}

		// Rethrow original parser exception.
		throw;
	}
}

GameInfo FindMostInterestingGame(const vector<GameInfo>& games)
{
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

	return games[currentGameIndex];
}

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		cerr << "Usage: " << argv[0] << endl;
		return -1;
	}

// 	TeamInfo team1;
// 	team1.primaryColor.Set(0, 79, 48);
// 	team1.secondaryColor.Set(241, 179, 16);
// 	team1.score = 5;
// 	team1.teamName = "Minnesota Wild";

// 	TeamInfo team2;
// 	team2.primaryColor.Set(198, 12, 48);
// 	team2.secondaryColor.Set(255, 255, 255);
// 	team2.score = 2;
// 	team2.teamName = "Chicago Blackhawks";

	try
	{
		IRenderTargetPtr renderTarget = IRenderTarget::GetDefaultRenderer(argv[0], LED_DIMENSION, LED_DIMENSION);

		Image backbuffer(LED_DIMENSION, LED_DIMENSION);
		FrameTimer timer(1.0/60.0);

		while (true)
		{
			timer.StartFrame();

			vector<GameInfo> games = PopulateGamesList();
			GameInfo currentGame = FindMostInterestingGame(games);

			cout << "Showing game: " << currentGame << endl;

			RenderGame(currentGame, backbuffer);

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
