#include "DrunkenWalk.h"
#define doubleRate 2
#include <iostream>

std::vector<std::vector<int>> DrunkenWalk::generate2DMap()
{
    //! This grabs the first tile id listed in the tile map, this is the lowest numeric id in the tileset.
    int tileID=4;

    TileSpec currentTile=tileSet.getTileMap().find(tileID)->second;
    //! This clears the field (ensuring any height or width changes are reflected in the new map.
    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
    resizeMatrix();
    zeroMatrix();

    //! Seed the random number generator.
    srand(time(NULL));
    
    //! Set the step related values: zeroes the step count.
    int stepsTaken = 0;

    //! Randomly set the x start point.
    int x = 0;
    
    //! Sets the starting y to the horizon (subtract from the height then offeset by one).
    int y = height - tileSet.getHorizon() -1;

    int direction=-1;
    
    //! The failure sentinel.
    bool failed = true;

 
    matrix[y][x]=tileID;


    while (x < width-1){
        // Get a random number from 0-3 and react accordingly.
        switch (direction=currentTile.getNextDirection()){
            // North - step up.
            case north:
                if(y > 0){
                    y--;
                    failed = false;
                }
                break;
            // East - step right.
            case east:
                if(x < width-1){
                    x++;
                    failed = false;
                }
                else{
                    x++;
                    continue;
                }
                break;
            // South - step down.
            case south:
                if(y < height-1){
                    y++;
                    failed = false;
                }
                
                break;
            // West - step left.
            case west:
                if(x > 0){
                    x--;
                    failed = false;
                }
                break;
            default:
                break;
        }
                std::cout << direction;

        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
        if(!failed && matrix[y][x] == tileSet.getEmptyTile()) {
           try{ 
               tileID = static_cast<TileSpec>(*tileSet.getTileID(tileID)).getNextTile(direction);

               if (tileID == INT_MIN)
                 exit(0); //This is a major violation and indicates a bad tile specification

               currentTile=*tileSet.getTileID(tileID);
           }
           catch(...){
           }
           
           matrix[y][x] = tileID;
        }

        failed = true;
    }
    return matrix;
}