/*!
* \author John Dunham
* \date 7-28-12
* 
* \brief The base class for all Maptal map generators. Ensures consistent map generation, allowing the end user to change map generation as simply as possible.
* 
*/
#ifndef MAPTALS_MAPTAL_H
#define MAPTALS_MAPTAL_H

#include <vector>
#include <time.h>
#include "TileSet.h"
#include "MapObject.h"

class Maptal{
public:
    /*
     *! \brief An overloaded constructor that accepts all the possible inputs for Maptal configuration.
     *! \param width The width of the map (in tiles). [defaults to 0]
     *! \param height The height of the map (in tiles). [defaults to 0]
     *! \param tSet The tile set to be used by the maptal operations. [defaults to the generic TileSet]
     */
    Maptal(int width = 0, int height = 0, TileSet tSet=TileSet());

    /*
     *! \brief The gettor for the tileSet field.
     *! \return the tileSet field.
     */
    TileSet getTileSet();

    /*
     *! \brief A settor for the tileSet referenced by the Maptal map/matrix.
     *! \param tSet The new value of the tileSet field.
     */
    void setTileSet(TileSet tSet);

    /*
     *! \brief A settor for the height of the Maptal map/matrix.
     *! \param height The new value of the height field.
     */
    void setHeight(int height);

    /*
     *! \brief A settor for the width of the Maptal map.
     *! \param width The new value of the width field.
     */
    void setWidth(int width);

    /*
     *! \brief generates and writes the 2DMap to a tmx file.
     *! \param fileDestination The path/filename of the tmx file to be output.
     */
    void toTMX(const char * fileDestination);


    /*
     *! \brief Generates a byte array of the supplied vector which is them compressed using the zlib library and encoded to a base64 encoded string.
     *! \param matrix The tileID matrix to encode, assumed to be rectangular.
     *! \param falseTile The tile that splits so called "real tiles" and false tiles (oid based tiles).
     *! \return The base64 encoded string of the compressed map data.
     */
    std::string base64Encode(std::vector<std::vector<int> > matrix, int falseTile);

    /*
     *! \brief Generate a 2D map utilizing the Maptal supplied TileSet with the world building algorithm specified by sub classes.
     *!
     *! \param maxDeviation The distance from the largest possible height or width. For example if one were to make a 6 tile high horizontal map and wanted 
     *!                     to keep the top 2 slots open this field would be set to 2. [defaults to 0]
     *!
     *! \param minDeviation The distance from the smallest possible height or width. For example if one were to make a 6 tile high horizontal map and wanted 
     *!                     to keep the bottom 2 slots open this field would be set to 2. [defaults to 0] 
     *!
     *! *Programmer's note: When selecting these deviations please ensure that you select a range conducive to your tileset and avoid making the bottom equivalent to your horizon.
     *!                     I'm still developing recovery for failed executions, so please tread lightly on this feature.
     */
    virtual void generate2DMap(int maxDeviation=0, int minDeviation=0)=0;        

    /*!
     * \brief The gettor for the matrix, ideal for reusing the map for respawn. 
     * \return The map matrix, performs no procedural operation to recieve the map.
     */
    std::vector<std::vector<int> > get2DMap();  
protected:

    static int failCount; 
    
    /*
     *! \brief The height of the map in tiles.
     */
    int height;

    /*
     *! \brief The width of the map in tiles.
     */
    int width;

    /*
     *! \brief A tile set containing information vital to creating maps.
     */
    TileSet tileSet;

    /*
     *! \brief A matrix with dimensions height by width or matrix[height][width], containing a mapping of tileIDs.
     */
    std::vector<std::vector<int> > matrix;

    /*
     *! \brief Zeroes the matrices associated with the Maptal object with the "empty tile" value of the tileSet.
     */
    void zeroMatrix();
    
    /*
     *! \brief Resizes the matrices associated with the Maptal object to its height and width fields.
     */
    void resizeMatrix();
private:
    /*
     *! \brief Appends objects within an object vector as children to the root node supplied in the function call. [For toTMX]
     *! \param objects A vector containing the objects to serialize.
     *! \param tileSet Contains the object mapping and tile width and height (used in translating the object dimensions to tmx format.
     *! \param rootNodePrt The parent node for objects in the XML (TMX) document. [should be objectGroup]
     *! \param tmx_doc The XML document, used for string and node allocation.
     */
    void objectsFromVector(std::vector<MapObject> objects, 
                            TileSet *tileSet,
                            rapidxml::xml_node<char> * rootNodePtr, 
                            rapidxml::xml_document<char> * tmx_doc);

    /*
     *! \brief Generates a vector of MapObjects based on the supplied tileID matrix that references the tileMap in the supplied TileSet. [For toTMX]
     *! \param matrix A vector of a vector that holds a matrix of tileIDs
     *! \param tiles Contains the tile specifications that are referenced by the contents of the matrix.
     *! \return A vector containing MapObjects that contain the oid, start x and y and the end x and y.
     */
    std::vector<MapObject> generateObjectVector(std::vector<std::vector<int> > matrix,TileSet tiles);
};

#endif
