#include "Maptal.h"

Maptal::Maptal(){
    minValue = 0;
    maxValue = 0;
    height = 0;
    width = 0;
    emptyValue = minValue-1;
    zeroMatrix();
}

Maptal::Maptal(int _width, int _height, int _minValue, int _maxValue){
    width= _width;
    height = _height;
    minValue = _minValue;
    maxValue = _maxValue;
    emptyValue = minValue-1;
    zeroMatrix();

}

Maptal::~Maptal(){
    removeMatrix();   
}

void Maptal::setMinValue(int min){
    minValue = min;
    emptyValue =min - 1;
}

void Maptal::setMaxValue(int max){
    maxValue = max;
}

void Maptal::setHeight(int _height){
    height = _height;
}

void Maptal::setWidth(int _width){
    width = _width;
}

void Maptal::zeroMatrix(){
    matrix = new int*[width];

    for(int widt = 0; widt < width; widt++){
        matrix[widt] = new int[height];
        for(int heigt = 0; heigt < height; heigt++){
            matrix[widt][heigt] = emptyValue;
        }
    }    
}
void Maptal::removeMatrix(){
 
    for(int i = 0; i < width; i++) {
        delete [] matrix[i];
    }
    
    delete [] matrix;
}

