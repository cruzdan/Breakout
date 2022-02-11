// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Mountain.h"

Mountain::Mountain():
	totalX(),
	totalY(),
	coordinates()
{
	setMountainCoordinates();
}

void Mountain::setMountainCoordinates() {
	totalX[0] = 4;
	totalY[0] = 3;
	//coordinates with y = -1 means there is no mountain
	coordinates[0].push_back({ 74,-1 });
	coordinates[0].push_back({ 75,10 });
	coordinates[0].push_back({ 76,10 });
	coordinates[0].push_back({ 77,-1 });

	coordinates[0].push_back({ 74,-1 });
	coordinates[0].push_back({ 75,11 });
	coordinates[0].push_back({ 76,11 });
	coordinates[0].push_back({ 77,-1 });

	coordinates[0].push_back({ 74,12 });
	coordinates[0].push_back({ 75,12 });
	coordinates[0].push_back({ 76,12 });
	coordinates[0].push_back({ 77,12 });

	totalX[1] = 6;
	totalY[1] = 4;

	coordinates[1].push_back({ 108,-1 });
	coordinates[1].push_back({ 109,-1 });
	coordinates[1].push_back({ 110,9 });
	coordinates[1].push_back({ 111,9 });
	coordinates[1].push_back({ 112,-1 });
	coordinates[1].push_back({ 113,-1 });

	coordinates[1].push_back({ 108,-1 });
	coordinates[1].push_back({ 109,-1 });
	coordinates[1].push_back({ 110,10 });
	coordinates[1].push_back({ 111,10 });
	coordinates[1].push_back({ 112,10 });
	coordinates[1].push_back({ 113,-1 });

	coordinates[1].push_back({ 108,-1 });
	coordinates[1].push_back({ 109,-1 });
	coordinates[1].push_back({ 110,-1 });
	coordinates[1].push_back({ 111,-1 });
	coordinates[1].push_back({ 112,-1 });
	coordinates[1].push_back({ 113,-1 });

	coordinates[1].push_back({ 108,12 });
	coordinates[1].push_back({ 109,12 });
	coordinates[1].push_back({ 110,12 });
	coordinates[1].push_back({ 111,12 });
	coordinates[1].push_back({ 112,12 });
	coordinates[1].push_back({ 113,12 });

	totalX[2] = 6;
	totalY[2] = 4;

	coordinates[2].push_back({ 138,-1 });
	coordinates[2].push_back({ 139,-1 });
	coordinates[2].push_back({ 140,9 });
	coordinates[2].push_back({ 141,9 });
	coordinates[2].push_back({ 142,-1 });
	coordinates[2].push_back({ 143,-1 });

	coordinates[2].push_back({ 138,-1 });
	coordinates[2].push_back({ 139,10 });
	coordinates[2].push_back({ 140,10 });
	coordinates[2].push_back({ 141,10 });
	coordinates[2].push_back({ 142,10 });
	coordinates[2].push_back({ 143,-1 });

	coordinates[2].push_back({ 138,-1 });
	coordinates[2].push_back({ 139,11 });
	coordinates[2].push_back({ 140,11 });
	coordinates[2].push_back({ 141,11 });
	coordinates[2].push_back({ 142,11 });
	coordinates[2].push_back({ 143,-1 });

	coordinates[2].push_back({ 138,12 });
	coordinates[2].push_back({ 139,12 });
	coordinates[2].push_back({ 140,12 });
	coordinates[2].push_back({ 141,12 });
	coordinates[2].push_back({ 142,12 });
	coordinates[2].push_back({ 143,12 });

	totalX[3] = 4;
	totalY[3] = 4;

	coordinates[3].push_back({ 178,-1 });
	coordinates[3].push_back({ 179,5 });
	coordinates[3].push_back({ 180,5 });
	coordinates[3].push_back({ 181,-1 });

	coordinates[3].push_back({ 178,6 });
	coordinates[3].push_back({ 179,6 });
	coordinates[3].push_back({ 180,6 });
	coordinates[3].push_back({ 181,6 });

	coordinates[3].push_back({ 178,7 });
	coordinates[3].push_back({ 179,7 });
	coordinates[3].push_back({ 180,7 });
	coordinates[3].push_back({ 181,7 });

	coordinates[3].push_back({ 178,-1 });
	coordinates[3].push_back({ 179,8 });
	coordinates[3].push_back({ 180,8 });
	coordinates[3].push_back({ 181,-1 });

	totalX[4] = 4;
	totalY[4] = 3;

	coordinates[4].push_back({ 194,-1 });
	coordinates[4].push_back({ 195,10 });
	coordinates[4].push_back({ 196,10 });
	coordinates[4].push_back({ 197,-1 });

	coordinates[4].push_back({ 194,-1 });
	coordinates[4].push_back({ 195,11 });
	coordinates[4].push_back({ 196,11 });
	coordinates[4].push_back({ 197,-1 });

	coordinates[4].push_back({ 194,12 });
	coordinates[4].push_back({ 195,12 });
	coordinates[4].push_back({ 196,12 });
	coordinates[4].push_back({ 197,12 });

	totalX[5] = 4;
	totalY[5] = 3;

	coordinates[5].push_back({ 202,-1 });
	coordinates[5].push_back({ 203,10 });
	coordinates[5].push_back({ 204,10 });
	coordinates[5].push_back({ 205,-1 });

	coordinates[5].push_back({ 202,-1 });
	coordinates[5].push_back({ 203,11 });
	coordinates[5].push_back({ 204,11 });
	coordinates[5].push_back({ 205,-1 });

	coordinates[5].push_back({ 202,12 });
	coordinates[5].push_back({ 203,12 });
	coordinates[5].push_back({ 204,12 });
	coordinates[5].push_back({ 205,12 });
}

