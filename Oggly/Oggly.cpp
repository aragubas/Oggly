// Oggly.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED 
#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
	if (Mix_Init(MIX_INIT_OGG) < 0)
	{
		std::cout << "Error while initializing mixer: " << Mix_GetError() << std::endl;
		return 1;
	}
	
	std::string executableName = argv[0];

	const size_t last_slash_idx = executableName.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		executableName.erase(0, last_slash_idx + 1);
	}

	if (argc < 2)
	{
		std::cout << "Oggly v1.0; Usage: " << executableName << " <file.ogg>" << std::endl;
		return 1;
	}

	std::string inputFileName = argv[1];
	fs::path f{ inputFileName };
	
	if (!inputFileName.ends_with(".ogg"))
	{
		std::cout << "Error: Input file must be an OGG file." << std::endl;
		return 1;
	}

	if (!fs::exists(f))
	{
		std::cout << "Error! Input File " << inputFileName << " does not exist" << std::endl;
		return 1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Error while opening audio device: " << Mix_GetError() << std::endl;
		return 1;
	}

	Mix_Music *music = Mix_LoadMUS(inputFileName.c_str());

	if (music == nullptr)
	{
		std::cout << "Error while loading file: " << Mix_GetError() << std::endl;
		return 1;
	}

	Mix_PlayMusic(music, 0);

	while (Mix_PlayingMusic())
	{
		SDL_Delay(100);
	}
}
