#include "SFML/Graphics.hpp"
#include "units.h"
#include <vector>

// ref
void initTexturesAndUnit();
void checkUnitCondition();
void spawnUnit(int playerID, int gotUnitTypeID, float posX, float posY);
void moveUnit(int i);
enum AllUnitsNames { test, fighter};
void changeAnimation(int i, int a);

namespace unitsByID
{
	enum AllUnitsNames {
		test = 0, 
		fighter = 1
	};

}
void spawnUnit(int playerID,int gotUnitTypeID, float posX, float posY) {
	sf::Sprite sprite;
	int x_Sprite = 0, y_Sprite = 0;
	int SPEED = 0;
	switch (gotUnitTypeID) {
	case 0:
	{
		x_Sprite = 15;
		y_Sprite = 20;
		sprite.setTexture(testIdle);
	}
	case 1:
	{
		x_Sprite = 25;
		y_Sprite = 46;
		SPEED = 1;
		sprite.setTexture(redSwordman);
	}
	sprite.setTextureRect(sf::IntRect(0, 0, x_Sprite, y_Sprite));
	}
	sprite.setPosition(posX, posY);
	UnitEntities.push_back(sprite);

	std::cout << posX << "\n";
	std::cout << "test" << "\n";

	int playerNumber					    = playerID;
	int unitSelected					    = 0;
	int x_Move						   	    = 0;
	int y_Move							    = 0;
	int unitTypeAction					    = 0; // 0 - idle, 1 - move, 2 - attack
	int x_hashLocation					    = posX / sizeOfHash;
	int y_hashLocation					    = posY / sizeOfHash;
	int iterationOfAnimation			    = 0;
	int unitPathIsConstructed			    = 0;
	mapHash[y_hashLocation][x_hashLocation] = playerNumber;

	std::vector<int> unitBehavior = { playerNumber, unitSelected, x_Move, y_Move, unitTypeAction,
		iterationOfAnimation, x_Sprite, y_Sprite, SPEED, x_hashLocation, y_hashLocation };

	UnitEntitiesBehavior.push_back(unitBehavior);
	std::cout << "Unit of player: " << UnitEntitiesBehavior[0][0] << "\n";
}


/* playerNumber		  = 0
unitSelected		  = 1
x_Move				  = 2
y_Move				  = 3
unitIsMoving	      = 4
iterationOfAnimation  = 5
x_Sprite			  = 6
y_Sprite			  = 7
SPEED				  = 8
x_hashLocation		  = 9
y_hashLocation		  = 10
*/


void checkUnitCondition() {
	for (int i = 0; i <= size(UnitEntities) - 1; ++i) {
		if (UnitEntitiesBehavior[i][4] == 1) {
			moveUnit(i);
		}

		else {
			if (GAME_TICKS == 8) {
				switch (UnitEntitiesBehavior[i][5]) {
				case 0:
					UnitEntities[i].setTextureRect(sf::IntRect(0, 0, UnitEntitiesBehavior[i][6], UnitEntitiesBehavior[i][7]));
					++UnitEntitiesBehavior[i][5];
					break;

				case 1:
					UnitEntities[i].setTextureRect(sf::IntRect(UnitEntitiesBehavior[i][6] + 1, 0, UnitEntitiesBehavior[i][6], UnitEntitiesBehavior[i][7]));
					UnitEntitiesBehavior[i][5] = 0;
					break;
				}

			}
		}
	}
}


void initTexturesAndUnit() {
	// UNITS
	testIdle.loadFromFile("sprites/units/Test/test.png");
	zealotPNG.loadFromFile("sprites/template/zealot.png");
	sithreSELECTED.loadFromFile("sprites/UI/sithreSELECTED_SELECTED.png");
	redSwordman.loadFromFile("sprites/units/red_swordman/red_swordman.psd");

	movePoit.loadFromFile("sprites/UI/movePoint.png");
	attackPoit.loadFromFile("sprites/UI/attackPoint.png");
}


