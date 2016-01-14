#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstdint>
#include "src/image.h"
#include "src/screen.h"
int main(int argc, char** argv){
	screen a;
	BmpImage b;
	if(argc==1){
		a.resize(1001,1001);
		b.resize(1001,1001);
		a.set(500,500,(cell){1,0});
		//a.rand();
	}else if(argc==2){
		a.load(argv[1]);
		b.resize(a._h,a._w);
	}else{
		printf("参数错误！\n");
		return 1;
	}
	a.print_info();
	for(int tt=1;tt<250;tt++){
		for(int i=0;i<a._h;i++){
			for(int j=0;j<a._w;j++){
				if(a.pixels[a.xy(i,j)].now==true){
					b.set(i,j,RGB(1));
				}else{
					b.set(i,j,RGB(0));
				}
			}
		}
		std::string temp="photo/";
		char temp_[10];
		sprintf(temp_,"%d",tt);
		temp+=temp_;
		temp+=".bmp";
		printf("%s\n",temp.c_str());
		b.saveBmp(temp.c_str());
		//a.print_n();
		a.change();
		a.calc();
		//sleep(1);
		//system("clear");
	}
	return 0;
}