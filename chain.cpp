/*----------------------------------------------------------------------------------------------------------/
/ ��Ϸ�Ǹɵ������������ر���ͨ��move��show������ʵ���������˶�Ч��                                         */
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include "control.h"
#include "mytimer.h"
#include "mydefine.h"
#include "diefall.h"
#include "edge.h"
#include "timebug.h"

extern struct EYE eye;

//Code created by Zhang Yumo, at 11:00AM 2018/3/7
//��ʼ������
void init()
{
	//�ṹ�������¼ÿһ�صĳ����ص�ͽ����ص�
	POINT initLocation[] = { 40,340, 40,50, 10,200, 10,120, 100,300, 110,300, 20,350, 5,35, 50,400, 0,332 };
	POINT endLocation[] = { 611,102, 613,130, 614,453, 611,72, 532,38, 612,201, 613,393, 184,35, 612,158, 630,332 };
	//��ȡͼƬ 
	loadimage(&img_eye1, "eye_bk1.jpg", 30, 30, 1);  //����ͼƬ
	loadimage(&img_eye12, "eye_bk12.jpg", 30, 30, 1); //blingking
	loadimage(&img_eye13, "eye_bk13.jpg", 30, 30, 1);
	loadimage(&img_eye2, "eye_bk2.jpg", 30, 30, 1);
	loadimage(&timebg, "timebg.bmp", 15, 15, 1);
	loadimage(&timebgbk, "timebgbk.bmp", 15, 15, 1);
	loadimage(&gear, "gear.bmp");
	loadimage(&gearbk, "gearbk.bmp");

	loadimage(&note, "picture\\note.jpg");
	loadimage(&intro, "picture\\intro.bmp");

	loadimage(&img_bk[0], "picture\\level1.bmp");//�ؿ�ͼƬ
	loadimage(&img_bk[1], "picture\\level2.bmp");
	loadimage(&img_bk[2], "picture\\level3.bmp");
	loadimage(&img_bk[3], "picture\\level4.bmp");
	loadimage(&img_bk[4], "picture\\level5.bmp");
	loadimage(&img_bk[5], "picture\\level6.bmp");
	loadimage(&img_bk[6], "picture\\level7.bmp");
	loadimage(&img_bk[7], "picture\\level8.bmp");
	loadimage(&img_bk[8], "picture\\level9.bmp");
	loadimage(&img_bk[9], "picture\\level10.bmp");
	loadimage(&img_bk_w, "picture\\level1w.bmp");
	
	mciSendString("open music\\��2.mp3 alias mymusic1", NULL, 0, NULL);
	mciSendString("open music\\����.mp3 alias mymusic2", NULL, 0, NULL);
	mciSendString("open music\\��Ծ.mp3 alias mymusic3", NULL, 0, NULL);
	mciSendString("open music\\�ؿ�ͼ��������.mp3 alias music", NULL, 0, NULL);
	eye.jump = 0;	//�տ�ʼ�ڵ���
	v0 = 0;
	Height = 0;
	Time = 0;
	again = 0;

	flag_fall = 0;  //ʹ����flag��Ϊ0
	flag_t = 0;		//����ʱ������
	die_x = 0;		
	die_y = 0;		
	cir_x = 0;		//�ò����ǹ���ʬ����亯���ĳ�ʼ��
	cir_y = 0;	
	degree = 0;		

	s_x = eye.x = initLocation[level].x; //���ݹؿ�����ͬ�ĳ�ʼֵ
	s_y = eye.y = initLocation[level].y;
	end_x = endLocation[level].x;        //���ݹؿ�����ͬ���յ�����
	end_y = endLocation[level].y;
}

