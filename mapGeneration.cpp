#include "mapGeneration.h"
#include <fstream>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "mapCity.h"


// ref
void initTexturesAndUnit();
void createHashList();

// creating an in-game map
class in_game_Map {
public:
    void preDrawMap() {


        
    }

};

// take x,y for map
void mapInit() {
    initTexturesAndUnit();
    std::cout << "map is initialising" << std::endl;
    in_game_Map currentMap;
    currentMap.preDrawMap();
    createHashList();
    ThisPlayerId = 1;
    

};

void createHashList() {
    std::vector<int> row;
    for (int i = 0; i < mainWindowHeigth / sizeOfHash; ++i) {
        for (int j = 0; j < mainWindowWidth / sizeOfHash; ++j) {
            bool x = false;
            row.push_back(x);
        }
        mapHash.push_back(row);
        row.clear();
    }
    /*for (int i = 0; i < size(mapHash); ++i) {
        std::cout << std::endl;
        for (int j =0; j < size(mapHash[i]); ++j) {
            std::cout << mapHash[i][j];
        }
    }*/
}
