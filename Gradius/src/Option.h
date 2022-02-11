#pragma once
#include <vector>
#include <SDL.h>
#include "Vecs.h"

class Option {
public:
	Option();

	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setW(const int newW) { w = newW; }
	void setH(const int newH) { h = newH; }
	void setHasMissile(const bool newMis) { hasMissile = newMis; }
	void setIndex(const int newIndex) { index = newIndex; }

	float getX() const { return x; }
	float getY() const { return y; }
	int getW() const { return w; }
	int getH() const { return h; }
	bool getHasMissile() const { return hasMissile; }
	int getIndex() const { return index; }
	std::vector<Vec2> getRoute() const { return route; }

	void update(float deltaTime);
	void addRoute(float x, float y);
	//move and set the next route coordinate
	void move(float newX, float newY);
	void show(SDL_Renderer* renderer);
private:
	float x;
	float y;
	int w;
	int h;
	//indicates if a missile of the ship is appeared
	bool hasMissile;
	std::vector<Vec2> route;
	int index;
	//put the new target coordinates in the route[index]
	void updateRoute(float newX, float newY);
	void updateIndex();
	class Sprites* sprites;
};