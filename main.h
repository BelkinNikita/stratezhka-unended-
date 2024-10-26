#include <list>
#include <SFML/System/Clock.hpp>

//window's settings
const int mainWindowWidth = 700;
const int mainWindowHeigth = 900;
sf::RenderWindow window(sf::VideoMode(mainWindowWidth, mainWindowHeigth), "stratezhka");

//for player's input
sf::Event event;
bool lftMouseIsPressed;
bool RhtMouseIsPressed;
bool loopIsStarted;
bool unitISOneClicked;

//color
sf::Color DarkGray = { 55, 55, 55, 255 };

//counts seconds for game ticks
sf::Clock game_ticks;
sf::Clock one_second;
int FPS_NUMBER = 0;
int GAME_TICKS = 0;



sf::RectangleShape rectangle;

std::vector<std::vector<int> > mapHash;
const int sizeOfHash = 10;

int ThisPlayerId = 0;




