/*-----------------------------------------------�˶��ຯ��˵��------------------------------------------/
/  ��һ�麯�����ɣ��� move �������ã������ı����ǵ�λ��
/  */
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include"edge.h"
#include"control.h"
#include"mydefine.h"
#include"diefall.h"

extern struct EYE eye;
//��ȡ������Ϣ
int GetCommand()
{
	int c = 0;

	if (GetAsyncKeyState('A') & 0x8000)
		c |= CMD_LEFT;                             //������Ƶ�1���л�����
	if (GetAsyncKeyState('D') & 0x8000)
		c |= CMD_RIGHT;                            //������Ƶ�10���л�����
	if (GetAsyncKeyState('W') & 0x8000)
		c |= CMD_UP;                               //������Ƶ�100���л�����
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		c |= CMD_ESC;                              //������Ƶ�1000���л�����
	return c;
}

//���ڸ��������˶��ĺ��� 
void left()
{
	int dis;
	dis = edgeDetect(eye.x, eye.y, W, 'L');
	if (dis < 0) {                     //�ߵ��յĵ�ͼ�߽磬edgeDetect�᷵�ظ�ֵ
		int i = 0;
		while (eye.x > 0 && i++ < STEP)
			eye.x--;
	}
	else if (dis < STEP) {
		eye.x -= dis;
		if (type == 1) {               //�������
			eye.x -= (rand() %10 +8);  //��������
			flag_die = 1;
		}
		else if (type == 2) {          //�ȵ����ٰ�
			superUp();
		}
		else if (type == -1) {         //�����ʱ������������
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
//�����ߺ�������left�ṹ��ͬ
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
		else if (type == -1) {   //���ҵ�ʱ������������
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

void up()      //��ͨ��Ծ
{
	v0 = -sqrt(2 * G*HIGH);		//���ٶȣ����ģ�
	eye.jump = 1;			//����״̬
	mciSendString("play mymusic1 from 0", NULL, 0, NULL);
}

void superUp()   //�ȼ��ٰ����Ծ
{
	v0 = -sqrt(2 * G*SUPERHIGH);  
	eye.jump = 1;
	mciSendString("play mymusic3 from 0", NULL, 0, NULL);
}

//����Ƿ���ͷ
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
			flag_fall = 3;           //����ʬ���������庯��                        
			eye.x = s_x;
			eye.y = s_y;
			die_v = 0;
		}
	}
}

//�ڿ���ʱ��״̬�仯����v0��y����ı仯
void fall()
{
	int dis;
	Height = v0*Time + G*pow(Time, 2) / 2;

	dis = edgeDetect(eye.x, eye.y, W, 'D');
	if (v0 >= 0) {	  //��������
		if (dis < 0);
		else if (Height > dis) {        //��ֹ��λʱ�����䳤�ȹ��࣬Ҫ��׼���
			Height = (double)dis;
			dis = edgeDetect(eye.x, eye.y + Height, W, 'D');//�����height�߶Ⱥ�����ϰ���ľ��룬�Լ�type
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
				else if (type == -1) {   //�����ʱ������������			
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
	else if (v0 < 0) {  //��������
		dis = edgeDetect(eye.x, eye.y, W, 'U');
		if (Height > dis) {
			Height = (double)dis;
		}

		is_head();  //������ʱ�����Ƿ���ͷ
	}
	eye.y += Height;  //��������
	v0 = v0 + G*Time; //���µ�ǰ�ٶ�
}

// ����Ƿ���� �Ƿ��ڵ���
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
//����ʱִ�еĺ���
void die()
{
	mciSendString("play mymusic2 from 0", NULL, 0, NULL);
	SetWorkingImage(&img_bk[level]);//�ڱ���ͼ�ϻ���ʬ��
	setfillcolor(BLACK);
	solidrectangle(eye.x, eye.y, eye.x + 25, eye.y + 25);
	SetWorkingImage();

	if (on_hint) {                    //��δ����bug
		hint();
		//putimage(100, 100, &gear);
		//Sleep(1000);
	}
	
	
	eye.x = s_x;     //���ǻص���ͼ������
	eye.y = s_y;
	v0 = 0;
}

//Code created by Zheng Pengyu, at 11:00AM 2018/3/8
//��ȡ�����Ϣ���ж��Ƿ�Ҫreset
int reset(int a, int b) //���¿�ʼ 
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
	int badx=0, bady=0; //����ĵ�
	int flag = 1;
	while (i < 30) {
		if ((eye.x + i) > 0 && (eye.x + i) <= 640) {
			if (getpixel(eye.x + i, eye.y - 1) >= 0x0d0d0d && getpixel(eye.x + i, eye.y - 1) <= 0x101010) {
				flag = 0; break;//�ϱ�����
			}
			else if (getpixel(eye.x + i, eye.y + 30) >= 0x0d0d0d && getpixel(eye.x + i, eye.y + 30) <= 0x101010) {
				flag = 0; break;//�±�����
			}
		}
		else
			badx++;
		if ((eye.y + j) > 0 && (eye.y + j) <=480) {
			if (getpixel(eye.x - 1, eye.y + j) >= 0x0d0d0d && getpixel(eye.x - 1, eye.y + j) <= 0x101010) {
				flag = 0; break;//�������
			}
			else if (getpixel(eye.x + 30, eye.y + j) >= 0x0d0d0d && getpixel(eye.x + 30, eye.y + j) <= 0x101010) {
				flag = 0; break;//�ұ�����
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