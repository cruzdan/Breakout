// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL.h>
#include <SDL_ttf.h>
#include "Music.h"
#include "Init.h"
#include "Command.h"
#include "Capsule.h"
#include "Render.h"
#include "Paddle.h"
#include "Brick.h"

int actualServeTime = 0;
int SCREEN_WIDTH = 720;
int SCREEN_HEIGHT = 480;
SDL_Texture* backgroundImages[10];

void setScreenWidth(int width) {
	SCREEN_WIDTH = width;
}

void setScreenHeight(int height) {
	SCREEN_HEIGHT = height;
}

int getScreenWidth() {
	return SCREEN_WIDTH;
}

int getScreenHeight() {
	return SCREEN_HEIGHT;
}

//board
int boardWidth;

//menu
int menuWidth;

//backgroundImage
int backGroundIndex = -1;//index of the backgorund image
SDL_Rect backGroundRect;
SDL_Texture* backgroundTexture;

//Game Menu
SDL_Rect score_board;
SDL_Color color = { 255,255,255 };
SDL_Texture* textScore;
SDL_Rect textScoreRect;
SDL_Texture* textPuntuation;
SDL_Rect textPuntuationRect;
SDL_Texture* textLevel;
SDL_Rect textLevelRect;
SDL_Texture* textLevelPuntuation;
SDL_Rect textLevelPuntuationRect;
SDL_Texture* textLives;
SDL_Rect textLivesRect;
SDL_Texture* textLifeNumber;
SDL_Rect textLifeNumberRect;
SDL_Texture* textRestart;
SDL_Rect textRestartRect;
int score = 0;
int level = 1;
int lifes = 3;
int menuIndex = 0;//0 -> game, 1 -> pause
bool fullscreen = false;

//PauseMenu
SDL_Texture* pauseTextures[9];
SDL_Rect pauseRects[9];
SDL_Rect musicVolumeRect[5];
SDL_Rect soundVolumeRect[5];
int soundActiveRects = 5;
int musicActiveRects = 5;
bool musicOn = true;
bool soundOn = true;

//start
SDL_Texture* textStart;
SDL_Rect startRect;

bool serve = true;
float timer = 0;

//assign the coordinates, width and height on the middle of the menuX
void assignProperties(SDL_Rect* rect, int y, int w, int h) {
	rect->y = y;
	rect->w = w;
	rect->h = h;
	rect->x = boardWidth + menuWidth / 2 - rect->w / 2;
}

void initBackgroundIndex() {
	int random;
	do {
		random = rand() % 10;
	} while (random == backGroundIndex);
	backGroundIndex = random;
}

void loadBackgroundImage(SDL_Renderer* renderer) {
	backgroundTexture = NULL;
	backgroundTexture = backgroundImages[backGroundIndex];
}

void writeGameMenu(SDL_Renderer* renderer) {
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30, "Score", &textScore, renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30, std::to_string(score), &textPuntuation, renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30, "Level", &textLevel, renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30, std::to_string(level), &textLevelPuntuation, renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30, "Lifes", &textLives, renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30, std::to_string(lifes), &textLifeNumber, renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30, "Press R to restart", &textRestart, renderer);
	generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-Stencil.ttf", getScreenHeight() / 15, "1", &textStart, renderer);
}

void writePauseMenu(SDL_Renderer* renderer) {
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", (int)(SCREEN_HEIGHT * 0.15), "Pause", &pauseTextures[0], &pauseRects[0], renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "Press Esc to return to the game", &pauseTextures[1], &pauseRects[1], renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "Music volume", &pauseTextures[2], &pauseRects[2], renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "Sound volume", &pauseTextures[3], &pauseRects[3], renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "Fullscreen", &pauseTextures[4], &pauseRects[4], renderer);
	generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "Press here to exit", &pauseTextures[5], &pauseRects[5], renderer);
	if (musicOn)
		generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[6], &pauseRects[6], renderer);
	else
		generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[6], &pauseRects[6], renderer);
	if (soundOn)
		generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[7], &pauseRects[7], renderer);
	else
		generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[7], &pauseRects[7], renderer);
	if (fullscreen)
		generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[8], &pauseRects[8], renderer);
	else
		generateTextTexture(color, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[8], &pauseRects[8], renderer);
}

