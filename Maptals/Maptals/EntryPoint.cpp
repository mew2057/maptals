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
    TileSet tSet= TileFactory::generateTileSet("tileset.xml");
    do{
       //DrunkenWalk dwlk = DrunkenWalk(10,5,1,1);

       // std::cout << endl << "==========Naive==========" << endl;

       // int** matrix = dwlk.walkPathNaive(20);

       //  for(int i = 0; i < 5; i++){
       //     for(int j = 0; j < 10; j ++){
       //         std::cout << matrix[i][j] << " ";
       //     }
       //     std::cout << endl;
       // }

       // std::cout << endl << "=========\"Predictive\"=========" << endl;
       // 
       // int** matrix2 = dwlk.walkPathNoRetrace(20);

       //  for(int i = 0; i < 5; i++){
       //     for(int j = 0; j < 10; j ++){
       //         std::cout << matrix2[i][j] << " ";
       //     }
       //     std::cout << endl;
       // }
       // std::cout << endl << "==========Mapped==========" << endl;
       // 
       // int** matrix3 = dwlk.walkPathWithTileSet(tSet);

       //   for(int i = 0; i < 5; i++){
       //     for(int j = 0; j < 10; j ++){
       //         std::cout << matrix3[i][j] << " ";
       //     }
       //     std::cout << endl;
       // }


        std::cout << endl << "==========Tile Set==========" << endl;
        
        DrunkenWalk dwalk = DrunkenWalk(width,height, tSet);

        std::vector<std::vector<int>> matrix4 = dwalk.generate2DMap();
        cout << endl;

          for(int i = 0; i < matrix4.size(); i++){
            for(int j = 0; j < matrix4[i].size(); j ++){
                std::cout << matrix4[i][j] << " ";
            }
            std::cout << endl;
        }

        dwalk.toTMX();

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