//Code created by Lan Xin, at 5:00PM 2018/3/8
//4��Show ���� չʾ���в������һ֡
void show()
{
	setfillcolor(BLACK);
	putimage(0, 0, 640, 480, &img_bk[level], 0, 0);
	//����ͬ�ĳ���ͼʵ��ת��Ч��
	if (level == 2) {
		if (gear_t / 5 % 3 == 1) {
			putimage(75, 185, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(75, 185, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(75, 185, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(75, 185, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(75, 185, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(75, 185, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(519, 195, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(519, 195, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(519, 195, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(519, 195, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(519, 195, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(519, 195, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(481, 195, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(481, 195, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(481, 195, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(481, 195, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(481, 195, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(481, 195, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(557, 195, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(557, 195, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(557, 195, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(557, 195, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(557, 195, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(557, 195, 36, 36, &gear, 282, 142, SRCPAINT);
		}
	}


	else if (level == 3) {
		if (gear_t / 5 % 3 == 1) {
			putimage(347, 184, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(347, 184, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(347, 184, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(347, 184, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(347, 184, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(347, 184, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(260, 108, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(260, 108, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(260, 108, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(260, 108, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(260, 108, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(260, 108, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(174, 184, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(174, 184, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(174, 184, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(174, 184, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(174, 184, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(174, 184, 36, 36, &gear, 282, 142, SRCPAINT);
		}
	}


	else if (level == 4) {
		if (gear_t / 5 % 3 == 1) {
			putimage(206, 265, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(206, 265, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(206, 265, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(206, 265, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(206, 265, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(206, 265, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(292, 265, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(292, 265, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(292, 265, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(292, 265, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(292, 265, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(292, 265, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(405, 205, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(405, 205, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(405, 205, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(405, 205, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(405, 205, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(405, 205, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(462, 265, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(462, 265, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(462, 265, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(462, 265, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(462, 265, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(462, 265, 36, 36, &gear, 282, 142, SRCPAINT);
		}
	}


	else if (level == 5) {
		if (gear_t / 5 % 3 == 1) {
			putimage(263, 152, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(263, 152, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(263, 152, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(263, 152, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(263, 152, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(263, 152, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(432, 152, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(432, 152, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(432, 152, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(432, 152, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(432, 152, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(432, 152, 36, 36, &gear, 282, 142, SRCPAINT);
		}
	}
	else if (level == 6) {
		if (gear_t / 5 % 3 == 1) {
			putimage(142, 120, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(142, 120, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(142, 120, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(142, 120, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(142, 120, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(142, 120, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(222, 120, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(222, 120, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(222, 120, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(222, 120, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(222, 120, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(222, 120, 36, 36, &gear, 282, 142, SRCPAINT);
		}
		if (gear_t / 5 % 3 == 1) {
			putimage(302, 120, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(302, 120, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(302, 120, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(302, 120, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(302, 120, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(302, 120, 36, 36, &gear, 282, 142, SRCPAINT);
		}
		if (gear_t / 5 % 3 == 1) {
			putimage(382, 120, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(382, 120, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(382, 120, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(382, 120, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(382, 120, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(382, 120, 36, 36, &gear, 282, 142, SRCPAINT);
		}
		if (gear_t / 5 % 3 == 1) {
			putimage(462, 120, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(462, 120, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(462, 120, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(462, 120, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(462, 120, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(462, 120, 36, 36, &gear, 282, 142, SRCPAINT);
		}


		if (gear_t / 5 % 3 == 1) {
			putimage(302, 182, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(302, 182, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(302, 182, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(302, 182, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(302, 182, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(302, 182, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(302, 222, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(302, 222, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(302, 222, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(302, 222, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(302, 222, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(302, 222, 36, 36, &gear, 282, 142, SRCPAINT);
		}

		if (gear_t / 5 % 3 == 1) {
			putimage(302, 262, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(302, 262, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(302, 262, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(302, 262, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(302, 262, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(302, 262, 36, 36, &gear, 282, 142, SRCPAINT);
		}
		if (gear_t / 5 % 3 == 1) {
			putimage(302, 302, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(302, 302, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(302, 302, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(302, 302, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(302, 302, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(302, 302, 36, 36, &gear, 282, 142, SRCPAINT);
		}
		if (gear_t / 5 % 3 == 1) {
			putimage(302, 342, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(302, 342, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(302, 342, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(302, 342, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(302, 342, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(302, 342, 36, 36, &gear, 282, 142, SRCPAINT);
		}
	}
	else if (level == 7) {
		if (gear_t / 5 % 3 == 1) {
			putimage(306, 206, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(306, 206, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(306, 206, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(306, 206, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(306, 206, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(306, 206, 36, 36, &gear, 282, 142, SRCPAINT);
		}
		if (gear_t / 5 % 3 == 1) {
			putimage(525, 157, 36, 36, &gearbk, 182, 142, SRCAND);
			putimage(525, 157, 36, 36, &gear, 182, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 2) {
			putimage(525, 157, 36, 36, &gearbk, 382, 142, SRCAND);
			putimage(525, 157, 36, 36, &gear, 382, 142, SRCPAINT);
		}
		else if (gear_t / 5 % 3 == 0) {
			putimage(525, 157, 36, 36, &gearbk, 282, 142, SRCAND);
			putimage(525, 157, 36, 36, &gear, 282, 142, SRCPAINT);
		}
	}

	//��ʬ����У�ÿһ֡�ģ�show����
	if (flag_fall == 2 || flag_fall == 1 || flag_fall == -1 || flag_fall == 3) {
		diefall_show();
	}
	putimage(eye.x, eye.y, 30, 30, &img_eye2, 0, 0, SRCAND);		//������ɫͼ 
	if (gear_t % 70 == 0) {
		putimage(eye.x, eye.y, 30, 30, &img_eye12, 0, 0, SRCPAINT);
	}
	else if (gear_t % 70 == 1 || gear_t % 70 == 2 || gear_t % 70 == 3) {
		putimage(eye.x, eye.y, 30, 30, &img_eye13, 0, 0, SRCPAINT);
	}
	else if (gear_t % 70 == 6 || gear_t % 70 == 4 || gear_t % 70 == 5) {
		putimage(eye.x, eye.y, 30, 30, &img_eye12, 0, 0, SRCPAINT);
	}
	else {
		putimage(eye.x, eye.y, 30, 30, &img_eye1, 0, 0, SRCPAINT);
	}
	//ʱ���
	for (int i = 0; i < 6; i++) {
		putimage(bug_x[i], bug_y[i], 15, 15, &timebgbk, 0, 0, SRCAND);
		putimage(bug_x[i], bug_y[i], 15, 15, &timebg, 0, 0, SRCPAINT);
	}
}



void move()
{
	mciSendString("play music repeat", NULL, 0, NULL);
	MyTimer tt;
	int waitTime[NBUG];    //����ʱ�����ͣ
	for (int i = 0; i < NBUG; i++)
		waitTime[i] = rand() % 1500;
	timebugInit();
	while (1) {
		gear_t++;
		tt.Sleep(25);
		if (_kbhit()) {
			int c;
			flag_t++;	 //ÿSleepһ��ʱ��flag_t����+1����elapse��

			Time = sqrt(2 * HIGH / G) / 14;

			is_land();    //����Ƿ����

			c = GetCommand();
			if (c&CMD_LEFT)                                      //�����һλ��1����ִ�������ߺ��� 
				left();
			if (c&CMD_RIGHT)                                     //����ڶ�λ��1����ִ������ 
				right();
			if ((c&CMD_UP) && eye.jump == 0)
				up();
			if (c&CMD_ESC) {                                     //����ESC����Ϸ��ͣ
				pause = 1;
				flag3 = 0;
				break;
			}

			if (eye.jump == 1) {				//һ֡��������ڿ��������
				fall();
			}
		}
		if (flag_die == 1) {
			die();
		}
		if (on_hint == 2) {
			Sleep(2000);
			BeginBatchDraw();
			putimage(28, 110, &note);
			FlushBatchDraw();
			Sleep(5000);
			on_hint = 0;
		}

		//ʱ������ͣ
		for (int i = 0; i < NBUG; i++) {
			if ((vx[i] <= 0 || vy[i] <= 0) && waitTime[i]  < 0)//ʱ�����˶���Ϊֹͣ
				waitTime[i] = 0;
			if (waitTime[i] >= 0 && waitTime[i] < 60)
				waitTime[i]++;
			else {
				timebug(i);
				waitTime[i] = -1;
			}
		}


		//�������в����󣬿�ʼshow 
		BeginBatchDraw();
		show();
		FlushBatchDraw();
		//EndBatchDraw();
		if (MouseHit()) {                     //��������������
			MOUSEMSG m;
			int a, b;
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {   //��ȡ����������ж��Ƿ�reset
				a = m.x;
				b = m.y;
				again = reset(a, b);
				if (again == 1) {
					putimage(0, 0, 640, 480, &img_bk_w, 0, 0);
					FlushBatchDraw();
					Sleep(50);
					putimage(0, 0, 640, 480, &img_bk[level], 0, 0);
					FlushBatchDraw();
					break;
				}
			}
		}
		type = 0;
		flag_die = 0;

		if (is_win()) {
			if (level < 9) {
				again = 1;
				level++;
				if (level > nlevel)
					nlevel = level;//����
			}
			flag3 = 0;
			break;

		}
	}
}
