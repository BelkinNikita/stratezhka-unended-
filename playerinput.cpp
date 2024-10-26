#include <vector>
#include "SFML/Graphics.hpp"
#include <iostream>
#include "playerInput.h"

//ref
void drawSelectingRect();
void clearSelectingUnits();
void createMovePoint(float posX, float posY);
void createAttackPoint(float posX, float posY);


//methods
void playerInput() {

	//mouse
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && lftMouseIsPressed == false)
	{
		if (unitISOneClicked) {
			int i = -1;
			for (const auto& sprite : UnitEntities) {
				++i;
				if (UnitEntitiesBehavior[i][0] == ThisPlayerId) {
					SelectedUnits.push_back(sprite);
					UnitEntitiesBehavior[i][1] = 1;
				}
			}
		}
		else {
			lftMouseIsPressed = true;
			clearSelectingUnits();
			posMouseStarted = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			int i = 0;
			for (sf::Sprite sprite : UnitEntities) {
				++i;
				sf::FloatRect bounds = sprite.getGlobalBounds();
				if (bounds.contains(posMouseStarted))
				{
					if (UnitEntitiesBehavior[i-1][0] == ThisPlayerId) {
					SelectedUnits.push_back(sprite);
					std::cout << "unit " << i << " is selected:" << std::endl;
					UnitEntitiesBehavior[i - 1][1] = 1;
					unitISOneClicked = true;
					}
				}
			}

		}
	}
		
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Right)) && RhtMouseIsPressed == false) {
		if ((sf::Keyboard::isKeyPressed((sf::Keyboard::A)))) {
			std::cout << "unit attacks" << std::endl;
			createAttackPoint(posMouse.x, posMouse.y);
		}
		else {
			std::cout << "unit moves" << std::endl;
			createMovePoint(posMouse.x, posMouse.y);
			
		}
		RhtMouseIsPressed = true;
	}

	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) {
		lftMouseIsPressed = false;
		rectIsDrawing = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == false) {
		RhtMouseIsPressed = false;
	}
}





void drawSelectingRect() {
	if (rectIsDrawing = false) { rectangle.setSize(sf::Vector2f(15, 15)); }
	else { rectangle.setSize(sf::Vector2f((posMouse.x - posMouseStarted.x ), posMouse.y- posMouseStarted.y )); }
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Green);
	rectangle.setOutlineThickness(2);
	rectangle.setPosition(posMouseStarted.x, posMouseStarted.y);
	rectIsDrawing = true;
}

void clearSelectingUnits(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) == false)
	{
		SelectedUnits.clear();
		UIEntities.clear();
		for (int i = 0; i <= size(UnitEntities)-1; ++i) {
			UnitEntitiesBehavior[i][1] = 0;
		}
	}
}

void createMovePoint(float posX, float posY) {
	for (int i = 0; i <= size(UnitEntities) - 1; ++i) {
		if (UnitEntitiesBehavior[i][1] == 1) {
			UnitEntitiesBehavior[i][4] = 1;
			UnitEntitiesBehavior[i][2] = posX;
			UnitEntitiesBehavior[i][3] = posY;
			UIEntities.clear();
		}
	}

	
}

void AttackObject(float posX, float posY) {}

void createAttackPoint(float posX, float posY) {
	sf::Sprite sprite;
	sprite.setTexture(attackPoit);
	sprite.setTextureRect(sf::IntRect(0, 0, 8, 12));
	sprite.setPosition(posX, posY);
	UIEntities.push_back(sprite);
}

