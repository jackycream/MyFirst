#define _CRT_SECURE_NO_WARNINGS 1
#define PI 3.14159265358979323846264338327950238

#include <stdio.h>
#include <easyx.h>

int main(void)
{
	//创建图形界面窗口
	initgraph(400, 450);
	//重置坐标原点
	setorigin(getwidth() / 2, getheight() / 2);
	//设置背景颜色
	setbkcolor(WHITE);
	//清空一下
	cleardevice();
	//画哆啦A梦
	//画哆啦A梦头
	setfillcolor(RGB(7, 190, 234));
	setlinecolor(BLACK);
	fillroundrect(-135, -206, 135, 54, 248, 248);
	Sleep(1000);
	//画哆啦A梦脸
	setfillcolor(WHITE);
	fillellipse(-115, -145, 115, 46);
	Sleep(1000);
	//画哆啦A梦之左眼眶
	fillroundrect(-63, -169, 0, -95, 56, 56);
//	Sleep(1000);
	//画哆啦A梦之右眼眶
	fillroundrect(63, -169, 0, -95, 56, 56);
	Sleep(1000);
	//------------------
	setfillcolor(BLACK);
	//画哆啦A梦之左眼珠
	solidcircle(-16, -116, 6);
//	Sleep(1000);
	//画哆啦A梦之右眼珠
	solidcircle(16, -116, 6);
	Sleep(1000);
	//画哆啦A梦之鼻子
	setfillcolor(RGB(201, 62, 0));
	fillcircle(0, -92, 15);
	Sleep(1000);
	//画哆啦A梦之人中
	line(0, -75, 0, 0);
	Sleep(1000);
	//画哆啦A梦之迷之微笑
	arc(-110, -220, 110, 0, (PI * 5) / 4, (PI * 7) / 4);
	Sleep(1000);
	//画哆啦A梦之胡子
	line(-42, -73, -90, -91);
//	Sleep(1000);
	line(42, -73, 90, -91);
	Sleep(1000);
	line(-41, -65, -92, -65);
//	Sleep(1000);
	line(41, -65, 92, -65);
	Sleep(1000);
	line(-42, -57, -90, -39);
//	Sleep(1000);
	line(42, -57, 90, -39);
	Sleep(1000);
	//画哆啦A梦之身体
	//画哆啦A梦之手臂
	line(-81, 32, -138, 72);
//	Sleep(1000);
	line(81, 32, 138, 72);
	Sleep(1000);
	line(-96, 96, -116, 110);
//	Sleep(1000);
	line(96, 96, 116, 110);
	Sleep(1000);
	line(-96, 85, -96, 178);
//	Sleep(1000);
	line(96, 85, 96, 178);
	Sleep(1000);
	arc(-10, 168, 10, 188, 0, PI);
	Sleep(1000);
	setfillcolor(WHITE);
	fillcircle(-140, 99, 27);
//	Sleep(1000);
	fillcircle(140, 99, 27);
	Sleep(1000);
	fillroundrect(-2, 178, -112, 205, 24, 24);
//	Sleep(1000);
	fillroundrect(2, 178, 112, 205, 24, 24);
	Sleep(1000);
	setfillcolor(RGB(7, 190, 234));
	floodfill(0, 100, BLACK);
	Sleep(1000);
	setfillcolor(WHITE);
	fillcircle(0, 81, 75);
	solidrectangle(-60, 4, 60, 24);
	Sleep(1000);
	pie(-58, 23, 58, 139, PI, 0);
	Sleep(1000);
	setfillcolor(RGB(169, 38, 0));
	fillroundrect(-100, 23, 100, 42, 12, 12);
	Sleep(1000);
	setfillcolor(RGB(245, 237, 38));
	fillcircle(0, 49, 19);
	setfillcolor(BLACK);
	solidellipse(-4, 50, 4, 57);
	setlinestyle(PS_SOLID, 3);
	line(0, 57, 0, 68);
	setlinestyle(PS_SOLID, 1);
	line(-16, 40, 16, 40);
	line(-18, 44, 18, 44);

	//防止图形界面窗口消失
	char c = getchar();
	//关闭图形界面窗口
	closegraph();

	return 0;
}