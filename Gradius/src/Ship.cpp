// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Ship.h"
#include "Textures.h"
#include "HorizontalBullet.h"
#include "InclinedBullet.h"
#include "Missile.h"
#include "Laser.h"
#include "Option.h"
#include "Shield.h"
#include "Render.h"
#include "Mountain.h"
#include "Level.h"

Ship::Ship():
	x(0),
	y(0),
	w(0),
	h(0),
	direction(0),
	speedX(0),
	speedY(0),
	bulletTimer(0),
	lifes(3),
	score(0),
	firstX(0),
	firstY(0),
	endX(0),
	endY(0),
	actualUpgrade(-1),
	hasMissile(false),
	keyUp(),
	keyDown(),
	keyRight(),
	keyLeft(),
	keyShoot(),
	keySelectUpgrade(),
	shield(nullptr),
	menuRects(),
	spriteRects(),
	menuTextures(),
	maxUpgrades(),
	gettedUpgrades(),
	incrementSpeedX(0),
	incrementSpeedY(0),
	missileUpgrade(false),
	doubleUpgrade(false),
	laserUpgrade(false),
	mountain(nullptr),
	level(nullptr),
	invincible(false),
	timerInvincible(0),
	timeInvincible(0),
	dead(false)
{
	shield = new Shield();
	mountain = new Mountain();

	initUpgrades();
	
}

void Ship::moveUp(int limit, float deltaTime) {
	if (y - speedY * deltaTime >= limit) {
		y -= speedY * deltaTime;
		direction = 1;
	}
}

void Ship::moveDown(int limit, float deltaTime) {
	if (y + h + speedY * deltaTime <= limit) {
		y += speedY * deltaTime;
		direction = 2;
	}
}

void Ship::moveRight(int limit, float deltaTime) {
	if (x + w + speedX * deltaTime <= limit)
		x += speedX * deltaTime;
}

void Ship::moveLeft(int limit, float deltaTime) {
	if (x - speedX * deltaTime >= limit)
		x -= speedX * deltaTime;
}

void Ship::shootLaserBullet(float mx, float my) {
	Laser* bull = new Laser();
	bull->setX(mx + w);
	bull->setY(my + h / 2 - h / 8);
	bull->setW(w / 3);
	bull->setH(h / 4);
	bull->setfirstX(firstX);
	bull->setfirstY(firstY);
	bull->setEndX(endX);
	bull->setEndY(endY);
	bull->setSpeedX(800);
	bull->setDamage(2);
	addBullet(bull);
}

void Ship::shootMissile(float mx, float my, int mId) {
	Missile* missile = new Missile();
	missile->setX(mx + w);
	missile->setY(my + h / 2 - h / 10);
	missile->setW(w / 4);
	missile->setH(h / 5);
	missile->setfirstX(firstX);
	missile->setfirstY(firstY);
	missile->setEndX(endX);
	missile->setEndY(endY);
	missile->setSpeedX(200);
	missile->setSpeedY(200);
	missile->setAngle(315);
	missile->setID(mId);
	missile->setDamage(1);
	missile->setLevel(level);
	addMissile(missile);
}

void Ship::shootInclinedBullet(float mx, float my) {
	InclinedBullet* bull = new InclinedBullet();
	bull->setX(mx + w);
	bull->setY(my + h / 2 - h / 6);
	bull->setW(w / 3);
	bull->setH(h / 3);
	bull->setfirstX(firstX);
	bull->setfirstY(firstY + endY / 13);
	bull->setEndX(endX);
	bull->setEndY(endY);
	bull->setSpeed(500, 45);
	bull->setDamage(1);
	addBullet(bull);
}

void Ship::shootHorizontalBullet(float mx, float my) {
	HorizontalBullet* bull = new HorizontalBullet();
	bull->setX(mx + w);
	bull->setY(my + h / 2 - h / 6);
	bull->setW(w / 3);
	bull->setH(h / 3);
	bull->setfirstX(firstX);
	bull->setfirstY(firstY);
	bull->setEndX(endX);
	bull->setEndY(endY);
	bull->setSpeedX(500);
	bull->setDamage(1);
	addBullet(bull);
}

void Ship::shoot(float mx, float my) {

	if (doubleUpgrade || laserUpgrade) {
		if (doubleUpgrade) {
			shootHorizontalBullet(mx, my);
			shootInclinedBullet(mx, my);
			for (auto option : options) {
				shootHorizontalBullet(option->getX(), option->getY());
				shootInclinedBullet(option->getX(), option->getY());
			}
		}
		else {
			shootLaserBullet(mx, my);
			for (auto option : options) {
				shootLaserBullet(option->getX(), option->getY());
			}
		}
	}
	else {
		shootHorizontalBullet(mx, my);
		for (auto option : options) {
			shootHorizontalBullet(option->getX(), option->getY());
		}
	}
	
}

void Ship::updateBulletTimer(float deltaTime) {
	if (bulletTimer > 0) {
		bulletTimer -= deltaTime;
	}
}

