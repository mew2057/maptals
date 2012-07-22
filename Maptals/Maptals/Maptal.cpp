#include "Maptal.h"
#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_print.hpp"


#include <istream>
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
    for (int y =0; y<matrix.size();y++)
    {
        for(int x=0; x< matrix[y].size(); x++)
        {
            matrix[y][x]=tileSet.getEmptyTile();
        }
    }
    
}
void Maptal::resizeMatrix(){
    matrix.resize(height, std::vector<int>(width));
    zeroMatrix();
}

std::vector<std::vector<int>> Maptal::get2DMap()
{
    return matrix;
}
const char * convertToChar(void * ptr)
{
    int size = sizeof(ptr);
    char * convertedPtr;

    if(size ==sizeof(int)){
        char tempChar= static_cast<char>(*reinterpret_cast <int *>(ptr));
        convertedPtr= &tempChar;
    }

    return const_cast <char*>(convertedPtr);
}
void Maptal::toTMX()
{
    rapidxml::xml_document<char> tmx;   
    rapidxml::xml_node<char> * nodePtr = tmx.allocate_node(rapidxml::node_declaration);
    
    nodePtr->append_attribute(tmx.allocate_attribute("version", "1.0"));
    nodePtr->append_attribute(tmx.allocate_attribute("encoding", "utf-8"));

    tmx.append_node(nodePtr);

    nodePtr = tmx.allocate_node(rapidxml::node_element, "map");
    nodePtr->append_attribute(tmx.allocate_attribute("version", "1.0"));
    nodePtr->append_attribute(tmx.allocate_attribute("orientation", "orthagonal")); 

    //This is hilarious.
    nodePtr->append_attribute(tmx.allocate_attribute("width", convertToChar(&width)));
    nodePtr->append_attribute(tmx.allocate_attribute("height",  convertToChar(&height)));    
    //nodePtr->append_attribute(tmx.allocate_attribute("tileWidth", const_cast <char*>(reinterpret_cast <char *>(&(tileSet.getTileWidth())))));
    //nodePtr->append_attribute(tmx.allocate_attribute("tileHeight",  const_cast <char*>(reinterpret_cast <char *>(&(tileSet.getTileHeight())))));

    tmx.append_node(nodePtr);
    rapidxml::print(std::cout, tmx, 0); 
    




}

