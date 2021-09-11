#include <iostream>
#include "Image.h"

void loadImage(SDL_Renderer* renderer, SDL_Texture** texture, std::string path) {
	SDL_Surface* image;
	image = IMG_Load(path.c_str());
	if (!image) {
		std::cout << "failed in load image" << std::endl;
	}
	*texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}