#include "TileFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


TileSet TileFactory::generateTileSet(std::string fileName){
    std::map<int, TileSpec> tileMap;
    
    std::ifstream tileFile=std::ifstream(fileName);

    int currentTile;
    
    std::istringstream stringconvertor;

    //! Start xml initialization.

    rapidxml::xml_document<> xmlTileSet;
    rapidxml::xml_node<> * tileNode, * tileValueNode;
    
    std::vector<char> xmlDoc((std::istreambuf_iterator<char>(tileFile)), std::istreambuf_iterator<char>( ));  

    xmlDoc.push_back('\0');

    xmlTileSet.parse<0>(&xmlDoc[0]);
       
    tileNode = xmlTileSet.first_node("tileset");

    //!End XML Initialization.

    TileSet tileSet = initializeTileSet(tileNode);

    tileNode=tileNode->first_node("tile");

    while(tileNode !=0)
    {
        std::istringstream(tileNode->first_attribute("id")->value()) >> currentTile;
        
        tileValueNode=tileNode->first_node();

        tileSet.appendTileSpec(currentTile, appendCardinality(tileValueNode));

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