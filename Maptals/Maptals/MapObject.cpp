#include "MapObject.h"

MapObject::MapObject(int x, int y, int newoid)
{
    startX=endX=x;
    startY=endY=y;
    oid=newoid;
}

void MapObject::setStart(int x, int y)
{
    startX=x;
    startY=y;
}
 
void MapObject::setEnd(int x, int y)
{
    endX=x;
    endY=y;
}

void MapObject::setOid(int newoid)
{
    oid=newoid;
}

bool MapObject::isAdjacentY(const MapObject *objectToCompare)
{
    return endY+1 == objectToCompare->startY || startY-1 == objectToCompare->endY;
}

bool MapObject::isAdjacentX(const MapObject *objectToCompare)
{
    return endX+1 == objectToCompare->startX || startX-1 == objectToCompare->endX;
}

int MapObject::getStartX()
{
    return startX;
}
 
int MapObject::getStartY()
{
    return startY;
}
 
int MapObject::getEndX()
{
    return endX;
}
 
int MapObject::getEndY()
{
    return endY;
}

int MapObject::getWidth()
{
    return startX-endX;
}
    
int MapObject::getHeight()
{
    return startY-endY;
}

int MapObject::getOid()
{
    return oid;
}