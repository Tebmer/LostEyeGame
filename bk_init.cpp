#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include "edge.h"
#include "mydefine.h"

//此函数用于加载九张关卡图
void bk_init()
{
	//flag3 为此函数打开的标志
	if(flag3==1 )
	{
	loadimage(&levelbk[0], "picture\\1.jpg");//主菜单图片
	loadimage(&levelbk[1], "picture\\2.jpg");
	loadimage(&levelbk[2], "picture\\3.jpg");
	loadimage(&levelbk[3], "picture\\4.jpg");
	loadimage(&levelbk[4], "picture\\5.jpg");
	loadimage(&levelbk[5], "picture\\6.jpg");
	loadimage(&levelbk[6], "picture\\7.jpg");
	loadimage(&levelbk[7], "picture\\8.jpg");
	loadimage(&levelbk[8], "picture\\9.jpg");

	putimage(0,0,&levelbk[nlevel],SRCCOPY);
	}

}