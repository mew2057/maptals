#include "DrunkenWalk.h"

int** DrunkenWalk::generate2DMap(int numSteps){
    //TODO make this more efficient!

    //! This clears the field (ensuring any height or width changes are reflected in the new map.
    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
    removeMatrix();
    zeroMatrix();

    //! Seed the random number generator.
    srand(time(NULL));
    
    //! Set the step related values: zeroes the step count and ensures the number of steps is positive 
    //! and not greater than the size of the map.
    int stepsTaken = 0;
    int numberSteps = abs(numSteps) < width*height ? abs(numSteps) :width*height;

    //! Randomly set the start point.
    int x = rand() % (width);
    int y = rand() % (height);
    
    //! Sets the difference in the ids to reduce the number of computations in the loop and primes the failure sentinel.
    int valueDiff = maxValue - minValue + 1;
    bool failed = true;

    while (stepsTaken < numberSteps){
        // Get a random number from 0-3 and react accordingly.
        switch (rand()%4){
            // North - step up.
            case 0:
                if(y != height-1){
                    y++;
                    failed = false;
                }
                break;
            // East - step right.
            case 1:
                if(x != width-1){
                    x++;
                    failed = false;
                }
                break;
            // South - step down.
            case 2:
                if(y != 0){
                    y--;
                    failed = false;
                }
                break;
            // West - step left.
            case 3:
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

int** DrunkenWalk::get2DMap(){
    return matrix;
}
