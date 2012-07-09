using namespace std;

#include <iostream>
#include <string>
#include "TileFactory.h"
#include "DrunkenWalk.h"
int main(){
	int height = 10;
    int width = 5;
    int minValue = 1;
    int maxValue = 1;
    string temp;
    bool cont;
    cout << TileFactory::generateTileMap("Text.txt").at(0).getNextTile(0) << endl;


    do{
       DrunkenWalk dwlk = DrunkenWalk(10,5,1,5);

        std::cout << endl << "==========Naive==========" << endl;

        int** matrix = dwlk.generate2DMap(20);

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 10; j ++){
                std::cout << matrix[j][i] << " ";
            }
            std::cout << endl;
        }

        std::cout << endl << "==========Predictive==========" << endl;
        
        int** matrix2 = dwlk.walkPathNoRetrace(20);

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 10; j ++){
                std::cout << matrix2[j][i] << " ";
            }
            std::cout << endl;
        }

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

