#include "TileSpec.h" 
#include <iostream>

//! This is evenly random, no weight on outcomes.
int TileSpec::getNextTile(int direction, unsigned int seed, int badTile){
    srand(seed);
    return getNextTile(direction,badTile);  
}

int TileSpec::getNextTile(int direction, int badTile){
    if(direction < succeedingTiles.size() && succeedingTiles[direction].size() > 0)
    {
        if(badTile!=-1)
        {
            int temp =  rand() % succeedingTiles[direction].size();

            if(succeedingTiles[direction][temp] == badTile && succeedingTiles[direction].size() > 1)
                return succeedingTiles[direction][(temp+1) % succeedingTiles[direction].size()];
        }
        else if (badTile ==-1)
        {
            return succeedingTiles[direction][rand() % succeedingTiles[direction].size()];
        }
    }
    return INT_MIN;
}

int TileSpec::getNextDirection(int badDirection){
    if(badDirection!=-1 && validDirections.size() > 1)
    {
        int index =rand()%validDirections.size();

        return validDirections[index]!=badDirection?validDirections[index]:validDirections[(index+1)%validDirections.size()];
    }
    else if(badDirection==-1 && validDirections.size()>0)
    {
        return validDirections[rand()%validDirections.size()];
    }
    return INT_MIN;
}

int TileSpec::getOID()
{
    return oid;
}
void TileSpec::setOID(int objectID)
{
    oid=objectID;
}


void TileSpec::appendTile(int direction, int tile){
    if(direction < succeedingTiles.size()) 
    {
        succeedingTiles[direction].push_back(tile);

        if(succeedingTiles[direction].size()==1)
        {
            validDirections.push_back(direction);
        }
    }
}

TileSpec::TileSpec(int _oid){
    succeedingTiles = std::vector<std::vector<int>>(4, std::vector<int>(0));
    validDirections = std::vector<int>(0);
    oid=_oid;
    srand(time(NULL));
}

std::ostream& operator<< ( std::ostream& outputStream, TileSpec& specification ){
    return outputStream << " North : \n" 
                        << specification.succeedingTiles[0].size() << "\n East: \n"
                        << specification.succeedingTiles[1].size() << "\n West: \n"
                        << specification.succeedingTiles[2].size() << "\n South: \n"
                        << specification.succeedingTiles[3].size() << "\n";
}