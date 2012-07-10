#ifndef MAPTALS_MAPTAL_H
#define MAPTALS_MAPTAL_H

#include <cstdlib>
#include <time.h>


class Maptal{
    public:
        Maptal();
        Maptal(int width, int height, int minValue, int maxValue);
        virtual ~Maptal();
        void setMinValue(int min);
        void setMaxValue(int max);
        void setHeight(int height);
        void setWidth(int width);

    protected:
        void zeroMatrix();
        void removeMatrix();
        int minValue;
        int maxValue;
        int emptyValue;
        int height;
        int width;
        int** matrix;
};

#endif