/// <summary>
/// check if the cordinates are the first element by left(down and left side) of the mountain
/// </summary>
/// <param name="mountainIndex">index to check the mountain collision</param>
/// <param name="coordX">coordinate x of the element to check the collision</param>
/// <param name="coordY">coordinate y of the element to check the collision</param>
/// <returns>true if coordX and coordY are the first left coordinate of the mountain, false in other case</returns>
bool Mountain::checkFirstMountainCoordinateForLeft(int mountainIndex, int coordX, int coordY) {
	//first element by left: down and left side of mountain
	Coordinate coord = coordinates[mountainIndex].at(0 + (totalY[mountainIndex] - 1) * totalY[mountainIndex]);
	if (coord.x == coordX && coord.y == coordY) {
		return true;
	}
	return false;
}

/// <summary>
/// check if the cordinates are the first element by right(down and right side) of the mountain
/// </summary>
/// <param name="mountainIndex">index to check the mountain collision</param>
/// <param name="coordX">coordinate x of the element to check the collision</param>
/// <param name="coordY">coordinate y of the element to check the collision</param>
/// <returns>true if coordX and coordY are the first right coordinate of the mountain, false in other case</returns>
bool Mountain::checkFirstMountainCoordinateForRight(int mountainIndex, int coordX, int coordY) {
	//first element by right: down and right side of mountain
	int ind = totalX[mountainIndex] - 1 + (totalY[mountainIndex] - 1) * totalY[mountainIndex];
	Coordinate coord = coordinates[mountainIndex].at(ind);
	if (coord.x == coordX && coord.y == coordY) {
		return true;
	}
	return false;
}

//get the mountain index when the [actualCoordX, distanceCoord] has a collision with mountain[index?], if it has no collision, return -1
int Mountain::getMountainIndexOnRate(int actualCoordX, int distanceCoord) {
	int firstCoord;
	int lastCoord;
	if (actualCoordX + distanceCoord > actualCoordX) {
		firstCoord = actualCoordX;
		lastCoord = actualCoordX + distanceCoord;
	}
	else {
		firstCoord = actualCoordX + distanceCoord;
		lastCoord = actualCoordX;
	}

	for (int i = 0; i < 2; i++) {
		int ind = totalX[i] - 1;
		if ((coordinates[i].at(0).x >= firstCoord && coordinates[i].at(0).x <= lastCoord)
			|| (coordinates[i].at(ind).x >= firstCoord && coordinates[i].at(ind).x <= lastCoord)) {
			//the coordinates by parameter(at least one) are outside the mountain
			return i;
		}
		if ((firstCoord >= coordinates[i].at(0).x && firstCoord <= coordinates[i].at(ind).x) ||
			(lastCoord >= coordinates[i].at(0).x && lastCoord <= coordinates[i].at(ind).x)) {
			//the coordinates by parameter are inside the mountain
			return i;
		}
	}
	return -1;
}

