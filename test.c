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
	printf("1.ע��\n");
	printf("2.ɾ��\n");
	printf("3.�޸�\n");
	printf("4.��¼\n");
	printf("0.�˳�\n");
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
	printf("����������(������%d��,�����ַ�):", NAMEMAX);
	SRet = scanf("%s", (game->people + game->size)->name);
	printf("����������(������%d��,��������,���ո�,�����Ǹ���):", PASSWORDMAX);
	SRet = scanf("%d", &((game->people + game->size)->password));
	game->size++;
}

void DeleteAccount(Account* game)
{
	char peoplename[NAMEMAX + 1] = { 0 };
	printf("������Ҫɾ���˺ŵ�����:");
	SRet = scanf("%s", peoplename);
	int pos = FindAccount(peoplename, game);
	if (pos == -2)
	{
		printf("%c", c);
		printf("û�ж�������ɾ!\n");
		return;
	}
	if (pos == -1)
	{
		printf("%c", c);
		printf("Ҫɾ���˺Ų�����!\n");
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
	printf("ɾ���ɹ�!\n");
}

void ReviseAccount(Account* game)
{
	char peoplename[NAMEMAX + 1] = { 0 };
	printf("������Ҫ�޸ĵ��˺ŵ�����:");
	SRet = scanf("%s", peoplename);
	int pos = FindAccount(peoplename, game);
	if (-2 == pos)
	{
		printf("%c", c);
		printf("û�ж��������޸�!\n");
		return;
	}
	if (-1 == pos)
	{
		printf("%c", c);
		printf("Ҫ�޸ĵ��˺Ų�����!\n");
		return;
	}
	printf("����������(������%d��,�����ַ�):", NAMEMAX);
	SRet = scanf("%s", (game->people + pos)->name);
	printf("����������(������%d��,��������,���ո�,�����Ǹ���):", PASSWORDMAX);
	SRet = scanf("%d", &((game->people + pos)->password));
	printf("�޸ĳɹ�!\n");
}

int LoginAccount(Account* game)
{
	char peoplename[NAMEMAX + 1] = { 0 };
	printf("������Ҫ��¼���˺ŵ�����:");
	SRet = scanf("%s", peoplename);
	int pos = FindAccount(peoplename, game);
	if (-2 == pos)
	{
		printf("%c", c);
		printf("û�ж������Ե�¼!\n");
		return 0;
	}
	if (-1 == pos)
	{
		printf("%c", c);
		printf("Ҫ��¼���˺Ų�����!\n");
		return 0;
	}
	int password = 0;
	printf("����������:");
	scanf("%d", &password);
	if (password == (game->people + pos)->password)
	{
		printf("��¼�ɹ�!\n");
		return 1;
	}
	else 
	{
		printf("%c", c);
		printf("�������,�ڿ�����!\n");
		return 0;
	}
}

void FightingWineMenu(void)
{
	printf("1.����\n");
	printf("2.�ۿ�Ǯ��\n");
	printf("3.�ۿ�ʣ��ɶ�������\n");
	printf("0.�˳�\n");
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
		printf("�㵱ǰ�ľ���Ϊ�ٷ�֮%d\n", wine);
		printf("�Ƿ�Ҫ������(0��ֹͣ,�����Ǽ�����):");
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
		printf("��ϲ,Ӯ��%dԪ!\n", money2);
		money += money2;
	}
	else
	{
		money -= random(8, 14);
		printf("����ʧ��!\n");
	}
}

void FightingWine(void)
{
	int input = 0;
	srand((unsigned int)time(NULL));

	printf("����:������(��ʾ:����%d�˶���,���������ڵ��ڰٷ�֮100����,�Ӱٷ�֮40~�ٷ�֮60�ľ�����ʼ,ÿ��������Ӿ���,��1������,��0ֹͣ,ֹͣʱ����Խ��,Ǯ��Ŀ�����Խ��)\n", PEOPLENUM);
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
				printf("���������,�޷���������!\n");
			}
			break;
		case 2:
			printf("%d\n", money);
			break;
		case 3:
			printf("%d\n", people);
			break;
		case 0:
			printf("�˳�!\n");
			break;
		default:
			printf("%c", c);
			printf("�������,����������!\n");
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
	printf("��Ϸ:������\n");
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
			printf("�˳�\n");
			judge = 0;
			break;
		default:
			printf("%c", c);
			printf("�������,����������!\n");
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