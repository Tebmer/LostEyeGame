#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include "edge.h"
#include "mydefine.h"

//�˺������ڼ��ؾ��Źؿ�ͼ
void bk_init()
{
	//flag3 Ϊ�˺����򿪵ı�־
	if(flag3==1 )
	{
	loadimage(&levelbk[0], "picture\\1.jpg");//���˵�ͼƬ
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