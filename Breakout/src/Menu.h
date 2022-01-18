#pragma once
#include <SDL.h>

extern SDL_Texture* textLifeNumber;
extern SDL_Texture* textLevelPuntuation;
extern SDL_Texture* textPuntuation;
extern int boardWidth;
extern float timer;
extern int score;
extern int level;
extern int lifes;
extern bool serve;
extern int menuIndex;
extern bool musicOn;
extern bool soundOn;
extern SDL_Texture* textStart;
extern SDL_Rect startRect;
extern SDL_Rect pauseRects[];
extern SDL_Rect musicVolumeRect[];
extern SDL_Rect soundVolumeRect[];


void assignProperties(SDL_Rect* rect, int y, int w, int h);
void writeGameMenu(SDL_Renderer* renderer);
void closeMenu();
void showGameMenu(SDL_Renderer* renderer);
void start(float time, SDL_Renderer* renderer);
void initMenu(SDL_Renderer* renderer);
void showPauseMenu(SDL_Renderer* renderer);
void writePauseMenu(SDL_Renderer* renderer);
void setSoundRects(int number);
void setMusicRects(int number);
void musicOnOff(SDL_Renderer* renderer);
void soundOnOff(SDL_Renderer* renderer);
void fullscreenOnOff(SDL_Renderer* renderer);
void changeMusicRects(SDL_Renderer* renderer, int numberRect);
void changeSoundRects(SDL_Renderer* renderer, int activeSoundRects);
void changeFullscreenGameSize(SDL_Renderer* renderer, int fps, SDL_Window* window);
void changeWindowGameSize(SDL_Renderer* renderer, int fps, SDL_Window* window);
void turnOnMusic(SDL_Renderer* renderer);
void turnOffMusic(SDL_Renderer* renderer);
void turnOnSound(SDL_Renderer* renderer);
void turnOffSound(SDL_Renderer* renderer);
void initBackgroundIndex();
void loadBackgroundImage(SDL_Renderer* renderer);
void showBackgroundImage(SDL_Renderer* renderer);
void setScreenWidth(int width);
void setScreenHeight(int height);
int getScreenWidth();
int getScreenHeight();
void loadBackgroundImages(SDL_Renderer* renderer);
void resizeBricks();