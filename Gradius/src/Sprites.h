#pragma once
#include "Vecs.h"
#include <vector>

class Sprites {
public:
	Sprites();

	void setTimer(const float newTimer) { timer = newTimer; }
	void setTimeNext(const float newTime) { timeNext = newTime; }
	void setIndex(const int newIndex) { index = newIndex; }

	float getTimer() const { return timer; }
	float getTimeNext() const { return timeNext; }
	int getIndex() const { return index; }

	void addSprite(int x, int y, int w, int h);
	void update(float deltaTime);
	Vec4 getActualSprite();
	void clearSprites();

private:

	void changeIndex();

	//sprite rects
	std::vector<Vec4> sprites; 
	//timer to count the time to pass to the next sprite
	float timer; 
	//time to pass to the next sprite
	float timeNext;
	//index of actual sprite
	int index;
};