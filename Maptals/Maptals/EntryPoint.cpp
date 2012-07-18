using namespace std;

#include <iostream>
#include <string>

#include "DrunkenWalk.h"
#include "TileFactory.h"
int main(){
	int height = 10;
    int width = 5;
    int minValue = 1;
    int maxValue = 1;
    string temp;
    bool cont;
    std::map<int,TileSpec> tMap= TileFactory::generateTileMap("Text.txt");
    do{
       DrunkenWalk dwlk = DrunkenWalk(10,5,1,1);

        std::cout << endl << "==========Naive==========" << endl;

        int** matrix = dwlk.generate2DMap(20);

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 10; j ++){
                std::cout << matrix[j][i] << " ";
            }
            std::cout << endl;
        }

        std::cout << endl << "=========\"Predictive\"=========" << endl;
        
        int** matrix2 = dwlk.walkPathNoRetrace(20);

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 10; j ++){
                std::cout << matrix2[j][i] << " ";
            }
            std::cout << endl;
        }

        std::cout << endl << "==========Mapped==========" << endl;
        
        int** matrix3 = dwlk.walkPathWithMap(20,tMap);

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 10; j ++){
                std::cout << matrix3[j][i] << " ";
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

