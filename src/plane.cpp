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

void plane::run(){
    for(int i=1;i<=time;i++){
        printf("Start\t");
        char temp[20];
        sprintf(temp,"%d",i);
        path+=temp;
        path+=".bmp";
        printf("%s\t",path.c_str());
        change();
        save(path.c_str());
        //std::thread t([path,pla](){pla.save(path.c_str());});
        pla.calc();
        printf("Done!\n");
        //t.join();
    }
}

void plane::save(const char *path){
    bmp temp(height,width,now);
    temp.save(path);
}

bool plane::read_json(const char *path){
    using namespace rapidjson;
    Document d;
    std::ifstream in(path);
    if(!in.is_open()){
        return false;
    }
    IStreamWrapper isw(in);
    d.ParseStream(isw);
    resize(d["height"].GetInt(),d["width"].GetInt());
    if(d["rand"].GetBool()){
        rand();
    }else{
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                set(height-1-i,j,d["screen"][i][j].GetInt());
            }
        }
    }
    for(int i=0;i<9;i++){
        set_rule(i,d["rules"][i].GetInt());
    }
    path=d["path"].GetString();
    return true;
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

void plane::calc(){
    #pragma omp parallel for schedule(guided)
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            now[i][j]=count(i,j);
        }
    }
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

void plane::resize(int h,int w){
    if(now!=nullptr){
        for(int i=0;i<height;i++){
            delete [] now[i];
        }
        delete [] now;
    }
    if(past!=nullptr){
        for(int i=0;i<height;i++){
            delete [] past[i];
        }
        delete [] past;
    }
    height=h;
    width=w;
    now=new pixel*[h];
    past=new pixel*[h];
    for(int i=0;i<h;i++){
        now[i]=new pixel[w];
        past[i]=new pixel[w];
    }
}

void plane::set_rule(int i,char rule){
    rules[i]=rule;
}

void plane::set(int x,int y,pixel data){
    now[x][y]=data;
}