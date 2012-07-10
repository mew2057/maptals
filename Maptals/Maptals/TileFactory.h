/*!
* \author John Dunham
* \date 7-6-12
*
* A factory for deserializing and creating tile specification maps to be used in Maptal algorithms.
* A properly formatted data file example follows.
*
* General Template:
* TileID | direction{ TileID, TileID, TileID } direction{...} ... ;
*
* Sample:
* 0| 0{1,2} 1{0,2} 2{0} 3{0,1,2};
* 1| 0{0,1} 1{2} 3{0,1};
* 2| 0{1} 1{2} 2{2,0} 3{0,1,2};
*
* Warning:
* If a tile doesn't have a tile ID associated with a direction other than its own, that ID can potentially dominate the tile maps!
*/
#ifndef MAPTALS_TILE_FACTORY_H
#define MAPTALS_TILE_FACTORY_H

#include <map>
#include "TileSpec.h"
#include <string>



class TileFactory{
public:
    /*!
    * \brief A deserializer that converts the file contents into a map with the tile value as the key and the tileSpec as the value.
    * \param fileName The name of the file to be converted.
    * \return A map with the tile value as the key and the tileSpec as the value.
    */
    static std::map<int,TileSpec> generateTileMap(std::string fileName);

private:
    /*!
    * \brief A function that generates a TileSpec object from a serialized tileString.
    * \param tileString The line from the serialized file to be made into the tileSpec object (will contain cardinal data).
    * \return The TileSpec generated from the given string.
    */
    static TileSpec TileFactory::appendCardinality(std::string tileString);
};

#endif