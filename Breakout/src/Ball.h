#pragma once
#include <SDL.h>
#include <vector>

class Ball {
public:
	void setX(const float x) { mx = x; }
	void setY(const float y) { my = y; }
	void setWidth(const int w) { mw = w; }
	void setHeight(const int h) { mh = h; }
	void setSpeedX(const float speed) { mballSpeedX = speed; }
	void setSpeedY(const float speed) { mballSpeedY = speed; }
	float getX() const { return mx; }
	float getY() const { return my; }
	int getWidth() const { return mw; }
	int getHeight() const { return mh; }
	float getSpeedX() const { return mballSpeedX; }
	float getSpeedY() const { return mballSpeedY; }

private:
	float mx;
	float my;
	int mw;
	int mh;
	float mballSpeedX;
	float mballSpeedY;
};

void deleteBallElement(std::vector<class Ball*>* balls, class Ball* ball);
extern SDL_Texture* ballTexture;
extern std::vector<class Ball*> balls;
extern float ballSpeedChangeX;
extern float maxBallSpeed;
extern int actualBalls;
void closeTextureBall();
void initBall();
void changeBallMovementWithBrick(SDL_Rect brick, Ball* ball, float time);
void incrementBallSpeed();
void decrementBallSpeed();
SDL_Point* getBallSpeedMultiplicators(SDL_Point* ballMultiplicator);
void setMultiplicatorBallSpeed(SDL_Point* ballMultiplicator);
float* getBallSpeedMultiplicatorsX(float* ballMultiplicatorX);
float* getBallSpeedMultiplicatorsY(float* ballMultiplicatorY);
void setMultiplicatorBallSpeed(float* ballMultiplicatorX, float* ballMultiplicatorY);
void initBallSpeed(Ball* ball);
void showBalls(SDL_Renderer* renderer);
void addNewBall();
void restartBall();
SDL_Point* getActualBallPercentages(SDL_Point* percentages);
void reziseBalls();