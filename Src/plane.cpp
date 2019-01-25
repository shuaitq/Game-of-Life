#include "plane.h"

namespace plane{

    plane::plane():height(0),width(0),now(nullptr),past(nullptr){}

    plane::~plane(){
        for(int i=0;i<height;i++){
            delete [] now[i];
            delete [] past[i];
        }
        delete [] now;
        delete [] past;
    }

    void plane::run(){
        char temp[MAX_LENGTH];
        for(int i=1;i<=time;i++){
            change();
            std::thread t([&](){save(temp);});
            sprintf(temp,"%s%d.bmp",path,i);
            printf("Start\t%s\t",temp);
            calc();
            printf("Done!\n");
            t.join();
        }
    }

    bool plane::save(const char *path){
        bmp::bmp temp(height,width);
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                temp.set_pixel(i,j,past[i][j]);
            }
        }
        return temp.save(path);
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
                    now[height-1-i][j]=d["screen"][i][j].GetInt();
                }
            }
        }
        for(int i=0;i<9;i++){
            rules[i]=d["rules"][i].GetInt();
        }
        strcpy(this->path,d["path"].GetString());
        time=d["time"].GetInt();
        return true;
    }

    void plane::rand(){
        srand(std::time(nullptr));
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

}