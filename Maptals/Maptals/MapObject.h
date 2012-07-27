#ifndef MAPTALS_MAP_OBJECT_H
#define MAPTALS_MAP_OBJECT_H

class MapObject
{
public:
    MapObject();
    MapObject(int x, int y, int oid);

    void setStart(int x, int y);
    void setEnd(int x, int y);
    void setOid(int oid);

    bool isAdjacentY(const MapObject *objectToCompare);
    bool isAdjacentX(const MapObject *objectToCompare);


    int getStartX();
    int getStartY();

    int getEndX();
    int getEndY();

    int getWidth();
    int getHeight();

    int getOid();
private:
    int startX;
    int startY;
    
    int endX;
    int endY;

    int oid;
};

#endif
