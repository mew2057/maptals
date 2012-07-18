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
        return succeedingTiles[direction][rand() % succeedingTiles[direction].size()];
    }
    else
    {
        return -1;
    }
}

void TileSpec::appendTile(int direction, int tile){
    if(direction < succeedingTiles.size())
        succeedingTiles[direction].push_back(tile);
}

TileSpec::TileSpec(){
    succeedingTiles = std::vector<std::vector<int>>(4, std::vector<int>(0));
}

TileSpec::~TileSpec(){
}

std::ostream& operator<< ( std::ostream& outputStream, TileSpec& specification ){
    return outputStream << " North : \n" 
                        << specification.succeedingTiles[0].size() << "\n East: \n"
                        << specification.succeedingTiles[1].size() << "\n West: \n"
                        << specification.succeedingTiles[2].size() << "\n South: \n"
                        << specification.succeedingTiles[3].size() << "\n";
}