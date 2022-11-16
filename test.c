#define _CRT_SECURE_NO_WARNINGS 1
#define PEOPLENUM 10
#define NAMEMAX 15
#define PASSWORDMAX 10

#define random(smallest,biggest) (rand() % (biggest - smallest + 1)) + smallest

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct PeopleInfo
{
	char name[NAMEMAX + 1];
	int password;
}PeopleInfo;

typedef struct Account
{
	PeopleInfo* people;
	int size;
	int capacity;
}Account;

int SRet = 0;

int money = 0;
int people = PEOPLENUM;
char c = 7;

void Menu(void)
{
	printf("1.注册\n");
	printf("2.删除\n");
	printf("3.修改\n");
	printf("4.登录\n");
	printf("0.退出\n");
}

int FindAccount(char* peoplename, Account* game)
{
	int count = 0;
	if (game->people == NULL)
	{
		return -2;
	}
	while ((game->people + count)->password > 0)
	{
		if (!strcmp(peoplename, (game->people + count)->name))
		{
			return count;
		}
		count++;
	}

	return -1;
}

void InitAccount(Account* game)
{
	game->people = NULL;
	game->size = 0;
	game->capacity = 0;
}

void EnrollAccount(Account* game)
{
	if (game->size == game->capacity)
	{
		int newcapacity = game->capacity > 0 ? game->capacity + 3 : 4;
		game->people = (PeopleInfo*) realloc(game->people,newcapacity * sizeof(PeopleInfo));
		assert(game->people != NULL);
		game->capacity = newcapacity;
	}
	printf("请输入名字(不超过%d个,都是字符):", NAMEMAX);
	SRet = scanf("%s", (game->people + game->size)->name);
	printf("请输入密码(不超过%d个,都是数字,不空格,不能是负数):", PASSWORDMAX);
	SRet = scanf("%d", &((game->people + game->size)->password));
	game->size++;
}

void DeleteAccount(Account* game)
{
	char peoplename[NAMEMAX + 1] = { 0 };
	printf("请输入要删的账号的名字:");
	SRet = scanf("%s", peoplename);
	int pos = FindAccount(peoplename, game);
	if (pos == -2)
	{
		printf("%c", c);
		printf("没有东西可以删!\n");
		return;
	}
	if (pos == -1)
	{
		printf("%c", c);
		printf("要删的账号不存在!\n");
		return;
	}
	int cur = 0;
	if ((game->people) + cur + 1)
	{
		cur++;
	}
	strcpy((game->people + pos)->name, (game->people + cur)->name);
	(game->people + pos)->password = (game->people + cur)->password;
	game->size--;
	printf("删除成功!\n");
}

void ReviseAccount(Account* game)
{
	char peoplename[NAMEMAX + 1] = { 0 };
	printf("请输入要修改的账号的名字:");
	SRet = scanf("%s", peoplename);
	int pos = FindAccount(peoplename, game);
	if (-2 == pos)
	{
		printf("%c", c);
		printf("没有东西可以修改!\n");
		return;
	}
	if (-1 == pos)
	{
		printf("%c", c);
		printf("要修改的账号不存在!\n");
		return;
	}
	printf("请输入名字(不超过%d个,都是字符):", NAMEMAX);
	SRet = scanf("%s", (game->people + pos)->name);
	printf("请输入密码(不超过%d个,都是数字,不空格,不能是负数):", PASSWORDMAX);
	SRet = scanf("%d", &((game->people + pos)->password));
	printf("修改成功!\n");
}

int LoginAccount(Account* game)
{
	char peoplename[NAMEMAX + 1] = { 0 };
	printf("请输入要登录的账号的名字:");
	SRet = scanf("%s", peoplename);
	int pos = FindAccount(peoplename, game);
	if (-2 == pos)
	{
		printf("%c", c);
		printf("没有东西可以登录!\n");
		return 0;
	}
	if (-1 == pos)
	{
		printf("%c", c);
		printf("要登录的账号不存在!\n");
		return 0;
	}
	int password = 0;
	printf("请输入密码:");
	scanf("%d", &password);
	if (password == (game->people + pos)->password)
	{
		printf("登录成功!\n");
		return 1;
	}
	else 
	{
		printf("%c", c);
		printf("密码错误,黑客入侵!\n");
		return 0;
	}
}

void FightingWineMenu(void)
{
	printf("1.斗酒\n");
	printf("2.观看钱数\n");
	printf("3.观看剩余可斗酒人数\n");
	printf("0.退出\n");
}

void DrinkWine(void)
{
	int money2 = 0;
	int input = 0;
	int judge = 0;
	int wine = random(40, 60);
	while (1)
	{
		if (wine >= 100)
		{
			judge = 0;
			break;
		}
		money2 += random(1,3);
		printf("你当前的酒量为百分之%d\n", wine);
		printf("是否要继续喝(0是停止,其他是继续喝):");
		SRet = scanf("%d", &input);
		if (!input)
		{
			judge = 1;
			break;
		}
		wine += random(5, 17);
	}
	if (judge)
	{
		printf("恭喜,赢了%d元!\n", money2);
		money += money2;
	}
	else
	{
		money -= random(8, 14);
		printf("斗酒失败!\n");
	}
}

void FightingWine(void)
{
	int input = 0;
	srand((unsigned int)time(NULL));

	printf("任务:斗斗酒(提示:可与%d人斗酒,若酒量大于等于百分之100则输,从百分之40~百分之60的酒量开始,每次随机增加酒量,按1继续喝,按0停止,停止时酒量越大,钱多的可能性越大)\n", PEOPLENUM);
	do
	{
		FightingWineMenu();
		SRet = scanf("%d", &input);
		switch (input)
		{
		case 1:
			if (people > 0)
			{
				DrinkWine();
				people--;
			}
			else
			{
				printf("%c", c);
				printf("任务已完成,无法继续斗酒!\n");
			}
			break;
		case 2:
			printf("%d\n", money);
			break;
		case 3:
			printf("%d\n", people);
			break;
		case 0:
			printf("退出!\n");
			break;
		default:
			printf("%c", c);
			printf("输入错误,请重新输入!\n");
			break;
		}
	} while (input);
}

int main(void)
{	
	int judge = 1;
	Account game;
	InitAccount(&game);
	int input = 0;
	printf("游戏:大话西游\n");
	while (1)
	{
		Menu();
		SRet = scanf("%d", &input);
		switch (input)
		{
		case 1:
			EnrollAccount(&game);
			break;
		case 2:
			DeleteAccount(&game);
			break;
		case 3:
			ReviseAccount(&game);
			break;
		case 4:
			judge = LoginAccount(&game);
			break;
		case 0:
			printf("退出\n");
			judge = 0;
			break;
		default:
			printf("%c", c);
			printf("输入错误,请重新输入!\n");
			break;
		}
		if (input == 0)
		{
			break;
		}
		if (input == 4 && judge == 1)
		{
			break;
		}
	}

	if (judge == 1)
	{
		FightingWine();
	}

	return 0;
}