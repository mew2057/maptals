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


void DrunkenWalk::generate2DMap(int maxDeviation, int minDeviation)
{
    // The guardians of valid space for tiles to spawn on the map.
    int maxDeviationX, minDeviationX,maxDeviationY, minDeviationY;


    if(tileSet.isHorizontal())
    {
        maxDeviationX = width-1;
        minDeviationX = 0;

        maxDeviationY = 0 + maxDeviation;
        maxDeviationY = maxDeviationY >= height ? 0 : maxDeviationY;
        maxDeviationY = maxDeviationY < 0 ? 0 : maxDeviationY;

        minDeviationY = height - 1 - minDeviation;
        minDeviationY = minDeviationY < 0 ? height-1 : minDeviationY;
        minDeviationY = minDeviationY >= height ? height-1 : minDeviationY;

    }
    else
    {
        //TODO TEST!!!
        maxDeviationY = 0;
        minDeviationY = height - 1;

        maxDeviationX = width - maxDeviation;
        maxDeviationX = maxDeviationX >= width ? width-1 : maxDeviationX;
        maxDeviationX = maxDeviationX < 0 ? width-1 : maxDeviationX;

        minDeviationX = 0 + minDeviation;
        minDeviationX = minDeviationX >= width ? 0 : minDeviationX;
        minDeviationX = minDeviationX < 0 ? 0 : minDeviationX;
    }

    //! Prevents crashing due to garbage input.
    if(minDeviationX >= maxDeviationX || minDeviationY <= maxDeviationY)
    {
        maxDeviationY = 0;
        minDeviationY = height - 1;
        maxDeviationX = width-1;
        minDeviationX = 0;
    }

    //! This grabs the first tile id listed in the tile map, this is specified id in tileset.
    int tileID=tileSet.getStartTile();

    TileSpec currentTile=tileSet.getTileMap().find(tileID)->second;

    //! This clears the field (ensuring any height or width changes are reflected in the new map.
    //! The the freshly defined map is "zeroed", or each index is set to minValue-1.
    resizeMatrix();
    zeroMatrix();

    //! Seed the random number generator.
    srand(time(NULL));

    //! Randomly set the x start point.
    int x = 0;
    
    //! Sets the starting y to the horizon (subtract from the height then offeset by one).
    int y = height - tileSet.getHorizon() -1;

    int direction=-1,failDirection =-1,oldTile=-1;

    std::stack<short> directions;
    
    //! The failure sentinel.
    bool failed = true;

    matrix[y][x]=tileID;

    while ((x < width-1 && tileSet.isHorizontal()) || (y >0 && !tileSet.isHorizontal())){
        // Get a random number from 0-3 and react accordingly.
        switch (direction=currentTile.getNextDirection(failDirection)){
            // North - step up.
            case north:
                if(y > maxDeviationY){
                    y--;
                    failed = false;
                }
                else if(!tileSet.isHorizontal()){
                    y--;
                    continue;
                }
                break;
            // East - step right.
            case east:
                if(x < maxDeviationX){
                    x++;
                    failed = false;
                }
                else if(tileSet.isHorizontal()){
                    x++;
                    continue;
                }
                break;
            // South - step down.
            case south:
                if(y < minDeviationY){
                    y++;
                    failed = false;
                }
                
                break;
            // West - step left.
            case west:
                if(x > minDeviationX){
                    x--;
                    failed = false;
                }
                break;
            default:

                do{
                    if(directions.size()==0)
                    {
                        tileID=INT_MIN;
                        continue;
                    }

                    failDirection=directions.top();

                    oldTile=matrix[y][x];

                    matrix[y][x]=tileSet.getEmptyTile();

                    getRetryPosition(&x,&y,failDirection);
                           
                    tileID=matrix[y][x];

                    currentTile=*tileSet.getTileID(tileID);

                    tileID = currentTile.getNextTile(failDirection, oldTile);

                    directions.pop();
                }while( tileID == INT_MIN);
                
                // IF fails is less than 5 Rerun the map generator. else exit.
                if (tileID == INT_MIN && ++Maptal::failCount < 5)
                {                   
                    generate2DMap(maxDeviation,minDeviation);
                    return;
                }
                else if(tileID == INT_MIN)
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

                // IF fails is less than 5 Rerun the map generator. else exit.
                if (tileID == INT_MIN && ++Maptal::failCount < 5)
                {                   
                    generate2DMap(maxDeviation,minDeviation);
                    return;
                }
                else if (tileID == INT_MIN)
                {
                    exit(1); //This is a major violation and indicates a bad tile specification
                }

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
}