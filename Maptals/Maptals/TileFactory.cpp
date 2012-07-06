#include "TileFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

#define TILE_SEPARATOR '|'
#define SUCCESSOR_TILE_START '{'
#define SUCCESSOR_TILE_END '}'
#define TILE_DELIMITER ','
#define LINE_SEPARTOR ';'


std::map<int,TileSpec> TileFactory::generateTileMap(std::string fileName){
    std::ifstream tileFile =std::ifstream(fileName);

    std::string fileContents;

    std::map<int, TileSpec> tileMap;

    int delimiterLocation =0;
    
    int currentTile = 0;

    istringstream stringconvertor;

    while(std::getline(tileFile, fileContents,LINE_SEPARTOR)){

        std::remove (fileContents.begin(),fileContents.end(),' ');
        
        delimiterLocation = fileContents.find_first_of(TILE_SEPARATOR);

        stringconvertor = istringstream(fileContents.substr(0,delimiterLocation));
        
        stringconvertor >> currentTile;        

        fileContents.erase(0,delimiterLocation + 1);

        tileMap.insert(std::pair<int,TileSpec>(currentTile, appendCardinality(fileContents)));

    }

    return tileMap;
}

TileSpec TileFactory::appendCardinality(std::string tileString){
    TileSpec specification;    
    
    int direction;
    int location;
    int tile;
    istringstream stringconvertor;
    string successorTiles;

    while((location = tileString.find_first_of(SUCCESSOR_TILE_START)) != -1)
    {
        stringconvertor =  istringstream(tileString.substr(0,location));

        tileString.erase(0,location + 1);

        if((location = tileString.find_first_of(SUCCESSOR_TILE_END)) != -1)
        {
            successorTiles = tileString.substr(0,location);
        }
        
        tileString.erase(0,location + 1);
       
        stringconvertor >> direction;
        
        while((location = successorTiles.find_first_of(TILE_DELIMITER)) != -1)
        {
            stringconvertor =  istringstream(successorTiles.substr(0,location));
            
            successorTiles.erase(0,location + 1);

            stringconvertor >> tile;

            specification.appendTile(direction, tile);
        }
        stringconvertor =  istringstream(successorTiles);
            
        stringconvertor >> tile;

        specification.appendTile(direction, tile);
    }

    return specification;
}
