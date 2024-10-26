#include "SFML/Graphics.hpp"
#include <iostream>
#include "main.h"
#include "mapGeneration.cpp"
#include "units.cpp"
#include <vector>
#include <SFML/System/Clock.hpp>
#include <thread>
#include "time.cpp"
#include "playerInput.cpp"

using namespace std;

//ref
void playerInput();
void timeUpdate();
void drawGame();
void collideRectWithSprite();


// game loop
int main()
{
	// window.setFramerateLimit(144);
	window.setVerticalSyncEnabled(true);
	mapInit();
	
	//only for  test
	for (float i = 0; i < 40; ++i) {
		spawnUnit(1, 1, i * 10, i * 20);
	}
	for (float i = 0; i < 5; ++i) {
		spawnUnit(2, 1, i * 40, i * 30);
	}
	for (float i = 0; i < 4; ++i) {
		spawnUnit(1, 0, i * 50, i * 50);
	}



	while (window.isOpen())
	{
		loopIsStarted = true;
		playerInput();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		posMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		timeUpdate();
		 checkUnitCondition(); 
		drawGame();
		window.display();

		
	}
	return 0;
}

//draws entities
void drawGame() {
	window.clear(DarkGray); {
		for (int i = 0; i <= size(UnitEntities) - 1; ++i) {
			if (UnitEntitiesBehavior[i][1] == 1) {
				sf::Sprite sprite;
				sf::Vector2f position = UnitEntities[i].getPosition();
				sprite.setTexture(sithreSELECTED);
				sprite.setTextureRect(sf::IntRect(0, 0, 25, 46));
				sprite.setPosition(position.x, position.y);
				SelectedUnits.push_back(sprite);

			}
			} /*
			for (auto& sprite : SelectedUnits) {
				sf::Vector2f position = sprite.getPosition();
				sprite.setTexture(sithreSELECTED);
				sprite.setTextureRect(sf::IntRect(0, 0, 16, 23));
			}*/
			for (const auto& sprite : SelectedUnits)
				window.draw(sprite);
			for (const auto& sprite : UnitEntities)
				window.draw(sprite);
			for (const auto& sprite : UIEntities)
				window.draw(sprite);
			SelectedUnits.clear();
			collideRectWithSprite();
		}
	}


void collideRectWithSprite() {
	if (lftMouseIsPressed == true) { drawSelectingRect(); }
	int i = 0;
	if (rectIsDrawing) {
		for (const auto& sprite : UnitEntities) {
			++i;
			if (UnitEntitiesBehavior[i - 1][0] == ThisPlayerId) {
				sf::FloatRect rect = rectangle.getGlobalBounds();
				sf::FloatRect bounds = sprite.getGlobalBounds();
				if (bounds.intersects(rect)) {
					if (UnitEntitiesBehavior[i - 1][1] != 1) {
						SelectedUnits.push_back(sprite);
						//cout << "unit " << i << " is selected" << endl;
						UnitEntitiesBehavior[i - 1][1] = 1;
					}
				}
			}
			window.draw(rectangle);
		}
	}
}
