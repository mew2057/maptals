#ifndef MAPTALS_MAPTAL_H
#define MAPTALS_MAPTAL_H

#include <cstdlib>
#include <time.h>
#include "TileSet.h"
#include "MapObject.h"

class Maptal{
public:
    /*
     *!  \brief An overloaded constructor that accepts all the possible inputs for Maptal configuration.
     *!  \param width The width of the map (in tiles). [defaults to 0]
     *!  \param height The height of the map (in tiles). [defaults to 0]
     *!  \param tSet The tile set to be used by the maptal operations. [defaults to the generic TileSet]
     */
    Maptal(int width = 0, int height = 0, TileSet tSet=TileSet());

    TileSet getTileSet();
    void setTileSet(TileSet tSet);
    void setHeight(int height);
    void setWidth(int width);
    void toMappy();
    void toTMX();


    std::string base64Encode(std::vector<std::vector<int>> matrix, int emptyTile);

    /*!
     * \brief The gettor for the matrix, ideal for reusing the map for respawn. 
     * \return The map matrix, performs no procedural operation to recieve the map.
     */
    std::vector<std::vector<int>> get2DMap();  
protected:
    void zeroMatrix();
    void resizeMatrix();


    int height;
    int width;
    TileSet tileSet;

    /*
     *! \brief A matrix with dimensions height by width or matrix[height][width].
     */
    std::vector<std::vector<int>> matrix;

    std::vector<std::vector<int>> oid_matrix;

private:
    /*
     *! \brief Appends objects within an object vector as children to the root node supplied in the function call.
     *! \param objects A vector containing the objects to serialize.
     *! \param tileSet
     *! \param rootNodePrt
     *! \param tmx_doc
     */
    void objectsFromVector(std::vector<MapObject> *objects, 
                            TileSet *tileSet,
                            rapidxml::xml_node<char> * rootNodePtr, 
                            rapidxml::xml_document<char> * tmx_doc);

    std::vector<MapObject> generateObjectVector(std::vector<std::vector<int>> matrix,TileSet tiles);
};

#endif