void moveUnit(int i) {
	bool unitMoved = false;

	sf::Vector2f positionOfSprite = UnitEntities[i].getPosition();
	//++y
	if (UnitEntitiesBehavior[i][3] > positionOfSprite.y && mapHash[(positionOfSprite.y / sizeOfHash) + 1][positionOfSprite.x / sizeOfHash] == false) {
		mapHash[positionOfSprite.y / sizeOfHash][positionOfSprite.x / sizeOfHash] = false;
		if ((GAME_TICKS & UnitEntitiesBehavior[i][8]) == 0) { ++positionOfSprite.y; }
		unitMoved = true;
		changeAnimation(i, 1);
	}
	//--y
	else if (UnitEntitiesBehavior[i][3] < positionOfSprite.y && mapHash[(positionOfSprite.y / sizeOfHash) - 1][positionOfSprite.x / sizeOfHash] == false) {
		mapHash[positionOfSprite.y / sizeOfHash][positionOfSprite.x / sizeOfHash] = false;
		if ((GAME_TICKS & UnitEntitiesBehavior[i][8]) == 0) { positionOfSprite.y = positionOfSprite.y - UnitEntitiesBehavior[i][8]; }
		unitMoved = true;
		changeAnimation(i, 2);
	}
	//++x
	if (UnitEntitiesBehavior[i][2] > positionOfSprite.x && mapHash[positionOfSprite.y / sizeOfHash][(positionOfSprite.x / sizeOfHash) + 1] == false) {
		mapHash[positionOfSprite.y / sizeOfHash][positionOfSprite.x / sizeOfHash] = false;
		if ((GAME_TICKS & UnitEntitiesBehavior[i][8]) == 0) { positionOfSprite.x = positionOfSprite.x + UnitEntitiesBehavior[i][8]; }
		if (unitMoved == false) { changeAnimation(i, 3); }

	}
	//--x
	else if (UnitEntitiesBehavior[i][2] < positionOfSprite.x && mapHash[positionOfSprite.y / sizeOfHash][(positionOfSprite.x / sizeOfHash) - 1] == false) {
		mapHash[positionOfSprite.y / sizeOfHash][positionOfSprite.x / sizeOfHash] = false;
		if ((GAME_TICKS & UnitEntitiesBehavior[i][8]) == 0) { positionOfSprite.x = positionOfSprite.x - UnitEntitiesBehavior[i][8]; }
		if (unitMoved == false) { changeAnimation(i, 4); 
		
		}
	}
	UnitEntities[i].setPosition(positionOfSprite.x, positionOfSprite.y);
	UnitEntitiesBehavior[i][9] = positionOfSprite.y / sizeOfHash;
	UnitEntitiesBehavior[i][10] = positionOfSprite.x / sizeOfHash;
	mapHash[UnitEntitiesBehavior[i][9]][UnitEntitiesBehavior[i][10]] = UnitEntitiesBehavior[i][0];

		if (positionOfSprite.x == UnitEntitiesBehavior[i][2] && positionOfSprite.y == UnitEntitiesBehavior[i][3]) {
		UnitEntitiesBehavior[i][4] = false;
		std::cout << "is arrived \n";
	}


	if ((UnitEntitiesBehavior[i][1] == true) && RhtMouseIsPressed == true) {

		sf::Sprite sprite;
		sprite.setTexture(movePoit);
		sprite.setTextureRect(sf::IntRect(0, 0, 8, 12));
		sprite.setPosition(UnitEntitiesBehavior[i][2], UnitEntitiesBehavior[i][3] - 6);
		UIEntities.push_back(sprite);
	}
}


void changeAnimation(int i, int a) {
	if (GAME_TICKS == 16) {
		switch (UnitEntitiesBehavior[i][5]) {
		case 0:
			UnitEntities[i].setTextureRect(sf::IntRect(0, (UnitEntitiesBehavior[i][7] + 1) * a, UnitEntitiesBehavior[i][6], UnitEntitiesBehavior[i][7]));
			++UnitEntitiesBehavior[i][5];
			break;


		case 1:
			UnitEntities[i].setTextureRect(sf::IntRect(UnitEntitiesBehavior[i][6] + 1, (UnitEntitiesBehavior[i][7] + 1) * a, UnitEntitiesBehavior[i][6], UnitEntitiesBehavior[i][7]));
			UnitEntitiesBehavior[i][5] = 0;
			break;

		}
	}
}