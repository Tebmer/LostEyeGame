/*---------------------------------------------������⺯��˵��-----------------------------------------/
/  ����ͨ�����������˶���Χ���ص����ɫ�����ж����Ǿ����ϰ��ﻹ�ж�Զ����ͨ����ɫ�����ϰ��������
/  �ú�����ҪΪ control.cpp �еĸ��������ṩ������Ϣ�͵��νṹ
/  ����ȱ�㣺³���Խϲ��������ɫ�򵥵Ļ��棬ͬʱ��ͼƬ����Ҫ��Ƚϸ�                                
/------------------------------------------------------------------------------------------------------*/
#include<graphics.h>
#include<math.h>
#include"mydefine.h"

extern struct EYE eye;
int mini(int *, int);
int edgeDetect(int x, int y, int lenth, char dir)        //��ⷽ����Χ�Ƿ���ǽ�ڣ�x��yΪ���Ͻ�����,dΪ�߳�
{                                                    //���ط�����ǽ�ڵ���С����
	int n, i;
	int dis[30];
	COLORREF pixel;
	for (n = 0; n < d; n++) {
		i = 0;
		while (true) {
			switch (dir) {                                  //����������ֱ𷵻��������Ҿ���ǽ�ڵľ���
			case 'R': pixel = getpixel(x + d + 1 + i, y + n);
				break;
			case 'L': pixel = getpixel(x - 1 - i, y + n);
				break;
		 	case 'U': pixel = getpixel(x + n, y - 1 - i);
				break;
			case 'D': pixel = getpixel(x + n, y +d + 1 + i);
				break;
			}
			if (pixel != BLACK && (pixel < 0x0d0d0d || pixel > 0x101010) && 
				(  pixel < 0x272828 || pixel > 0x292b2b) && pixel != WHITE && i<50)
				i++;                                  //���������ɫ����Ŀ�귶Χ�ڣ�˵��û�����ڣ��������Ӿ���
			else
				break;
		}
		dis[n] = i;                                   //��n+1����λ������ǽ�ڵľ���
	}
	int minpos = mini(dis, d);
	switch (dir) {                                  //����ǳ��֡���̡�����ǽ�ڡ����ٰ�
	case 'R': pixel = getpixel(x + d + 1 + dis[minpos], y + minpos);
		break;
	case 'L': pixel = getpixel(x - 1 - dis[minpos], y + minpos);
		break;
	case 'U': pixel = getpixel(x + minpos, y - 1 - dis[minpos]);
		break;
	case 'D': pixel = getpixel(x + minpos, y + d + 1 + dis[minpos]);
		break;
	}
	if (pixel == BLACK) {
		type = 0;//ǽ�ڣ�����0
		return dis[minpos];
	}
	else if ((0x0d0d0d <= pixel && pixel <= 0x101010)) {  //��RGB 14 14 14 Ϊ��׼ֵ�����Ҹ���
		type = 1;//��̣�����1
		return dis[minpos];
	}
	else if (pixel == WHITE) {
		type = 2;//���ٰ壬����2
		return dis[minpos];
	}
	else if (pixel >= 0x272828 && pixel <= 0x292b2b) {
		type = -1;//���֣�����-1
		return dis[minpos];
	}
	else {
		type = 0;
		return dis[minpos];
	}
}

int mini(int *data, int n)  //�������飬�ҳ����鵱�е���Сֵ���������������
{
	int min = 640;
	int minpos, i;
	for (i = 0; i < n; i++) {
		if (data[i] < min) {
			min = data[i];
			minpos = i;
		}
	}
	return minpos;
}

bool is_win()  //�ж��Ƿ񵽴��յ�
{
	double dx = eye.x + d/2 - end_x;
	double dy = eye.y +d/2 - end_y;
	double dis = sqrt(dx*dx + dy *dy);  //�������ϽǾ����յ��Ƶľ���
	if (dis <= 35)           //�Ƿ񵽴��Գ�������Ϊ���ĵģ��뾶Ϊ35��Բ��
		return true;
	else
		return false;
}

