#include "TileSpec.h" 

int TileSpec::getNextTile(int direction){
    unsigned int defaultSeed = static_cast<unsigned int>(time(NULL));

    return getNextTile(direction, defaultSeed);
}

//! This is evenly random, no weight on outcomes.
int TileSpec::getNextTile(int direction, unsigned int seed){
    srand(seed);

    if(direction < succeedingTiles.size())
    {
        return succeedingTiles.at(direction).at(rand() % succeedingTiles.at(direction).size());
    }
    else
    {
        return -1;
    }
}

void TileSpec::appendTile(int direction, int tile){
    if(direction < succeedingTiles.size())
        succeedingTiles.at(direction).push_back(tile);
    //TODO add error condition.    
}

TileSpec::TileSpec(){
    succeedingTiles = std::vector<std::vector<int>>(4, std::vector<int>(0));
}

TileSpec::~TileSpec(){
}