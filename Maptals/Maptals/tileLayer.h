/*!
* \author John Dunham
* \date 8-9-12
*
* \brief A class designed address the multi layer issue.
*/
#ifndef MAPTALS_TILE_LAYER_H
#define MAPTALS_TILE_LAYER_H
#include <string>
#include <map>
#include "TileSpec.h"


class TileLayer
{
public:
    TileLayer();
    
    /*
     *! \brief A gettor for the TileSpec associated with a given tile id.
     *! \param tileID The tile identifier for a specific tile specification.
     *! \return The TileSpec if the tileID was found, 0 if not.
     */
    TileSpec * getTileID(int tileID);

    /*
     *! \brief The so called empty tile.
     *! \return The emptyTile field.
     */
    int getEmptyTile();

    /*
     *! \brief The tile that the map should begin with.
     *! \return The startTile field.
     */
    int getStartTile();
    
    /*
     *! \brief The false tile that prevents object overwrite.
     *! \return The falseTile field.
     */
    int getFalseTile();

    // XXX Should this get removed?
    /*
     *! \brief Retrieves the tile map associated with the TileSet.
     *! \return A Mapping of the tile ids to associated TileSpec objects.
     */
    std::map<int,TileSpec> getTileMap();

    std::string getLayerName();
    
    void setLayerName(std::string _layerName);

    /*
     *! \brief A settor for the emptyTile field.
     *! \param empty The new emptyTile.
     */
    void setEmptyTile(int empty);

    /*
     *! \brief A settor for the startTile field.
     *! \param start The new startTile.
     */
    void setStartTile(int start);
    
    /*
     *! \brief  A settor for the falseTile field.
     *! \param tile The new falseTile field.
     */
    void setFalseTile(int tile);

     /*
     *! \brief Adds the given tileID TileSpec pair to the tileMap.
     *! \param tileID The ID of the supplied TileSpec.
     *! \param specification The specification of one tile.
     */
    void appendTileSpec(int tileID, TileSpec specification);
    

private:
    /*
     *! \brief A "fake" tile that's used to define objects, but prevent them from being overwritten by new tiles. 
     *! All tiles with a tileID greater or equal to than this tile are considered "fake" and replaced with this tileID.
     */
    int falseTile;

    /*
     *! \brief The so called empty tile.
     */
    int emptyTile;
    
    /*
     *! \brief The tile that the map should begin with.
     */
    int startTile;

    std::string layerName;

    /*
     *! \brief The tilemap containing tile rules for use with map generators.
     */
    std::map<int, TileSpec> tileMap;

};

#endif