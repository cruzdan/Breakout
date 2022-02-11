// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Level.h"

Level::Level():
	timer(0),
	timeRound(),
	totalPhaseRounds(),
	actualRound(0),
	actualProgressEnemy(0),
	phaseTimeEnemies(),
	phaseProgressEnemies(),
	actualPhase(0),
	progress(0)
{

}

void Level::update(float actualX, float size) {
	progress = actualX / size;
}

void Level::addTimeRound(float time) {
	timeRound.push_back(time);
}

void Level::addTotalPhaseRound(int total) {
	totalPhaseRounds.push_back(total);
}

void Level::addTimeEnemyData(EnemyData element) {
	phaseTimeEnemies.push_back(element);
}

void Level::addProgressEnemyData(ProgressEnemyData element) {
	phaseProgressEnemies.push_back(element);
}