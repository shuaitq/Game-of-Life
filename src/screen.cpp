#include "screen.h"
screen::screen(){
	_h=0;
	_w=0;
	pixels=NULL;
}
screen::screen(int h,int w){
	pixels=NULL;
	init(h,w,NULL);
}
screen::~screen(){
	delete [] pixels;
}
void screen::set(int x,int y,cell data){
	pixels[xy(x,y)]=data;
}
void screen::init(int h,int w,cell *data){
	if(pixels){
		delete [] pixels;
	}
	_h=h;
	_w=w;
	pixels=new cell[h*w];
	if(data){
		memcpy(pixels,data,sizeof(cell)*h*w);
	}
}
void screen::rand(){
	for(int i=0;i<_h;i++){
		for(int j=0;j<_w;j++){
			if(std::rand()%2==1){
				pixels[xy(i,j)].now=true;
			}else{
				pixels[xy(i,j)].now=false;
			}
		}
	}
}
void screen::load_screen(const char *path){
	FILE *fd=fopen(path,"r");
	if(!fd){
		printf("页面文件打开失败！\n");
	}else{
		int h,w;
		fscanf(fd,"%d%d",&h,&w);
		cell *data;
		data=new cell[h*w];
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				int temp;
				fscanf(fd,"%d",&temp);
				if(temp){
					data[i*w+j].now=true;
				}else{
					data[i*w+j].now=false;
				}
			}
		}
		init(h,w,data);
	}
}
void screen::load_rules(const char *path){
	FILE *fd=fopen(path,"r");
	if(!fd){
		printf("规则文件打开失败！\n");
	}else{
		for(int i=0;i<8;i++){
			fscanf(fd,"%d",&_ru._r[i]);
		}
	}
}
void screen::print_info(){
	_ru.show();
	printf("大小：\n");
	printf(" 高%d 宽%d\n",_h,_w);
}
void screen::change(){
	for(int i=0;i<_h;i++){
		for(int j=0;j<_w;j++){
			pixels[xy(i,j)].past=pixels[xy(i,j)].now;
		}
	}
}
void screen::calc(){
	for(int i=0;i<_h;i++){
		for(int j=0;j<_w;j++){
			pixels[xy(i,j)].now=liveordie(i,j);
		}
	}
}
void screen::resize(int h,int w){
	init(h,w,NULL);
}