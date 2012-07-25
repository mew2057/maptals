#ifndef MAPTALS_TILE_SET_H
#define MAPTALS_TILE_SET_H

#include "TileSpec.h"
#include <string>
#include <map>
#include "rapidxml-1.13\rapidxml.hpp"
class TileSet
{
public:
    //! \brief The width of a single tile (pixels).
    //! \return The tileWidth field.
    int getTileWidth();

    void setTileWidth(int width);

    //! \brief The height of a single tile (pixels).
    //! \return The tileHeight field.
    int getTileHeight();

    void setTileHeight(int height);

    //! \brief The absolute path of the tileset image.
    //! \return The imagePath field.
    std::string getImagePath();

    void setImagePath(std::string path);
    
    //! \brief The so called empty tile.
    //! \return The emptyTile field.
    int getEmptyTile();

    void setEmptyTile(int empty);

    //! \brief The tile that the map should begin with.
    //! \return The startTile field.
    int getStartTile();

    void setStartTile(int start);

    //! \brief The division of the map (y value in tiles for the starting location).
    //! \return The horizon field.
    int getHorizon();
    
    void setHorizon(int horiz);

    int getImageHeight();
    
    void setImageHeight(int height);

    int getImageWidth();
    
    void setImageWidth(int width);

    void appendTileSpec(int tileID, TileSpec specification);

    std::map<int,TileSpec> getTileMap();

    TileSpec * getTileID(int tileID);

    std::string getObjectType(int oid);

    void addObjectType(int oid, std::string objectType);

    TileSet();
    ~TileSet();

    friend std::ostream& operator<< ( std::ostream& outputStream, TileSet& set );
    

private:
    //! The tilemap containing tile rules for use with map generators.
    std::map<int, TileSpec> tileMap;

    //! The width of a single tile (pixels).
    int tileWidth;

    //! The height of a single tile (pixels).
    int tileHeight;

    //! The absolute path of the tileset image.
    std::string imagePath;
    
    //! The so called empty tile.
    int emptyTile;

    //! The tile that the map should begin with.
    int startTile;
    
    //! The division of the map (y value in tiles for the starting location).
    int horizon;

    //! The height of the tileset image in pixels.
    int imageHeight;

    //! The width of the tileset image in pixels.
    int imageWidth;

    std::map<int, std::string> objectMap;

    
};

#endif // !MAPTALS_TILE_SET_H
