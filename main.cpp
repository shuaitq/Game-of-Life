#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
const int live=3,maintain=2,l=30,s=30;
struct cell{
	bool now,past;
};
struct screen{
    cell pixel[s][l];
    void print_n(){
        for(int i=0;i<s;i++){
            for(int j=0;j<l;j++){
                if(pixel[i][j].now){
                    printf("●");
                }else{
                    printf("○");
                }
            }
			printf("\n");
        }
    }
    void print_p(){
        for(int i=0;i<s;i++){
            for(int j=0;j<l;j++){
                if(pixel[i][j].past){
                    printf("●");
                }else{
                    printf("○");
                }
            }
			printf("\n");
        }
    }
    inline int count(int x,int y){
    	return (pixel[(x+1)%s][(y+1)%l].past
    			+pixel[x][(y+1)%l].past
    			+pixel[(x-1+s)%s][(y+1)%l].past
    			+pixel[(x+1)%s][y].past
    			+pixel[(x-1+s)%s][y].past
    			+pixel[(x+1)%s][(y-1+l)%l].past
    			+pixel[x][(y-1+l)%l].past
    			+pixel[(x-1+s)%s][(y-1+l)%l].past
    	);
    }
    inline bool liveordie(int x,int y){
        int temp=count(x,y);
        if(temp==live){
            return true;
        }else if(temp==maintain){
            return pixel[x][y].past;
        }else{
            return false;
        }
    }
	void start(){
		for(int i=0;i<s;i++){
			for(int j=0;j<l;j++){
				if(rand()%2==1){
					pixel[i][j].now=true;
				}else{
					pixel[i][j].now=false;
				}
			}
		}
	}
	void print_info(){
		printf("规则 生%d 保持%d\n",live,maintain);
		printf("长%d 宽%d\n",l,s);
	}
	void change(){
		for(int i=0;i<s;i++){
			for(int j=0;j<l;j++){
				pixel[i][j].past=pixel[i][j].now;
			}
		}
	}
	void calc(){
		for(int i=0;i<s;i++){
			for(int j=0;j<l;j++){
				pixel[i][j].now=liveordie(i,j);
			}
		}
	}
};
int main(void){
	screen a;
	a.print_info();
	a.start();
	while(true){
		a.print_n();
		a.change();
		a.calc();
		sleep(1);
		system("clear");
	}
	return 0;
}