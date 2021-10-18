#include <SDL.h>
#include <SDL_ttf.h>
#include "GlobalVariables.h"
#include "Music.h"
#include "Init.h"
#include "Command.h"
#include "Capsule.h"
#include "Image.h"

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
	switch (backGroundIndex) {
	case 0:
		loadImage(renderer, &backgroundTexture, "images/background/common-heather.jpg");
		break;
	case 1:
		loadImage(renderer, &backgroundTexture, "images/background/field.jpg");
		break;
	case 2:
		loadImage(renderer, &backgroundTexture, "images/background/house.jpg");
		break;
	case 3:
		loadImage(renderer, &backgroundTexture, "images/background/lightning.jpg");
		break;
	case 4:
		loadImage(renderer, &backgroundTexture, "images/background/petit-minou-lighthouse.jpg");
		break;
	case 5:
		loadImage(renderer, &backgroundTexture, "images/background/port.jpg");
		break;
	case 6:
		loadImage(renderer, &backgroundTexture, "images/background/street.jpg");
		break;
	case 7:
		loadImage(renderer, &backgroundTexture, "images/background/walking.jpg");
		break;
	case 8:
		loadImage(renderer, &backgroundTexture, "images/background/water.jpg");
		break;
	case 9:
		loadImage(renderer, &backgroundTexture, "images/background/sand.jpg");
		break;
	}
}

void writeGameMenu(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30);
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Solid(font, "Score", color);
	textScore = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "0", color);
	textPuntuation = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Level", color);
	textLevel = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "1", color);
	textLevelPuntuation = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Lives", color);
	textLives = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "3", color);
	textLifeNumber = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Press R to restart", color);
	textRestart = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

