#include <SDL_mixer.h>
#include <iostream>
Mix_Music* music;
Mix_Chunk* sound;

void closeMusic() {
	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);
}

void loadMusic() {
	music = Mix_LoadMUS("sounds/happy-clappy-ukulele.mp3");
	if (!music) {
		std::cout << "The music is not loaded" << std::endl;
	}
	sound = Mix_LoadWAV("sounds/hit.wav");
	if (!sound) {
		std::cout << "The sound is not loaded" << std::endl;
	}
}