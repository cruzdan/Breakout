#include <SDL_mixer.h>
#include <iostream>
Mix_Music* music;
Mix_Chunk* sound;

void initSounds() {
	music = Mix_LoadMUS("sounds/kart-mario.mp3");
	if (!music) {
		std::cout << "The music is not loaded" << std::endl;
	}
	sound = Mix_LoadWAV("sounds/hit.wav");
	if (!sound) {
		std::cout << "The sound is not loaded" << std::endl;
	}
}

void updateMusic() {
	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, -1);
	}
	else if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}

void closeMusic() {
	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);
}