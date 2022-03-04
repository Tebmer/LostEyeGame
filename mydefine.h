#pragma once
#include<graphics.h>

#ifndef MYDEFINE
#define MYDEFINE

#define STEP		4           //�����ƶ�����

#define	CMD_LEFT	1			// �����
#define	CMD_RIGHT	2
#define	CMD_UP		4
#define CMD_DOWN	8
#define CMD_SHOOT	16
#define CMD_ESC		32

#pragma comment(lib, "Winmm.lib");
#define XSIZE 640               //���泤�Ϳ�
#define YSIZE 480

#define G			9.8			// �������ٶ�
#define HIGH		100			// ������Ծ�����߶�
#define SUPERHIGH   300         // ���ǲȼ��ٰ����Ծ
#define W		30				// ���ǵĿ�͸�
#define H		30
#define d       30

#define NBUG    20

#endif
//��ɫ�Ľṹ�� 
struct EYE {
	int x;
	int y;
	int jump;  //û����Ծ��ʱ�� jumpΪ0 
};

//ȫ�ֱ���(��define.cpp)
extern IMAGE gear, gearbk, timebg, timebgbk, start, end, note, intro;
extern IMAGE img_eye1, img_eye12, img_eye13, img_eye2;
extern IMAGE img_bk[10], levelbk[10], img_bk_w;
extern double v0;					
extern double Height;				
extern double Time;
extern int	type;
extern int gear_t;
extern int flag_die;
extern int again;
extern double die_h;
extern double flag_t;
extern double degree;    
extern double cir_x, cir_y; 
extern int flag_fall;
extern double die_v;
extern int die_x, die_y;
extern int s_x, s_y, end_x, end_y;
extern int level ;
extern int pause;
extern int flag3;
extern int back;
extern int nlevel;

extern double bug_x[], bug_y[];
extern int xdir[], ydir[];
extern double vx[], vy[];

extern int on_hint;
