#pragma once
void update(SDL_Renderer* renderer, int time);
bool checkRectCollisionBricks(SDL_Rect rect, SDL_Renderer* renderer, bool ball, int ballIndex);