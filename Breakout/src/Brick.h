#pragma once
#include <SDL.h>
#include <vector>

class Brick {
public:
	float getX() const { return mx; }
	float getY() const { return my; }
	int getW() const { return mw; }
	int getH() const { return mh; }
	int getLifes() const { return mlifes; }
	int getType() const { return mtype; }
	int getIndex() const { return mindex; }
	void setX(const float x) { mx = x; }
	void setY(const float y) { my = y; }
	void setW(const int w) { mw = w; }
	void setH(const int h) { mh = h; }
	void setLifes(const int lifes) { mlifes = lifes; }
	void setType(const int type) { mtype = type; }
	void setIndex(const int index) { mindex = index; }
private:
	float mx;
	float my;
	int mw;
	int mh;
	int mlifes;//indicates the lives of the bricks
	int mtype;//indicates the type of image of the bricks
	int mindex;
};
extern std::vector <class Brick*> bricks;
extern int freeSizeY;
extern int freeSizeX;
extern int lastBrickY;
extern int initialBrickY;
extern int actualBricks;
const int totalRectanglesX = 14;
extern int totalRectanglesY;
extern int totalRectangles;
void createRectangles();
void showBricks(SDL_Renderer* renderer);
void initBrickTextures(SDL_Renderer* renderer);
void resizeBricks();