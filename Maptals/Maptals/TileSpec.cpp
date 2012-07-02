#include "TileSpec.h"

int TileSpec::getTileValue(){
    return tileValue;
}

void TileSpec::setTileValue(int newVal){
    tileValue = newVal;
}
    

int TileSpec::getNextTile(int direction){
    unsigned int defaultSeed = static_cast<unsigned int>(time(NULL));

    return getNextTile(direction, defaultSeed);
}

int TileSpec::getNextTile(int direction, unsigned int seed){
    srand(seed);

    
    return 0;
}

void TileSpec::appendTile(int direction, int tile){
    succeedingTiles.at(direction).push_back(tile);
}

TileSpec::TileSpec(){
    succeedingTiles = std::vector<std::vector<int>>(4, std::vector<int>(0));
    tileValue = -1;


}

TileSpec::~TileSpec(){
}