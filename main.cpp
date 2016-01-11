#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <unistd.h>
#include "src/image.h"
#include "src/screen.h"
int main(int argc, char** argv){
	screen a;
	if(argc==1){
		a.resize(10,10);
		a.rand();
	}else if(argc==2){
		a.load(argv[1]);
	}else{
		printf("参数错误！\n");
		return 1;
	}
	a.print_info();
	while(true){
		a.print_n();
		a.change();
		a.calc();
		sleep(1);
		system("clear");
	}
	return 0;
}