#include "Maptal.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include <sstream>
#include <istream>
#include <fstream>
#include "base64/Base64.h"
#include "zlib/zlib.h"

#include <iostream>
// A masking tool for base 64 encoding.
#define MAPTAL_LAST_BYTE 0xFF

int Maptal::failCount=0;

const char * intToString(int x, rapidxml::xml_document<char> * tmx_doc)
{
    std::ostringstream intstream;
    intstream << x;
    return const_cast<const char *>(tmx_doc->allocate_string(intstream.str().c_str()));
};

Maptal::Maptal(int width, int height, TileSet tSet)
{
    setWidth(width);
    setHeight(height);
    setTileSet(tSet);

    int numLayers = tSet.getNumLayers();

    for (int i=0;i<numLayers;i++)
    {
        matrices.insert(std::pair<int,std::vector<std::vector<int> > >(i, std::vector<std::vector<int> > (height, std::vector<int>(width))));
    }

    zeroMatrices();
}

        
TileSet Maptal::getTileSet()
{
    return tileSet;
}

void Maptal::setTileSet(TileSet tSet)
{
    tileSet=tSet;
}

void Maptal::setHeight(int _height)
{
    height = _height;
}

void Maptal::setWidth(int _width)
{
    width = _width;
}

void Maptal::zeroMatrices()
{
    int emptyTile;
    std::vector<std::vector<int> > * currentMatrix;
    for(int i=0; i<matrices.size(); i++)
    {
        emptyTile = tileSet.getLayer(i).getEmptyTile();
        currentMatrix = &matrices[i];

        for (unsigned int y =0; y<currentMatrix->size();y++)
        {
            for(unsigned int x=0; x< currentMatrix->operator[](y).size(); x++)
            {
                currentMatrix->operator[](y)[x]=emptyTile;
            }
        }
    }
    
}

void Maptal::resizeMatrices()
{
    for(int i=0; i<matrices.size(); i++)
    {
        matrices[i].resize(height, std::vector<int>(width));
    }
}

//!DEPRECATED
std::vector<std::vector<int> > Maptal::get2DMap()
{
    return matrices[0];
}

void Maptal::objectsFromVector(std::vector<MapObject> objects, 
                            TileSet *tileSet,
                            rapidxml::xml_node<char> * rootNodePtr,
                            rapidxml::xml_document<char> * tmx_doc)
{
    // Placeholders.
    MapObject currentObject;
    rapidxml::xml_node<char> * tempNode,*subNodePtr;
    ObjectType currentType;

    // Iterates over the map objects and writes their contents to the supplied xml node.
    for (unsigned int i = 0; i < objects.size();i++)
    {
        
        currentObject = objects[i];
        currentType = tileSet->getObjectType(currentObject.getOid());
        
        //******************************************************* 
        subNodePtr=rootNodePtr->first_node("objectgroup");

        //! rapidxml has no xpath query support so I have to include this to allow for multiple object groups.
        while (subNodePtr !=0)
        {         
            if(subNodePtr->first_attribute("name") == 0 || 
                subNodePtr->first_attribute("name")->value() != currentType.group)
            {
                subNodePtr=subNodePtr->next_sibling("objectgroup");
                continue;
            }
            break;
        }
        
        //! Generates an object group as needed.
        if(subNodePtr==0)
        {
            subNodePtr=tmx_doc->allocate_node(rapidxml::node_element, "objectgroup");
            subNodePtr->append_attribute(tmx_doc->allocate_attribute("name", tmx_doc->allocate_string(currentType.group.c_str())));
            rootNodePtr->append_node(subNodePtr);
        }
        //******************************************************* 
        
        tempNode=tmx_doc->allocate_node(rapidxml::node_element, "object");

        tempNode->append_attribute(tmx_doc->allocate_attribute("type",tmx_doc->allocate_string(currentType.type.c_str())));

        tempNode->append_attribute(tmx_doc->allocate_attribute("x",intToString((currentObject.getStartX())*tileSet->getTileWidth(),tmx_doc)));
        tempNode->append_attribute(tmx_doc->allocate_attribute("y",intToString((currentObject.getStartY())*tileSet->getTileHeight(),tmx_doc)));


        tempNode->append_attribute(tmx_doc->allocate_attribute("width",intToString((currentObject.getEndX()+1 -currentObject.getStartX())*tileSet->getTileWidth(),tmx_doc)));
        tempNode->append_attribute(tmx_doc->allocate_attribute("height",intToString((currentObject.getEndY()+1-currentObject.getStartY())*tileSet->getTileHeight(),tmx_doc)));

        subNodePtr->append_node(tempNode);
    }    
}

