/*!
* \author John Dunham
* \date 6-18-12
*
* This is my first attempt at a procedurally generated world. To say it is simple/ naive is an understatement, 
* but it illustrates the basic concepts of procedural generation. The algorithm is simple and lacks any form of
* intelligence in execution. The main benefit of this alogrithm lies in the guaranteed complete paths. For the
* random number generator I am simply using srand and rand. -John
*/
#ifndef MAPTALS_DRUNKEN_WALK_H
#define MAPTALS_DRUNKEN_WALK_H
#endif

#include "Maptal.h"
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
        * \brief The gettor for the matrix, ideal for reusing the map for respawn. 
        * \return The map matrix, performs no procedural operation to recieve the map.
        * XXX should this be in Maptal (probably).
        **/
        int** get2DMap();  
};