void Ship::update(float deltaTime) {
	updateBulletTimer(deltaTime);
	if (invincible) {
		timerInvincible += deltaTime;
		if (timerInvincible >= timeInvincible) {
			invincible = false;
			timerInvincible = 0;
		}
	}
	for (auto bullet : bullets) {
		bullet->update(deltaTime);
	}
	for (auto missile : missiles) {
		missile->update(deltaTime);
	}
	
	shield->update(deltaTime);
	for (auto option : options) {
		option->update(deltaTime);
	}

	for (auto bullet : bullets) {
		if (bullet->getDead()){
			deleteBullet(bullet);
		}
	}
	for (auto missile : missiles) {
		if (missile->getDead()) {
			switch (missile->getID()) {
			case 0:
				hasMissile = false;
				break;
			case 1:
				options.at(0)->setHasMissile(false);
				break;
			case 2:
				options.at(1)->setHasMissile(false);
				break;
			}
			deleteMissile(missile);
		}
	}
}

void Ship::show(SDL_Renderer* renderer) {
	SDL_Rect shipRect, spriteRect;
	shipRect = { (int)x,(int)y,w,h };
	int widthImage = 32;

	if (invincible) {
		int k = (int)(timerInvincible * 10) % 5;
		if (k > 2.5) {
			spriteRect = { 0,0,widthImage,20 };
			switch (direction) {
			case 1:
				spriteRect.x = widthImage;
				break;
			case 2:
				spriteRect.x = 2 * widthImage;
				break;
			}
			SDL_RenderCopy(renderer, shipTexture, &spriteRect, &shipRect);
		}
	}
	else {
		spriteRect = { 0,0,widthImage,20 };
		switch (direction) {
		case 1:
			spriteRect.x = widthImage;
			break;
		case 2:
			spriteRect.x = 2 * widthImage;
			break;
		}
		SDL_RenderCopy(renderer, shipTexture, &spriteRect, &shipRect);
	}
	for (auto bullet : bullets) {
		bullet->show(renderer);
	}
	for (auto missile : missiles) {
		missile->show(renderer);
	}
	
	if (shield->getLifes() > 0)
		shield->show(renderer);

	for (auto option : options) {
		option->show(renderer);
	}
}

void Ship::moveShield() {
	if (shield->getLifes() > 0) {
		shield->setX(x + w);
		shield->setY(y);
	}
}

void Ship::moveComponents() {
	moveShield();
	int i = 0;
	for (auto option : options) {
		if (i == 0)
			option->move(x, y);
		else
			option->move(options.at(0)->getX(), options.at(0)->getY());
		i++;
	}
}

void Ship::detectKey(float deltaTime, const Uint8* keys) {
	if (keys[keyUp]) {
		moveUp(firstY, deltaTime);
		moveComponents();
	}
	if (keys[keyDown]) {
		moveDown(endY, deltaTime);
		moveComponents();
	}
	if (keys[keyRight]) {
		moveRight(endX, deltaTime);
		moveComponents();
	}
	if (keys[keyLeft]) {
		moveLeft(firstX, deltaTime);
		moveComponents();
	}
	if (keys[keyShoot]) {
		if (bulletTimer <= 0){
			shoot(x, y);
			bulletTimer = 0.25;
		}
		if (missileUpgrade) {
			if (!hasMissile) {
				hasMissile = true;
				shootMissile(x, y, 0);
			}
			int i = 1;
			for (auto option : options) {
				if (!option->getHasMissile()) {
					option->setHasMissile(true);
					shootMissile(option->getX(), option->getY(), i);
				}
				i++;
			}
		}
	}
	if (keys[keySelectUpgrade]) {
		if (actualUpgrade > -1) {
			if (gettedUpgrades[actualUpgrade] < maxUpgrades[actualUpgrade]) {
				switch (actualUpgrade) {
				case 0:
					incrementSpeed();
					break;
				case 1:
					missileUpgrade = true;
					break;
				case 2:
					if (laserUpgrade)
						laserUpgrade = false;
					doubleUpgrade = true;
					break;
				case 3:
					if (doubleUpgrade)
						doubleUpgrade = false;
					laserUpgrade = true;
					break;
				case 4:
					addOption(deltaTime);
					break;
				case 5:
					shield->setLifes(10);
					shield->setBlueSprites();
					moveShield();
					break;
				}
				if (actualUpgrade < 6) {
					gettedUpgrades[actualUpgrade]++;
					if (gettedUpgrades[actualUpgrade] == maxUpgrades[actualUpgrade]) {
						spriteRects[actualUpgrade].x = 38;
						spriteRects[actualUpgrade].y = 100;
					}
					else {
						spriteRects[actualUpgrade].y = 82;
					}
				}
				actualUpgrade = -1;
			}
		}
	}
}

