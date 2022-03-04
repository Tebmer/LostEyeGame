/*-------------------------------------------------------------------------------------------------------/
/ ����ɫ��������ʱ����_init�������ú������Ը�������������Լ����ǳ��ֵĳ��Ƚ��м�������ֵİ뾶��
/ Բ���Լ���ɫ���ڳ��ֵ�����λ��
/ diefall_show()�������ж�ʬ���ͼƬ��������ʬ�����ڳ����ϵĲ�ͬ���������չʾ��ʬ��Ĳ�ͬ�˶�
/--------------------------------------------------------------------------------------------------------*/
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include "edge.h"
#include "mydefine.h"

//�˺�������  ȷ��ʬ��Բ���˶���Բ�ġ��Ƕȡ��Լ�����λ��
void diefall_init(int x, int y)     
{ 
	int n, i;
	double sum = 0;		//�и����·����ֵ����ص���ۼ�һ���������Լ�������ǳ��ȣ��Ӷ����м���
	int dis[30];
	COLORREF pixel;
	double r = 30;		//radius
	double h;			//��Բ�ĸ߶Ȳ�
       
	flag_t = 0;			//����ʱ��  ��ʹ�ý�ɫ��ʬ���t = 0��ʼת
	v0 = 0;
	type = 0;			//�ر�type=-1 ����ֹdie_x die_y ��ı䡣
	die_v = 0;			//����ʬ�������ٶ�

	//�������һ���߽������ص�Գ��ֵľ�����
	for (n = 0; n < d; n++) {   
		i = 0;
		while (true) {
		
			pixel = getpixel(x + n, y + d + 1 + i);
		
			if ( ( pixel < 0x282828 || pixel > 0x2b2b2b) && i<50)  //50Ϊshreshold ����loop time
				i++;
			else
				break;
		}
		dis[n] = i;     //ÿ�����ص������ֵľ���
		if(dis[n] < 50){
			sum++;      //�и����·����ֵ����ص���ۼ�һ
		}
	}


	h = sqrt(pow(30, 2) - pow((30 - sum), 2));  //���ɶ������h
	

	//�ж�����λ��
	if(dis[0] == 50 && dis[29] != 50){			//˵�������ڳ��ֵ����
		cir_x = x + d - sum + r;
		cir_y =	y + d + h;
		flag_fall = -1;
	}else if(dis[0] != 50 && dis[29] == 50){	//˵�������ڳ��ֵ��ұ�	
		cir_x = x + sum -d;
		cir_y = y + d + h;
		flag_fall = 1;
		
	}else {										//˵�������ڳ����м�
		flag_fall = 2;		
	}
	degree = acos((r - sum)/r);		//�н�
}


void diefall_show()    //����show����  ��ͬ�����show��ͬ��ͼ
{
	setfillcolor(BLACK);
	double r = 30;
	double die_h;		//��λTimeʱ���ڵ�·��
	int g = 12;			//�������ٶ�

						//  now I have to judge the position of body relatively to the central of gear 
	if (die_y + d / 2 < cir_y && flag_fall != 3) {	  //�������ڳ����ϲ���
													  //�����ڳ����Ϸ� ��ת
		if (flag_fall == -1) {				//���������
			die_y = cir_y - r*sin((1 - flag_t / 10)*degree) - d;			//����flag_t��������Ʋ����һ֡ʬ������
			die_x = cir_x - r*cos((1 - flag_t / 10)*degree) - d;
		}
		else if (flag_fall == 1 || flag_fall == 2) {		//�������ұ�
			die_y = cir_y - r*sin((1 - flag_t / 10)*degree) - d;			//����flag_t��������Ʋ����һ֡ʬ������
			die_x = cir_x + r*cos((1 - flag_t / 10)*degree);
		}
		if (die_y + d / 2 >= cir_y) {   //��ʬ����ת���������ƽ�е�ʱ�� �������������ʱ��
			flag_t = 0;
			flag_fall = 3;   //Besides, turn on the switch of free falling
		}
		setfillcolor(BLACK);
		solidrectangle(die_x, die_y, die_x + 25, die_y + 25);
	}
	else if (flag_fall == 3) {						//�ڳ������²��� �Ǿ���������
		int dis;
		int	type = 0;
		die_h = die_v*Time + g*pow(Time, 2) / 2;   //��λTʱ����������ĸ߶� 
		dis = edgeDetect(die_x, die_y, d, 'D');  //�����������Բ��ˮƽʱ �����߶�

		if (die_h > dis) {  //������߶ȹ���ʱ  h = dis
			die_h = dis;
		}
		die_y += die_h;

		dis = edgeDetect(die_x, die_y, d, 'D');  //�����������Բ��ˮƽʱ �����߶�

		if (dis < 5) {			//��ʬ�����������Сʱ
			die_y += dis + 5;		//��Ҫ��Ϊʲô��dis�ټ�5 ��Ϊ��Ҳ��֪���� //ʵ��������
			SetWorkingImage(&img_bk[level]);
			setfillcolor(BLACK);
			solidrectangle(die_x, die_y, die_x + 25, die_y + 25);
			SetWorkingImage();
			flag_fall = 0;   //�ر�ʬ����俪��
		}


		setfillcolor(BLACK);
		solidrectangle(die_x, die_y, die_x + 25, die_y + 25);  //��ͼ
		die_v = die_v + g*Time;

	}
}