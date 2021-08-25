#pragma once
#include <SDL_mixer.h>
extern Mix_Music* music;
extern Mix_Chunk* sound;

void initSounds();
//start music if it is paused or pause the music if it is started
void updateMusic();
void closeMusic();