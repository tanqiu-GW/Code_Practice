#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUM 37
struct student
{     long term;          //ѧ��
      long num;          //ѧ��
      int classes;      //�༶
      char name[10];   //����
      int score[4];
      int sum; 
      float average;  
}stu[NUM];
void zcd();

/*������Ϣ����*/
void input()
{
    int i;
	char a;
	system("cls");
   for(i=0;i<NUM;i++)
	{  printf(" \n������ѧ����ѧ�ڣ�");
	   scanf("%ld",&stu[i].term);
      
      printf(" \n������ѧ����ѧ�ţ�");
	  fflush(stdin);
	  scanf("%ld",&stu[i].num);
	  
	  printf(" \n������ѧ���İ༶��");
	  scanf("%d",&stu[i].classes);
	  
	  printf("\n������ѧ����������");
	  scanf("%s", stu[i].name) ;
	  
	  printf("\n������ѧ�������ĳɼ���");
	  scanf("%d",&stu[i].score[0]);
	  
	  printf("\n������ѧ������ѧ�ɼ���");
	  scanf("%d", &stu[i].score[1]);	 
	   printf("\n������ѧ����Ӣ��ɼ���");
      scanf("%d", &stu[i].score[2]);
      
	  printf("\n������ѧ���ļ�����ɼ���");
	  scanf("%d", &stu[i].score[3]);
	
	   stu[i].sum=stu[i].score[0]+stu[i].score[1]+stu[i].score[2]+stu[i].score[3];//���ֺܷ�ƽ��
       stu[i].average=(float)stu[i].sum/4.0;

	   printf("�Ƿ�Ҫ�������(��N&n�˳�)");
	   fflush(stdin);//����������뻺��

	  a=getchar();
	  if(a=='n'||a=='N')
		 break;
	}
}


void print()
{
	int i;
	printf("ѧ��\t����\t�༶ ���� ��ѧ Ӣ�� ����� �ܷ� ƽ����\n");
	for(i=0;i<NUM;i++)
	{
	  
	  {
		  stu[i].sum=stu[i].score[0]+stu[i].score[1]+stu[i].score[2]+stu[i].score[3];
          stu[i].average=(float)stu[i].sum/4.0;
          printf("%d\t%s\t%d%5d%5d%5d%6d%7d%8.2f\n",stu[i].num,stu[i].name,stu[i].classes,
		  stu[i].score[0],stu[i].score[1],stu[i].score[2], stu[i].score[3],stu[i].sum,stu[i].average); /*���ѧ����Ϣ*/
	  }
	}
	
	system("pause");
}




/*���Ҳ���ʾһ����¼*/ 
void search_num() 
{ 
   int number=0,i;  //ע�ⶨ��Ҫ������ǰ��
   system("cls");/*����*/
    
   printf("\t\t\t ������Ҫ����ѧ����ѧ��:");  
   scanf("%d",&number);
   printf("ѧ��\t����\t�༶ ���� ��ѧ Ӣ�� ����� �ܷ� ƽ����\n");

	for(i=0;i<NUM;i++)
	{
		if (number == stu[i].num)
		{
			printf("%d\t%s\t%d%5d%5d%5d%6d%7d%8.2f\n", stu[i].num, stu[i].name, stu[i].classes,
			stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].score[3], stu[i].sum, stu[i].average); /*���ѧ����Ϣ*/
			break;
		}
		else
		{
			printf("û�ҵ���ѧ������Ϣ\n");
		}
	}

	system("pause");
}

 /*���Ҳ���ʾһ����¼*/ 
void search_name() 
{
	int i;  //ע�ⶨ��Ҫ������ǰ��
	char name[10] = { 0 };
	system("cls");/*����*/

	printf("\t\t\t ������Ҫ����ѧ��������:");
	fgets(name, 10, stdin);
	printf("ѧ��\t����\t�༶ ���� ��ѧ Ӣ�� ����� �ܷ� ƽ����\n");

	for (i = 0; i < NUM; i++)
	{
		if (strcmp(name, stu[i].name) == 0)	//�Ƚ��ַ�������������
		{
			printf("%d\t%s\t%d%5d%5d%5d%6d%7d%8.2f\n", stu[i].num, stu[i].name, stu[i].classes,
			stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].score[3], stu[i].sum, stu[i].average); /*���ѧ����Ϣ*/
			break;
		}
		else
		{
			printf("û�ҵ���ѧ������Ϣ\n");
		}
	}

	system("pause");
}

