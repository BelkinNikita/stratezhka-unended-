#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>


std::vector<sf::Sprite> UnitEntities;
std::vector<sf::Sprite> UIEntities;
std::vector<std::vector<int> > UnitEntitiesBehavior;
std::vector<sf::Sprite> SelectedUnits;


//UNITS
sf::Texture testIdle;
sf::Texture redSwordman;
sf::Texture zealotPNG;
sf::Texture sithreSELECTED;
// text
sf::Texture qwqw;

// UI
sf::Texture movePoit;
sf::Texture attackPoit;

bool pathIsConstructed = false;
std::vector<std::vector<int> >  UnitPath;