#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
const int live=3,die=2,l=40,s=40;
bool now[s][l],past[s][l];
template<typename T>
inline void swap(T a,T b){
	T c=a;
	a=b;
	b=c;
}
inline void change(void){
	for(int i=0;i<s;i++){
		for(int j=0;j<l;j++){
			
		}
	}
}
void print(bool flag){
	if(flag){
		for(int i=0;i<s;i++){
			for(int j=0;j<l;j++){
				if(now[i][j]){
					printf("●");
				}else{
					printf("○");
				}
			}
			printf("\n");
		}
	}else{
		for(int i=0;i<s;i++){
			for(int j=0;j<l;j++){
				if(past[i][j]){
					printf("●");
				}else{
					printf("○");
				}
			}
			printf("\n");
		}
	}
}
int count(int a,int b){
	return (past[(a+1)%s][(b+1)%l]
			+past[a][(b+1)%l]
			+past[(a-1+s)%s][(b+1)%l]
			+past[(a+1)%s][b]
			+past[(a-1+s)%s][b]
			+past[(a+1)%s][(b-1+l)%l]
			+past[a][(b-1+l)%l]
			+past[(a-1+s)%s][(b-1+l)%l]
	);
}
bool liveordie(int a,int b){
	int temp=count(a,b);
	if(temp==3){
		return true;
	}else if(temp==2){
		return past[a][b];
	}else{
		return false;
	}
}
int main(void){
	srand(time(NULL));
	printf("规则 生%d 死%d\n",live,die);
	printf("长%d 宽%d\n",l,s);
	for(int i=0;i<s;i++){
		for(int j=0;j<l;j++){
			if(rand()%2==1){
				now[i][j]=true;
			}else{
				now[i][j]=false;
			}
		}
	}
	while(true){
		print(1);
		for(int i=0;i<s;i++){
			for(int j=0;j<l;j++){
				past[i][j]=now[i][j];
			}
		}
		for(int i=0;i<s;i++){
			for(int j=0;j<l;j++){
				now[i][j]=liveordie(i,j);
			}
		}
		sleep(0.1);
		system("clear");
	}
	return 0;
}