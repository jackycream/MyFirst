#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <time.h>
#include <easyx.h>

#define STRINGNUM 20
#define RAINNUM 128
#define CHARWIDTH 15
#define STARNUM 5
#define SCREEN_TIME_PER_FRAME 1000 / 100

struct Rain
{
	int speed;
	int x;
	int y;
	char str[STRINGNUM];
}rains[RAINNUM];
struct Star
{
	int x;
	int y;
	int h;
	int w;
	int speedx,speedy;
	POINT five[STARNUM];
}stars[STARNUM];

char CreateChar(void)
{
	short s = rand() % 3;
	if (s == 0)
	{
		//·µ»ØÊý×Ö×Ö·û
		return '0' + rand() % 10;
	}
	else if (s == 1)
	{
		//·µ»Ø´óÐ´×ÖÄ¸×Ö·û
		return 'A' + rand() % 26;
	}
	else
	{
		//·µ»ØÐ¡Ð´×ÖÄ¸×Ö·û
		return 'a' + rand() % 26;
	}
}

void InitRain(void)
{
	for (int i = 0; i < RAINNUM; i++)
	{
		rains[i].x = 0;
		rains[i].y = rand() % getheight();
		rains[i].speed = rand() % 3 + 1;
		for (int j = 0; j < STRINGNUM - 1; j++)
		{
			rains[i].str[j] = CreateChar();
		}
	}
}

void DrawRain(void)
{
	for (int i = 0; i < RAINNUM; i++)
	{
		for (int j = 0; j < STRINGNUM; j++)
		{
			settextcolor(RGB(0, 255 - j * 13, 0));
			outtextxy(rains[i].x + i * CHARWIDTH,rains[i].y - j * CHARWIDTH,rains[i].str[j]);
		}
	}
}

void ChangeChar(void)
{
	for (int i = 0; i < RAINNUM; i++)
	{
		rains[i].str[rand() % STRINGNUM] = CreateChar();
	}
}

void Rainning(void)
{
	for (int i = 0; i < RAINNUM; i++)
	{
		rains[i].y += rains[i].speed;
		if (rains[i].y - STRINGNUM * CHARWIDTH > getheight())
		{
			rains[i].y = 0;
			rains[i].speed = rand() % 3 + 1;
		}
	}
}

void AssignmentStar(int x,int y,int num,int w,int h)
{
	stars[num].five[0] = { x,y + h / 5 * 2 };
	stars[num].five[1] = { x + w / 5, y + h };
	stars[num].five[2] = { x + w / 5 * 4, y + h };
	stars[num].five[3] = { x + w,y + h / 5 * 2 };
	stars[num].five[4] = { x + w / 2, y };
}

void InitStar(int x, int y, int h, int w, int num)
{
	stars[num].x = x;
	stars[num].y = y;
	stars[num].h = h;
	stars[num].w = w;
	stars[num].speedx = rand() % 5 + 1;
	stars[num].speedy = rand() % 5 + 1;
	AssignmentStar(x,y,num, w, h);
}

void DrawStar(int num)
{
	line(stars[num].five[0].x, stars[num].five[0].y, stars[num].five[3].x, stars[num].five[3].y);
	line(stars[num].five[3].x, stars[num].five[3].y, stars[num].five[1].x, stars[num].five[1].y);
	line(stars[num].five[1].x, stars[num].five[1].y, stars[num].five[4].x, stars[num].five[4].y);
	line(stars[num].five[4].x, stars[num].five[4].y, stars[num].five[2].x, stars[num].five[2].y);
	line(stars[num].five[2].x, stars[num].five[2].y, stars[num].five[0].x, stars[num].five[0].y);
}

//void DrawFiveStar(int x, int y, int h, int w)
//{
//	POINT star[5] = {
//					{x,				  y + h / 5 * 2},
//					{x + w / 5, y + h		     },
//					{x + w / 5 * 4, y + h		     },
//					{x + w,			  y + h / 5 * 2},
//					{x + w / 2, y		         }
//					};
//	line(star[0].x, star[0].y, star[3].x, star[3].y);
//	line(star[3].x, star[3].y, star[1].x, star[1].y);
//	line(star[1].x, star[1].y, star[4].x, star[4].y);
//	line(star[4].x, star[4].y, star[2].x, star[2].y);
//	line(star[2].x, star[2].y, star[0].x, star[0].y);
//}



void MoveStar(int num)
{
	stars[num].x += stars[num].speedx;
	stars[num].y += stars[num].speedy;
	if (stars[num].x + stars[num].w >= getwidth() || stars[num].x <= 0)
	{
		stars[num].speedx *= -1;
	}
	if (stars[num].y + stars[num].h >= getheight() || stars[num].y <= 0 )
	{
		stars[num].speedy *= -1;
	}
	
	
	AssignmentStar(stars[num].x,stars[num].y, num, stars[num].w, stars[num].h);
	DrawStar(num);
}

int main(void)
{
	initgraph(960, 640);
	srand((unsigned int)time(NULL));
	InitRain();
	setbkmode(TRANSPARENT);
	BeginBatchDraw();
	InitStar(getheight() / 2, getwidth() / 2, 50, 50, 0);
	InitStar(getheight() / 2, getwidth() / 2, 100, 100, 1);
	InitStar(getheight() / 2, getwidth() / 2, 25, 25, 2);
	
	while (true)
	{
		int startTime = time(NULL);
		cleardevice();
		//DrawFiveStar(300, 200, 50, 50);
		DrawRain();
		ChangeChar();
		//DrawStar(1);
		Rainning();
		MoveStar(0);
		MoveStar(1);
		MoveStar(2);
		
		FlushBatchDraw();
		int frameTime = time(NULL) - startTime;
		if (frameTime < SCREEN_TIME_PER_FRAME)
		{
			Sleep(SCREEN_TIME_PER_FRAME - frameTime);
		}
	}

	return 0;
}