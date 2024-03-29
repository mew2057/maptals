/*!
* \author John Dunham
* \date 6-18-12
*
* \brief An implementation of the DrunkenWalk world generation algorithm for the Maptal library.
*
* This is my first attempt at a procedurally generated world. To say it is simple/ naive is an understatement, 
* but it illustrates the basic concepts of procedural generation. The algorithm is simple and lacks any form of
* intelligence in execution. The main benefit of this alogrithm lies in the guaranteed complete paths. For the
* random number generator I am simply using srand and rand. -John
*
* Update 6-21-12 : Added the walkPathNoRetrace function in an effort to beautify the results of the map generation.
*
* Update 6-21-12 : I was reviewing the general algorithm for this and I realized that I implemented an additive variation of this walk.
*                  It should be noted that the logic is unchanged, and this variation is slightly more expandable for what I want to do
*                  with it.
*
* Update 7-28-12 : Cleaned up the haeder file, updated Doxygen docs.
*
*/
#ifndef MAPTALS_DRUNKEN_WALK_H
#define MAPTALS_DRUNKEN_WALK_H

#include "Maptal.h"
#include "TileSpec.h"
#include "TileSet.h"

class DrunkenWalk: public Maptal{
public:
   /*
    *! \brief The Constructor of Drunken Walk, not much else to say here.
    *!
    *! \param width The width of the map to be generated. [defaults to 0]
    *! \param height The height of the map to be generated. [defaults to 0]
    *! \param tileSet The tileSet the walk will be generated from. [defaults to the generic TileSet]
    */
    DrunkenWalk(int width=0, int height=0,TileSet tileSet=TileSet()):Maptal(width, height, tileSet){};



   /*
    *! \brief Generate a 2D map utilizing the Maptal supplied TileSet with the DrunkenWalk world building algorithm.
    *!
    *! Initially the algorithm zeroes the map matrix, then a start point in the matrix to begin the drunken walk from (derived from the tileSet).
    *! After zeroing and getting the initial details from the tileSet the algorithm procedes to randomly determine the next direction to take 
    *! (as limited by the current tile specification) and randomly retrieves the next valid tile specification from the tileset. This process loops
    *! until the bounding condition is reached.
    *!
    *! \param maxDeviation The distance from the largest possible height or width. For example if one were to make a 6 tile high horizontal map and wanted 
    *!                     to keep the top 2 slots open this field would be set to 2. [defaults to 0]
    *!
    *! \param minDeviation The distance from the smallest possible height or width. For example if one were to make a 6 tile high horizontal map and wanted 
    *!                     to keep the bottom 2 slots open this field would be set to 2. [defaults to 0] 
    *! *Programmer's note: When selecting these deviations please ensure that you select a range conducive to your tileset and avoid making the bottom equivalent to your horizon.
    *!                     I'm still developing recovery for failed executions, so please tread lightly on this feature.
    */
    void generate2DMap(int maxDeviation=0, int minDeviation=0);     

    void generate2DMap(std::vector<std::vector<int> > * matrix, TileLayer layer,int maxDeviation, int minDeviation);

};

#endif