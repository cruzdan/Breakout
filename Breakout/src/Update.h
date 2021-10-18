#pragma once
void update(SDL_Renderer* renderer, float time);
bool checkRectCollisionBricks(SDL_Rect rect, SDL_Renderer* renderer, bool ball, int ballIndex);
void nextLevel(SDL_Renderer* renderer);