void closeMenu() {
	SDL_DestroyTexture(textScore);
	SDL_DestroyTexture(textPuntuation);
	SDL_DestroyTexture(textLevel);
	SDL_DestroyTexture(textLevelPuntuation);
	SDL_DestroyTexture(textLives);
	SDL_DestroyTexture(textLifeNumber);
	SDL_DestroyTexture(textStart);
	SDL_DestroyTexture(textRestart);
	for (int i = 0; i < 9; i++) {
		SDL_DestroyTexture(pauseTextures[i]);
	}
	SDL_DestroyTexture(backgroundTexture);
}

void showBackgroundImage(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, backgroundTexture, NULL, &backGroundRect);
}

void showGameMenu(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, textScore, NULL, &textScoreRect);
	SDL_RenderCopy(renderer, textPuntuation, NULL, &textPuntuationRect);
	SDL_RenderCopy(renderer, textLevel, NULL, &textLevelRect);
	SDL_RenderCopy(renderer, textLevelPuntuation, NULL, &textLevelPuntuationRect);
	SDL_RenderCopy(renderer, textLives, NULL, &textLivesRect);
	SDL_RenderCopy(renderer, textLifeNumber, NULL, &textLifeNumberRect);
	SDL_RenderCopy(renderer, textRestart, NULL, &textRestartRect);
	if (paddleShoot) {
		showTextScore(renderer);
	}
}

