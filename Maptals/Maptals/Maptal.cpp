#include "Maptal.h"
#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_print.hpp"

#include <sstream>

#include <istream>
#include <fstream>

#include "base64\Base64.h"
#include "zlib-1.2.7/zlib.h"

#define LAST_BYTE 0x000000FF

Maptal::Maptal(){
    height = 0;
    width = 0;
    zeroMatrix();
}
Maptal::Maptal(int width, int height, TileSet tSet){
    setWidth(width);
    setHeight(height);
    setTileSet(tSet);

    matrix = std::vector<std::vector<int>>(height, std::vector<int>(width));
    oid_matrix = std::vector<std::vector<int>>(height, std::vector<int>(width));

    zeroMatrix();
}
Maptal::~Maptal(){ 
}
        
TileSet Maptal::getTileSet(){
    return tileSet;
}
void Maptal::setTileSet(TileSet tSet)
{
    tileSet=tSet;
}

void Maptal::setHeight(int _height){
    height = _height;
}
void Maptal::setWidth(int _width){
    width = _width;
}

void Maptal::zeroMatrix(){
    for (unsigned int y =0; y<matrix.size();y++)
    {
        for(unsigned int x=0; x< matrix[y].size(); x++)
        {
            matrix[y][x]=tileSet.getEmptyTile();
            oid_matrix[y][x]=-1;
        }
    }
    
}
void Maptal::resizeMatrix(){
    matrix.resize(height, std::vector<int>(width));
    oid_matrix.resize(height, std::vector<int>(width));
}

std::vector<std::vector<int>> Maptal::get2DMap()
{
    return matrix;
}

void Maptal::objectsFromVector(std::vector<MapObject> *objects, 
                            TileSet *tileSet,
                            rapidxml::xml_node<char> * rootNodePtr,
                            rapidxml::xml_document<char> * tmx_doc)
{
    auto intToString = [&tmx_doc](int x){return const_cast<const char *>(tmx_doc->allocate_string(std::to_string(x).c_str()));};


    MapObject currentObject;
    rapidxml::xml_node<char> * tempNode;

    for (unsigned int i = 0; i < objects->size();i++)
    {
        currentObject = objects->at(i);
        tempNode=tmx_doc->allocate_node(rapidxml::node_element, "object");

        tempNode->append_attribute(tmx_doc->allocate_attribute("Type",tmx_doc->allocate_string(tileSet->getObjectType(currentObject.getOid()).c_str())));

        tempNode->append_attribute(tmx_doc->allocate_attribute("x",intToString((currentObject.getStartX())*tileSet->getTileWidth())));
        tempNode->append_attribute(tmx_doc->allocate_attribute("y",intToString((currentObject.getStartY())*tileSet->getTileHeight())));


        tempNode->append_attribute(tmx_doc->allocate_attribute("width",intToString((currentObject.getEndX()+1 -currentObject.getStartX())*tileSet->getTileWidth())));
        tempNode->append_attribute(tmx_doc->allocate_attribute("height",intToString((currentObject.getEndY()+1-currentObject.getStartY())*tileSet->getTileHeight())));

        rootNodePtr->append_node(tempNode);
    }    
}

