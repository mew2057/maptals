#ifndef MAPTALS_MAPTAL_H
#define MAPTALS_MAPTAL_H

#include <cstdlib>
#include <time.h>
#include "TileSet.h"

class Maptal{
    public:
        Maptal();
        Maptal(int width, int height, TileSet tSet);
        virtual ~Maptal();
        
        TileSet getTileSet();
        void setTileSet(TileSet tSet);
        void setHeight(int height);
        void setWidth(int width);
        void toMappy();
        void toTMX();

          /*!
        * \brief The gettor for the matrix, ideal for reusing the map for respawn. 
        * \return The map matrix, performs no procedural operation to recieve the map.
        **/
        std::vector<std::vector<int>> get2DMap();  


    protected:
        void zeroMatrix();
        void resizeMatrix();
      
        int height;
        int width;
        TileSet tileSet;

        /*!
        *   \brief A matrix with dimensions height by width or matrix[height][width].
        */
        std::vector<std::vector<int>> matrix;


};

#endif