std::vector<MapObject> Maptal::generateObjectVector(std::map<int, std::vector<std::vector<int> > >matrices,TileSet tiles)
{
   //! The vector of valid map object gorups or singletons.
   std::vector<MapObject> objects;

   for(int i = 0; i < matrices.size(); i++)
   {
       generateObjectVector(matrices[i], &objects, tileSet.getLayer(i));
   }

   return objects;
}


void Maptal::generateObjectVector(std::vector<std::vector<int> > matrix,std::vector<MapObject> * objects,TileLayer layer)
{
    //! The tile id to be ignored in searching for objects.
   int empty = layer.getEmptyTile();
   
   //! oid placeholders.
   int currentoid=-1, previousoid=-1;

   //! Used in streamlining the logic to select the appropriate reactin to the current state of the process.
   bool grouped =false,bufferedObject=false;  

   //! Map objects used to ensure the tightest possible groupings.
   MapObject * currentGroup=new MapObject(), * previousGroup=new MapObject(), tempObject;
   
   //! The matrix of objects that may benefit from vertical grouping.
   std::vector<std::vector<MapObject> > singularObjects= std::vector<std::vector<MapObject> >(matrix[0].size());

   // Generate tile collisions.
   for(unsigned int y=0, offset=0; y < matrix.size();y++)
   {
       for( unsigned int x=0; x < matrix[y].size();x++,offset+=4)
       {
           // If the tileID is not empty either execute object creation or expansion logic.
           // Else If an object is "buffered" place it in the respective collection.
           if(matrix[y][x] != empty)
           {
               currentoid = layer.getTileID(matrix[y][x])->getOID();
               /*
                * If An object is in the "buffer" and the current and previous oids match expand the group.
                * Else place the current object in either the objects vector or singular matrix 
                *    (if no buffered object exists, create it)
                */
               if(bufferedObject && currentoid == previousoid )
               {
                   // "Expand" the object.
                   currentGroup->setEnd(x,y);
                   
                   previousoid=currentoid;
                   
                   grouped=true;
               }
               else
               {
                   // If an object is present use grouped to select the correct structure to place it in.
                   if(grouped && bufferedObject)
                   {
                       objects->push_back(*currentGroup);
                       grouped=!grouped;
                   }
                   else if(bufferedObject)
                   {
                       singularObjects[x].push_back(*currentGroup);
                   }                   

                   // If the oid is non negative generate an object for it.
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
                       objects->push_back(*currentGroup);
                       grouped=!grouped;
                   }
                   else
                   {
                       singularObjects[x].push_back(*currentGroup);
                   }
                   bufferedObject=false;                   
           }              
       }

       // If an object was still in the "buffer" place it where it belongs.
       if(bufferedObject)
       {
           if(grouped)
           {
               objects->push_back(*currentGroup);
               grouped=false;
           }
           else
           {
               singularObjects[matrix[y].size()-1].push_back(*currentGroup);
           }

           bufferedObject=false;
       }
   }

   //! Reset necessary helper variables.
   currentGroup=previousGroup=0;
   bufferedObject=false;

   for(unsigned int x=0; x< singularObjects.size(); x++)
   {
       for(unsigned int y=0; y< singularObjects[x].size();y++)
       {           
           currentGroup=&(singularObjects[x][y]);

           /*
            * If an object is present (eg the object is not the first of its row), the two have matching oids and are adjacent expand the group.
            * Else If an object is present it needs to be placed in the objects vector.
            */
           if(bufferedObject 
               && previousGroup->getOid()==currentGroup->getOid() 
               && currentGroup->isAdjacentY(previousGroup))
           {
               previousGroup->setEnd(currentGroup->getEndX(),currentGroup->getEndY());
               currentGroup=previousGroup;
           }
           else if(bufferedObject)
           {
               objects->push_back(*previousGroup);
           }

           // The current is now the previous, and there is at least one object in the row.
           previousGroup=currentGroup;
           bufferedObject=true;

       }
       // If an object is still in the "buffer" make sure it makes it to the objects vector. (ensures single objects on a row make it to the vector)
       if(bufferedObject)
       {
           objects->push_back(*previousGroup); 
           bufferedObject=false;
       }
   }
}



