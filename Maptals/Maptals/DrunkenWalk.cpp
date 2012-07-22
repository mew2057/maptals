#include "DrunkenWalk.h"
#define doubleRate 2
#include <iostream>

//int** DrunkenWalk::walkPathNaive(int numSteps){
//    //! This clears the field (ensuring any height or width changes are reflected in the new map.
//    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
//    removeMatrix();
//    zeroMatrix();
//
//    //! Seed the random number generator.
//    srand(time(NULL));
//    
//    //! Set the step related values: zeroes the step count.
//    int stepsTaken = 0;
//
//    //! Ensures the number of steps is positive and not greater than the size of the map.
//    int numberSteps = abs(numSteps) < width*height ? abs(numSteps) :width*height;
//
//    //! Randomly set the x start point.
//    int x = rand() % (width);
//    
//    //! Randomly set the y start point.
//    int y = rand() % (height);
//    
//    //! Sets the difference in the ids to reduce the number of computations in the loop.
//    int valueDiff = maxValue - minValue + 1;
//
//    //! The failure sentinel.
//    bool failed = true;
//
//    while (stepsTaken < numberSteps){
//        // Get a random number from 0-3 and react accordingly.
//        switch (rand()%4){
//            // North - step up.
//            case north:
//                if(y > 0){
//                    y--;
//                    failed = false;
//                }
//                break;
//            // East - step right.
//            case east:
//                if(x < width-1){
//                    x++;
//                    failed = false;
//                }
//                break;
//            // South - step down.
//            case south:
//                 if(y < height-1){
//                    y++;
//                    failed = false;
//                }                
//                break;
//            // West - step left.
//            case west:
//                if(x > 0){
//                    x--;
//                    failed = false;
//                }
//                break;
//            default:
//                break;
//        }
//        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
//        if(!failed && matrix[y][x] == emptyValue) {
//            matrix[y][x] = rand() % valueDiff + minValue;
//            stepsTaken++;
//        }
//
//        failed = true;
//    }
//
//    return matrix;
//}
//
//int** DrunkenWalk::walkPathNoRetrace(int numSteps){
//    //! This clears the field (ensuring any height or width changes are reflected in the new map.
//    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
//    removeMatrix();
//    zeroMatrix();
//
//     //! Seed the random number generator.
//    srand(time(NULL));
//
//    //! A short for maintaining the las direction moved to prevent the algorithm from doubleing back on itself.
//    short lastDirection=-1;
//
//    //! Set the step related values: zeroes the step count.
//    int stepsTaken = 0;
//
//    //! Ensures the number of steps is positive and not greater than the size of the map.
//    int numberSteps = abs(numSteps) < width*height ? abs(numSteps) :width*height;
//
//    //! Randomly set the x start point.
//    int x = rand() % (width);
//    
//    //! Randomly set the y start point.
//    int y = rand() % (height);
//        
//    //! Sets the difference in the ids to reduce the number of computations in the loop.
//    int valueDiff = maxValue - minValue + 1;
//
//    //! The failure sentinel.
//    bool failed = true;
//
//    while (stepsTaken < numberSteps){
//        // Get a random number from 0-3 and react accordingly.
//        switch (rand() % doubleRate || lastDirection == -1 ? rand() % 4 : lastDirection){
//            // North - step up.
//            case north:
//                if(y > 0 && lastDirection != north){
//                    y--;
//                    failed = false;
//                    lastDirection=south;
//                }
//                break;
//            // East - step right.
//            case east:
//                if(x < width-1 && lastDirection != west){
//                    x++;
//                    failed = false;
//                    lastDirection=east;
//                }
//                break;
//            // South - step down.
//            case south:
//                if(y < height-1 && lastDirection != south){
//                    y++;
//                    failed = false;
//                    lastDirection=north;
//                }
//              
//                break;
//            // West - step left.
//            case west:
//                if(x > 0 && lastDirection != east){
//                    x--;
//                    failed = false;
//                    lastDirection=west;
//                }
//                break;
//            default:
//                break;
//        }
//        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
//        if(!failed && matrix[y][x] == emptyValue) {
//            matrix[y][x] = rand() % valueDiff + minValue;
//            stepsTaken++;
//        }
//
//        failed = true;
//    }
//
//    return matrix;
//}
//
//int** DrunkenWalk::walkPathWithTileSet(TileSet tileSet){
//    //! This grabs the first tile id listed in the tile map, this is the lowest numeric id in the tileset.
//    int tileID=4;
//
//    TileSpec currentTile=tileSet.getTileMap().find(tileID)->second;
//    emptyValue=-1;
//    //! This clears the field (ensuring any height or width changes are reflected in the new map.
//    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
//    removeMatrix();
//    zeroMatrix();
//
//    //! Seed the random number generator.
//    srand(time(NULL));
//    
//    //! Set the step related values: zeroes the step count.
//    int stepsTaken = 0;
//
//    //! Randomly set the x start point.
//    int x = 0;
//    
//    //! Randomly set the y start point.
//    int y = tileSet.getHorizon();
//
//    int direction=-1;
//    
//    //! The failure sentinel.
//    bool failed = true;
//
// 
//    matrix[y][x]=tileID;
//
//
//    while (x < width-1){
//        // Get a random number from 0-3 and react accordingly.
//        switch (direction=currentTile.getNextDirection()){
//            // North - step up.
//            case north:
//                if(y > 0){
//                    y--;
//                    failed = false;
//                }
//                break;
//            // East - step right.
//            case east:
//                if(x < width-1){
//                    x++;
//                    failed = false;
//                }
//                else{
//                    x++;
//                    continue;
//                }
//                break;
//            // South - step down.
//            case south:
//                if(y < height-1){
//                    y++;
//                    failed = false;
//                }
//                
//                break;
//            // West - step left.
//            case west:
//                if(x > 0){
//                    x--;
//                    failed = false;
//                }
//                break;
//            default:
//                break;
//        }
//
//        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
//        if(!failed && matrix[y][x] == emptyValue) {
//           try{ 
//               tileID = static_cast<TileSpec>(tileSet.getTileMap().find(tileID)->second).getNextTile(direction);
//
//               if (tileID == INT_MIN)
//                 exit(0); //This is a major violation and indicates a bad tile specification
//
//               currentTile=tileSet.getTileMap().find(tileID)->second;
//           }
//           catch(...){
//           }
//           
//
//            matrix[y][x] = tileID;
//        }
//
//        failed = true;
//
//    }
//    return matrix;
//}

std::vector<std::vector<int>> DrunkenWalk::generate2DMap()
{
    //! This grabs the first tile id listed in the tile map, this is the lowest numeric id in the tileset.
    int tileID=4;

    TileSpec currentTile=tileSet.getTileMap().find(tileID)->second;
    //! This clears the field (ensuring any height or width changes are reflected in the new map.
    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
    resizeMatrix();

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

        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
        if(!failed && matrix[y][x] == tileSet.getEmptyTile()) {
           try{ 
               tileID = static_cast<TileSpec>(tileSet.getTileMap().find(tileID)->second).getNextTile(direction);

               if (tileID == INT_MIN)
                 exit(0); //This is a major violation and indicates a bad tile specification

               currentTile=tileSet.getTileMap().find(tileID)->second;
           }
           catch(...){
           }
           
           matrix[y][x] = tileID;
        }

        failed = true;
    }
    return matrix;
}



