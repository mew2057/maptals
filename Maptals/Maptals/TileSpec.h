/*!
* \author John Dunham
* \date 7-1-12
* 
* This is a class designed to specify a set of rules for a tile in a tile based game, indicating valid tiles that follow it in the 4 cardinal directions.
* This class should not be handled by any user of this library.
*
*/

#ifndef MAPTALS_TILE_SPEC_H
#define MAPTALS_TILE_SPEC_H

#define north 0
#define east 1
#define south 2
#define west 3


#include <cstdlib>
#include <time.h>
#include <vector>
#include <iostream>


// TODO
// Variable tile rarity.
// References to other tiles.
// Design a file format for storing alongside tile.
// 
class TileSpec {
private:
    //! Holds the valid adjacent tiles.
    std::vector<std::vector<int>> succeedingTiles;
    std::vector<int> validDirections;

public:    
    int getNextTile(int direction);
    int getNextTile(int direction, unsigned int seed);
    void appendTile(int direction, int tile);
    int getNextDirection();

    TileSpec();
    ~TileSpec();

    friend std::ostream& operator<< ( std::ostream& outputStream, TileSpec& specification );
};

#endif