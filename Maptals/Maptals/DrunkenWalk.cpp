#include "DrunkenWalk.h"
#define doubleRate 2
#include <stack>

void getRetryPosition(int * x,int * y,short direction)
{
    switch(direction)
    {
        // North - step up.
        case north:
             (*y)++;
             break;
          // East - step right.
          case east:
             (*x)--; 
             break;
         // South - step down.
         case south:
             (*y)--;  
             break;
         // West - step left.
         case west:
             (*x)++;  
             break;
         default:
             break;
        
    }

}


std::vector<std::vector<int> > DrunkenWalk::generate2DMap()
{
    //! This grabs the first tile id listed in the tile map, this is the lowest numeric id in the tileset.
    int tileID=tileSet.getStartTile();

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

    int direction=-1,failDirection =-1,oldTile=-1;

    std::stack<short> directions;
    
    //! The failure sentinel.
    bool failed = true;

    matrix[y][x]=tileID;

    while (x < width-1){
        // Get a random number from 0-3 and react accordingly.
        switch (direction=currentTile.getNextDirection(failDirection)){
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
                do{
                    failDirection=directions.top();

                    oldTile=matrix[y][x];

                    matrix[y][x]=tileSet.getEmptyTile();

                    getRetryPosition(&x,&y,failDirection);
                           
                    tileID=matrix[y][x];

                    currentTile=*tileSet.getTileID(tileID);

                    tileID = currentTile.getNextTile(failDirection, oldTile);
                             
                    directions.pop();
                }while(directions.size()>0 && tileID == INT_MIN);
                
                if (tileID == INT_MIN)
                {
                    exit(1); //This is a major violation and indicates a bad tile specification
                }
                directions.push(failDirection);

                getRetryPosition(&x,&y,(failDirection+2)%4);

                matrix[y][x]=tileID;

                currentTile=*tileSet.getTileID(tileID);

                break;
        }
        //! Reset the failure direction.
        failDirection=-1;
        
        //! If the new position is not out of bounds and the matrix at that point is empty add a new value there.
        if(!failed && matrix[y][x] == tileSet.getEmptyTile() && oldTile == -1) {
           try{ 
               tileID = currentTile.getNextTile(direction);

               if (tileID == INT_MIN)
                 exit(0); //This is a major violation and indicates a bad tile specification

               currentTile=*tileSet.getTileID(tileID);
           }
           catch(...){
           }
           
           matrix[y][x] = tileID;
           directions.push(direction);
        } 
        else if(failed && oldTile == -1)
        {
            failDirection=direction;
        }

        oldTile = -1;
        failed = true;
    }
    return matrix;
}