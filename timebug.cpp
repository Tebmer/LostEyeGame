/*调整时间虫数组的参数，实现每只时间虫独立随机的飞行*/

#include<graphics.h>
#include<conio.h>
#include<time.h>
#include"mydefine.h"
#define a 10
#define dt 0.05

void timebugInit()
{
	for (int i = 0; i < NBUG; i++) {
		bug_x[i] = rand() % 1280 - 320;
		bug_y[i] = rand() % 960 - 240;
		vx[i] = rand() % 50 + 20;
		vy[i] = rand() % 50 + 20;
		xdir[i] = rand() % 2;
		ydir[i] = rand() % 2;
	}
}

void timebug(int i)
{
	int dx[2] = { -1, 1 };
	int dy[2] = { -1, 1 };
	if (vx[i] >= 0 && vy[i] >= 0) {
		bug_x[i] += dx[xdir[i]] * (vx[i] * dt - a*dt*dt / 2);
		vx[i] = vx[i] - a*dt;
		bug_y[i] += dy[ydir[i]] * (vy[i] * dt - a*dt*dt / 2);
		vy[i] = vy[i] - a*dt;
	}
	else {
		xdir[i] = rand() % 2;
		ydir[i] = rand() % 2;
		vx[i] = rand() % 80 + 5;
		vy[i] = rand() % 80 + 5;
		bug_x[i] += dx[xdir[i]] * (vx[i] * dt - a*dt*dt / 2);
		vx[i] = vx[i] - a*dt;
		bug_y[i] += dy[ydir[i]] * (vy[i] * dt - a*dt*dt / 2);
		vy[i] = vy[i] - a*dt;
	}	
}
