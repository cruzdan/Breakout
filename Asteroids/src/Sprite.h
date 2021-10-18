#pragma once
#pragma once
#include <SDL.h>
extern SDL_Texture* backgroundTexture;
extern SDL_Texture* shipTexture;
extern SDL_Texture* rocketTexture;
extern SDL_Texture* asteroidTexture;

//menu 0
extern SDL_Texture* titleTexture;
extern SDL_Texture* playTexture;
extern SDL_Texture* controlsTexture;
extern SDL_Texture* exitTexture;

//menu 1
extern SDL_Texture* scoreTexture;
extern SDL_Texture* lifeTexture;
extern SDL_Texture* numberScore;

//menu 2
extern SDL_Texture* instruction1Texture;
extern SDL_Texture* instruction2Texture;
extern SDL_Texture* instruction3Texture;
extern SDL_Texture* instruction4Texture;

void loadImage(SDL_Renderer* renderer);
void closeSprite();