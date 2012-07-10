/*!
* \author John Dunham
* \date 6-18-12
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
*/
#ifndef MAPTALS_DRUNKEN_WALK_H
#define MAPTALS_DRUNKEN_WALK_H

#include "Maptal.h"
#include <map>
#include "TileSpec.h"

class DrunkenWalk: public Maptal{
    public:
        /*!
        * \brief This is the default constructor for which the Maptals constructor suffices.
        *
        **/
        DrunkenWalk():Maptal(){}

        /*!
        * \brief This is the Overloaded constructor, it takes in the base elements of a drunken walk map generation.
        *
        * \param width The width of the map to be generated.
        * \param height The height of the map to be generated.
        * \param minValue The minimum id for drunken walk generation.
        * \param maxValue The maximum id for drunken walk generation.
        **/
        DrunkenWalk(int width, int height, int minValue, int maxValue):Maptal(width, height, minValue, maxValue){}

        /*!
        * \brief This generation takes roughly O(n) to O(n^2) time to execute (I haven't done full calculations at the time of this write up 6-18-12).
        *
        * Initially the algorithm zeroes the map matrix, then randomly assigns a start point in the matrix to begin the drunken walk from.
        * The drunken walk itself in this implementation is rather naive: a while loop guarded by the number of steps supplied in the function call
        * containing an invocation of the rand() function seeded by time(NULL). The results of the rand call are then converted to range from 0-3, with each 
        * number in the range representing a cardinal direction (0-N, 1-E, 2-S, 3-W). The algorithm then takes a "step" in that direction (adding or subtracting 1
        * from the x or y) if the direction is valid and empty a newvalue in the id range is randomly assigned and the step counter is incremented. If the step is 
        * out of bounds or the cell is occupied the state of the map and number of steps remain unchanged.
        *
        * John's aside:
        * The main strength of this implementation lies in the simplicity of implementation and a guaranteed connected path, making it excellent for "rouge-like" games.
        * As it stands this algorithm is useless for most platformers, but a second pass may be beneficial.
        * 
        * \param numSteps The number of steps the algorithm should take for the map to be considered "complete".
        * \return A double pointer to the now populated map matrix.        
        **/
        int** generate2DMap(int numSteps);        
        
        /*!
        * \brief A variation on the basic drunken walk that adds a variable to prevent the walk from doubling back to the drunken walk.
        *
        * This modification is born of the cluttered appearance of the base drunken walk algorithm. As such new techniques are being employed in attempting to
        * find more aesthetic variations in the maps that would be more interesting to traverse.
        *
        * John's aside (6-21-12):
        * The addition of the last direction variable appears to increase the likelihood of winding paths considerably versus the naive aproach,
        * granted this is possible in both variations. To improve the occurance of winding paths in the map I added a randomized selection of a repeat of the 
        * last direction or a newly random direction. I found that this increases the straight path rate considerably. Still the maps are too linear for a
        * good map and some variations need to be added. Perhaps this is a good time to move onto the next map generation algorithm, using some of the knowledge 
        * acquired from this experience. However, this is not the end of my exploration and modification of this algorithm as there are still more modifications that
        * may be done to improve the produced maps.
        *
        * 
        *
        * \param numSteps The number of steps the algorithm should take for the map to be considered "complete".
        * \return A double pointer to the now populated map matrix.       
        */
        int** walkPathNoRetrace(int numSteps);

        /**!
        * \brief Uses the tileMap specified by the user to generate a map with the drunken walk algorithm.
        * 
        * \param numSteps The number of steps the algorithm should take for the map to be considered "complete".
        * \param tileMap The Map of the tile value and TileSpec that the map will be based on.
        * \return A double pointer to the now populated map matrix.       
        */
        int** walkPathWithMap(int numSteps, const std::map<int,TileSpec> tileMap);

        /*!
        * \brief The gettor for the matrix, ideal for reusing the map for respawn. 
        * \return The map matrix, performs no procedural operation to recieve the map.
        * XXX should this be in Maptal (probably).
        **/
        int** get2DMap();  
};

#endif