/*该函数用于进入游戏时选择关卡菜单，和在游戏中摁退出键的菜单栏，并检测鼠标点击位置来进行不同的操作*/
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include "edge.h"
#include "mydefine.h"

//  此函数用于摁esc时 产生菜单栏，进行选择关卡
void menu()
{
	int flag1=1,flag2=0;  //定义两个开关 -> 1为地图菜单开关
						  //			 -> 2为菜单栏开关

	if(pause==1)		//摁下暂停键
	{

		//这一段为显示菜单栏的作用
		BeginBatchDraw();
		POINT points[4]={ {275, 195}, {365, 195}, {365, 285}, {275, 285} };
		setfillcolor(0xA0A0A0);
		fillpolygon(points, 4);
		setbkmode(TRANSPARENT);
		settextstyle(20,0,"黑体");
    	RECT r2={275,195,365,225};rectangle(275,195,365,225);
    	drawtext("回到游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    	RECT r3={275,225,365,255};rectangle(275,225,365,255);
        drawtext("游戏说明", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    RECT r4={275,255,365,285};rectangle(275,255,365,285);
    	drawtext(" 主 菜 单 ", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FlushBatchDraw();

		flag2=1;		//菜单栏开关标志，进入暂停菜单
	 
		MOUSEMSG m;
		while(flag2==1)
		{
			BeginBatchDraw();
    		m=GetMouseMsg();
    		switch(m.uMsg)
            {
			case WM_LBUTTONDOWN:
				EndBatchDraw();
				if(m.x>275&&m.x<XSIZE/2+45&&m.y>YSIZE/2-45&&m.y<YSIZE/2-15)//如果点到 “回到游戏”
				{
					pause = 0;	//重置暂停键
					flag1 = 0;	//关闭地图菜单的开关
					flag2 = 0;	//关闭菜单栏开关	
					back = 1;	//返回标志
					break;
				}
    			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/2-15&&m.y<YSIZE/2+15)//如果点到“游戏说明”   
				{
					putimage(0, 0, &intro);
					Sleep(5000);
					pause = 0;	//重置暂停键
					flag1 = 0;	//关闭地图菜单的开关
					flag2 = 0;	//关闭菜单栏开关	
					back = 1;	//返回标志
					
					break;
     			}
    			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/2+15&&m.y<YSIZE/2+45)//如果点到返回主菜单
				{
					flag1=1;	//打开地图菜单（主菜单）的开关
					flag2=0;	//关闭菜单栏开关
					flag3=1;  //打开bk_init()函数 put一张levelbk图片
					pause=0;
					cleardevice();
					putimage(0,0,&levelbk[nlevel],SRCCOPY);  //载入主菜单图片
    				break;
				}
    			else
    				break;
			}
			
		}
	
	}

	
	MOUSEMSG m;
	//flag1  地图菜单开启标志
	while(flag1==1 )
		{
			BeginBatchDraw();
			m=GetMouseMsg();
			switch(m.uMsg)
			{
			case WM_LBUTTONDOWN:
				EndBatchDraw();
				if(m.x>40&&m.x<200&&m.y>30&&m.y<150&&flag1==1&&flag2==0)  //第一关
				{
					cleardevice();
					flag1=0;					
					level = 0;  //不同的关卡为level赋不同的值
					break;
				}
				else if(m.x>240&&m.x<400&&m.y>30&&m.y<150&&flag1==1&&flag2==0)	//第二关
				{
					cleardevice();
					flag1=0;
					level = 1;
					break;
				}
				else if(m.x>440&&m.x<600&&m.y>30&&m.y<150&&flag1==1&&flag2==0)//第三关 以此类推
				{
					cleardevice();
					flag1=0;
					level = 2;
					break;
				}
				else if(m.x>40&&m.x<200&&m.y>180&&m.y<300&&flag1==1&&flag2==0)
				{
					cleardevice();
					flag1=0;
					level = 3;
					break;
				}
				else if(m.x>240&&m.x<400&&m.y>180&&m.y<300&&flag1==1&&flag2==0)
				{
					cleardevice();
					flag1=0;
					flag3=0;
					level = 4;
					break;
				}
				else if(m.x>440&&m.x<600&&m.y>180&&m.y<300&&flag1==1&&flag2==0)
				{
					cleardevice();
					flag1 = 0;
					flag3 = 0;
					level = 5;
					break;
				}
				else if (m.x>40 && m.x<200 && m.y>330 && m.y<450 && flag1 == 1 && flag2 == 0)
				{
						cleardevice();
					flag1 = 0;
					flag3 = 0;

						level = 6;						break;
				}
				else if (m.x>240 && m.x<400 && m.y>330 && m.y<450 && flag1 == 1 && flag2 == 0)
				{
					cleardevice();
					flag1 = 0;
					flag3 = 0;
					level = 7;
					break;
				}
				else if (m.x>440 && m.x<600 && m.y>330 && m.y<450 && flag1 == 1 && flag2 == 0)
				{
					cleardevice();
					flag1 = 0;
					flag3 = 0;
					level = 8;
					break;
				}
				else
					break;
			}
		}
}