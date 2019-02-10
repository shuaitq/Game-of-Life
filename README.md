# Game of life - 生命游戏

## 关于生命游戏
> 康威生命游戏（英语：Conway's Game of Life），又称康威生命棋，是英国数学家约翰·何顿·康威在1970年发明的细胞自动机。它最初于1970年10月在《科学美国人》杂志上马丁·葛登能的“数学游戏”专栏出现。
> ——维基百科

维基百科链接[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway's_Game_of_Life)

简而言之就是，在一个二维空间内每一个格子就是一个「细胞」，每个细胞存在着两种状态，生和死，并通过一定的规则进行演算的结果。结果如下

## 运行结果
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/otcametapixel.png"><img src="https://github.com/shuaitq/Game-of-Life/raw/master/Image/otcametapixel.png" width="200pt" height="200pt"></a>
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/wings.gif"><img src="https://github.com/shuaitq/Game-of-Life/blob/master/Image/wings.gif" width="200pt" height="200pt"></a>
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/stilllifes.png"><img src="https://github.com/shuaitq/Game-of-Life/blob/master/Image/stilllifes.png" width="216pt" height="152pt"></a>
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/stargate.gif"><img src="https://github.com/shuaitq/Game-of-Life/blob/master/Image/stargate.gif" width="232.5pt" height="189pt"></a>
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/toggleable.gif"><img src="https://github.com/shuaitq/Game-of-Life/blob/master/Image/toggleable.gif" width="270pt" height="223.5pt"></a>
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/tnosedp4on56p27.gif"><img src="https://github.com/shuaitq/Game-of-Life/blob/master/Image/tnosedp4on56p27.gif" width="170pt" height="160pt"></a>
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/quasar.gif"><img src="https://github.com/shuaitq/Game-of-Life/blob/master/Image/quasar.gif" width="200pt" height="200pt"></a>
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/quasar2.gif"><img src="https://github.com/shuaitq/Game-of-Life/blob/master/Image/quasar2.gif" width="200pt" height="200pt"></a>
<a target="_blank" rel="noopener noreferrer" href="https://github.com/shuaitq/Game-of-Life/blob/master/Image/quasar3.gif"><img src="https://github.com/shuaitq/Game-of-Life/blob/master/Image/quasar3.gif" width="200pt" height="200pt"></a>

## 规则
### 最为经典的「B3S23」
* 当前细胞为存活状态时，当周围八个细胞低于2个（不包含2个）存活细胞时， 该细胞变成死亡状态。（模拟生命数量稀少）
* 当前细胞为存活状态时，当周围八个细胞有2个或3个存活细胞时， 该细胞保持原样。
* 当前细胞为存活状态时，当周围八个细胞有3个以上的存活细胞时，该细胞变成死亡状态。（模拟生命数量过多）
* 当前细胞为死亡状态时，当周围八个细胞有3个存活细胞时，该细胞变成存活状态。 （模拟繁殖）

就这样简单的规则和初始状态决定了生命游戏的发展。

## 特性
* 使用C++进行编写
* 支持通用[RLE](http://www.conwaylife.com/wiki/RLE)模式文件
* 模拟结果保存为[PPM](https://en.wikipedia.org/wiki/Netpbm_format)图片
* 通过简单的命令行参数设置模拟用的模式文件和模拟次数

## 怎么构建

**请确认您已经安装了make和支持C++11的C++编译器（默认使用g++，可以在Makefile修改）**

1. 下载.zip或是git clone把代码下载下来。
2. 进入目录，使用make命令进行构建，构建成功后可以使用make clean把编译过程中的.o文件删除。
3. 接下来你就可以使用Pattern文件夹中的RLE文件，或者你自己的RLE文件去simulate the world了。

## 怎么使用
```shell
./Game.out -p [RLE文件] -t [模拟次数]
Example:
    ./Game.out -p Pattern/otcametapixel.rle -t 100
```

**Have a good time.**

## 感谢
感谢[LifeWiki](http://www.conwaylife.com/wiki/Main_Page)完整的各种资料，包括且不限于：

1. 完整的RLE文件格式文档。
2. 巨量的RLE模式文件总计2000+，和各个模式的资料。

## 最后
邮箱 <i@shuaitq.com>

博客 [Tom smith](http://www.shuaitq.com/)
