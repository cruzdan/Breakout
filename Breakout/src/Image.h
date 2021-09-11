#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

void loadImage(SDL_Renderer* renderer, SDL_Texture** texture, std::string path);