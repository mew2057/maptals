#include "TileFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

std::map<int,TileSpec> TileFactory::generateTileMap(std::string fileName){
    std::map<int, TileSpec> tileMap;

    std::ifstream tileFile=std::ifstream(fileName);

    int currentTile;
    
    istringstream stringconvertor;

    rapidxml::xml_document<> tileSet;

    rapidxml::xml_node<> *tileNode;
    rapidxml::xml_node<> *tileValueNode;
    
    vector<char> xmlDoc((istreambuf_iterator<char>(tileFile)), istreambuf_iterator<char>( ));  

    xmlDoc.push_back('\0');

    tileSet.parse<0>(&xmlDoc[0]);
       
    tileNode = tileSet.first_node("tileset");

    initializeTileSet(tileNode);

    tileNode=tileNode->first_node("tile");

    while(tileNode !=0)
    {
        istringstream(tileNode->first_attribute("id")->value()) >> currentTile;
        
        tileValueNode=tileNode->first_node();

        tileMap.insert(std::pair<int,TileSpec>(currentTile, appendCardinality(tileValueNode)));       

        tileNode=tileNode->next_sibling("tile");
    }

    return tileMap;

}

TileSpec TileFactory::appendCardinality(rapidxml::xml_node<> *tileNode){
        TileSpec specification;    
        string dir;
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
                istringstream(tempNode->value()) >> nextTile;
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

    string attributeName;

    while(currentAttribute != 0){
        attributeName=currentAttribute->name();

        if(attributeName=="horizon"){
            ;
        }

        currentAttribute=currentAttribute->next_attribute();
    }
    return newSet;
};
