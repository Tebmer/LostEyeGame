/*---------------------------------------------声波检测函数说明-----------------------------------------/
/  函数通过分析主角运动周围像素点的颜色，来判断主角距离障碍物还有多远，并通过颜色区分障碍物的种类
/  该函数主要为 control.cpp 中的各个函数提供距离信息和地形结构
/  函数缺点：鲁棒性较差，适用于颜色简单的画面，同时对图片质量要求比较高                                
/------------------------------------------------------------------------------------------------------*/
#include<graphics.h>
#include<math.h>
#include"mydefine.h"

extern struct EYE eye;
int mini(int *, int);
int edgeDetect(int x, int y, int lenth, char dir)        //检测方块周围是否有墙壁，x，y为左上角坐标,d为边长
{                                                    //返回方块与墙壁的最小距离
	int n, i;
	int dis[30];
	COLORREF pixel;
	for (n = 0; n < d; n++) {
		i = 0;
		while (true) {
			switch (dir) {                                  //四种情况，分别返回上下左右距离墙壁的距离
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
				i++;                                  //如果像素颜色不在目标范围内，说明没有碰壁，继续增加距离
			else
				break;
		}
		dis[n] = i;                                   //第n+1个定位像素离墙壁的距离
	}
	int minpos = mini(dis, d);
	switch (dir) {                                  //检测是齿轮、尖刺、还是墙壁、加速板
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
		type = 0;//墙壁，返回0
		return dis[minpos];
	}
	else if ((0x0d0d0d <= pixel && pixel <= 0x101010)) {  //以RGB 14 14 14 为标准值的左右浮动
		type = 1;//尖刺，返回1
		return dis[minpos];
	}
	else if (pixel == WHITE) {
		type = 2;//加速板，返回2
		return dis[minpos];
	}
	else if (pixel >= 0x272828 && pixel <= 0x292b2b) {
		type = -1;//齿轮，返回-1
		return dis[minpos];
	}
	else {
		type = 0;
		return dis[minpos];
	}
}

int mini(int *data, int n)  //处理数组，找出数组当中的最小值，并返回数组序号
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

bool is_win()  //判断是否到达终点
{
	double dx = eye.x + d/2 - end_x;
	double dy = eye.y +d/2 - end_y;
	double dis = sqrt(dx*dx + dy *dy);  //主角左上角距离终点牌的距离
	if (dis <= 35)           //是否到达以出口牌子为中心的，半径为35的圆内
		return true;
	else
		return false;
}

