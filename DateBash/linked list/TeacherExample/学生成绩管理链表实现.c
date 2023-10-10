#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#define MAXSIZE 1024
typedef struct student
{
	char cno[10];
	char cname[10];
	int  score; 
}elemtype;

typedef struct node
{
	elemtype data;
	struct node *next;
}LinkList;

LinkList *Create_LinkListR();
int  Print_LinkList(LinkList *head);
int  LinkList_Length(LinkList *head);
void InsertBypos(LinkList *head);
void Insert(LinkList *head);
void DeleteBypos(LinkList *head);
void ShowMenu();
int SearchByName(LinkList *head);

//β�巨���������� (���ļ�����ԭʼ����)
LinkList *Create_LinkListR()
{
	elemtype ix;
	int i;
	LinkList *head,*p,*tail;
	FILE *fp;
	fp=fopen("D:\\score.txt","r+");
	head=(LinkList *)malloc(sizeof(LinkList));
	if(head==NULL)
	{
		return head;
	}
	head->next=NULL;
	tail=head;
	for(i=0;i<10;i++)
	{
		p=(LinkList *)malloc(sizeof(LinkList));
		if(p==NULL)
		{
			return head;
		}
		fscanf(fp,"%s%s%d",p->data.cno,p->data.cname,&p->data.score);
		tail->next=p;
		tail=p;
		tail->next=NULL;
	}
	fclose(fp);
	return head;	
}

//��Ϣ�������
int Print_LinkList(LinkList *head)
{
	LinkList *p;
	p=head->next;
	if(p==NULL)
	{
		return 0;
	}
	printf("%10s%10s%10s\n","ѧ��","����","�ɼ�");//�����ͷ
	while(p!=NULL)
	{
			
			printf("-----------------------------------\n"); 
			printf("%10s%10s%10d\n",p->data.cno,p->data.cname,p->data.score);
			p=p->next; 
	}
	printf("-----------------------------------\n");
} 

//�����ȵļ��� 
int  LinkList_Length(LinkList *head)
{
	LinkList *p=head;
	int j=0;
	while(p->next!=NULL)
	{
		p=p->next;
		j++;
	}
	return j;
} 

//����һ����ѧ������Ϣ����������Ϣλ������ָ���� 
void InsertBypos(LinkList *head)
{
	int pos,count=0;//pos��ʾ����ѧ����λ��
	LinkList *s,*p;
	char cno[10];
	Print_LinkList(head);
	printf("����������ѧ������Ϣ:\n");
	printf("λ��:");
	scanf("%d",&pos);
	s=(LinkList *)malloc(sizeof(LinkList));
	s->next=NULL; 
	while(1)
	{
		printf("ѧ��:");
		fflush(stdin);
		gets(cno);
		if(JudgeCnoValid(head,cno)==1)
		{
			strcpy(s->data.cno,cno);
			break;
		}
		else
		{
			printf("ѧ���ظ�������������!\n");
		}
	}	
	printf("����:");
	fflush(stdin);
	gets(s->data.cname);
	printf("�ɼ�:");
	scanf("%d",&s->data.score);
	//ͨ��ѭ�������ҵ�pos-1���λ��
	p=head;
	while(p->next!=NULL)
	{
		if(count==pos-1)
		{
			break;
		}
		count++;
		p=p->next;
	}
	//�������Ľ�㣬���뵽ԭ����������ȥ
	s->next=p->next;
	p->next=s; 
	Print_LinkList(head);
} 

//����һ����ѧ������Ϣ����������Ϣ����ԭ�������� 
void Insert(LinkList *head)
{
	LinkList *s,*p;
	char cno[10]; 
	p=head->next;
	Print_LinkList(head);
	while(p->next!=NULL)//ѭ���������ǲ������������һ����� 
	{
		p=p->next;
	}
	s=(LinkList *)malloc(sizeof(LinkList));
	s->next=NULL;
	printf("����������ѧ������Ϣ:\n");
	while(1)
	{
		printf("ѧ��:");
		fflush(stdin);
		gets(cno);
		if(JudgeCnoValid(head,cno)==1)
		{
			strcpy(s->data.cno,cno);
			break;
		}
		else
		{
			printf("ѧ���ظ�������������!\n");
		}
	}	
	printf("����:");
	fflush(stdin);
	gets(s->data.cname);
	printf("�ɼ�:");
	scanf("%d",&s->data.score);
	p->next=s;
	Print_LinkList(head);
}

//ɾ��ָ��λ�õĽ��
void DeleteBypos(LinkList *head)
{
	int pos,count=0;//��ʾ����ѧ����λ��
	LinkList *r,*p;
	Print_LinkList(head);
	printf("��������Ҫɾ��ѧ����λ��:\n");
	scanf("%d",&pos);
	//ͨ��ѭ�������ҵ�pos-1���λ��
	p=head;
	while(p->next!=NULL)
	{
		if(count==pos-1)
		{
			break;
		}
		count++;
		p=p->next;//pָ����ǵ�pos-1��λ�� 
	}
	r=p->next;//r����ָ����ǵ�pos��λ��
	p->next=r->next;
	Print_LinkList(head);
	free(r);	
} 

//�����ֲ���ѧ�� 
int SearchByName(LinkList *head)
{
	char name[10];
	int flag=0;
	LinkList *p=head->next;;
	if(p==NULL)
	{
		printf("ѧ����ϢΪ�գ�����ʧ�ܣ�\n");
		return 0;
	}
	printf("������Ҫ����ѧ��������:");
	fflush(stdin);
	gets(name);
	printf("%10s%10s%10s\n","ѧ��","����","�ɼ�");//�����ͷ
	while(p!=NULL)
	{
			if(strcmp(p->data.cname,name)==0)
			{
				flag=1;
				printf("--------------------------------\n"); 
				printf("%10s%10s%10d\n",p->data.cno,p->data.cname,p->data.score);				
			}
			p=p->next;			
	}
	if(flag==0)
	{
		printf("�����ڸ�ѧ��������ʧ�ܣ�\n");
		return 0;
	}
	printf("--------------------------------\n");
	return 1;
}

//ѧ�źϷ����жϣ�ѧ�ŵ�Ψһ�ԣ� 
int JudgeCnoValid(LinkList *head,char cno[]) 
{
	LinkList *p=head->next;
	while(p!=NULL)
	{
		if(strcmp(p->data.cno,cno)==0)
		{
			return 0;
		}
		p=p->next;
	}
	return 1;
}

//ϵͳ���ܲ˵� 
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

//�޸Ĺ��ܲ˵� 
void ModifyShowMenu()
{
	//system("CLS");
	printf("1.�޸�ѧ��\n");
	printf("2.�޸�����\n");
	printf("3.�޸ĳɼ�\n");
	printf("0.�˳�ϵͳ\n");
	printf("���������ѡ��:");
}

//ѧ����Ϣ�޸�
int main()
{
	LinkList *head;
	int choice,pos;
	head=Create_LinkListR();//ͷ�巨��������ԭʼ���ݴ��ļ��е��롣 
	while(1)
	{
		//������ܲ˵�
		ShowMenu();
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: InsertBypos(head);system("PAUSE");break;
			case 2: DeleteBypos(head);system("PAUSE");break;
			case 3: SearchByName(head);system("PAUSE");break;
			case 4: //ModifyStuInfo(StuList);system("PAUSE");break;
			case 5: Print_LinkList(head);system("PAUSE");break;
			case 0: printf("Bye bye!");return 0;
		} 
	}
	return 0;
}


