/*-----------------------------------------------运动类函数说明------------------------------------------/
/  由一组函数构成，归 move 函数调用，用来改变主角的位置
/  */
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include"edge.h"
#include"control.h"
#include"mydefine.h"
#include"diefall.h"

extern struct EYE eye;
//获取键盘信息
int GetCommand()
{
	int c = 0;

	if (GetAsyncKeyState('A') & 0x8000)
		c |= CMD_LEFT;                             //与二进制的1进行或运算
	if (GetAsyncKeyState('D') & 0x8000)
		c |= CMD_RIGHT;                            //与二进制的10进行或运算
	if (GetAsyncKeyState('W') & 0x8000)
		c |= CMD_UP;                               //与二进制的100进行或运算
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		c |= CMD_ESC;                              //与二进制的1000进行或运算
	return c;
}

//关于各个方向运动的函数 
void left()
{
	int dis;
	dis = edgeDetect(eye.x, eye.y, W, 'L');
	if (dis < 0) {                     //走到空的地图边界，edgeDetect会返回负值
		int i = 0;
		while (eye.x > 0 && i++ < STEP)
			eye.x--;
	}
	else if (dis < STEP) {
		eye.x -= dis;
		if (type == 1) {               //碰到尖刺
			eye.x -= (rand() %10 +8);  //向里插深点
			flag_die = 1;
		}
		else if (type == 2) {          //踩到加速板
			superUp();
		}
		else if (type == -1) {         //下落的时候检测碰到齿轮
			flag_fall = 3;
			die_x = eye.x;
			die_y = eye.y;
			eye.x = s_x;
			eye.y = s_y;
			die_v = 0;
		}
	}
	else {
		eye.x -= STEP;
	}
}
//向右走函数，与left结构相同
void right()
{
	int dis;
	dis = edgeDetect(eye.x, eye.y, W, 'R');
	if (dis < 0) {
		int i = 0;
		while (eye.x < 610 && i++ < STEP)
			eye.x++;
	}
	else if (dis < STEP) {
		eye.x += dis;
		if (type == 1) {   
			eye.x += (rand()%10 + 8) ;  
			die();
		}
		else if (type == 2) {
			superUp();
		}
		else if (type == -1) {   //向右的时候检测碰到齿轮
			flag_fall = 3;
			die_x = eye.x;
			die_y = eye.y;
			eye.x = s_x;
			eye.y = s_y;
			die_v = 0;
		}
	}
	else {
		eye.x += STEP;
	}
}

void up()      //普通跳跃
{
	v0 = -sqrt(2 * G*HIGH);		//初速度（负的）
	eye.jump = 1;			//空中状态
	mciSendString("play mymusic1 from 0", NULL, 0, NULL);
}

void superUp()   //踩加速板的跳跃
{
	v0 = -sqrt(2 * G*SUPERHIGH);  
	eye.jump = 1;
	mciSendString("play mymusic3 from 0", NULL, 0, NULL);
}

//检测是否碰头
void is_head()
{
	int dis;
	dis = edgeDetect(eye.x, eye.y + Height, W, 'U');
	if (!type && (dis == 0 || dis == 1)) {
		v0 = 0;
	}
	else if (dis < 0)
		;
	else if (dis < STEP) {
		if (type == 1) {
			eye.y -= (rand() % 10 + 8);
			flag_die = 1;
		}
		else if (type == 2) {
			superUp();
			return;
		}
		else if (type == -1) {
			die_x = eye.x;
			die_y = eye.y;
			flag_fall = 3;           //开启尸体自由落体函数                        
			eye.x = s_x;
			eye.y = s_y;
			die_v = 0;
		}
	}
}