void Ship::getUpgrade() {
	if (actualUpgrade > -1) {
		if (gettedUpgrades[actualUpgrade] < maxUpgrades[actualUpgrade]) {
			spriteRects[actualUpgrade].y = 82;
		}
		else {
			spriteRects[actualUpgrade].x = 38;
			spriteRects[actualUpgrade].y = 100;
		}
	}
	if (actualUpgrade < 5) {
		actualUpgrade++;
	}
	else {
		actualUpgrade = 0;
	}
	if (gettedUpgrades[actualUpgrade] < maxUpgrades[actualUpgrade]) {
		spriteRects[actualUpgrade].y = 91;
	}
	else {
		spriteRects[actualUpgrade].x = 6;
		spriteRects[actualUpgrade].y = 100;
	}
}

void Ship::incrementSpeed() {
	speedX += incrementSpeedX;
	speedY += incrementSpeedY;
}

void Ship::addBullet(class Bullet* bullet) {
	bullets.push_back(bullet);
}

void Ship::deleteBullet(class Bullet* bullet) {
	auto index = std::find(bullets.begin(), bullets.end(), bullet);
	if (index != bullets.end())
		bullets.erase(index);
}

void Ship::addMissile(class Missile* missile) {
	missiles.push_back(missile);
}

void Ship::deleteMissile(class Missile* missile) {
	auto index = std::find(missiles.begin(), missiles.end(), missile);
	if (index != missiles.end())
		missiles.erase(index);
}

void Ship::addOption(float deltaTime) {
	switch (options.size()) {
	case 0:
		createOptionToShip(deltaTime);
		break;
	case 1:
		createOptionToOption(deltaTime);
		break;
	}
}

void Ship::createOptionToShip(float deltaTime) {
	Option* option = new Option();
	option->setW(w / 2);
	option->setH(h / 2);
	for (int i = 10; i >= 1; i--) {
		option->addRoute(x, y + (speedY * deltaTime * i));
	}
	option->setX(option->getRoute().at(0).x);
	option->setY(option->getRoute().at(0).y);
	options.push_back(option);
}

void Ship::createOptionToOption(float deltaTime) {
	Option* option = new Option();
	option->setW(w / 2);
	option->setH(h / 2);
	for (int i = 10; i >= 1; i--) {
		option->addRoute(options.at(0)->getX(), options.at(0)->getY() + (speedY * deltaTime * i));
	}
	option->setX(option->getRoute().at(0).x);
	option->setY(option->getRoute().at(0).y);
	options.push_back(option);
}

void Ship::decrementShieldUpgrade() {
	gettedUpgrades[5]--;
}

void Ship::deleteOption(class Option* option) {
	auto index = std::find(options.begin(), options.end(), option);
	if (index != options.end())
		options.erase(index);
}

void Ship::setMenuRect(int index, int x, int y, int w, int h) {
	menuRects[index] = { x,y,w,h };
}

void Ship::setSpriteRect(int index, int x, int y, int w, int h) {
	spriteRects[index] = { x,y,w,h };
}

void Ship::changeScoreTexture(int height, SDL_Renderer* renderer) {
	std::string auxiliar = "";
	int total = 7 - (int)std::to_string(score).length();
	for (int i = 0; i < total; i++) {
		auxiliar += "0";
	}
	auxiliar += std::to_string(score);
	generateTextTexture({ 255,255,255 }, "ttf/Oswald-BoldItalic.ttf", height, auxiliar, &menuTextures[1], renderer);
}

void Ship::changeLifeTexture(int height, SDL_Renderer* renderer) {
	generateTextTexture({ 255,255,255 }, "ttf/Oswald-BoldItalic.ttf", height, std::to_string(lifes), &menuTextures[0], renderer);
}

void Ship::initMenuTexture(int height, SDL_Renderer* renderer) {
	generateTextTexture({ 255,255,255 }, "ttf/Oswald-BoldItalic.ttf", height , std::to_string(lifes), &menuTextures[0], renderer);
	generateTextTexture({ 255,255,255 }, "ttf/Oswald-BoldItalic.ttf", height, "0000000", &menuTextures[1], renderer);
}

void Ship::setYellowUpgrades() {
	for (int i = 0; i < 6; i++) {
		spriteRects[i].x = 6;
		spriteRects[i].y = 100;
	}
}

void Ship::initUpgrades() {
	maxUpgrades[0] = 10;
	maxUpgrades[1] = 1;
	maxUpgrades[2] = 1;
	maxUpgrades[3] = 1;
	maxUpgrades[4] = 2;
	maxUpgrades[5] = 1;

	for (int i = 0; i < 6; i++)
		gettedUpgrades[i] = 0;
	
	missileUpgrade = false;
	doubleUpgrade = false;
	laserUpgrade = false;
	hasMissile = false;
}

Vec4 Ship::getMenuRect(int index) {
	return menuRects[index];
}

Vec4 Ship::getSpriteRect(int index) {
	return spriteRects[index];
}

SDL_Texture* Ship::getMenuTexture(int index) {
	return menuTextures[index];
}

void Ship::clearBullets() {
	bullets.clear();
}

void Ship::clearMissiles() {
	missiles.clear();
}

void Ship::clearOptions() {
	options.clear();
}