std::vector<MapObject> Maptal::generateObjectVector(std::vector<std::vector<int>> matrix,TileSet tiles)
{
   int empty = tiles.getEmptyTile(), currentoid=-1, previousoid=-1;
   bool grouped =false,bufferedObject=false;

   TileSpec *currentTileSpec;
    
   MapObject * currentGroup=new MapObject(), * previousGroup=new MapObject(), tempObject;

   std::vector<MapObject> objects;
   std::vector<std::vector<MapObject>> singularObjects= std::vector<std::vector<MapObject>>(matrix[0].size());

   // Generate tile collisions.
   for(unsigned int y=0, offset=0; y < matrix.size();y++)
   {
       for( unsigned int x=0; x < matrix[y].size();x++,offset+=4)
       {
           if(matrix[y][x] != empty)
           {
               currentoid = tiles.getTileID(matrix[y][x])->getOID();
                
               if(bufferedObject && currentoid == previousoid && currentGroup!=0)
               {
                   currentGroup->setEnd(x,y);
                   previousoid=currentoid;
                   grouped=true;
               }
               else
               {
                   if(grouped && bufferedObject)
                   {
                       objects.push_back(*currentGroup);
                       grouped=!grouped;
                   }
                   else if(bufferedObject)
                   {
                       singularObjects[x].push_back(*currentGroup);
                   }                   

                   if( currentoid >= 0)
                   {
                        currentGroup=new MapObject(x,y,currentoid);
                        previousoid=currentoid;
                        bufferedObject=true;
                   }
                   else
                       bufferedObject=false;
               }
           }
           else if(bufferedObject)
           {
                   if(grouped)
                   {
                       objects.push_back(*currentGroup);
                       grouped=!grouped;
                   }
                   else
                   {
                       singularObjects[x].push_back(*currentGroup);
                   }
                   bufferedObject=false;                   
           }              
       }

       if(bufferedObject)
       {
           objects.push_back(*currentGroup);
           grouped=false;
           bufferedObject=false;

       }
   }

   currentGroup=previousGroup=0;
   bufferedObject=false;
   for(unsigned int x=0; x< singularObjects.size(); x++)
   {
       for(unsigned int y=0; y< singularObjects[x].size();y++)
       {           
           currentGroup=&(singularObjects[x][y]);

           if(bufferedObject 
               && previousGroup->getOid()==currentGroup->getOid() 
               && currentGroup->isAdjacentY(previousGroup))
           {
               previousGroup->setEnd(currentGroup->getEndX(),currentGroup->getEndY());
               currentGroup=previousGroup;
           }
           else if(bufferedObject)
           {
               objects.push_back(*previousGroup);
           }
           previousGroup=currentGroup;
           bufferedObject=true;

       }

       if(bufferedObject)
       {
           objects.push_back(*previousGroup); 
           bufferedObject=false;
       }
   }

   return objects;
}


//! Assumes a rectangular vector with heightxwidth
//Only has support for integers up to 1000 characters (shouldn't be an issue.
std::string  Maptal::base64Encode(std::vector<std::vector<int>> matrix, int emptyTile)
{
    // Assumes the matrix is square.
    uLongf bufferSize = matrix.size() * matrix[0].size() * 4;

    // This is per the zlib standardization.
    uLongf destinationSize = (uLongf)(bufferSize + (bufferSize * 0.1) + 12);
    
    Bytef * bufferedTiles = (Bytef*)malloc(bufferSize);
    Bytef * compressedTiles = (Bytef*) malloc(destinationSize);
   
    for(unsigned int y=0, offset=0, currentId =0; y < matrix.size();y++)
    {
        for(unsigned int x=0; x < matrix[y].size();x++,offset+=4)
        {
            
            //Seems as though an offset is needed.
            currentId=matrix[y][x]+1;

            // This adds each byte of the integer to the tile buffer, the SLL is by byte intervals which are then masked by LAST_BYTE.
            bufferedTiles[offset] = (currentId       & LAST_BYTE);
            bufferedTiles[offset+1] = (currentId >> 8  & LAST_BYTE);
            bufferedTiles[offset+2] = (currentId >> 16 & LAST_BYTE);
            bufferedTiles[offset+3] = (currentId >> 24 & LAST_BYTE);
        }
    }
    compress(compressedTiles, &destinationSize,bufferedTiles, bufferSize);

    return Base64::base64_encode(compressedTiles,destinationSize);
}

