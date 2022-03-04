#include<graphics.h>
#include"mydefine.h"

IMAGE gear, gearbk, timebgbk, timebg, start, end, note, intro;
IMAGE img_eye1, img_eye12, img_eye13, img_eye2;
IMAGE img_bk[10], levelbk[10], img_bk_w;
struct EYE eye;    //主角左上角的坐标
int gear_t;        //放第几张齿轮图片

//运动相关参数
double v0;         //主角初速度
double Height;     //下落高度
double Time;       //下落时间
int type;          //撞到地形的类型
int flag_die;      //死亡标志
int again;         //判断是否重来

//碰齿轮及下落相关参数
double die_h;         //单位时间Time内尸体下落高度
double flag_t;        //角速度
double degree;        //角度
double cir_x, cir_y;  //圆心
int flag_fall;//尸体下落标志  0为无效果 1为重心在右边  -1为左边  2为中间 3为从齿轮下方碰到齿轮 所以不需要开启旋转开关
double die_v; //尸体的下落时的速度
int die_x;	  //尸体的坐标
int die_y;

//关卡相关参数
int s_x, s_y, end_x, end_y; //出生位置坐标和结束坐标
int level;                  //当前是第几关

//主界面相关参数
int pause = 0;              //初始化暂停开关为关闭，当按下esc时开启
int flag3 = 1;              //打开bk_init函数的标志
int back;                   //
int nlevel = 0;             //当前到达的最高关卡

//时间虫相关参数
double bug_x[NBUG];         //时间虫的x坐标和y坐标
double bug_y[NBUG];
int xdir[NBUG], ydir[NBUG]; //运动方向
double vx[NBUG];            //速度的x分量和y分量
double vy[NBUG];

int on_hint = 1;