void showPauseMenu(SDL_Renderer* renderer) {
	for (int i = 0; i < 9; i++) {
		SDL_RenderCopy(renderer, pauseTextures[i], NULL, &pauseRects[i]);
	}
	if (musicOn) {
		//show white rects
		int musicIndex;
		for (musicIndex = 0; musicIndex < musicActiveRects; musicIndex++) {
			SDL_RenderFillRect(renderer, &musicVolumeRect[musicIndex]);
		}
		//show gray rects
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
		for (musicIndex; musicIndex < 5; musicIndex++) {
			SDL_RenderFillRect(renderer, &musicVolumeRect[musicIndex]);
		}
	}
	else {
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
		for (int i = 0; i < 5; i++) {
			SDL_RenderFillRect(renderer, &musicVolumeRect[i]);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

	if (soundOn) {
		//show white rects
		int soundIndex;
		for (soundIndex = 0; soundIndex < soundActiveRects; soundIndex++) {
			SDL_RenderFillRect(renderer, &soundVolumeRect[soundIndex]);
		}
		//show gray rects
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
		for (soundIndex; soundIndex < 5; soundIndex++) {
			SDL_RenderFillRect(renderer, &soundVolumeRect[soundIndex]);
		}
	}
	else {
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
		for (int i = 0; i < 5; i++) {
			SDL_RenderFillRect(renderer, &soundVolumeRect[i]);
		}
	}
}

void start(float time, SDL_Renderer* renderer) {
	timer += time;
	if (actualServeTime != (int)timer) {
		actualServeTime = (int)timer;
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-Stencil.ttf", getScreenHeight() / 15, std::to_string((int)timer + 1), &textStart, renderer);
	}
	if (timer >= 3.0f) {
		timer = 0;
		serve = false;
	}
}

void loadBackgroundImages(SDL_Renderer* renderer) {
	loadImage(renderer, "images/background/common-heather.jpg", &backgroundImages[0]);
	loadImage(renderer, "images/background/field.jpg", &backgroundImages[1]);
	loadImage(renderer, "images/background/house.jpg", &backgroundImages[2]);
	loadImage(renderer, "images/background/lightning.jpg", &backgroundImages[3]);
	loadImage(renderer, "images/background/petit-minou-lighthouse.jpg", &backgroundImages[4]);
	loadImage(renderer, "images/background/port.jpg", &backgroundImages[5]);
	loadImage(renderer, "images/background/street.jpg", &backgroundImages[6]);
	loadImage(renderer, "images/background/walking.jpg", &backgroundImages[7]);
	loadImage(renderer, "images/background/water.jpg", &backgroundImages[8]);
	loadImage(renderer, "images/background/sand.jpg", &backgroundImages[9]);
}

void initMenu(SDL_Renderer* renderer) {

	boardWidth = int(SCREEN_WIDTH * 0.8);

	menuWidth = SCREEN_WIDTH - boardWidth;

	startRect.w = boardWidth / 2;
	startRect.h = SCREEN_HEIGHT / 2;
	startRect.x = boardWidth / 2 - startRect.w / 2;
	startRect.y = SCREEN_HEIGHT / 2 - startRect.h / 2;

	int spaceY = SCREEN_HEIGHT / 10;
	assignProperties(&textScoreRect, 0, menuWidth / 2, spaceY);
	assignProperties(&textPuntuationRect, textScoreRect.y + textScoreRect.h,
		menuWidth / 5, spaceY);
	assignProperties(&textLevelRect, textPuntuationRect.y + textPuntuationRect.h,
		textScoreRect.w, spaceY);
	assignProperties(&textLevelPuntuationRect, textLevelRect.y + textLevelRect.h,
		textPuntuationRect.w, spaceY);
	assignProperties(&textLivesRect, textLevelPuntuationRect.y +
		textLevelPuntuationRect.h, textScoreRect.w, spaceY);
	assignProperties(&textLifeNumberRect, textLivesRect.y +
		textLivesRect.h, textPuntuationRect.w, spaceY);
	assignProperties(&textRestartRect, textLifeNumberRect.y +
		textLifeNumberRect.h, menuWidth, spaceY);

	assignProperties(&textShootTimerRect, textRestartRect.y +
		textRestartRect.h, menuWidth, spaceY);

	spaceY = SCREEN_HEIGHT / 20;
	pauseRects[0].x = SCREEN_WIDTH / 3;
	pauseRects[0].y = spaceY;
	pauseRects[0].h = 3 * spaceY;

	for (int i = 1; i < 6; i++) {
		pauseRects[i].x = 0;
	}

	for (int i = 1; i < 6; i++) {
		pauseRects[i].y = pauseRects[i - 1].y + pauseRects[i - 1].h + spaceY;
		pauseRects[i].h = SCREEN_HEIGHT / 10;
	}
	for (int i = 6; i < 9; i++) {
		pauseRects[i].x = (int)(SCREEN_WIDTH * 0.75) - pauseRects[i].w / 2;
		pauseRects[i].y = pauseRects[i - 4].y;
		pauseRects[i].h = SCREEN_HEIGHT / 10;
	}

	for (int i = 0; i < 5; i++) {
		musicVolumeRect[i].w = (int)(SCREEN_WIDTH * 0.03);
		musicVolumeRect[i].h = (int)(SCREEN_WIDTH * 0.01 * ((double)i + 1));
		musicVolumeRect[i].y = pauseRects[2].y + pauseRects[2].h - musicVolumeRect[i].h;

		soundVolumeRect[i].w = musicVolumeRect[i].w;
		soundVolumeRect[i].h = musicVolumeRect[i].h;
		soundVolumeRect[i].y = pauseRects[3].y + pauseRects[3].h - musicVolumeRect[i].h;
	}
	musicVolumeRect[0].x = SCREEN_WIDTH / 2;
	soundVolumeRect[0].x = SCREEN_WIDTH / 2;
	for (int i = 1; i < 5; i++) {
		musicVolumeRect[i].x = musicVolumeRect[i - 1].x + musicVolumeRect[i - 1].w;
		soundVolumeRect[i].x = soundVolumeRect[i - 1].x + soundVolumeRect[i - 1].w;
	}
	backGroundRect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
}

void setSoundRects(int number) {
	soundActiveRects = number;
}

void setMusicRects(int number) {
	musicActiveRects = number;
}

void turnOnMusic(SDL_Renderer* renderer) {
	musicOn = true;
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
	if (musicOn)
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[6], renderer);
	else
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[6], renderer);
}

