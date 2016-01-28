#include <cstdio>
#include <string>
#include "src/image.h"
#include "src/screen.h"
#include "src/rules.h"
int h=100,w=100,tt=50;
bool helpornot=false;
bool setornot=false;
char *rules_path=NULL;
char *screen_path=NULL;
screen scr;
BmpImage image;
void help(){
	printf("选项：\n");
	//abcdefghijklmnopqrstuvwxyz
	printf(" -help\t\t查看帮助。\n");
	printf(" -l FILE\t载入页面,如不加载页面将以随机初始化。\n");
	printf(" -r FILE\t载入规则。\n");
	printf(" -set x y\t把页面设置成高x宽y。\n");
	printf(" -time t\t设置迭代的代数。\n");
	printf("文件格式：\n");
	printf(" 1.页面文件：*.screen\n");
	printf("  H W\t\t第一行两个参数分别代表的页面的高和宽。\n");
	printf("  1 0 0....\t接下来的H行每行W个数字中间用空格隔开。\n");
	printf("\t\t代表一个细胞的死或者活（1活，0死）\n");
	printf(" 2.规则文件：*.rule\n");
	printf("  0 0 1 2 0 0 0 0 0 0\n");
	printf("  一共八个数用空格隔开，分别代表九宫格中有几个活细胞下一代的状态。\n");
	printf("  0 DIE\t1 KEEP\t2 LIVE\n");
	printf("默认设置：\n");
	printf(" 程序将默认运行在：页面100X100，状态随机，规则B3S2，迭代代数50。\n");
	printf(" 图片使用1bit bmp存储，生成位置在photo文件夹中。\n");
}
int main(int argc, char** argv){
	for(int i=1;i<argc;i++){
		if(!strcmp(argv[i],"-help")){
			helpornot=true;
		}else if(!strcmp(argv[i],"-l")){
			i++;
			screen_path=argv[i];
		}else if(!strcmp(argv[i],"-r")){
			i++;
			rules_path=argv[i];
		}else if(!strcmp(argv[i],"-set")){
			i++;
			sscanf(argv[i],"%d",&h);
			i++;
			sscanf(argv[i],"%d",&w);
			setornot=true;
		}else if(!strcmp(argv[i],"-time")){
			i++;
			sscanf(argv[i],"%d",&tt);
		}else{
			printf("参数错误！\n");
			return 0;
		}
	}
	if(helpornot==false){
		if(setornot&&screen_path){
			printf("不能同时加载页面和设置页面大小！\n");
			printf("请选择是加载页面还是设置页面大小。\n");
			printf("1.加载页面\t2.设置页面大小\n");
			int temp;
			scanf("%d",&temp);
			if(temp==1){
				setornot=false;
			}else if(temp==2){
				screen_path=NULL;
			}else{
				printf("错误！\n");
				return -1;
			}
		}
		if(screen_path){
			scr.load_screen(screen_path);
			image.resize(scr._h,scr._w);
		}else{
			scr.resize(h,w);
			image.resize(h,w);
			scr.rand();
		}
		if(rules_path){
			scr.load_rules(rules_path);
		}
	}else{
		help();
		return 0;
	}
	scr.print_info();
	for(int i=1;i<=tt;i++){
		printf("正在生成第%d代\t\t",i);
		for(int j=0;j<scr._h;j++){
			for(int k=0;k<scr._w;k++){
				if(scr.pixels[scr.xy(j,k)].now==true){
					image.set(j,k,RGB(1));
				}else{
					image.set(j,k,RGB(0));
				}
			}
		}
		std::string temp="photo/";
		char temp_[10];
		sprintf(temp_,"%d",i);
		temp+=temp_;
		temp+=".bmp";
		image.saveBmp(temp.c_str());
		scr.change();
		scr.calc();
		printf("生成完成。\n");
	}
	return 0;
}