std::string  Maptal::backgroundEncode(TileSet tSet,int height, int width)
{
    uLongf bufferSize = height * width * 4;

     // This is per the zlib standardization.
    uLongf destinationSize = (uLongf)(bufferSize + (bufferSize * 0.1) + 12);
    
    //! The data buffers.
    Bytef * bufferedTiles = (Bytef*)malloc(bufferSize);
    Bytef * compressedTiles = (Bytef*) malloc(destinationSize);

    for(unsigned int y=0, offset=0, currentId =0; y < height;y++)
    {
        if(tSet.isHorizontal())
        {
            currentId = (y < height - tSet.getHorizon()?tSet.getSkyID():tSet.getGroundID()) + 1;
        }

        for(unsigned int x=0; x < width;x++,offset+=4)
        {
            if(!tSet.isHorizontal())
            {
                currentId =( x > width - tSet.getHorizon()?tSet.getSkyID():tSet.getGroundID())+1;
            }
            
             // This adds each byte of the integer to the tile buffer, the SLL is by byte intervals which are then masked by LAST_BYTE.
            bufferedTiles[offset] =   (currentId       & MAPTAL_LAST_BYTE);
            bufferedTiles[offset+1] = (currentId >> 8  & MAPTAL_LAST_BYTE);
            bufferedTiles[offset+2] = (currentId >> 16 & MAPTAL_LAST_BYTE);
            bufferedTiles[offset+3] = (currentId >> 24 & MAPTAL_LAST_BYTE);
        }
    }
        
    compress(compressedTiles, &destinationSize,bufferedTiles, bufferSize);

    return Base64::base64_encode(compressedTiles,destinationSize);

}


std::string  Maptal::base64Encode(std::vector<std::vector<int> > matrix, int falseTile)
{
    // Assumes the matrix is square.
    uLongf bufferSize = matrix.size() * matrix[0].size() * 4;

    // This is per the zlib standardization.
    uLongf destinationSize = (uLongf)(bufferSize + (bufferSize * 0.1) + 12);
    
    //! The data buffers.
    Bytef * bufferedTiles = (Bytef*)malloc(bufferSize);
    Bytef * compressedTiles = (Bytef*) malloc(destinationSize);
   
    for(unsigned int y=0, offset=0, currentId =0; y < matrix.size();y++)
    {
        for(unsigned int x=0; x < matrix[y].size();x++,offset+=4)
        {
            
            //Seems as though an offset is needed.
            currentId=matrix[y][x]+1;

            if (currentId > falseTile)
            {
                currentId=falseTile;
            }

            // This adds each byte of the integer to the tile buffer, the SLL is by byte intervals which are then masked by LAST_BYTE.
            bufferedTiles[offset] =   (currentId       & MAPTAL_LAST_BYTE);
            bufferedTiles[offset+1] = (currentId >> 8  & MAPTAL_LAST_BYTE);
            bufferedTiles[offset+2] = (currentId >> 16 & MAPTAL_LAST_BYTE);
            bufferedTiles[offset+3] = (currentId >> 24 & MAPTAL_LAST_BYTE);
        }
    }
    
    compress(compressedTiles, &destinationSize,bufferedTiles, bufferSize);

    return Base64::base64_encode(compressedTiles,destinationSize);
}

