// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

void loadImage(SDL_Renderer* renderer, std::string path, SDL_Texture** texture) {
	SDL_Surface* image;
	image = IMG_Load(path.c_str());
	if (!image) {
		SDL_Log("the image can't be loaded");
	}
	*texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}

bool initRenderer(SDL_Window** window, SDL_Renderer** renderer, int width, int height) {

	*window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	return true;
}

void closeRenderer(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void generateTextTexture(SDL_Color color, std::string fontRoute, int fontSize, std::string text, SDL_Texture** texture, SDL_Renderer* renderer) {

	TTF_Font* font = TTF_OpenFont(fontRoute.c_str(), fontSize);
	SDL_Surface* textSurface;

	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	*texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

//generate a texture and assign the width of the texture to the rect
void generateTextTexture(SDL_Color color, std::string fontRoute, int fontSize, std::string text, SDL_Texture** texture, SDL_Rect* rect, SDL_Renderer* renderer) {

	TTF_Font* font = TTF_OpenFont(fontRoute.c_str(), fontSize);
	SDL_Surface* textSurface;

	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	*texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	rect->w = textSurface->w;

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);

}