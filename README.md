# Game of life - 生命游戏
## 首先
这是一个用c++写的进行生命游戏并保存为bmp图片格式的项目。  
你能够通过简单的修改配置文件自定义：
* 初始页面的大小。
* 初始页面状态。
* 游戏规则。
* 生命迭代的代数。

## 关于生命游戏
>康威生命游戏（英语：Conway's Game of Life），又称康威生命棋，是英国数学家约翰·何顿·康威在1970年发明的细胞自动机。它最初于1970年10月在《科学美国人》杂志上马丁·葛登能的“数学游戏”专栏出现。
>——维基百科

维基百科链接[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway's_Game_of_Life)  
**墙内请自备梯子!**  

简而言之就是，在一个二维空间内每一个格子就是一个「细胞」，每个细胞存在着两种状态，生和死，并通过一定的规则进行演算的结果。结果就像下面这张图一样  
![](https://upload.wikimedia.org/wikipedia/commons/e/e5/Gospers_glider_gun.gif)

### 生命游戏的规则
#### 最为经典的「B3S23」
* 当前细胞为存活状态时，当周围八个细胞低于2个（不包含2个）存活细胞时， 该细胞变成死亡状态。（模拟生命数量稀少）
* 当前细胞为存活状态时，当周围八个细胞有2个或3个存活细胞时， 该细胞保持原样。
* 当前细胞为存活状态时，当周围八个细胞有3个以上的存活细胞时，该细胞变成死亡状态。（模拟生命数量过多）
* 当前细胞为死亡状态时，当周围八个细胞有3个存活细胞时，该细胞变成存活状态。 （模拟繁殖）

就这样简单的规则和初始状态决定了生命游戏的发展。

## 怎么使用
1. 使用下载.zip或是git clone把代码下载下来。
2. 进入目录，使用make命名进行构建，构建成功后可以使用make clean把编译过程中的.o文件删除。  
**请确认您已经安装了make g++ 并且g++支持c++11**
3. 第一次运行建议使用./main.out -help你可以了解设置相关参数的方法。
4. 接下来你就可以通过使用自带的几个demo，或者你自己写的文件去make the world了。

**Have a good time.**

## 文件目录
	.
	├── main.cpp			逻辑代码
	├── Makefile			make编译
	├── photo				图片默认存放位置
	├── README.md			README
	├── rules				规则存放位置，以.rule结尾
	│   └── B3S23.rule
	├── screen
	│   ├── beacon.screen	页面初始化文件存放位置，以.screen结尾
	└── src				库文件位置
    	├── cell.cpp		细胞
    	├── cell.h
    	├── image.cpp		bmp图片
    	├── image.h
    	├── rules.cpp		规则
    	├── rules.h
    	├── screen.cpp	生命游戏页面
    	└── screen.h

## 最后
邮箱 <i@shuaitq.com>

博客 [Tom smith](http://www.shuaitq.com/)