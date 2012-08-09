#include "TileFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define TILE_FACTORY_HORIZON "horizon"
#define TILE_FACTORY_HORIZONTAL "horizontal"
#define TILE_FACTORY_EMPTY_TILE "emptyTile"
#define TILE_FACTORY_START_TILE "startTile"
#define TILE_FACTORY_IMAGE_PATH "imagePath"
#define TILE_FACTORY_TILE_WIDTH "tileWidth"
#define TILE_FACTORY_TILE_HEIGHT "tileHeight"
#define TILE_FACTORY_IMAGE_HEIGHT "imageHeight"
#define TILE_FACTORY_IMAGE_WIDTH "imageWidth"
#define TILE_FACTORY_FALSE_TILE "falseTile"
#define TILE_FACTORY_SKY_ID "skyid"
#define TILE_FACTORY_GROUND_ID "groundid"
#define TILE_FACTORY_LAYER_NAME "name"


TileSet TileFactory::generateTileSet(const char * fileName){
    
    //! Placeholders.
    int id;
    std::string objectGroup="";

    //! The stream that reads the xml file.
    std::ifstream tileFile;
    tileFile.open(fileName);

    //! Start xml initialization.
    //! The XML document that the parse operations are exeuted on.
    rapidxml::xml_document<> xmlTileSet;

    //! Multiple Nodes allows for the preservation of all levels and allows for fast access 
    rapidxml::xml_node<> * rootNode, *tileNode,* objectNode, *parentNode;
    
    //Creates a null terminated vector of the xml document that is then loaded into xmlDoc.
    std::vector<char> xmlDoc((std::istreambuf_iterator<char>(tileFile)), std::istreambuf_iterator<char>( ));  

    xmlDoc.push_back('\0');

    xmlTileSet.parse<0>(&xmlDoc[0]);
    //!End XML Initialization.

    //! Initialize the root node.
    rootNode = xmlTileSet.first_node("tileset");

    objectNode=rootNode->first_node("objects");   
        
    TileSet tileSet = initializeTileSet(rootNode);
    
    //! Begin initialization of map of tileset objects.
    parentNode=objectNode->first_node("objectgroup");

    while(parentNode!=0)
    {
        objectGroup = parentNode->first_attribute("name")->value();

        objectNode=parentNode->first_node("object");
                
        while(objectNode != 0)
        {
            std::istringstream(objectNode->first_attribute("oid")->value()) >> id;

            tileSet.addObjectType(id, (std::string)objectNode->first_attribute("type")->value(),objectGroup);

            objectNode=objectNode->next_sibling("object");
        }

        parentNode=parentNode->next_sibling("objectgroup");
    }
    //! End initialization of map of tileset objects.

    //! Begin initialization of TileSpec Map.
    tileNode=rootNode->first_node("layer");
    id=0;

    while(tileNode !=0)
    {
        tileSet.addTileLayer(id, makeTileLayer(tileNode));

        //! Advance
        tileNode=tileNode->next_sibling("layer");
        id++;
    }
    //! End initialization of TileSpec Map.


    //! Closes the fstream.
    tileFile.close();

    return tileSet;

}

TileSpec TileFactory::appendCardinality(rapidxml::xml_node<> *tileNode){
    //! The TileSpec object initialized by this method.
    TileSpec specification;    
    
    //! The string version of the direction.
    std::string dir;

    //! variables that keep track of vital data related to tile constraints.
    int direction, nextTile;

    //! A place holder node that prevents invalid access in the xml parser. 
    rapidxml::xml_node<> *tempNode;

    while(tileNode !=0)
    {
        //! Gets the direction from the xml and converts it to an integer.
        dir=tileNode->name();

        if(dir=="north")
        {
            direction=north;
        }
        else if(dir=="south")
        {
            direction=south;
        }
        else if(dir=="east")
        {
            direction=east;
        }
        else if(dir=="west")
        {
            direction=west;
        }

        //! Load and check for a nexTile node then iterate over the present nextTile nodes.
        tempNode=tileNode->first_node("nextTile");

        while(tempNode != 0)
        {
            //! Convert, append then advance.
            std::istringstream(tempNode->value()) >> nextTile;
            specification.appendTile(direction,nextTile);
            tempNode=tempNode->next_sibling("nextTile");
        }

        //! Gets the next cardinality node.
        tileNode=tileNode->next_sibling();
    }
    
    return specification;
}

