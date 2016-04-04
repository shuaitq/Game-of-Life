#include <cstdio>
#include <fstream>
#include <thread>
#include "src/json.hpp"
#include "src/screen.h"
nlohmann::json json;
screen scr;
int main(int argc, char** argv){
	if(argc!=2){
		printf("Error! Please input the path!\n");
		return 0;
	}else{
		std::ifstream in;
		in.open(argv[1]);
		if(!in.is_open()){
			printf("Path error! Please input the right path!\n");
			return 0;
		}
		in>>json;
		in.close();
	}
	scr.Resize(json["height"],json["width"]);
	if(json["rand"]){
		scr.Rand();
	}else{
		for(int i=0;i<json["height"];i++){
			for(int j=0;j<json["width"];j++){
				scr.Set(scr.height-1-i,j,(int)json["screen"][i][j]);
			}
		}
	}
	for(int i=0;i<9;i++){
		scr.rules[i]=json["rules"][i];
	}
	for(int i=1;i<=json["time"];i++){
		printf("Start\t");
		std::string path=json["path"];
		char temp[20];
		sprintf(temp,"%d",i);
		path+=temp;
		path+=".bmp";
		printf("%s\t",path.c_str());
		scr.Change();
		std::thread t([path](){scr.Save(path.c_str());});
		scr.Calc();
		printf("Done!\n");
		t.join();
	}
	return 0;
}
