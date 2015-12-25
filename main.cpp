#include <cstdio>
int live=3,die=2;
int main(void){
	while(true){
		printf("你想要改变规则吗？Y/N 默认：生3死2\n");
		char word;
		scanf("%c",&word);
		if(word=='Y'){
			printf("请输入你所想要的规则，格式\"生 死\" 中间用一个空格隔开。\n");
			scanf("%d%d",&live,&die);
			if(live>8||live<0||die>8||die<0){
				printf("输入错误，请重新输入！");
			}else{
				break;
			}
		}else if(word=='N'){
			break;
		}else{
			printf("错误！请输入正确的内容。\n");
		}
	}
	printf("%d %d\n",live,die);
	return 0;
}