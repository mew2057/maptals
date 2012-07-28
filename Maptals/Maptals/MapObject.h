#ifndef MAPTALS_MAP_OBJECT_H
#define MAPTALS_MAP_OBJECT_H

class MapObject
{
public:
    /*
     *! \brief The Constructor for a MapObject.
     *! \param x Sets the startX and endX fields. [defaults to 0]
     *! \param y Sets the startY and endY fields. [defaults to 0]
     *! \param oid The Object IDentification for the map object, -1 is not considered a legitimate object type. [defaults to -1]
    */
    MapObject(int x=0, int y=0, int oid=-1);

    /*
     *! \brief The settor for the StartX and StartY fields.
     *!  From experience consolidating the two settors tends to reduce function calls in this case.
     *! \param x Sets the StartX field.
     *! \param y Sets the StartY field.
    */
    void setStart(int x, int y);

    /*
     *! \brief The settor for the EndX and EndY fields.
     *!  From experience consolidating the two settors tends to reduce function calls in this case.
     *! \param x Sets the EndX field.
     *! \param y Sets the EndY field.
    */
    void setEnd(int x, int y);

    /*
     *! \brief The settor for the oid field.
     *! \param oid The numeric Object IDentifier.
     */
    void setOid(int oid);

    /*
     *! \brief Deterimes if two tiles are adjacent on the Y axis.
     *!  Adjacency is confirmed if either the value of the start field of the invoking object differs 
     *!     by no more than one than the value of the end field of the passed MapObject,
     *!  or the value of the end field of the invoking object differs by no more than one 
     *!      than the value of the start field of the passed MapObject.
     *! \param objectToCompare The object that is being check for vertical adjacency. 
     *! \return True if adjacency is confirmed.
     */
    bool isAdjacentY(const MapObject *objectToCompare);

    /*
     *! \brief Deterimes if two tiles are adjacent on the X axis.
     *!  Adjacency is confirmed if either the value of the start field of the invoking object differs 
     *!     by no more than one than the value of the end field of the passed MapObject,
     *!  or the value of the end field of the invoking object differs by no more than one 
     *!      than the value of the start field of the passed MapObject.
     *! \param objectToCompare The object that is being check for horizontal adjacency. 
     *! \return True if adjacency is confirmed.
     */
    bool isAdjacentX(const MapObject *objectToCompare);

    /*
     *! \brief Gettor for the startX field.
     *! \return The startX field.
     */
    int getStartX();
    
    /*
     *! \brief Gettor for the startY field.
     *! \return The startY field.
     */
    int getStartY();
   
    /*
     *! \brief Gettor for the endX field.
     *! \return The endX field.
     */
    int getEndX();

    /*
     *! \brief Gettor for the endY field.
     *! \return The endY field.
     */
    int getEndY();

    /*
     *! \brief calculates and returns the width from the endX and startX fields.  
     *! \return The width as determined from the results of startX-endX.
     */
    int getWidth();
    
    /*
     *! \brief calculates and returns the height from the endY and startY fields.  
     *! \return The height as determined from the results of startY-endY.
     */
    int getHeight();

    /*
     *! \brief The gettor for the Object IDentifier field.
     *! \return The Object IDentifier field.
     */
    int getOid();
private:
    /*
     *! \brief The X coordinate marking the start tile of the MapObject.
     */
    int startX;

    /*
     *! \brief The Y coordinate marking the start tile of the MapObject.
     */
    int startY;
    
    /*
     *! \brief The X coordinate marking the end tile of the MapObject.
     */    
    int endX;

    /*
     *! \brief The Y coordinate marking the end tile of the MapObject.
     */  
    int endY;

    /*
     *! \brief The Object IDentifier for the MapObject. [works best with an external table of oids]
     */
    int oid;
};

#endif
