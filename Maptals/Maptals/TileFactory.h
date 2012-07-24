/*!
* \author John Dunham
* \date 7-18-12
*
* The following factory generates a tile map from a user supplied xml file, the xml file currently follows the following standards:
* 
* <tileset> is the root directory in the DOM, this should contain the following attributes:
*
* <tile> is the root of a tile definition, the following attributes are valid:
*   id:<int> The tileid of the tile (must be an integer)
*
* <north>,<south>,<east>,<west> cardinality tags defined within a tile tree.
*
* <nextTile> An array element between the cardinality tags, should contain the id of a valid tile as the value.
* Warning:
* If a tile doesn't have a tile ID associated with a direction other than its own, that ID can potentially dominate the tile maps!
*/
#ifndef MAPTALS_TILE_FACTORY_H
#define MAPTALS_TILE_FACTORY_H

#include "TileSpec.h"
#include "TileSet.h"
#include "rapidxml-1.13\rapidxml.hpp"
#include <string>
#include <map>

class TileFactory
{
public:
    /*!
    * \brief A deserializer that converts the file contents into a map with the tile value as the key and the tileSpec as the value.
    * \param fileName The name of the file to be converted.
    * \return The tileset generated from the file.
    */
    static TileSet generateTileSet(std::string fileName);

private:
    /*!
    * \brief A function that generates a TileSpec object from an xml root node.
    * \param tileNode The root of the xml tree for a particular tileNode.
    * \return The TileSpec generated from the root tileNode.
    */
    static TileSpec appendCardinality(rapidxml::xml_node<> *tileNode);

    
    /*!
    * \brief 
    * \param
    * \return
    */
    static TileSet initializeTileSet(const rapidxml::xml_node<> *headerNode);
};

#endif