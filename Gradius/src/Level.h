#pragma once
#include <vector>

struct EnemyData {
	int type{};
	int totalEnemies{};
	//vector of size = total enemies, positions of the enemies: up,middle,down
	std::vector<int> positions{};
	//index of the elements with an upgrade
	std::vector<int> upgrade{};
	int lifes{};
	int speedY{};
};

struct ProgressEnemyData {
	int progress{};
	EnemyData enemyData{};
};

class Level {
public:
	Level();

	

	void setTimer(const float newTimer) { timer = newTimer; }
	void setActualRound(const int newIndex) { actualRound = newIndex; }
	void setActualPhase(const int newPhase) { actualPhase = newPhase; }
	void setProgress(const float newProgress) { progress = newProgress; }
	void setActualProgressEnemy(const int newPE) { actualProgressEnemy = newPE; }

	float getTimer() const { return timer; }
	int getActualRound() const { return actualRound; }
	int getActualPhase() const { return actualPhase; }
	int getActualProgressEnemy() const { return actualProgressEnemy; }
	float getProgress() const { return progress; }
	std::vector<float> getTimeRounds() const { return timeRound; }
	std::vector<int> getTotalPhaseRounds() const { return totalPhaseRounds; }
	std::vector<ProgressEnemyData> getPhaseProgressEnemies() const { return phaseProgressEnemies; }
	std::vector<EnemyData> getTimeEnemyData() const { return phaseTimeEnemies; }

	//take the actual pixel in x and the size of the sprite of the map and calculates the position in sprites
	void update(float actualX, float size);
	void addTimeRound(float time);
	void addTotalPhaseRound(int total);
	void addTimeEnemyData(EnemyData element);
	void addProgressEnemyData(ProgressEnemyData element);
	
private:
	int actualPhase;

	float timer;
	
	std::vector<float> timeRound; 
	//total enemy rounds on phase <index = phase>
	std::vector<int> totalPhaseRounds; 
	//actual round index
	int actualRound;
	std::vector<EnemyData> phaseTimeEnemies;


	int actualProgressEnemy;
	std::vector<ProgressEnemyData> phaseProgressEnemies;
	
	float progress;
};