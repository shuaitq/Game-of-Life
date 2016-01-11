#include "screen.h"
screen::screen(){
	_s=0;
	_l=0;
	pixels=NULL;
}
screen::screen(int s,int l){
	pixels=NULL;
	init(s,l,NULL);
}
screen::~screen(){
	delete [] pixels;
}
void screen::init(int s,int l,cell *data){
	if(pixels){
		delete [] pixels;
	}
	_s=s;
	_l=l;
	pixels=new cell[l*s];
	if(data){
		memcpy(pixels,data,sizeof(cell)*_l*_s);
	}
}
void screen::print_n(){
	for(int i=0;i<_s;i++){
		for(int j=0;j<_l;j++){
			if(pixels[xy(i,j)].now){
				printf("●");
			}else{
				printf("○");
			}
		}
		printf("\n");
	}
}
void screen::print_p(){
	for(int i=0;i<_s;i++){
		for(int j=0;j<_l;j++){
			if(pixels[xy(i,j)].past){
				printf("●");
			}else{
				printf("○");
			}
		}
		printf("\n");
	}
}
inline int screen::count(int x,int y){
	return (pixels[xy((x+1)%_s,(y+1)%_l)].past
			+pixels[xy(x,(y+1)%_l)].past
			+pixels[xy((x-1+_s)%_s,(y+1)%_l)].past
			+pixels[xy((x+1)%_s,y)].past
			+pixels[xy((x-1+_s)%_s,y)].past
			+pixels[xy((x+1)%_s,(y-1+_l)%_l)].past
			+pixels[xy(x,(y-1+_l)%_l)].past
			+pixels[xy((x-1+_s)%_s,(y-1+_l)%_l)].past
			);
}
inline bool screen::liveordie(int x,int y){
	int temp=count(x,y);
	if(temp==3){
		return true;
	}else if(temp==2){
		return pixels[xy(x,y)].past;
	}else{
		return false;
	}
}
void screen::rand(){
	for(int i=0;i<_s;i++){
		for(int j=0;j<_l;j++){
			if(std::rand()%2==1){
				pixels[xy(i,j)].now=true;
			}else{
				pixels[xy(i,j)].now=false;
			}
		}
	}
}
void screen::load(const char *path){
	FILE *fd=fopen(path,"r");
	if(!fd){
		printf("文件打开失败，请确认文件存在！\n");
	}else{
		int s,l;
		fscanf(fd,"%d%d",&s,&l);
		cell *data;
		data=new cell[s*l];
		for(int i=0;i<s;i++){
			for(int j=0;j<l;j++){
				int temp;
				fscanf(fd,"%d",&temp);
				if(temp){
					data[i*l+j].now=true;
				}else{
					data[i*l+j].now=false;
				}
			}
		}
		init(s,l,data);
	}
}
void screen::print_info(){
	printf("规则 生%d 保持%d\n",3,2);
	printf("长%d 宽%d\n",_l,_s);
}
void screen::change(){
	for(int i=0;i<_s;i++){
		for(int j=0;j<_l;j++){
			pixels[xy(i,j)].past=pixels[xy(i,j)].now;
		}
	}
}
void screen::calc(){
	for(int i=0;i<_s;i++){
		for(int j=0;j<_l;j++){
			pixels[xy(i,j)].now=liveordie(i,j);
		}
	}
}
inline int screen::xy(int x,int y){
	return x*_l+y;
}
void screen::resize(int s,int l){
	init(s,l,NULL);
}