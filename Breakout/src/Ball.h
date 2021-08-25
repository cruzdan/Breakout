#pragma once
#include <SDL.h>
extern SDL_Texture* ballTexture;
extern SDL_Rect ballImageRect;
extern SDL_Rect ballRect;
void centerBall();
void loadImage(SDL_Renderer* renderer);
void closeTextureBall();
void initBall();