void turnOffMusic(SDL_Renderer* renderer) {
	musicOn = false;
	if (Mix_PlayingMusic()) {
		Mix_PauseMusic();
	}
	if (musicOn)
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[6], renderer);
	else
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[6], renderer);
}

void turnOnSound(SDL_Renderer* renderer) {
	soundOn = true;
	Mix_VolumeChunk(sound, (int)(MIX_MAX_VOLUME * 0.2 * soundActiveRects));
	if (soundOn)
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[7], renderer);
	else
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[7], renderer);
}

void turnOffSound(SDL_Renderer* renderer) {
	soundOn = false;
	if (soundOn)
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[7], renderer);
	else
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[7], renderer);
	Mix_VolumeChunk(sound, 0);
}

void musicOnOff(SDL_Renderer* renderer) {
	musicOn = !musicOn;
	if (musicOn) {
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME * 0.2 * musicActiveRects));
		if (Mix_PausedMusic()) {
			Mix_ResumeMusic();
		}
	}
	else {
		if (Mix_PlayingMusic()) {
			Mix_PauseMusic();
		}
	}
	if (musicOn)
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[6], renderer);
	else
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[6], renderer);
}

void soundOnOff(SDL_Renderer* renderer) {
	soundOn = !soundOn;
	if (soundOn)
		Mix_VolumeChunk(sound, (int)(MIX_MAX_VOLUME * 0.2 * soundActiveRects));
	else
		Mix_VolumeChunk(sound, 0);
	if (soundOn)
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[7], renderer);
	else
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[7], renderer);
}

void fullscreenOnOff(SDL_Renderer* renderer) {
	fullscreen = !fullscreen;
	if (fullscreen)
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "ON", &pauseTextures[8], renderer);
	else
		generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10, "OFF", &pauseTextures[8], renderer);
}


//change volume of music to 0.2 * activeMusicRects and change the text on/off if it is necesary
void changeMusicRects(SDL_Renderer* renderer, int activeMusicRects) {
	Mix_VolumeMusic((int)(MIX_MAX_VOLUME * activeMusicRects * 0.2));
	setMusicRects(activeMusicRects);
	if (!musicOn) {
		musicOnOff(renderer);
	}
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
}

void changeWindowGameSize(SDL_Renderer* renderer, int fps, SDL_Window* window) {
	int screenWidth;
	int screenHeight;
	SDL_GetWindowSize(window, &screenWidth, &screenHeight);
	setScreenWidth(screenWidth);
	setScreenHeight(screenHeight);
	initMenu(renderer);
	initPaddle();
	resizeBricks();
	initCommandLine();
	initCapsuleVariables(renderer);
	writeGameMenu(renderer);
	writePauseMenu(renderer);
	writeCommandLineText(renderer, command);
	writeAllCommands(renderer);
	generateTextTexture({ 36,144,98 }, "fonts/OpenSans-Bold.ttf", fpsTextRect.h, std::to_string(fps), &fpsText, &fpsTextRect, renderer);
}

void changeFullscreenGameSize(SDL_Renderer* renderer, int fps, SDL_Window* window) {
	if (fullscreen) {
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_SetWindowSize(window, Width, Height);
		setScreenWidth(Width);
		setScreenHeight(Height);
		initMenu(renderer);
		initPaddle();
		resizeBricks();
		initCommandLine();
		initCapsuleVariables(renderer);
		writeGameMenu(renderer);
		writePauseMenu(renderer);
	}
	else {
		SDL_SetWindowFullscreen(window, 0);
		changeWindowGameSize(renderer, fps, window);
	}
}

//change volume of sound to 0.2 * activeMusicRects and change the text on/off if it is necesary
void changeSoundRects(SDL_Renderer* renderer, int activeSoundRects) {
	Mix_VolumeChunk(sound, (int)(MIX_MAX_VOLUME * activeSoundRects * 0.2));
	setSoundRects(activeSoundRects);
	if (!soundOn) {
		soundOnOff(renderer);
	}
}