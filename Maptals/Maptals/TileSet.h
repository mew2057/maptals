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
#include "TileLayer.h"

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
     
    int getNumLayers();

    TileLayer getLayer(int lid);

    
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
     *! \brief Adds the given oid and object type pair to the object map.
     *! \param oid The object identifier.
     *! \param objectType The user specified name for the oid.
     *! \param group The user specified group for the oid.
     */
    void addObjectType(int oid, std::string objectType, std::string group="");

    void addTileLayer(int lid, TileLayer layer);

    TileSet();   

private:  
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
     *! \brief Specifies whether or not the map should have a horizontal bulding preference. [defaults to true]
     */
    bool horizontal;

    /*
     *! \brief A map of the objects associated with the TileSet.
     */
    std::map<int, ObjectType> objectMap;

    /*
     *! \brief A collection of layer ids and their associated layers.
     */   
    std::map<int, TileLayer> layers;

};


#endif // !MAPTALS_TILE_SET_H
