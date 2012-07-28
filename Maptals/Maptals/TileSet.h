#ifndef MAPTALS_TILE_SET_H
#define MAPTALS_TILE_SET_H

#include "TileSpec.h"
#include <string>
#include <map>
#include "rapidxml-1.13\rapidxml.hpp"
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

    // XXX Should this get removed?
    /*
     *! \brief Retrieves the tile map associated with the TileSet.
     *! \return A Mapping of the tile ids to associated TileSpec objects.
     */
    std::map<int,TileSpec> getTileMap();
        
    /*
     *! \brief A gettor for the TileSpec associated with a given tile id.
     *! \param tileID The tile identifier for a specific tile specification.
     *! \return The TileSpec if the tileID was found, nullptr if not.
     */
    TileSpec * getTileID(int tileID);
    
    /*
     *! \brief A gettor for the Map Object associated with a given oid.
     *! \param oid The Object IDentifier for a specific MapObject.
     *! \return The object type if found, an empty string if not.
     */
    std::string getObjectType(int oid);

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
     *! \brief Adds the given tileID TileSpec pair to the tileMap.
     *! \param tileID The ID of the supplied TileSpec.
     *! \param specification The specification of one tile.
     */
    void appendTileSpec(int tileID, TileSpec specification);
    
    /*
     *! \brief Adds the given oid and object type pair to the object map.
     *! \param oid The object identifier.
     *! \param objectType The user specified name for the oid.
     */
    void addObjectType(int oid, std::string objectType);

    TileSet();

    //! A function for ostream output convenience in debugging.
    friend std::ostream& operator<< ( std::ostream& outputStream, TileSet& set );
    

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
     *! \briefThe width of the tileset image in pixels.
     */
    int imageWidth;

    /*
     *! \brief A map of the objects associated with the TileSet.
     */
    std::map<int, std::string> objectMap;

    
};

#endif // !MAPTALS_TILE_SET_H
