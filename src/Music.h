#pragma once
#include <SDL_mixer.h>
extern Mix_Music* music;
extern Mix_Chunk* sound;
void closeMusic();
void loadMusic();