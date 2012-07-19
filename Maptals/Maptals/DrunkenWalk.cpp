#include "DrunkenWalk.h"
#define doubleRate 2
#include <iostream>

int** DrunkenWalk::generate2DMap(int numSteps){
    //! This clears the field (ensuring any height or width changes are reflected in the new map.
    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
    removeMatrix();
    zeroMatrix();

    //! Seed the random number generator.
    srand(time(NULL));
    
    //! Set the step related values: zeroes the step count.
    int stepsTaken = 0;

    //! Ensures the number of steps is positive and not greater than the size of the map.
    int numberSteps = abs(numSteps) < width*height ? abs(numSteps) :width*height;

    //! Randomly set the x start point.
    int x = rand() % (width);
    
    //! Randomly set the y start point.
    int y = rand() % (height);
    
    //! Sets the difference in the ids to reduce the number of computations in the loop.
    int valueDiff = maxValue - minValue + 1;

    //! The failure sentinel.
    bool failed = true;

    while (stepsTaken < numberSteps){
        // Get a random number from 0-3 and react accordingly.
        switch (rand()%4){
            // North - step up.
            case north:
                if(y != height-1){
                    y++;
                    failed = false;
                }
                break;
            // East - step right.
            case east:
                if(x != width-1){
                    x++;
                    failed = false;
                }
                break;
            // South - step down.
            case south:
                if(y != 0){
                    y--;
                    failed = false;
                }
                break;
            // West - step left.
            case west:
                if(x != 0){
                    x--;
                    failed = false;
                }
                break;
            default:
                break;
        }
        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
        if(!failed && matrix[x][y] == emptyValue) {
            matrix[x][y] = rand() % valueDiff + minValue;
            stepsTaken++;
        }

        failed = true;
    }

    return matrix;
}

int** DrunkenWalk::walkPathNoRetrace(int numSteps){
    //! This clears the field (ensuring any height or width changes are reflected in the new map.
    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
    removeMatrix();
    zeroMatrix();

     //! Seed the random number generator.
    srand(time(NULL));

    //! A short for maintaining the las direction moved to prevent the algorithm from doubleing back on itself.
    short lastDirection=-1;

    //! Set the step related values: zeroes the step count.
    int stepsTaken = 0;

    //! Ensures the number of steps is positive and not greater than the size of the map.
    int numberSteps = abs(numSteps) < width*height ? abs(numSteps) :width*height;

    //! Randomly set the x start point.
    int x = rand() % (width);
    
    //! Randomly set the y start point.
    int y = rand() % (height);
        
    //! Sets the difference in the ids to reduce the number of computations in the loop.
    int valueDiff = maxValue - minValue + 1;

    //! The failure sentinel.
    bool failed = true;

    while (stepsTaken < numberSteps){
        // Get a random number from 0-3 and react accordingly.
        switch (rand() % doubleRate || lastDirection == -1 ? rand() % 4 : lastDirection){
            // North - step up.
            case north:
                if(y != height-1 && lastDirection != south){
                    y++;
                    failed = false;
                    lastDirection=north;
                }
                break;
            // East - step right.
            case east:
                if(x != width-1 && lastDirection != west){
                    x++;
                    failed = false;
                    lastDirection=east;
                }
                break;
            // South - step down.
            case south:
                if(y != 0 && lastDirection != north){
                    y--;
                    failed = false;
                    lastDirection=south;
                }
                break;
            // West - step left.
            case west:
                if(x != 0 && lastDirection != east){
                    x--;
                    failed = false;
                    lastDirection=west;
                }
                break;
            default:
                break;
        }
        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
        if(!failed && matrix[x][y] == emptyValue) {
            matrix[x][y] = rand() % valueDiff + minValue;
            stepsTaken++;
        }

        failed = true;
    }

    return matrix;
}

int** DrunkenWalk::walkPathWithMap(const std::map<int,TileSpec> tileMap){
    //! This grabs the first tile id listed in the tile map, this is the lowest numeric id in the tileset.
    int tileID=4;

    TileSpec currentTile=tileMap.find(tileID)->second;
    emptyValue=-1;
    //! This clears the field (ensuring any height or width changes are reflected in the new map.
    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
    removeMatrix();
    zeroMatrix();

    //! Seed the random number generator.
    srand(time(NULL));
    
    //! Set the step related values: zeroes the step count.
    int stepsTaken = 0;

    //! Randomly set the x start point.
    int x = 0;
    
    //! Randomly set the y start point.
    int y = height-1;

    int direction=-1;
    
    //! The failure sentinel.
    bool failed = true;

 
    matrix[x][y]=tileID;


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

        std::cout<< direction<<std::endl;
        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
        if(!failed && matrix[x][y] == emptyValue) {
            // This prevents fatal crashes due to poorly organized constraints. 
            // Please note, this makes the remainder of the ma a standard drunken walk with one tile.
            if(tileMap.find(tileID) != tileMap.end()){
               tileID = static_cast<TileSpec>(tileMap.find(tileID)->second).getNextTile(direction);

               if (tileID == INT_MIN)
                exit(0); //This is a major violation and indicates a bad tile specification

               currentTile=tileMap.find(tileID)->second;
            }
            else
                ;//TODO add exception.
            std::cout << "x: " << x << " y: " << y << std::endl;
            matrix[x][y] = tileID;
        }

        failed = true;

    }
    return matrix;
}


int** DrunkenWalk::get2DMap(){
    return matrix;
}


