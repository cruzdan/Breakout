#pragma once
#include <vector>
#include "Vecs.h"

class Mountain {
public:
	Mountain();

	int getTotalX(const int index) const { return totalX[index]; }
	int getTotalY(const int index) const { return totalY[index]; }
	std::vector<Coordinate> getCoordinates(const int index) { return coordinates[index]; }

	bool checkFirstMountainCoordinateForLeft(int mountainIndex, int coordX, int coordY);
	bool checkFirstMountainCoordinateForRight(int mountainIndex, int coordX, int coordY);
	int getMountainIndexOnRate(int actualCoordX, int distanceCoord);
	int getLastRightMountainCoordinate(int mountainIndex);
	int getLastLeftMountainCoordinate(int mountainIndex);
	int getCollisionIndexOnRate(int actualCoordX, int distanceCoord);
	bool hasCenterCollision(int xCenter, int yCenter, int collisionIndex);
	int getMissileStateMap(int actualX, int actualY, int rightX, int downY, int mountainIndex);

private:
	void setMountainCoordinates();
	int totalX[6];
	int totalY[6];
	std::vector<Coordinate> coordinates[6];
};
