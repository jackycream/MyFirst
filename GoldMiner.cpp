#define _CRT_SECURE_NO_WARNINGS 1

#include <easyx.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int num = rand() % 4 + 5;
IMAGE imgs[5];
IMAGE mines[8];
int who;

void LoadResource(void)
{
	loadimage(imgs + 4, "./Goldminerphoto/bk.png", getwidth(), getheight() - 120);
	for (int i = 0; i < 4; i++)
	{
		char str[25] = { 0 };
		sprintf(str, "./Goldminerphoto/%d.png", i);
		loadimage(imgs + i, str, 50, 50);
		//putimage(i * 50, 0, imgs + i);
	}
}

enum Dir{LEFT,RIGHT};
enum Status{ST_Normal,ST_Long,ST_Short};
enum BumpInto{BINo,BIYes};

typedef struct Hook
{
	//开始点的坐标
	double x;
	double y;
	//结束点的坐标
	double ex;
	double ey;
	//钩子的长度
	double len;
	//钩子的角度
	double angle;
	//钩子的角度
	int dir;
	//速度分量
	double dx;
	double dy;
	//当前的状态
	int state;
	//是否碰到
	int bumpInto;
}Hook;

typedef struct Mine
{
	int x;
	int y;
}Mine;

Mine mines2[8];

void InitHook(Hook* hook,int x,int y,int len)
{
	hook->x = x;
	hook->y = y;
	hook->len = len;
	hook->ex = hook->x;
	hook->ey = hook->y + hook->len;
	hook->angle = 0.0;
	hook->dir = RIGHT;
	hook->dx = 0;
	hook->dy = 0;
	hook->state = ST_Normal;
	hook->bumpInto = BINo;
}

void DrawHook(Hook* hook)
{
	setlinestyle(PS_SOLID, 3);
	setlinecolor(BROWN);
	line(hook->x, hook->y, hook->ex, hook->ey);
	setfillcolor(WHITE);
	solidcircle(hook->ex, hook->ey, 5);
}

void SwingHook(Hook* hook)
{
	if (hook->state == ST_Normal)
	{
		if (hook->dir == RIGHT)
		{
			hook->angle += 0.1;
		}
		else if (hook->dir == LEFT)
		{
			hook->angle -= 0.1;
		}

		if (hook->angle > 90)
		{
			hook->dir = LEFT;
		}
		else if (hook->angle < -90)
		{
			hook->dir = RIGHT;
		}
		hook->ex = hook->x + sin((3.14159265 / 180) * hook->angle) * hook->len;
		hook->ey = hook->y + cos((3.14159265 / 180) * hook->angle) * hook->len;
	}
}

void ContorlHook(Hook* hook)
{
	int speed = 5;
	if (GetAsyncKeyState(VK_SPACE))
	{
		hook->state = ST_Long;
		hook->dx = sin((3.14159265 / 180) * hook->angle) * speed;
		hook->dy = cos((3.14159265 / 180) * hook->angle) * speed;
	}
	if (hook->state == ST_Long)
	{
		hook->ex += hook->dx;
		hook->ey += hook->dy;
		for (int i = 0; i < num; i++)
		{
			if (hook->ex >= mines2[i].x && hook->ex <= mines2[i].x + (mines+i)->getwidth() && hook->ey >= mines2[i].y && hook->ey <= mines2[i].y + (mines + i)->getheight())
			{
				who = i;
				hook->bumpInto = BIYes;
			}
		}
		if (hook->ex >= getwidth() || hook->ey >= getheight() || hook->ey <= 0 || hook->bumpInto == BIYes)
		{
			hook->state = ST_Short;
		}
	}
	else if (hook->state == ST_Short)
	{
		hook->ex -= hook->dx;
		hook->ey -= hook->dy;
		if (hook->bumpInto == BIYes)
		{
			mines2[who].x -= hook->dx;
			mines2[who].y -= hook->dy;
		}
		double dis = sqrt(pow(hook->x - hook->ex, 2) + pow(hook->y - hook->ey, 2));
		if (dis <= hook->len)
		{
			hook->state = ST_Normal;
			if (hook->bumpInto == BIYes)
			{
				//loadimage(mines + who, "./Goldminerphoto/white");
				mines2[who].x = 0;
				mines2[who].y = 0;
				hook->bumpInto = BINo;
			}
		}
	}
}

Hook gHook;

void Init(void)
{
	LoadResource();
	InitHook(&gHook, 500, 100, 60);
}

void Draw(void)
{
	putimage(0, 120, imgs + 4);
	setfillcolor(RGB(245, 204, 132));
	solidrectangle(0, 0, 1080, 120);
	DrawHook(&gHook);
	putimage(485, 55, imgs + 3);
}

void BuryMine()
{
	int random = 0;
	int x = 0;
	int y = 0;
	for (int i = 0; i < num; i++)
	{
		random = rand() % 3;
		char str[25] = { 0 };
		sprintf(str, "./Goldminerphoto/%d.png", random);
		loadimage(mines + i, str, 50, 50);
	}
	for (int i = 0; i < num; i++)
	{
		x = rand() % getwidth();
		while (x < 0 || x > getwidth() - ((mines + i)->getwidth()))
		{
			x = rand() % getwidth();
		}
		y = rand() % getheight();
		while (y < 120 || y > getheight() - ((mines + i)->getheight()))
		{
			y = rand() % getheight();
		}
		mines2[i].x = x;
		mines2[i].y = y;
		putimage(x, y, mines + i);
	}
}

void PutMine()
{
	for (int i = 0; i < num; i++)
	{
		putimage(mines2[i].x, mines2[i].y, mines + i);
	}
}
int judge(void)
{
	int count = 0;
	for (int i = 0; i < num; i++)
	{
		if (mines2[i].x == 0 && mines2[i].y == 0)
		{
			count++;
		}
	}
	if (count == num)
		return 1;
	return 0;
}

int main(void)
{
	srand((unsigned int)time(NULL));
	//创建窗口
	initgraph(1080, 640);
	
	Init();
	BuryMine();
	while (true)
	{
		cleardevice();
		Draw();
		PutMine();
		BeginBatchDraw();
		FlushBatchDraw();
		SwingHook(&gHook);
		ContorlHook(&gHook);
		if (judge())
		{
			closegraph();
			break;
		}
	}
	printf("你赢了!\n");

	return 0;
}