//get the x coordinate of the mountain that does not have collision on the top side (used to down the enemy 5),i: mountainIndex
int Mountain::getLastRightMountainCoordinate(int i) {
	int ind = totalX[i] - 1;
	int actualX = coordinates[i].at(ind).x;
	for (int j = totalX[i] - 1; j >= 0; j--) {
		if (coordinates[i].at(j).y == -1) {
			actualX = coordinates[i].at(j).x;
		}
		else {
			break;
		}
	}
	return actualX;
}

//get the x coordinate of the mountain that does not have collision on the top side (used to down the enemy 5),i: mountainIndex
int Mountain::getLastLeftMountainCoordinate(int i) {
	int actualX = coordinates[i].at(0).x;
	for (int j = 0; j < totalX[i] - 1; j++) {
		if (coordinates[i].at(j).y == -1) {
			actualX = coordinates[i].at(j).x;
		}
		else {
			break;
		}
	}
	return actualX;
}

//get the collision index when the [actualCoordX, distanceCoord] has a collision with a mountain[index?] or an obstacle, if it has no collision, return -1
int Mountain::getCollisionIndexOnRate(int actualCoordX, int distanceCoord) {
	int firstCoord;
	int lastCoord;
	if (actualCoordX + distanceCoord > actualCoordX) {
		firstCoord = actualCoordX;
		lastCoord = actualCoordX + distanceCoord;
	}
	else {
		firstCoord = actualCoordX + distanceCoord;
		lastCoord = actualCoordX;
	}

	for (int i = 0; i < 6; i++) {
		int ind = totalX[i] - 1;
		if ((coordinates[i].at(0).x >= firstCoord && coordinates[i].at(0).x <= lastCoord)
			|| (coordinates[i].at(ind).x >= firstCoord && coordinates[i].at(ind).x <= lastCoord)) {
			//the coordinates by parameter(at least one) are outside the mountain
			return i;
		}
		if ((firstCoord >= coordinates[i].at(0).x && firstCoord <= coordinates[i].at(ind).x) ||
			(lastCoord >= coordinates[i].at(0).x && lastCoord <= coordinates[i].at(ind).x)) {
			//the coordinates by parameter are inside the mountain
			return i;
		}
	}
	return -1;
}

bool Mountain::hasCenterCollision(int xCoordinate, int yCoordinate, int collisionIndex) {
	int ind = totalX[collisionIndex] - 1;
	if (xCoordinate >= coordinates[collisionIndex].at(0).x &&
		xCoordinate <= coordinates[collisionIndex].at(ind).x) {
		int indexInX = xCoordinate - coordinates[collisionIndex].at(0).x;
		for (auto cord : coordinates[collisionIndex]) {
			if (cord.x == xCoordinate && cord.y == yCoordinate) {
				return true;
			}
		}
	}
	return false;
}

//get the missile state with a collision on the map: -1->crash,0->move right, 1->falling down with the actual and next coordinates
int Mountain::getMissileStateMap(int actualX, int actualY, int rightX, int downY, int mountainIndex) {
	for (int k = 0; k < totalX[mountainIndex]; k++) {
		if (coordinates[mountainIndex].at(k).x > rightX) {
			// falling down
			return 1;
		}
		if (coordinates[mountainIndex].at(k).x == rightX) {
			for (int g = totalY[mountainIndex] - 1; g >= 0; g--) {
				int ind = k + g * totalX[mountainIndex];
				if (coordinates[mountainIndex].at(ind).y == actualY) {
					//missile crash with a colision
					return -1;
				}
				else if (coordinates[mountainIndex].at(ind).y == downY) {
					if (mountainIndex != 1 && rightX < coordinates[mountainIndex].at(0).x + totalX[mountainIndex] / 2) {
						//missile is crashing with the left side of a mountain
						return -1;
					}
					//move to right
					return 0;
				}
			}
		}
	}
	return 1;
}