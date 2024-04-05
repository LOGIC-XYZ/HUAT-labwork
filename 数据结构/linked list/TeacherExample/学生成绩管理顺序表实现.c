#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1024
typedef struct student
{
	char cno[10];
	char cname[10];
	int score;
} elemtype;

typedef struct stuscorelist
{
	elemtype data[MAXSIZE];
	int last;
} StuScoreList;
StuScoreList *Init_StuScoreList();
int StuScoreList_Length(StuScoreList *L);
int Insert_StuScoreList(StuScoreList *L);
int Delete_StuScoreList(StuScoreList *L);
void ShowMenu();
void LoadInitData(StuScoreList *L);
void Print(StuScoreList *L);
void SearchByName(StuScoreList *L);
int JudgeCnoValid(StuScoreList *L, char cno[]);
int ModifyStuInfo(StuScoreList *L);
// ��ʼ��˳���
StuScoreList *Init_StuScoreList()
{
	StuScoreList *L;
	L = (StuScoreList *)malloc(sizeof(StuScoreList));
	if (L != NULL)
	{
		L->last = -1;
	}
	return L;
}

int StuScoreList_Length(StuScoreList *L)
{
	return L->last + 1;
}
// ��ָ��λ�ò���ѧ����Ϣ
int Insert_StuScoreList(StuScoreList *L)
{
	int i, j;
	elemtype x;
	if (L->last >= MAXSIZE - 1)
	{
		return 0;
	}
	Print(L);
	printf("����Ҫ�����λ�ã�");
	scanf("%d", &i);
	if (i < 1 || i > L->last + 2)
	{
		return -1;
	}
	while (1)
	{
		printf("������ѧ������Ϣ:\n");
		printf("ѧ��:");
		fflush(stdin);
		gets(x.cno);
		if (JudgeCnoValid(L, x.cno) == 1)
		{
			printf("����:");
			fflush(stdin);
			gets(x.cname);
			printf("�ɼ�:");
			scanf("%d", &x.score);
			break;
		}
		else
		{
			printf("ѧ���ظ������������룡\n");
			system("PAUSE");
			continue;
		}
	}
	for (j = L->last; j >= i - 1; j--)
	{
		L->data[j + 1] = L->data[j];
	}
	L->data[i - 1] = x;
	L->last++;
	Print(L);
	return 1;
}
// ɾ��ָ��λ�õ�ѧ����Ϣ
int Delete_StuScoreList(StuScoreList *L)
{
	int i, j;
	Print(L);
	printf("����Ҫɾ��ѧ����λ�ã�");
	scanf("%d", &i);
	if (i < 1 || i > L->last + 1)
	{
		return 0;
	}
	else
	{
		for (j = i; j <= L->last; j++)
		{
			L->data[j - 1] = L->data[j];
		}
		L->last--;
	}
	Print(L);
	return 1;
}

// ϵͳ���ܲ˵�
void ShowMenu()
{
	system("CLS");
	printf("��ӭʹ��ѧ���ɼ�����ϵͳ\n");
	printf("1.����ѧ����Ϣ\n");
	printf("2.ɾ��ѧ����Ϣ\n");
	printf("3.����ѧ����Ϣ\n");
	printf("4.�޸�ѧ����Ϣ\n");
	printf("5.��ʾѧ����Ϣ\n");
	printf("0.�˳�ϵͳ\n");
	printf("���������ѡ��:");
}
// ���ļ�����ԭʼ��������
void LoadInitData(StuScoreList *L)
{
	FILE *fp;
	fp = fopen("D:\\score.txt", "r+");
	int i;
	for (i = 0; i < 10; i++)
	{
		fscanf(fp, "%s%s%d", L->data[i].cno, L->data[i].cname, &L->data[i].score);
		L->last++;
	}
	fclose(fp);
}

