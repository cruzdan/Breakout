#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
void loadImage(SDL_Renderer* renderer, std::string path, SDL_Texture** texture);
void loadTransparentImage(SDL_Renderer* renderer, std::string path, SDL_Texture** texture, int r, int g, int b);
bool initRenderer(SDL_Window** window, SDL_Renderer** renderer, int width, int height);
void closeRenderer(SDL_Window* window, SDL_Renderer* renderer);
void generateTextTexture(SDL_Color color, std::string fontRoute, int fontSize, std::string text, SDL_Texture** texture, SDL_Renderer* renderer);
void generateTextTexture(SDL_Color color, std::string fontRoute, int fontSize, std::string text, SDL_Texture** texture, SDL_Rect* rect, SDL_Renderer* renderer);