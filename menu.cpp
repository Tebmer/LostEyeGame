/*�ú������ڽ�����Ϸʱѡ��ؿ��˵���������Ϸ�����˳����Ĳ˵���������������λ�������в�ͬ�Ĳ���*/
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include "edge.h"
#include "mydefine.h"

//  �˺���������escʱ �����˵���������ѡ��ؿ�
void menu()
{
	int flag1=1,flag2=0;  //������������ -> 1Ϊ��ͼ�˵�����
						  //			 -> 2Ϊ�˵�������

	if(pause==1)		//������ͣ��
	{

		//��һ��Ϊ��ʾ�˵���������
		BeginBatchDraw();
		POINT points[4]={ {275, 195}, {365, 195}, {365, 285}, {275, 285} };
		setfillcolor(0xA0A0A0);
		fillpolygon(points, 4);
		setbkmode(TRANSPARENT);
		settextstyle(20,0,"����");
    	RECT r2={275,195,365,225};rectangle(275,195,365,225);
    	drawtext("�ص���Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    	RECT r3={275,225,365,255};rectangle(275,225,365,255);
        drawtext("��Ϸ˵��", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    RECT r4={275,255,365,285};rectangle(275,255,365,285);
    	drawtext(" �� �� �� ", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FlushBatchDraw();

		flag2=1;		//�˵������ر�־��������ͣ�˵�
	 
		MOUSEMSG m;
		while(flag2==1)
		{
			BeginBatchDraw();
    		m=GetMouseMsg();
    		switch(m.uMsg)
            {
			case WM_LBUTTONDOWN:
				EndBatchDraw();
				if(m.x>275&&m.x<XSIZE/2+45&&m.y>YSIZE/2-45&&m.y<YSIZE/2-15)//����㵽 ���ص���Ϸ��
				{
					pause = 0;	//������ͣ��
					flag1 = 0;	//�رյ�ͼ�˵��Ŀ���
					flag2 = 0;	//�رղ˵�������	
					back = 1;	//���ر�־
					break;
				}
    			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/2-15&&m.y<YSIZE/2+15)//����㵽����Ϸ˵����   
				{
					putimage(0, 0, &intro);
					Sleep(5000);
					pause = 0;	//������ͣ��
					flag1 = 0;	//�رյ�ͼ�˵��Ŀ���
					flag2 = 0;	//�رղ˵�������	
					back = 1;	//���ر�־
					
					break;
     			}
    			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/2+15&&m.y<YSIZE/2+45)//����㵽�������˵�
				{
					flag1=1;	//�򿪵�ͼ�˵������˵����Ŀ���
					flag2=0;	//�رղ˵�������
					flag3=1;  //��bk_init()���� putһ��levelbkͼƬ
					pause=0;
					cleardevice();
					putimage(0,0,&levelbk[nlevel],SRCCOPY);  //�������˵�ͼƬ
    				break;
				}
    			else
    				break;
			}
			
		}
	
	}

	
	MOUSEMSG m;
	//flag1  ��ͼ�˵�������־
	while(flag1==1 )
		{
			BeginBatchDraw();
			m=GetMouseMsg();
			switch(m.uMsg)
			{
			case WM_LBUTTONDOWN:
				EndBatchDraw();
				if(m.x>40&&m.x<200&&m.y>30&&m.y<150&&flag1==1&&flag2==0)  //��һ��
				{
					cleardevice();
					flag1=0;					
					level = 0;  //��ͬ�Ĺؿ�Ϊlevel����ͬ��ֵ
					break;
				}
				else if(m.x>240&&m.x<400&&m.y>30&&m.y<150&&flag1==1&&flag2==0)	//�ڶ���
				{
					cleardevice();
					flag1=0;
					level = 1;
					break;
				}
				else if(m.x>440&&m.x<600&&m.y>30&&m.y<150&&flag1==1&&flag2==0)//������ �Դ�����
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