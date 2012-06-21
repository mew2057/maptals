using namespace std;

#include <iostream>
#include <string>

#include "DrunkenWalk.h"
int main(){
	int height = 10;
    int width = 5;
    int minValue = 1;
    int maxValue = 1;
    string temp;
    bool cont;

    do{
       DrunkenWalk dwlk = DrunkenWalk(10,5,1,1);


        int** matrix = dwlk.generate2DMap(15);

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 10; j ++){
                cout << matrix[j][i] << " ";
            }
            cout << endl;
        }
        cout << "continue?(y|n):";
        getline( cin, temp );
        if(temp == "y"){
            cont =true;
            cout << "====================================" << endl;
        }
        else{
            cont = false;
        }

    }while(cont);
	
	return 0;
}