//在空中时的状态变化，如v0和y坐标的变化
void fall()
{
	int dis;
	Height = v0*Time + G*pow(Time, 2) / 2;

	dis = edgeDetect(eye.x, eye.y, W, 'D');
	if (v0 >= 0) {	  //自由落体
		if (dis < 0);
		else if (Height > dis) {        //防止单位时间下落长度过多，要精准落地
			Height = (double)dis;
			dis = edgeDetect(eye.x, eye.y + Height, W, 'D');//计算加height高度后距离障碍物的距离，以及type
			if (dis < 0)
				;
			else if (dis < STEP) {
				if (type == 1) {
					eye.y += (rand() % 10 + 14);
					flag_die = 1;
				}
				else if (type == 2) {
					eye.y += Height + (rand() % 5 + 5);
					superUp();
					return;
				}
				else if (type == -1) {   //下落的时候检测碰到齿轮			
					eye.y += Height;
					diefall_init(eye.x, eye.y);
					die_x = eye.x;
					die_y = eye.y;
					eye.x = s_x;
					eye.y = s_y;
					die_v = 0;
				}
			}
		}
	}
	else if (v0 < 0) {  //上升过程
		dis = edgeDetect(eye.x, eye.y, W, 'U');
		if (Height > dis) {
			Height = (double)dis;
		}

		is_head();  //上升的时候检测是否碰头
	}
	eye.y += Height;  //更新坐标
	v0 = v0 + G*Time; //更新当前速度
}

// 检测是否落地 是否在地上
void is_land()
{
	int dis;
	dis = edgeDetect(eye.x, eye.y, W, 'D');
	//if(getpixel(eye.x, eye.y+W) == BLACK){
	if (!type && (dis == 0 || dis == 1)) {
		eye.jump = 0;
		v0 = 0;
	}
	else {
		eye.jump = 1;
	}
	if (eye.y > 480) {
		eye.y = 480;
		flag_die = 1;
	}
}

//Code created by Xie Hanlei, at 4:00PM 2018/3/8
//死亡时执行的函数
void die()
{
	mciSendString("play mymusic2 from 0", NULL, 0, NULL);
	SetWorkingImage(&img_bk[level]);//在背景图上绘制尸体
	setfillcolor(BLACK);
	solidrectangle(eye.x, eye.y, eye.x + 25, eye.y + 25);
	SetWorkingImage();

	if (on_hint) {                    //尚未出现bug
		hint();
		//putimage(100, 100, &gear);
		//Sleep(1000);
	}
	
	
	eye.x = s_x;     //主角回到地图出生点
	eye.y = s_y;
	v0 = 0;
}

//Code created by Zheng Pengyu, at 11:00AM 2018/3/8
//获取鼠标信息后判断是否要reset
int reset(int a, int b) //重新开始 
{
	int judge = 0;
	/*if ((a >= 0) && (a <= 30)) {
		if ((b >= 0) && (b <= 30))
			judge = 1;
		else judge = 0;
		
	}*/
	if (getpixel(a, b)>= 0x1f1f1f && getpixel(a,b) <= 0x212121)
		judge = 1;
	return judge;
}

void hint()
{
	int i=0, j=0;
	int badx=0, bady=0; //出界的点
	int flag = 1;
	while (i < 30) {
		if ((eye.x + i) > 0 && (eye.x + i) <= 640) {
			if (getpixel(eye.x + i, eye.y - 1) >= 0x0d0d0d && getpixel(eye.x + i, eye.y - 1) <= 0x101010) {
				flag = 0; break;//上边碰刺
			}
			else if (getpixel(eye.x + i, eye.y + 30) >= 0x0d0d0d && getpixel(eye.x + i, eye.y + 30) <= 0x101010) {
				flag = 0; break;//下边碰刺
			}
		}
		else
			badx++;
		if ((eye.y + j) > 0 && (eye.y + j) <=480) {
			if (getpixel(eye.x - 1, eye.y + j) >= 0x0d0d0d && getpixel(eye.x - 1, eye.y + j) <= 0x101010) {
				flag = 0; break;//左边碰刺
			}
			else if (getpixel(eye.x + 30, eye.y + j) >= 0x0d0d0d && getpixel(eye.x + 30, eye.y + j) <= 0x101010) {
				flag = 0; break;//右边碰刺
			}
		}
		else
			bady++;
		i++;
		j++;
	}
	if (badx == 30 || bady == 30)
		return;
	if (flag) {
		/*putimage(28, 110, &note);
		Sleep(1000);*/
		on_hint = 2;
	}
}