/*ð������*/
void BubbleSort(int arr[], int num[], int length) 
{ 
	int temp = 0, temp2 = 0;
	int i = 0, j = 0;

	for (; i < length; i++) 
	{ 
		for (; j < length - i - 1; j++)
		{ 
			if (arr[j] > arr[j + 1])	//�����ֵܷ�������ȷ��ÿλͬѧ��ŵ�����
			{ 							//�����ܷ���ߵ�35��ͬѧ������ð�����������˵�һλ
				temp = arr[j + 1];
				temp2 = num[j + 1];
				arr[j + 1] = arr[j];
				num[j + 1] = num[j];
				arr[j] = temp;
				num[j] = temp;
			} 
		} 
	} 
}
/*�����ִܷӸߵ�������ÿλͬѧ����Ϣ*/
void sort_totalscore(void)
{
	int sum[37] = { 0 }, num[37] = { 0 };
	int i = 0;
	system("cls");/*����*/

	for (; i < NUM; i++)
	{
		sum[i] = stu[i].sum;	//��¼ÿλͬѧ���ܷ�
		num[i] = stu[i].num;	//��¼ÿλͬѧ�����
	}

	BubbleSort(sum, num, NUM);

	for (i = 0; i < NUM; i++)
	{
		printf("%d\t%s\t%d%5d%5d%5d%6d%7d%8.2f\n", stu[num[i]].num, stu[num[i]].name, stu[num[i]].classes,
			stu[num[i]].score[0], stu[num[i]].score[1], stu[num[i]].score[2], stu[num[i]].score[3], stu[num[i]].sum, stu[num[i]].average); /*���ѧ����Ϣ*/
	}

	system("pause");
}
/*��ÿ����Ŀ��߷֣�����ӡ��Ŀ��߷ֻ���ߵ���ţ��������༶*/
void highestscore(void)
{
	int max_score[4] = { 0 }, max_count[4] = { 0 };
	int i = 0;

	system("cls");/*����*/
	for (; i < NUM; i++)
	{
		if (stu[i].score[0] > max_score[0])
		{
			max_score[0] = stu[i].score[0];
			max_count[0] = i;
		}
		if (stu[i].score[1] > max_score[1])
		{
			max_score[1] = stu[i].score[1];
			max_count[1] = i;
		}
		if (stu[i].score[2] > max_score[2])
		{
			max_score[2] = stu[i].score[2];
			max_count[2] = i;
		}
		if (stu[i].score[3] > max_score[3])
		{
			max_score[3] = stu[i].score[3];
			max_count[3] = i;
		}
	}

	printf("����Ϊÿ����Ŀ����߷�\n");
	printf("���Ŀ�Ŀ��߷�Ϊ:%5d%d\t%s\t%d", stu[max_count[0]].score[0], stu[max_count[0]].num, stu[max_count[0]].name, stu[max_count[0]].classes);
	printf("��ѧ��Ŀ��߷�Ϊ:%5d%d\t%s\t%d", stu[max_count[1]].score[1], stu[max_count[1]].num, stu[max_count[1]].name, stu[max_count[1]].classes);
	printf("Ӣ���Ŀ��߷�Ϊ:%5d%d\t%s\t%d", stu[max_count[2]].score[2], stu[max_count[2]].num, stu[max_count[2]].name, stu[max_count[2]].classes);
	printf("�������Ŀ��߷�Ϊ:%5d%d\t%s\t%d", stu[max_count[3]].score[3], stu[max_count[3]].num, stu[max_count[3]].name, stu[max_count[3]].classes);

	system("pause");
}


/*����������*/  
void zcd()
{	
	int n=0;
	char m;
	system("cls");/*����*/
	printf("����һ���������˵�\n "); /*����һ���������˵�*/ 
    printf("********************************************************************************\n"); 
    printf("\t\t�Ӻ���ѧ����ѧԺ��ӭ��\n"); 
    printf("\n\t\t\t--------- ��ӭʹ��ѧ������ϵͳ\n\n\t\t\t\t\t-----------\n"); 
	printf("*************************************MENU***************************************\n"); 
    printf("\t\t\t1. ����ѧ���ɼ���¼ Input the record\n"); /*����ѧ���ɼ���¼*/ 
       
	printf("\t\t\t2. ��ʾ������Ϣ Print the record\n"); /*��ʾ*/ 
    printf("\t\t\t3. ��ѧ�Ų��Ҹ��˳ɼ� Search record on name\n"); /*����*/ 
    printf("\t\t\t4. ���������Ҹ��˳ɼ� Search record on name\n"); /*����*/
	printf("\t\t\t5. ���ܷ����� Sort by total score\n"); /*���ܷ�����*/
	printf("\t\t\t6. ��ÿ����Ŀ��߷��� Highest score per subject\n"); /*��ÿ����Ŀ��߷���*/
    printf("\t\t\t7. �˳� Quit\n"); /*�˳�*/ 
    printf("********************************************************************************\n"); 
    printf("\n\t\t\t�������ѡ��Enter your choice(1~7):"); 
    fflush(stdin);
	m=getchar(); 

	do
	{
		switch(m)
		{ 
		   case '1':input();zcd();break; 
           case '2':print();zcd();break;
		   case '3':search_num();zcd();break; 
           case '4':search_name();zcd();break; 
		   case '5':sort_totalscore(); zcd(); break;
		   case '6':highestscore(); zcd(); break;
		   case '7':exit(0); /*��˵�����ֵΪ7��������*/
		   default:printf("��������"); getchar();zcd();
       /*���Լ�����չ���ܣ���ÿ�����ֵ����Сֵ���ɼ�������������
	    һ���˵���߷֣���ͷ֣�ƽ���֣��ȹ���*/
		} 
	} while(1);

}



void main()
{
	zcd();
}
