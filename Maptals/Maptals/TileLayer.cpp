#include "TileLayer.h"

int TileLayer::getEmptyTile()
{
    return emptyTile;
}

void TileLayer::setEmptyTile(int empty)
{
    emptyTile=empty;
}

int TileLayer::getStartTile()
{
    return startTile;
}

void TileLayer::setStartTile(int start)
{
    startTile=start;
}

void TileLayer::appendTileSpec(int tileID, TileSpec specification)
{
    tileMap.insert(std::pair<int,TileSpec>(tileID, specification));
}

void TileLayer::setFalseTile(int tile)
{
    falseTile=tile;
}

int TileLayer::getFalseTile()
{
    return falseTile;
}

std::string TileLayer::getLayerName()    
{
    return layerName;
}
    
void TileLayer::setLayerName(std::string _layerName)
{
    layerName=_layerName;
}

std::map<int,TileSpec> TileLayer::getTileMap()
{
    return tileMap;
}

TileSpec * TileLayer::getTileID(int tileID)
{
    std::map<int, TileSpec>::iterator it = tileMap.find(tileID);
    if (it != tileMap.end())
        return &(tileMap.find(tileID)->second);
    else
        return 0;
}

TileLayer::TileLayer()
{
    setStartTile(0);
    setEmptyTile(0);
    setFalseTile(-1);
    setLayerName("default");
    tileMap=std::map<int, TileSpec>();

}