void writePauseMenu(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("fonts/Oswald-BoldItalic.ttf", (int)(SCREEN_HEIGHT * 0.15));
	SDL_Surface* textSurface;

	textSurface = TTF_RenderText_Solid(font, "Pause", color);
	pauseTextures[0] = SDL_CreateTextureFromSurface(renderer, textSurface);
	pauseRects[0].w = textSurface->w;

	font = TTF_OpenFont("fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10);

	textSurface = TTF_RenderText_Solid(font, "Press Esc to return to the game", color);
	pauseTextures[1] = SDL_CreateTextureFromSurface(renderer, textSurface);
	pauseRects[1].w = textSurface->w;

	textSurface = TTF_RenderText_Solid(font, "Music volume", color);
	pauseTextures[2] = SDL_CreateTextureFromSurface(renderer, textSurface);
	pauseRects[2].w = textSurface->w;

	textSurface = TTF_RenderText_Solid(font, "Sound volume", color);
	pauseTextures[3] = SDL_CreateTextureFromSurface(renderer, textSurface);
	pauseRects[3].w = textSurface->w;

	textSurface = TTF_RenderText_Solid(font, "Fullscreen", color);
	pauseTextures[4] = SDL_CreateTextureFromSurface(renderer, textSurface);
	pauseRects[4].w = textSurface->w;

	textSurface = TTF_RenderText_Solid(font, "Press here to exit", color);
	pauseTextures[5] = SDL_CreateTextureFromSurface(renderer, textSurface);
	pauseRects[5].w = textSurface->w;

	if(musicOn)
		textSurface = TTF_RenderText_Solid(font, "ON", color);
	else
		textSurface = TTF_RenderText_Solid(font, "OFF", color);
	pauseTextures[6] = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (soundOn)
		textSurface = TTF_RenderText_Solid(font, "ON", color);
	else
		textSurface = TTF_RenderText_Solid(font, "OFF", color);
	pauseTextures[7] = SDL_CreateTextureFromSurface(renderer, textSurface);
	
	if (fullscreen)
		textSurface = TTF_RenderText_Solid(font, "ON", color);
	else
		textSurface = TTF_RenderText_Solid(font, "OFF", color);
	pauseTextures[8] = SDL_CreateTextureFromSurface(renderer, textSurface);

	textSurface = TTF_RenderText_Solid(font, "ON", color);
	pauseRects[6].w = textSurface->w;
	pauseRects[7].w = textSurface->w;
	pauseRects[8].w = textSurface->w;

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
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

void start(float time) {
	timer += time;
	if (timer >= 3.0f) {
		timer = 0;
		serve = false;
	}
}

void countStart(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("fonts/Oswald-Stencil.ttf", SCREEN_HEIGHT / 15);
	SDL_Surface* textSurface;
	char c[4];
	int m = (int)timer + 1;
	SDL_itoa(m, c, 10);
	textSurface = TTF_RenderText_Solid(font, c, color);
	textStart = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

void writeLife(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30);
	SDL_Surface* textSurface;
	char c[2];
	SDL_itoa(lifes, c, 10);
	textSurface = TTF_RenderText_Solid(font, c, color);
	textLifeNumber = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

void writeLevel(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30);
	SDL_Surface* textSurface;
	char c[4];
	SDL_itoa(level, c, 10);
	textSurface = TTF_RenderText_Solid(font, c, color);
	textLevelPuntuation = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

void writeScore(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30);
	SDL_Surface* textSurface;
	//char c[4];
	//SDL_itoa(score, c, 10);
	textSurface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), color);
	textPuntuation = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

void initMenu() {
	
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
		musicVolumeRect[i].h = (int)(SCREEN_WIDTH * 0.01 * (i + 1));
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

void changeOnOffTextureText(SDL_Texture** texture, bool on, SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 10);
	SDL_Surface* textSurface;
	if (on)
		textSurface = TTF_RenderText_Solid(font, "ON", color);
	else
		textSurface = TTF_RenderText_Solid(font, "OFF", color);
	*texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

void turnOnMusic(SDL_Renderer* renderer) {
	musicOn = true;
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
	changeOnOffTextureText(&pauseTextures[6], musicOn, renderer);
}

void turnOffMusic(SDL_Renderer* renderer) {
	musicOn = false;
	if (Mix_PlayingMusic()) {
		Mix_PauseMusic();
	}
	changeOnOffTextureText(&pauseTextures[6], musicOn, renderer);
}

void turnOnSound(SDL_Renderer* renderer) {
	soundOn = true;
	Mix_VolumeChunk(sound, (int)(MIX_MAX_VOLUME * 0.2 * soundActiveRects));
	changeOnOffTextureText(&pauseTextures[7], soundOn, renderer);
}

void turnOffSound(SDL_Renderer* renderer) {
	soundOn = false;
	changeOnOffTextureText(&pauseTextures[7], soundOn, renderer);
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
	changeOnOffTextureText(&pauseTextures[6], musicOn, renderer);
}

void soundOnOff(SDL_Renderer* renderer) {
	soundOn = !soundOn;
	if (soundOn)
		Mix_VolumeChunk(sound, (int)(MIX_MAX_VOLUME * 0.2 * soundActiveRects));
	else
		Mix_VolumeChunk(sound, 0);
	changeOnOffTextureText(&pauseTextures[7], soundOn, renderer);
}

void fullscreenOnOff(SDL_Renderer* renderer) {
	fullscreen = !fullscreen;
	changeOnOffTextureText(&pauseTextures[8], fullscreen, renderer);
}


//cahnge volume of music to 0.2 * activeMusicRects and change the text on/off if it is necesary
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

void changeWindowGameSize(SDL_Renderer* renderer, int fps) {
	extern SDL_Window* window;
	int screenWidth;
	int screenHeight;
	SDL_GetWindowSize(window, &screenWidth, &screenHeight);
	setScreenWidth(screenWidth);
	setScreenHeight(screenHeight);
	initVariables(renderer);
	writeGameMenu(renderer);
	writePauseMenu(renderer);
	countStart(renderer);
	writeLife(renderer);
	writeLevel(renderer);
	writeScore(renderer);
	writeCommandLineText(renderer, command);
	writeAllCommands(renderer);
	writeFPSText(renderer, fps);
}

void changeFullscreenGameSize(SDL_Renderer* renderer, int fps) {
	if (fullscreen) {
		extern SDL_Window* window;
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_SetWindowSize(window, Width, Height);
		setScreenWidth(Width);
		setScreenHeight(Height);
		initVariables(renderer);
		writeGameMenu(renderer);
		writePauseMenu(renderer);
		countStart(renderer);
		writeLife(renderer);
		writeLevel(renderer);
		writeScore(renderer);
	}
	else {
		extern SDL_Window* window;
		SDL_SetWindowFullscreen(window, 0);
		changeWindowGameSize(renderer, fps);
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