void Maptal::toTMX(const char * fileDestination)
{
    rapidxml::xml_document<char> tmx;   
    rapidxml::xml_node<char> * dataNodePtr;

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
    rootNodePtr->append_attribute(tmx.allocate_attribute("width", intToString(width,&tmx)));
    rootNodePtr->append_attribute(tmx.allocate_attribute("height",  intToString(height,&tmx)));    
    rootNodePtr->append_attribute(tmx.allocate_attribute("tilewidth", intToString(tileSet.getTileWidth(),&tmx) ));
    rootNodePtr->append_attribute(tmx.allocate_attribute("tileheight",  intToString(tileSet.getTileHeight(),&tmx) ));
    //**********************************

    tmx.append_node(rootNodePtr);
        
        //**********************************
        //! Tileset node creation.
        //**********************************
        rapidxml::xml_node<char> * subNodePtr = tmx.allocate_node(rapidxml::node_element, "tileset");

    
        subNodePtr->append_attribute(tmx.allocate_attribute("name",tmx.allocate_string(tileSet.getImagePath().c_str())));
        subNodePtr->append_attribute(tmx.allocate_attribute("firstgid", "1"));
        subNodePtr->append_attribute(tmx.allocate_attribute("tilewidth", intToString(tileSet.getTileWidth(),&tmx)));
        subNodePtr->append_attribute(tmx.allocate_attribute("tileheight",  intToString(tileSet.getTileHeight(),&tmx)));

            //**********************************
            //! Image node creation.
            //**********************************
            rapidxml::xml_node<char> * imageNodePtr = tmx.allocate_node(rapidxml::node_element, "image");

            imageNodePtr->append_attribute(tmx.allocate_attribute("source",tmx.allocate_string(tileSet.getImagePath().c_str())));
            imageNodePtr->append_attribute(tmx.allocate_attribute("width", intToString(tileSet.getImageWidth(),&tmx)));
            imageNodePtr->append_attribute(tmx.allocate_attribute("height",  intToString(tileSet.getImageHeight(),&tmx)));
            //**********************************
        subNodePtr->append_node(imageNodePtr);
        //**********************************
    rootNodePtr->append_node(subNodePtr);

    //**********************************
    //! Layer node creation.
    //**********************************
    subNodePtr = tmx.allocate_node(rapidxml::node_element, "layer");
    subNodePtr->append_attribute(tmx.allocate_attribute("name",tmx.allocate_string("background")));
    subNodePtr->append_attribute(tmx.allocate_attribute("width", intToString(width,&tmx)));
    subNodePtr->append_attribute(tmx.allocate_attribute("height",  intToString(height,&tmx)));  

    //**********************************
    //! Data node creation.
    //**********************************
    dataNodePtr = tmx.allocate_node(rapidxml::node_element, "data");

    dataNodePtr->append_attribute(tmx.allocate_attribute("encoding","base64"));
    dataNodePtr->append_attribute(tmx.allocate_attribute("compression","zlib"));
            
    //**********************************
    //! Map data encoding.
    //**********************************
     dataNodePtr->value(tmx.allocate_string(backgroundEncode(tileSet,height, width).c_str()));

    //**********************************
    //**********************************
    subNodePtr->append_node(dataNodePtr);
    //**********************************
    rootNodePtr->append_node(subNodePtr);

    //Objects
    objectsFromVector(generateObjectVector(matrices, tileSet), &tileSet, rootNodePtr,&tmx);
    
    
    for(int layer=0;layer<matrices.size();layer++)
    {
        subNodePtr = tmx.allocate_node(rapidxml::node_element, "layer");
        subNodePtr->append_attribute(tmx.allocate_attribute("name",tmx.allocate_string(tileSet.getLayer(layer).getLayerName().c_str())));
        subNodePtr->append_attribute(tmx.allocate_attribute("width", intToString(width,&tmx)));
        subNodePtr->append_attribute(tmx.allocate_attribute("height",  intToString(height,&tmx)));  

        //**********************************
        //! Data node creation.
        //**********************************
        dataNodePtr = tmx.allocate_node(rapidxml::node_element, "data");

        dataNodePtr->append_attribute(tmx.allocate_attribute("encoding","base64"));
        dataNodePtr->append_attribute(tmx.allocate_attribute("compression","zlib"));
            
        //**********************************
        //! Map data encoding.
        //**********************************
        dataNodePtr->value(tmx.allocate_string(base64Encode(matrices[layer],tileSet.getLayer(layer).getFalseTile()).c_str()));

        //**********************************

        //**********************************
        subNodePtr->append_node(dataNodePtr);
    
        //**********************************
        rootNodePtr->append_node(subNodePtr);
    }


    
   
    std::ofstream tmxFile;
    tmxFile.open(fileDestination);

    tmxFile<<tmx;
        
    tmxFile.close();
}