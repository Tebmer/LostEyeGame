#include<graphics.h>
#include"mydefine.h"

IMAGE gear, gearbk, timebgbk, timebg, start, end, note, intro;
IMAGE img_eye1, img_eye12, img_eye13, img_eye2;
IMAGE img_bk[10], levelbk[10], img_bk_w;
struct EYE eye;    //�������Ͻǵ�����
int gear_t;        //�ŵڼ��ų���ͼƬ

//�˶���ز���
double v0;         //���ǳ��ٶ�
double Height;     //����߶�
double Time;       //����ʱ��
int type;          //ײ�����ε�����
int flag_die;      //������־
int again;         //�ж��Ƿ�����

//�����ּ�������ز���
double die_h;         //��λʱ��Time��ʬ������߶�
double flag_t;        //���ٶ�
double degree;        //�Ƕ�
double cir_x, cir_y;  //Բ��
int flag_fall;//ʬ�������־  0Ϊ��Ч�� 1Ϊ�������ұ�  -1Ϊ���  2Ϊ�м� 3Ϊ�ӳ����·��������� ���Բ���Ҫ������ת����
double die_v; //ʬ�������ʱ���ٶ�
int die_x;	  //ʬ�������
int die_y;

//�ؿ���ز���
int s_x, s_y, end_x, end_y; //����λ������ͽ�������
int level;                  //��ǰ�ǵڼ���

//��������ز���
int pause = 0;              //��ʼ����ͣ����Ϊ�رգ�������escʱ����
int flag3 = 1;              //��bk_init�����ı�־
int back;                   //
int nlevel = 0;             //��ǰ�������߹ؿ�

//ʱ�����ز���
double bug_x[NBUG];         //ʱ����x�����y����
double bug_y[NBUG];
int xdir[NBUG], ydir[NBUG]; //�˶�����
double vx[NBUG];            //�ٶȵ�x������y����
double vy[NBUG];

int on_hint = 1;