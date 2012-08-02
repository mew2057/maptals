/*!
* \author John Dunham
* \date 7-28-12
*
* \brief A class designed to contain all data that could possibly be relevant to one discrete tileset.
*/
#ifndef MAPTALS_TILE_SET_H
#define MAPTALS_TILE_SET_H

#include "TileSpec.h"
#include <string>
#include <map>
#include "rapidxml/rapidxml.hpp"

struct ObjectType
{
    std::string type;
    std::string group;
};

class TileSet
{
public:
    /*
     *! \brief The width of a single tile (pixels).
     *! \return The tileWidth field.
     */
    int getTileWidth();  

    /*
     *! \brief The height of a single tile (pixels).
     *! \return The tileHeight field.
     */
    int getTileHeight();

    /*
     *! \brief The absolute path of the tileset image.
     *! \return The imagePath field.
     */
    std::string getImagePath();    
    
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
     *! \brief The division of the map (y value in tiles for the starting location).
     *! \return The horizon field.
     */
    int getHorizon();

    /*
     *! \brief The height of the source image (pixels).
     *! \return The imageHeight field.
     */
    int getImageHeight();
    
    /*
     *! \brief The width of the source image (pixels).
     *! \return The widthHeight field.
     */
    int getImageWidth();

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
        
    /*
     *! \brief A gettor for the TileSpec associated with a given tile id.
     *! \param tileID The tile identifier for a specific tile specification.
     *! \return The TileSpec if the tileID was found, 0 if not.
     */
    TileSpec * getTileID(int tileID);
    
    /*
     *! \brief A gettor for the Map Object associated with a given oid.
     *! \param oid The Object IDentifier for a specific MapObject.
     *! \return The object type if found, a new ObjectType if not.
     */
    ObjectType getObjectType(int oid);
    
    /*
     *! \brief Return whether this tileset is to be used with horizontal or vertical maps.
     *! \return True if the map should be horizontal false if vertical.
     */
    bool isHorizontal();

    std::string getLayerName();
    
    void setLayerName(std::string _layerName);
        /*
     *! \brief The settor for the horizontal field. True indicates a horizontally oriented tileset.
     *! \param _horizontal The tileset preference for map generation.
     */
    void setHorizontal(bool _horizontal);

    /*
     *! \brief A settor for the tileWidth field.
     *! \param width The new tileWidth.
     */
    void setTileWidth(int width);

    /*
     *! \brief A settor for the imagePath field.
     *! \param path The new imagePath.
     */
    void setImagePath(std::string path);

    /*
     *! \brief A settor for the tileHeight field.
     *! \param height The new tileHeight.
     */
    void setTileHeight(int height);

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
     *! \brief A settor for the horizon field.
     *! \param horiz The new horizon.
     */
    void setHorizon(int horiz);  

    /*
     *! \brief A settor for the imageWidth field.
     *! \param width The new imageWidth.
     */
    void setImageWidth(int width);

     /*
     *! \brief A settor for the imageHeight field.
     *! \param height The new imageHeight.
     */
    void setImageHeight(int height);

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
    
    /*
     *! \brief Adds the given oid and object type pair to the object map.
     *! \param oid The object identifier.
     *! \param objectType The user specified name for the oid.
     *! \param group The user specified group for the oid.
     */
    void addObjectType(int oid, std::string objectType, std::string group="");

    TileSet();   

private:
    /*
     *! \brief The tilemap containing tile rules for use with map generators.
     */
    std::map<int, TileSpec> tileMap;
    
    /*
     *! \brief The width of a single tile (pixels).
     */
    int tileWidth;

    /*
     *! \brief The height of a single tile (pixels).
     */
    int tileHeight;
    
    /*
     *! \brief The absolute path of the tileset image.
     */
    std::string imagePath;
    
    /*
     *! \brief The so called empty tile.
     */
    int emptyTile;
    
    /*
     *! \brief The tile that the map should begin with.
     */
    int startTile;
    
    /*
     *! \brief The division of the map (y value in tiles for the starting location).
     */
    int horizon;

    /*
     *! \brief The height of the tileset image in pixels.
     */
    int imageHeight;

    /*
     *! \brief The width of the tileset image in pixels.
     */
    int imageWidth;

    /*
     *! \brief A "fake" tile that's used to define objects, but prevent them from being overwritten by new tiles. 
     *! All tiles with a tileID greater or equal to than this tile are considered "fake" and replaced with this tileID.
     */
    int falseTile;

    /*
     *! \brief Specifies whether or not the map should have a horizontal bulding preference. [defaults to true]
     */
    bool horizontal;


    /*
     *! \brief A map of the objects associated with the TileSet.
     */
    std::map<int, ObjectType> objectMap;

    std::string layerName;
    
};


#endif // !MAPTALS_TILE_SET_H