TileLayer TileFactory::makeTileLayer(const rapidxml::xml_node<> *headerNode)
{
    //! Some variables that keep track of data throughout the iteration.
    rapidxml::xml_attribute<char> *currentAttribute = headerNode->first_attribute();   
    rapidxml::xml_node<> * iterableNode;
    std::string attributeName;    
    int attributeValue, currentTile, oid;
    TileSpec currentSpec;
    TileLayer currentLayer;

    while(currentAttribute != 0){
        //! Get the attribute name.
        attributeName=currentAttribute->name();
        
        //! Converts the current value to an int (does nothing if string).
        std::istringstream(currentAttribute->value()) >> attributeValue;  

        if (attributeName == TILE_FACTORY_EMPTY_TILE)
        {
           currentLayer.setEmptyTile(attributeValue);
        }
        else if (attributeName == TILE_FACTORY_START_TILE)
        {
           currentLayer.setStartTile(attributeValue);
        }
	    else if (attributeName == TILE_FACTORY_LAYER_NAME)
        {
           currentLayer.setLayerName(currentAttribute->value());
        }        
	    else if(attributeName == TILE_FACTORY_FALSE_TILE)
        {
           currentLayer.setFalseTile(attributeValue);
        }

        currentAttribute=currentAttribute->next_attribute();
    }
    
    //! Begin initialization of TileSpec Map.
    iterableNode=headerNode->first_node("tile");

    while(iterableNode !=0)
    {
        //! Get tile id.
        std::istringstream(iterableNode->first_attribute("id")->value()) >> currentTile;

        //! Get oid.
        if(iterableNode->first_attribute("oid"))
        {
            std::istringstream(iterableNode->first_attribute("oid")->value()) >> oid;
        }
        else
        {
            oid=-1;
        }
       
        //! Generate the TileSpec, add the oid and append the TileSpec and tileID to the tileSet.
        currentSpec = appendCardinality(iterableNode->first_node());   
        currentSpec.setOID(oid);

        currentLayer.appendTileSpec(currentTile, currentSpec);

        //! Advance
        iterableNode=iterableNode->next_sibling("tile");
    }
    //! End initialization of TileSpec Map.
    return currentLayer;
}

TileSet TileFactory::initializeTileSet(const rapidxml::xml_node<> *headerNode){
    //! The TileSet the will be loaded with the attributes of the supplied nodes.
    TileSet newSet;
    
    //! Some variables that keep track of data throughout the iteration.
    rapidxml::xml_attribute<char> *currentAttribute = headerNode->first_attribute();    
    std::string attributeName;    
    int attributeValue;

    while(currentAttribute != 0){
        //! Get the attribute name.
        attributeName=currentAttribute->name();
        
        //! Converts the current value to an int (does nothing if string).
        std::istringstream(currentAttribute->value()) >> attributeValue;      
        
        //! While a switch may be prefered here, this is the simplest manner to implement this.
        if(attributeName == TILE_FACTORY_HORIZON)
        {
            newSet.setHorizon(attributeValue);
        }
        else if(attributeName == TILE_FACTORY_HORIZONTAL)
        {
            newSet.setHorizontal((bool)attributeValue);
        }
        else if (attributeName == TILE_FACTORY_IMAGE_PATH)
        {
            newSet.setImagePath(currentAttribute->value());
        }
        else if (attributeName == TILE_FACTORY_TILE_WIDTH)
        {
            newSet.setTileWidth(attributeValue);
        }
        else if (attributeName == TILE_FACTORY_TILE_HEIGHT)
        {
            newSet.setTileHeight(attributeValue);
        }
        else if(attributeName == TILE_FACTORY_IMAGE_HEIGHT)
        {
            newSet.setImageHeight(attributeValue);    
        }
        else if(attributeName == TILE_FACTORY_IMAGE_WIDTH)
        {
            newSet.setImageWidth(attributeValue);
        }
        else if(attributeName == TILE_FACTORY_SKY_ID)
        {
            newSet.setSkyID(attributeValue);    
        }
        else if(attributeName == TILE_FACTORY_GROUND_ID)
        {
            newSet.setGroundID(attributeValue);
        }         
    
        currentAttribute=currentAttribute->next_attribute();
    }

    return newSet;
};