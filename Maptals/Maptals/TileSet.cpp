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


bool TileSet::isHorizontal()    
{
    return horizontal;
}

void TileSet::setHorizontal(bool _horizontal)
{
    horizontal=_horizontal;
}


TileLayer TileSet::getLayer(int lid)
{
    std::map<int, TileLayer>::iterator it = layers.find(lid);
    if (it != layers.end())
        return layers.find(lid)->second;
    else
        return TileLayer();
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

void TileSet::addTileLayer(int lid, TileLayer layer)
{
    layers.insert(std::pair<int, TileLayer>(lid,layer));
}

int TileSet::getNumLayers()
{
    return layers.size();
}

int TileSet::getSkyID()
{
    return skyid;
}

void TileSet::setSkyID(int sky)
{
    skyid = sky;
}

int TileSet::getGroundID()
{
    return groundid;
}

void TileSet::setGroundID(int ground)
{
    groundid = ground;
}


TileSet::TileSet()
{
    setHorizon(0);    
    setTileHeight(0);
    setTileWidth(0);
    setGroundID(0);
    setSkyID(0);
    setImagePath("\\");
    setHorizontal(true);
    objectMap=std::map<int, ObjectType>();
    layers=std::map<int, TileLayer>();

}