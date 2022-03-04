/*----------------------------------------LOST EYE 游戏简介---------------------------------------------/
/  本游戏由Simple Fun制作
/  玩家通过 w/a/d 的操作控制主角“the eye”穿过重重障碍抵达终点，找回它的主人
/  玩家需要巧妙地利用留在地图上的尸体，来帮助自己通过不可逾越的障碍
/  游戏代码除了“mytimer.h”头文件外全部由Simple Fun原创
/------------------------------------------------------------------------------------------------------*/


/*----------------------------------------代码结构说明--------------------------------------------------/
/  游戏主体代码是 “chain.cpp” 中 move 函数和 show 函数的循环调用
/  通过获取键盘输入，主角位置参数会在 move 函数当中循环更改，当参数更新后， show 函数会依照当前参数重新
/绘制界面。
/  define.cpp 中有全局变量的详细说明
/  声波检测函数(edge.cpp)， 齿轮传动函数(diefall系列)，运动控制函数(control.cpp)和主菜单函数(menu.cpp)，
/均在各自的文件中有详细的说明
/-------------------------------------------------------------------------------------------------------*/
#include<graphics.h>
#include<time.h>
#include "mydefine.h"
#include "bk_init.h"
#include "menu.h"
#include "chain.h"



void main()
{
	srand(time(NULL));
	initgraph(640, 480);
	loadimage(&start, "picture\\start.jpg");
	loadimage(&end, "picture\\end.jpg");
	putimage(0, 0, &start);
	Sleep(4000);
	do {
		//如果reset或通关 则不执行这些关于菜单的函数
		if (again != 1) {
			bk_init();
			menu();
		}
		//如果只是暂停一下游戏，再返回游戏那么back为1，此时就不会再init
		if (back != 1) {
			init();
		}
		else {  //初始back为0 为了下次的reset
			back = 0;
		}
		move();
	} while (again == 1 || pause == 1);
	putimage(0, 0, &end);
	Sleep(5000);
	closegraph();
}



