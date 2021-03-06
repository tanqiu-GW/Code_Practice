// BitMap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "malloc.h"



/*	类型声明	*/
typedef struct
{
	unsigned char *map;
	int base;
	int size;
}BitMap;


/*	函数声明	*/
BitMap *initBitmap(int size, int start);
void setBitmap(BitMap *bitmap, int index);
int getBitmap(BitMap *bitmap, int index);
int dataBitmap(BitMap *bitmap, int index);
void freeBitmap(BitMap *bitmap);



BitMap *initBitmap(int size, int start)
{
	BitMap *bitmap = (BitMap *)malloc(sizeof(BitMap));
	assert(bitmap != NULL);
	bitmap->map = (unsigned char *)malloc((size / 8 + 1) *sizeof(char));
	assert(bitmap -> map != NULL);
	bitmap->base = start;
	bitmap->size = size / 8 + 1;
	return bitmap;
}

void setBitmap(BitMap *bitmap, int index)
{
	assert(bitmap != NULL);
	int quo = (index - bitmap->base) / 8;
	int remainder = (index - bitmap->base) % 8;
	unsigned char x = (0x01 << remainder);
	assert(quo <= bitmap->size);
	bitmap->map[quo] |= x;
}

int getBitmap(BitMap *bitmap, int index)
{
	assert(bitmap != NULL);
	int quo = (index) / 8;
	int remainder = (index) % 8;
	unsigned char x = (0x01 << remainder);
	unsigned char res;
	assert(quo <= bitmap->size);
	res = bitmap->map[quo] & x;
	return res > 0 ? 1 : 0;
}

int dataBitmap(BitMap *bitmap, int index)
{
	assert(bitmap != NULL);
	return (index + bitmap->base);
}

void freeBitmap(BitMap *bitmap)
{
	free(bitmap);
}

int main()
{
	int a[] = { 5,8,7,6,3,1,10,78,56,34,23,2,43,54,65,89,87,76,89,100,55 };
	int i;
	BitMap *bitmap = initBitmap(100, 0);
	for (i = 0; i <= 20; i++)
	{
		setBitmap(bitmap, a[i]);
	}

	for (i = 0; i < 100; i++)
	{
		if (getBitmap(bitmap, i) > 0)
		{
			printf("%d ", dataBitmap(bitmap, i));
		}
	}
	printf("\n");
	freeBitmap(bitmap);
    return 0;
}

