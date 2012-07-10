#include "DrunkenWalk.h"
#define doubleRate 2


struct predictor{
    short direction;
    short timesTaken;
};

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

int** DrunkenWalk::walkPathWithMap(int numSteps, const std::map<int,TileSpec> tileMap){
  
    
    //TODO pull from map.
    int tileID=0;
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
    int direction=-1;
    //! The failure sentinel.
    bool failed = true;

    while (stepsTaken < numberSteps){
        // Get a random number from 0-3 and react accordingly.
        switch ((direction=rand()%4)){
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
           tileID= static_cast<TileSpec>(tileMap.at(tileID)).getNextTile(direction);
            matrix[x][y] = tileID;
            stepsTaken++;
        }

        failed = true;
    }
    return matrix;
}


int** DrunkenWalk::get2DMap(){
    return matrix;
}


