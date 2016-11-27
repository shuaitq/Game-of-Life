#include <cstdio>
#include "src/plane.h"

int main(int argc, char** argv){
    plane pla;
    if(argc!=2){
        printf("Error! Please input the path!\n");
        return 0;
    }else{
        if(!pla.read_json(argv[1])){
            printf("Path error! Please input the right path!\n");
            return 0;
        }
    }
    pla.run();
    return 0;
}