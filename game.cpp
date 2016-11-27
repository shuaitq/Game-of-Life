#include <cstdio>
#include <thread>
#include <string>
#include <fstream>
#include "src/plane.h"
#include "src/json/document.h"
#include "src/json/istreamwrapper.h"

using namespace rapidjson;

int main(int argc, char** argv){
    Document d;
    if(argc!=2){
		printf("Error! Please input the path!\n");
		return 0;
	}else{
        std::ifstream ifs(argv[1]);
        IStreamWrapper isw(ifs);
        Document d;
        d.ParseStream(isw);
	}
    assert(d.IsObject());
    int height=d["height"].GetInt(),width=d["width"].GetInt();
    printf("Hello\n");
    plane pla(height,width);
	if(d["rand"].GetBool()){
		pla.rand();
	}else{
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				pla.set(height-1-i,j,d["screen"][i][j].GetInt());
			}
		}
	}
	for(int i=0;i<9;i++){
        pla.set_rule(i,d["rules"][i].GetInt());
	}
	for(int i=1;i<=d["time"].GetInt();i++){
		printf("Start\t");
		std::string path=d["path"].GetString();
		char temp[20];
		sprintf(temp,"%d",i);
		path+=temp;
		path+=".bmp";
		printf("%s\t",path.c_str());
		pla.change();
		pla.save(path.c_str());
        //std::thread t([path,pla](){pla.save(path.c_str());});
		pla.calc();
		printf("Done!\n");
		//t.join();
	}
	return 0;
}