void Maptal::toTMX()
{
    rapidxml::xml_document<char> tmx;   

    // A quick and dirty anonymous function to convert the attributes to a valid string.
    auto intToString = [&tmx](int x){return const_cast<const char *>(tmx.allocate_string(std::to_string(x).c_str()));};
    
    //**********************************
    //! Declaration node creation.
    //**********************************
    rapidxml::xml_node<char> * rootNodePtr = tmx.allocate_node(rapidxml::node_declaration);

    rootNodePtr->append_attribute(tmx.allocate_attribute("version", "1.0"));
    rootNodePtr->append_attribute(tmx.allocate_attribute("encoding", "utf-8"));

    //**********************************
    
    tmx.append_node(rootNodePtr);

    //**********************************
    //! Map node creation.
    //**********************************
    rootNodePtr = tmx.allocate_node(rapidxml::node_element, "map");
    rootNodePtr->append_attribute(tmx.allocate_attribute("version", "1.0"));
    rootNodePtr->append_attribute(tmx.allocate_attribute("orientation", "orthogonal")); 
    rootNodePtr->append_attribute(tmx.allocate_attribute("width", intToString(width)));
    rootNodePtr->append_attribute(tmx.allocate_attribute("height",  intToString(height)));    
    rootNodePtr->append_attribute(tmx.allocate_attribute("tilewidth", intToString(tileSet.getTileWidth()) ));
    rootNodePtr->append_attribute(tmx.allocate_attribute("tileheight",  intToString(tileSet.getTileHeight()) ));
    //**********************************

    tmx.append_node(rootNodePtr);
        
        //**********************************
        //! Tileset node creation.
        //**********************************
        rapidxml::xml_node<char> * subNodePtr = tmx.allocate_node(rapidxml::node_element, "tileset");

    
        subNodePtr->append_attribute(tmx.allocate_attribute("name",tmx.allocate_string(tileSet.getImagePath().c_str())));
        subNodePtr->append_attribute(tmx.allocate_attribute("firstgid", "1"));
        subNodePtr->append_attribute(tmx.allocate_attribute("tilewidth", intToString(tileSet.getTileWidth())));
        subNodePtr->append_attribute(tmx.allocate_attribute("tileheight",  intToString(tileSet.getTileHeight())));

            //**********************************
            //! Image node creation.
            //**********************************
            rapidxml::xml_node<char> * imageNodePtr = tmx.allocate_node(rapidxml::node_element, "image");

            imageNodePtr->append_attribute(tmx.allocate_attribute("source",tmx.allocate_string(tileSet.getImagePath().c_str())));
            imageNodePtr->append_attribute(tmx.allocate_attribute("width", intToString(tileSet.getImageWidth())));
            imageNodePtr->append_attribute(tmx.allocate_attribute("height",  intToString(tileSet.getImageHeight())));
            //**********************************
        subNodePtr->append_node(imageNodePtr);
        //**********************************
    rootNodePtr->append_node(subNodePtr);

    
    subNodePtr = tmx.allocate_node(rapidxml::node_element, "objectgroup");
    
    subNodePtr->append_attribute(tmx.allocate_attribute("name", "collisions"));

    objectsFromVector(&generateObjectVector(matrix, tileSet), &tileSet, subNodePtr,&tmx);

    rootNodePtr->append_node(subNodePtr);

    //**********************************
    //! Layer node creation.
    //**********************************
    subNodePtr = tmx.allocate_node(rapidxml::node_element, "layer");
    subNodePtr->append_attribute(tmx.allocate_attribute("name","default"));
    subNodePtr->append_attribute(tmx.allocate_attribute("width", intToString(width)));
    subNodePtr->append_attribute(tmx.allocate_attribute("height",  intToString(height)));  

            //**********************************
            //! Data node creation.
            //**********************************
            rapidxml::xml_node<char> * dataNodePtr = tmx.allocate_node(rapidxml::node_element, "data");

            dataNodePtr->append_attribute(tmx.allocate_attribute("encoding","base64"));
            dataNodePtr->append_attribute(tmx.allocate_attribute("compression","zlib"));
            
                //**********************************
                //! Map data encoding.
                //**********************************
                dataNodePtr->value(tmx.allocate_string(base64Encode(matrix, tileSet.getEmptyTile()).c_str()));

                //**********************************

            //**********************************
        subNodePtr->append_node(dataNodePtr);
    //**********************************
    rootNodePtr->append_node(subNodePtr);

   
    std::ofstream tmxFile;
    tmxFile.open("Maptal.tmx");

    tmxFile<<tmx;
        
    tmxFile.close();
}