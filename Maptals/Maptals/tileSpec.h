/*!
* \author John Dunham
* \date 7-1-12
* 
* \brief This is a class designed to specify a set of rules for a tile in a tile based game, indicating valid tiles that follow it in the 4 cardinal directions.
* This class should not be handled by any user of this library.
*
*/

#ifndef MAPTALS_TILE_SPEC_H
#define MAPTALS_TILE_SPEC_H

#define north 0
#define east 1
#define south 2
#define west 3


#include <cstdlib>
#include <time.h>
#include <vector>
#include <iostream>


// TODO
// Variable tile rarity.
class TileSpec {
 public:    
     /*
      *! \brief The constructor. 
      *! \param oid The object identifier associated with the tile. defaults to -1.
      */
     TileSpec(int oid=-1);

     /*
      *! \brief randomly selects the next tile from the supplied direction.
      *! \param direction The direction the next tile should be (N,E,S,W).
      *! \return The tileID of the next tile. If not found INT_MIN.
      */
     int getNextTile(int direction);

     /*
      *! \brief randomly selects the next tile from the supplied direction.
      *! \param direction The direction the next tile should be (N,E,S,W).
      *! \param seed reseeds the random number generator (be aware this reseeds each time).
      *! \return The tileID of the next tile. If not found INT_MIN.
      */
     int getNextTile(int direction, unsigned int seed);

     /*
      *! \brief Adds a tile to the vector for the supplied direction.
      *! \param direction The direction index to add to.
      *! \param tile The tileid of the tile to be added.
      */
     void appendTile(int direction, int tile);

     /*
      *! \brief Randomly gets the next direction from available directions.
      *! \return The new direction if any are present, INT_MIN if none are present.
      */
     int getNextDirection();

     /*
      *! \brief The gettor for the object identifier.
      *! \return The value of the oid field.
      */
     int getOID();

     /*
      *! \brief The oid settor.
      *! \param objectID The new oid.
      */
     void setOID(int objectID);

     /*
      *! \brief A convience function used to check vector sizes.
      */
     friend std::ostream& operator<< ( std::ostream& outputStream, TileSpec& specification );
private:
    
    /*
     *! \brief Holds the valid adjacent tiles.
     */
    std::vector<std::vector<int>> succeedingTiles;
    
    /*
     *! \brief A vector of directions that may be easily selected at random.
     */
    std::vector<int> validDirections;
    
    /*
     *! \brief The Object IDentifier for the tile.
     */
    int oid;
};

#endif