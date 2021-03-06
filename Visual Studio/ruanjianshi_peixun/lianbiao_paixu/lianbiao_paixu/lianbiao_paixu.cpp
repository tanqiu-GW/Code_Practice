// lianbiao_paixu.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"



#define SIZE	6



typedef struct
{
	int data;
	int next;
}Node;

typedef struct
{
	Node databuf[SIZE];
	int length;
}List;



void Arrange(List *SL)
{
	int p = SL->databuf[0].next;
	int i;
	for (i = 1; i < SL->length; i++)
	{
		while (p < i)
		{
			p = SL->databuf[p].next;
		}
		int q = SL->databuf[p].next;
		if (p != i)
		{
			Node t;
			t = SL->databuf[p];
			SL->databuf[p] = SL->databuf[i];
			SL->databuf[i] = t;
			SL->databuf[i].next = p;
		}
		p = q;
	}
}


int main()
{
	int i;
	List *SL = (List *)malloc(sizeof(List));
	SL->length = 6;
	SL->databuf[0].data = 0;
	SL->databuf[0].next = 4;

	SL->databuf[1].data = 44;
	SL->databuf[1].next = 3;

	SL->databuf[2].data = 33;
	SL->databuf[2].next = 1;

	SL->databuf[3].data = 55;
	SL->databuf[3].next = 0;

	SL->databuf[4].data = 11;
	SL->databuf[4].next = 5;

	SL->databuf[5].data = 22;
	SL->databuf[5].next = 2;

	Arrange(SL);
	for (i = 1; i < 6; i++)
	{
		printf("%d   ", SL->databuf[i].data);
	}
    return 0;
}

