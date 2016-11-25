#include "plane.h"

plane::plane():height(0),width(0),now(nullptr),past(nullptr){}

plane::plane(int h,int w):height(h),width(w){
	now=new pixel*[h];
	past=new pixel*[h];
	for(int i=0;i<h;i++){
		now[i]=new pixel[w];
		past[i]=new pixel[w];
	}
}

plane::~plane(){
	for(int i=0;i<height;i++){
		delete [] now[i];
		delete [] past[i];
	}
	delete [] now;
	delete [] past;
}

void plane::set(int x,int y,pixel data){
	now[x][y]=data;
}

void plane::set_rule(int i,char rule){
    rules[i]=rule;
}

void plane::rand(){
	srand(time(nullptr));
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			now[i][j]=std::rand()%2;
		}
	}
}

void plane::change(){
	pixel **temp=now;
	now=past;
	past=temp;
}

pixel plane::count(int x,int y){
    switch(rules[past[(x+1)%height][(y+1)%width]
                +past[x][(y+1)%width]
                +past[(x-1+height)%height][(y+1)%width]
                +past[(x+1)%height][y]
                +past[(x-1+height)%height][y]
                +past[(x+1)%height][(y-1+width)%width]
                +past[x][(y-1+width)%width]
                +past[(x-1+height)%height][(y-1+width)%width]]){
        case DIE:
            return false;
        case KEEP:
            return past[x][y];
        case LIVE:
            return true;
    }
}

void plane::calc(){
	#pragma omp parallel for schedule(guided)
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            now[i][j]=count(i,j);
        }
    }
}

void plane::save(const char *path){
    bmp temp(height,width,now);
    temp.save(path);
}