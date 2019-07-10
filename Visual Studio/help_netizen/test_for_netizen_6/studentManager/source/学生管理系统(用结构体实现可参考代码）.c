#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUM 37
struct student
{     long term;          //学期
      long num;          //学号
      int classes;      //班级
      char name[10];   //姓名
      int score[4];
      int sum; 
      float average;  
}stu[NUM];
void zcd();

/*输入信息函数*/
void input()
{
    int i;
	char a;
	system("cls");
   for(i=0;i<NUM;i++)
	{  printf(" \n请输入学生的学期：");
	   scanf("%ld",&stu[i].term);
      
      printf(" \n请输入学生的学号：");
	  fflush(stdin);
	  scanf("%ld",&stu[i].num);
	  
	  printf(" \n请输入学生的班级：");
	  scanf("%d",&stu[i].classes);
	  
	  printf("\n请输入学生的姓名：");
	  scanf("%s", stu[i].name) ;
	  
	  printf("\n请输入学生的语文成绩：");
	  scanf("%d",&stu[i].score[0]);
	  
	  printf("\n请输入学生的数学成绩：");
	  scanf("%d", &stu[i].score[1]);	 
	   printf("\n请输入学生的英语成绩：");
      scanf("%d", &stu[i].score[2]);
      
	  printf("\n请输入学生的计算机成绩：");
	  scanf("%d", &stu[i].score[3]);
	
	   stu[i].sum=stu[i].score[0]+stu[i].score[1]+stu[i].score[2]+stu[i].score[3];//算总分和平均
       stu[i].average=(float)stu[i].sum/4.0;

	   printf("是否要继续添加(按N&n退出)");
	   fflush(stdin);//用来清空输入缓存

	  a=getchar();
	  if(a=='n'||a=='N')
		 break;
	}
}


void print()
{
	int i;
	printf("学号\t姓名\t班级 语文 数学 英语 计算机 总分 平均分\n");
	for(i=0;i<NUM;i++)
	{
	  
	  {
		  stu[i].sum=stu[i].score[0]+stu[i].score[1]+stu[i].score[2]+stu[i].score[3];
          stu[i].average=(float)stu[i].sum/4.0;
          printf("%d\t%s\t%d%5d%5d%5d%6d%7d%8.2f\n",stu[i].num,stu[i].name,stu[i].classes,
		  stu[i].score[0],stu[i].score[1],stu[i].score[2], stu[i].score[3],stu[i].sum,stu[i].average); /*输出学生信息*/
	  }
	}
	
	system("pause");
}




/*查找并显示一个记录*/ 
void search_num() 
{ 
   int number=0,i;  //注意定义要放在最前面
   system("cls");/*清屏*/
    
   printf("\t\t\t 请输入要查找学生的学号:");  
   scanf("%d",&number);
   printf("学号\t姓名\t班级 语文 数学 英语 计算机 总分 平均分\n");

	for(i=0;i<NUM;i++)
	{
		if (number == stu[i].num)
		{
			printf("%d\t%s\t%d%5d%5d%5d%6d%7d%8.2f\n", stu[i].num, stu[i].name, stu[i].classes,
			stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].score[3], stu[i].sum, stu[i].average); /*输出学生信息*/
			break;
		}
		else
		{
			printf("没找到该学生的信息\n");
		}
	}

	system("pause");
}

 /*查找并显示一个记录*/ 
void search_name() 
{
	int i;  //注意定义要放在最前面
	char name[10] = { 0 };
	system("cls");/*清屏*/

	printf("\t\t\t 请输入要查找学生的姓名:");
	fgets(name, 10, stdin);
	printf("学号\t姓名\t班级 语文 数学 英语 计算机 总分 平均分\n");

	for (i = 0; i < NUM; i++)
	{
		if (strcmp(name, stu[i].name) == 0)	//比较字符串，查找姓名
		{
			printf("%d\t%s\t%d%5d%5d%5d%6d%7d%8.2f\n", stu[i].num, stu[i].name, stu[i].classes,
			stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].score[3], stu[i].sum, stu[i].average); /*输出学生信息*/
			break;
		}
		else
		{
			printf("没找到该学生的信息\n");
		}
	}

	system("pause");
}

