#include "TileFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


TileSet TileFactory::generateTileSet(std::string fileName){
    std::map<int, TileSpec> tileMap;
    
    TileSpec currentSpec;
    std::ifstream tileFile=std::ifstream(fileName);

    int currentTile;

    int oid;
    
    std::istringstream stringconvertor;

    //! Start xml initialization.

    rapidxml::xml_document<> xmlTileSet;
    rapidxml::xml_node<> * rootNode, * tileNode, * objectNode;
    
    std::vector<char> xmlDoc((std::istreambuf_iterator<char>(tileFile)), std::istreambuf_iterator<char>( ));  

    xmlDoc.push_back('\0');

    xmlTileSet.parse<0>(&xmlDoc[0]);

    //!End XML Initialization.

    
    rootNode = xmlTileSet.first_node("tileset");

    objectNode=rootNode->first_node("objects");   

    
    TileSet tileSet = initializeTileSet(rootNode);
    
    objectNode=objectNode->first_node("object");

    while(objectNode != 0)
    {
        std::istringstream(objectNode->first_attribute("oid")->value()) >> oid;

        tileSet.addObjectType(oid, (std::string)objectNode->first_attribute("type")->value());

        objectNode=objectNode->next_sibling("object");
    }


    tileNode=rootNode->first_node("tile");

    while(tileNode !=0)
    {
        std::istringstream(tileNode->first_attribute("id")->value()) >> currentTile;

        if(tileNode->first_attribute("objectID"))
            std::istringstream(tileNode->first_attribute("objectID")->value()) >> oid;
        else
            oid=-1;

       
        currentSpec = appendCardinality(tileNode->first_node());   
        currentSpec.setOID(oid);

        tileSet.appendTileSpec(currentTile, currentSpec);

        tileNode=tileNode->next_sibling("tile");
    }

    return tileSet;

}

TileSpec TileFactory::appendCardinality(rapidxml::xml_node<> *tileNode){
        TileSpec specification;    
        std::string dir;
        int direction;
        int nextTile;

        rapidxml::xml_node<> *tempNode;

        while(tileNode !=0)
        {
            dir=tileNode->name();

            if(dir=="north")
                direction=north;
            else if(dir=="south")
                direction=south;
            else if(dir=="east")
                direction=east;
            else if(dir=="west")
                direction=west;

            tempNode=tileNode->first_node("nextTile");

            while(tempNode != 0)
            {
                std::istringstream(tempNode->value()) >> nextTile;
                specification.appendTile(direction,nextTile);
                tempNode=tempNode->next_sibling("nextTile");
            }

            tileNode=tileNode->next_sibling();
        }
        return specification;
}

TileSet TileFactory::initializeTileSet(const rapidxml::xml_node<> *headerNode){
    TileSet newSet;

    rapidxml::xml_attribute<char> *currentAttribute = headerNode->first_attribute();
    
    std::string attributeName;
    
    int attributeValue;

    while(currentAttribute != 0){
        attributeName=currentAttribute->name();
        
        std::istringstream(currentAttribute->value()) >> attributeValue;      
        
        if(attributeName=="horizon")
        {
            newSet.setHorizon(attributeValue);
        }
        else if (attributeName == "emptyTile")
        {
            newSet.setEmptyTile(attributeValue);
        }
        else if (attributeName == "startTile")
        {
            newSet.setStartTile(attributeValue);
        }
        else if (attributeName == "imagePath")
        {
            newSet.setImagePath(currentAttribute->value());
        }
        else if (attributeName == "tileWidth")
        {
            newSet.setTileWidth(attributeValue);
        }
        else if (attributeName == "tileHeight")
        {
            newSet.setTileHeight(attributeValue);
        }
        else if(attributeName =="imageWidth")
        {
            newSet.setImageHeight(attributeValue);    
        }
        else if(attributeName =="imageHeight")
        {
            newSet.setImageWidth(attributeValue);
        }

        currentAttribute=currentAttribute->next_attribute();
    }

    std::cout << newSet;

    return newSet;
};