// ѧ����Ϣ���
void Print(StuScoreList *L)
{
	int i;
	if (L->last == -1)
	{
		return;
	}
	printf("%10s%10s%10s\n", "ѧ��", "����", "�ɼ�"); // �����ͷ
	for (i = 0; i <= L->last; i++)
	{

		printf("--------------------------------\n");
		printf("%10s%10s%10d\n", L->data[i].cno, L->data[i].cname, L->data[i].score);
	}
	printf("--------------------------------\n");
}
// �����ֲ���ѧ��
void SearchByName(StuScoreList *L)
{
	int i;
	char name[10];
	if (L->last == -1)
	{
		printf("ѧ����ϢΪ�գ�����ʧ�ܣ�\n");
		return;
	}
	printf("������Ҫ����ѧ��������:");
	fflush(stdin);
	gets(name);
	printf("%10s%10s%10s\n", "ѧ��", "����", "�ɼ�"); // �����ͷ
	for (i = 0; i <= L->last; i++)
	{
		if (strstr(L->data[i].cname, name) != 0)
		{
			printf("--------------------------------\n");
			printf("%10s%10s%10d\n", L->data[i].cno, L->data[i].cname, L->data[i].score);
		}
	}
	printf("--------------------------------\n");
}
// ѧ�źϷ����жϣ�ѧ�ŵ�Ψһ�ԣ�
int JudgeCnoValid(StuScoreList *L, char cno[])
{
	int i;
	for (i = 0; i <= L->last; i++)
	{
		if (strcmp(L->data[i].cno, cno) == 0)
		{
			return 0;
		}
	}
	return 1;
}
// �޸Ĺ��ܲ˵�
void ModifyShowMenu()
{
	// system("CLS");
	printf("1.�޸�ѧ��\n");
	printf("2.�޸�����\n");
	printf("3.�޸ĳɼ�\n");
	printf("0.�˳�ϵͳ\n");
	printf("���������ѡ��:");
}

// ѧ����Ϣ�޸�
int ModifyStuInfo(StuScoreList *L)
{
	char cno[10];
	int i, pos = -1, choice;
	if (StuScoreList_Length(L) == 0)
	{
		printf("ѧ���ɼ���Ϣ��Ϊ�գ��޸�ʧ��!\n");
		return 0;
	}
	else
	{
		// ���ҵ�Ҫ�޸ĵ�ѧ����Ϣ
		printf("������Ҫ����ѧ����ѧ��:");
		fflush(stdin);
		gets(cno);
		// ��ʼ�ж�����ѧ����Ϣ�����Ƿ���ڸ�ѧ��
		printf("%10s%10s%10s\n", "ѧ��", "����", "�ɼ�"); // �����ͷ
		for (i = 0; i <= L->last; i++)
		{
			if (strcmp(L->data[i].cno, cno) == 0)
			{
				printf("--------------------------------\n");
				printf("%10s%10s%10d\n", L->data[i].cno, L->data[i].cname, L->data[i].score);
				pos = i;
				break;
			}
		}
		printf("--------------------------------\n");
		if (pos == -1)
		{
			printf("��ѧ�������ڣ��޸�ʧ�ܣ�\n");
			return 0;
		}
		else
		{ // ��ɶԸ�����Ϣ���޸�
			ModifyShowMenu();
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:
				while (1)
				{
					printf("�������µ�ѧ��:");
					fflush(stdin);
					gets(cno);
					if (JudgeCnoValid(L, cno) == 1)
					{ // ѧ�Ų��ظ��������޸ġ�
						strcpy(L->data[pos].cno, cno);
						break;
					}
					else
					{
						continue;
					}
				}
				break;
			case 2:
				printf("�������µ�����:");
				fflush(stdin);
				gets(L->data[pos].cname);
				break;
			case 3:
				printf("�������µĳɼ�:");
				fflush(stdin);
				scanf("%d", &L->data[pos].score);
				break;
			}
			printf("�޸ĳɹ���\n");
			return 1;
		}
	}
}

int main()
{
	StuScoreList *StuList;
	int choice, pos;
	StuList = Init_StuScoreList();
	LoadInitData(StuList);
	while (1)
	{
		// ������ܲ˵�
		ShowMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Insert_StuScoreList(StuList);
			system("PAUSE");
			break;
		case 2:
			Delete_StuScoreList(StuList);
			system("PAUSE");
			break;
		case 3:
			SearchByName(StuList);
			system("PAUSE");
			break;
		case 4:
			ModifyStuInfo(StuList);
			system("PAUSE");
			break;
		case 5:
			Print(StuList);
			system("PAUSE");
			break;
		case 0:
			printf("Bye bye!");
			return 0;
		}
	}
	return 0;
}
