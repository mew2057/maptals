#include "TileSet.h"

int TileSet::getTileWidth()
{
    return tileWidth;
}

void TileSet::setTileWidth(int width)
{
    tileWidth=width;
}

int TileSet::getTileHeight()
{
    return tileHeight;
}

void TileSet::setTileHeight(int height)
{
    tileHeight=height;
}

std::string TileSet::getImagePath()
{
    return imagePath;
}

void TileSet::setImagePath(std::string path)
{
    imagePath=path;
}

int TileSet::getEmptyTile()
{
    return emptyTile;
}

void TileSet::setEmptyTile(int empty)
{
    emptyTile=empty;
}

int TileSet::getStartTile()
{
    return startTile;
}

void TileSet::setStartTile(int start)
{
    startTile=start;
}

int TileSet::getHorizon()
{
    return horizon;
}
    
void TileSet::setHorizon(int horiz)
{
    horizon=horiz;
}

int TileSet::getImageHeight()
{
    return imageHeight;
}
    
void TileSet::setImageHeight(int height)
{
    imageHeight=height;
}

int TileSet::getImageWidth()
{
    return imageWidth;
}
    
void TileSet::setImageWidth(int width)
{
    imageWidth=width;
}

void TileSet::appendTileSpec(int tileID, TileSpec specification)
{
    tileMap.insert(std::pair<int,TileSpec>(tileID, specification));
}

std::map<int,TileSpec> TileSet::getTileMap()
{
    return tileMap;
}

TileSpec * TileSet::getTileID(int tileID)
{
    std::map<int, TileSpec>::iterator it = tileMap.find(tileID);
    if (it != tileMap.end())
        return &(tileMap.find(tileID)->second);
    else
        return nullptr;
}

ObjectType TileSet::getObjectType(int oid)
{
    std::map<int, ObjectType>::iterator it = objectMap.find(oid);
    if (it != objectMap.end())
        return objectMap.find(oid)->second;
    else
        return ObjectType();
}

void TileSet::addObjectType(int oid, std::string objectType, std::string group)
{
    ObjectType temp;
    temp.type = objectType;
    temp.group = group;

    objectMap.insert(std::pair<int,ObjectType>(oid, temp));
}

TileSet::TileSet()
{
    setHorizon(0);
    setStartTile(0);
    setEmptyTile(0);
    setTileHeight(0);
    setTileWidth(0);
    setImagePath("\\");
    tileMap=std::map<int, TileSpec>();
    objectMap=std::map<int, ObjectType>();
}

std::ostream& operator<< ( std::ostream& outputStream, TileSet& set ){
    return outputStream << "Tile Path: " << set.getImagePath() <<"\n"
                        << "Tile Dimensions: (" << set.getTileWidth() << "x" << set.getTileHeight() << ")\n"
                        << "Horizon: " << set.getHorizon() << "\n" 
                        << "Empty Tile: " << set.getEmptyTile() << "\n"
                        << "Start Tile: " << set.getStartTile() << "\n";
}