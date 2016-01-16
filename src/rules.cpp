#include "rules.h"
rules::rules(){
	memset(_r,0,sizeof(_r));
	_r[2]=KEEP;
	_r[3]=LIVE;
}
void rules::show(){
	printf("规则：\n");
	printf(" B");
	for(int i=0;i<9;i++){
		if(_r[i]==LIVE){
			printf("%d",i);
		}
	}
	printf("S");
	for(int i=0;i<9;i++){
		if(_r[i]==KEEP){
			printf("%d",i);
		}
	}
	printf("\n");
}