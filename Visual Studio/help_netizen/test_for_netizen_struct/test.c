#include "stdafx.h"
#include<iostream>

int main()
{
	struct student
	{
		int num;
		char name[20];
		float sore;
	}student1, student2;
	printf("请输入学生1和学生2的信息\n");
	scanf_s("%d %s %f", &student1.num, student1.name, &student1.sore);
	printf("\n");
	scanf_s("%d %s %f", &student2.num, student2.name, &student2.sore);
	printf("高分是:\n");
	if (student1.sore > student2.sore)
		printf("%d   %s    %6.2f\n", student1.num, student1.name, student1.sore);
	else if (student1.sore < student2.sore)
		printf("%d   %s    %6.2f\n", student2.num, student2.name, student2.sore);
	else
	{
		printf("%d   %s    %6.2f\n", student1.num, student1.name, student1.sore);
		printf("%d   %s    %6.2f\n", student2.num, student2.name, student2.sore);
	}
	system("pause");
	return 0;
}