/*冒泡排序*/
void BubbleSort(int arr[], int num[], int length) 
{ 
	int temp = 0, temp2 = 0;
	int i = 0, j = 0;

	for (; i < length; i++) 
	{ 
		for (; j < length - i - 1; j++)
		{ 
			if (arr[j] > arr[j + 1])	//根据总分的排序，来确定每位同学序号的排序
			{ 							//例如总分最高的35号同学，利用冒泡排序来到了第一位
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
/*根据总分从高到底排序每位同学的信息*/
void sort_totalscore(void)
{
	int sum[37] = { 0 }, num[37] = { 0 };
	int i = 0;
	system("cls");/*清屏*/

	for (; i < NUM; i++)
	{
		sum[i] = stu[i].sum;	//记录每位同学的总分
		num[i] = stu[i].num;	//记录每位同学的序号
	}

	BubbleSort(sum, num, NUM);

	for (i = 0; i < NUM; i++)
	{
		printf("%d\t%s\t%d%5d%5d%5d%6d%7d%8.2f\n", stu[num[i]].num, stu[num[i]].name, stu[num[i]].classes,
			stu[num[i]].score[0], stu[num[i]].score[1], stu[num[i]].score[2], stu[num[i]].score[3], stu[num[i]].sum, stu[num[i]].average); /*输出学生信息*/
	}

	system("pause");
}
/*求每个科目最高分，并打印科目最高分获得者的序号，姓名，班级*/
void highestscore(void)
{
	int max_score[4] = { 0 }, max_count[4] = { 0 };
	int i = 0;

	system("cls");/*清屏*/
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

	printf("以下为每个科目的最高分\n");
	printf("语文科目最高分为:%5d%d\t%s\t%d", stu[max_count[0]].score[0], stu[max_count[0]].num, stu[max_count[0]].name, stu[max_count[0]].classes);
	printf("数学科目最高分为:%5d%d\t%s\t%d", stu[max_count[1]].score[1], stu[max_count[1]].num, stu[max_count[1]].name, stu[max_count[1]].classes);
	printf("英语科目最高分为:%5d%d\t%s\t%d", stu[max_count[2]].score[2], stu[max_count[2]].num, stu[max_count[2]].name, stu[max_count[2]].classes);
	printf("计算机科目最高分为:%5d%d\t%s\t%d", stu[max_count[3]].score[3], stu[max_count[3]].num, stu[max_count[3]].name, stu[max_count[3]].classes);

	system("pause");
}


/*主函数界面*/  
void zcd()
{	
	int n=0;
	char m;
	system("cls");/*清屏*/
	printf("按任一键进入主菜单\n "); /*按任一键进入主菜单*/ 
    printf("********************************************************************************\n"); 
    printf("\t\t河海大学文天学院欢迎您\n"); 
    printf("\n\t\t\t--------- 欢迎使用学生管理系统\n\n\t\t\t\t\t-----------\n"); 
	printf("*************************************MENU***************************************\n"); 
    printf("\t\t\t1. 输入学生成绩记录 Input the record\n"); /*输入学生成绩记录*/ 
       
	printf("\t\t\t2. 显示所有信息 Print the record\n"); /*显示*/ 
    printf("\t\t\t3. 按学号查找个人成绩 Search record on name\n"); /*查找*/ 
    printf("\t\t\t4. 按姓名查找个人成绩 Search record on name\n"); /*查找*/
	printf("\t\t\t5. 按总分排序 Sort by total score\n"); /*按总分排序*/
	printf("\t\t\t6. 求每个科目最高分数 Highest score per subject\n"); /*求每个科目最高分数*/
    printf("\t\t\t7. 退出 Quit\n"); /*退出*/ 
    printf("********************************************************************************\n"); 
    printf("\n\t\t\t输入你的选择Enter your choice(1~7):"); 
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
		   case '7':exit(0); /*如菜单返回值为7则程序结束*/
		   default:printf("错误命令"); getchar();zcd();
       /*可以继续扩展功能，求每科最大值、最小值、成绩排序、名字排序、
	    一个人的最高分，最低分，平均分，等功能*/
		} 
	} while(1);

}



void main()
{
	zcd();
}
