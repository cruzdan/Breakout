// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL_mixer.h>
#include <SDL.h>
Mix_Music* music;
Mix_Chunk* sound;

void closeMusic() {
	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);
}

void loadMusic() {
	music = Mix_LoadMUS("sounds/happy-clappy-ukulele.mp3");
	if (!music) {
		SDL_Log("Unable to load music: %s", SDL_GetError());
	}
	sound = Mix_LoadWAV("sounds/hit.wav");
	if (!sound) {
		SDL_Log("Unable to load sound: %s", SDL_GetError());
	}
}