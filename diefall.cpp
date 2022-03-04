/*-------------------------------------------------------------------------------------------------------/
/ 当角色碰到齿轮时调用_init函数，该函数可以根据死亡坐标点以及覆盖齿轮的长度进行计算出齿轮的半径、
/ 圆心以及角色对于齿轮的重心位置
/ diefall_show()函数进行对尸体的图片处理，根据尸体落在齿轮上的不同的情况，来展示出尸体的不同运动
/--------------------------------------------------------------------------------------------------------*/
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include "edge.h"
#include "mydefine.h"

//此函数用于  确定尸体圆周运动的圆心、角度、以及重心位置
void diefall_init(int x, int y)     
{ 
	int n, i;
	double sum = 0;		//有覆盖下方齿轮的像素点就累加一，这样可以计算出覆盖长度，从而进行计算
	int dis[30];
	COLORREF pixel;
	double r = 30;		//radius
	double h;			//与圆心高度差
       
	flag_t = 0;			//重置时间  来使得角色的尸体从t = 0开始转
	v0 = 0;
	type = 0;			//关闭type=-1 ，防止die_x die_y 会改变。
	die_v = 0;			//重置尸体下落速度

	//对下面的一条边进行像素点对齿轮的距离检测
	for (n = 0; n < d; n++) {   
		i = 0;
		while (true) {
		
			pixel = getpixel(x + n, y + d + 1 + i);
		
			if ( ( pixel < 0x282828 || pixel > 0x2b2b2b) && i<50)  //50为shreshold 减少loop time
				i++;
			else
				break;
		}
		dis[n] = i;     //每个像素点距离齿轮的距离
		if(dis[n] < 50){
			sum++;      //有覆盖下方齿轮的像素点就累加一
		}
	}


	h = sqrt(pow(30, 2) - pow((30 - sum), 2));  //勾股定理计算h
	

	//判断重心位置
	if(dis[0] == 50 && dis[29] != 50){			//说明重心在齿轮的左边
		cir_x = x + d - sum + r;
		cir_y =	y + d + h;
		flag_fall = -1;
	}else if(dis[0] != 50 && dis[29] == 50){	//说明重心在齿轮的右边	
		cir_x = x + sum -d;
		cir_y = y + d + h;
		flag_fall = 1;
		
	}else {										//说明重心在齿轮中间
		flag_fall = 2;		
	}
	degree = acos((r - sum)/r);		//夹角
}


void diefall_show()    //用于show函数  不同情况下show不同的图
{
	setfillcolor(BLACK);
	double r = 30;
	double die_h;		//单位Time时间内的路程
	int g = 12;			//重力加速度

						//  now I have to judge the position of body relatively to the central of gear 
	if (die_y + d / 2 < cir_y && flag_fall != 3) {	  //当重心在齿轮上部分
													  //中心在齿轮上方 旋转
		if (flag_fall == -1) {				//重心在左边
			die_y = cir_y - r*sin((1 - flag_t / 10)*degree) - d;			//随着flag_t逐个增加推测出下一帧尸体坐标
			die_x = cir_x - r*cos((1 - flag_t / 10)*degree) - d;
		}
		else if (flag_fall == 1 || flag_fall == 2) {		//重心在右边
			die_y = cir_y - r*sin((1 - flag_t / 10)*degree) - d;			//随着flag_t逐个增加推测出下一帧尸体坐标
			die_x = cir_x + r*cos((1 - flag_t / 10)*degree);
		}
		if (die_y + d / 2 >= cir_y) {   //当尸体旋转与齿轮中心平行的时候 重置自由落体的时间
			flag_t = 0;
			flag_fall = 3;   //Besides, turn on the switch of free falling
		}
		setfillcolor(BLACK);
		solidrectangle(die_x, die_y, die_x + 25, die_y + 25);
	}
	else if (flag_fall == 3) {						//在齿轮中下部分 那就自由落体
		int dis;
		int	type = 0;
		die_h = die_v*Time + g*pow(Time, 2) / 2;   //单位T时间内能下落的高度 
		dis = edgeDetect(die_x, die_y, d, 'D');  //计算在与齿轮圆心水平时 距地面高度

		if (die_h > dis) {  //当下落高度过大时  h = dis
			die_h = dis;
		}
		die_y += die_h;

		dis = edgeDetect(die_x, die_y, d, 'D');  //计算在与齿轮圆心水平时 距地面高度

		if (dis < 5) {			//当尸体离地面距离很小时
			die_y += dis + 5;		//不要问为什么加dis再加5 因为我也不知道。 //实践出真理
			SetWorkingImage(&img_bk[level]);
			setfillcolor(BLACK);
			solidrectangle(die_x, die_y, die_x + 25, die_y + 25);
			SetWorkingImage();
			flag_fall = 0;   //关闭尸体掉落开关
		}


		setfillcolor(BLACK);
		solidrectangle(die_x, die_y, die_x + 25, die_y + 25);  //绘图
		die_v = die_v + g*Time;

	}
}