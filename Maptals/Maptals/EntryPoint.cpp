using namespace std;

#include <iostream>
#include <string>
#include "TileSet.h"
#include "DrunkenWalk.h"
#include "TileFactory.h"
int main(){
	int height = 6;
    int width = 20;
    int minValue = 1;
    int maxValue = 1;
    string temp;
    bool cont;

    //Maptal tempMap = DrunkenWalk();
    TileSet tSet= TileFactory::generateTileSet("tileset.xml");
    do{
        std::cout << endl << "==========Tile Set==========" << endl;
        
        DrunkenWalk dwalk = DrunkenWalk(width,height, tSet);

        std::vector<std::vector<int> > matrix4 = dwalk.generate2DMap();
        cout << endl;

          for(unsigned int i = 0; i < matrix4.size(); i++){
            for(unsigned int j = 0; j < matrix4[i].size(); j ++){
                std::cout << matrix4[i][j] << " ";
            }
            std::cout << endl;
        }

        dwalk.toTMX("Maptal.tmx");

        std::cout << "continue?(y|n):";
       std::getline( cin, temp );
        if(temp == "y"){
            cont =true;
            std::cout << "====================================" << endl;
        }
        else{
            cont = false;
        }

    }while(cont);
	
	return 0;
}

