/********************************************************************************

 *************************Copyright (C), 2018, ScienTech Inc.**************************

 ********************************************************************************
 * @file     	 : Sequential_table.c
 * @brief   		  : .C file function description
 * @author       : gw
 * @version        : 1.0
 * @date          : 2018-12-01
 * 
 * 
 * @note History:
 * @note        : 顺序表功能函数 2018-12-01
 * @note        : 
 *   Modification: Created file

********************************************************************************/

/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "Sequential_table.h"



/* 局部变量 */
static Table *table;


/* 局部函数 */
static status reallocTable(Type type, U16 size);


/**
 * @fn       status reallocTable(Type type, U16 size)
 * @brief    申请更多的内存，返回是否成功状态值
 * 
 * @param[in]          Type type  
 * @param[in]        U16 size   
 * @return         
 */
status reallocTable(Type type, U16 size)
{
	switch(type)
	{
		case INT:
			/* 此处注意realloc用法:当table->data指向的内存后有足够的空间用于扩大size内存，
			则返回当前的table->data地址，即内存是连续的；若没有足够的空间，那么将从堆中寻
			找另一块内存，大小为(table->size + size)，把原来大小内存中的内容复制到新的内存
			中，返回新内存的地址 */
			table->data = (int *)realloc(table->data, (table->size + size) * sizeof(int));
			break;
		case CHAR:
			table->data = (char *)realloc(table->data, (table->size + size) * sizeof(char));
			break;
	}

	if(!table->data)
	{
		printf("申请新的内存失败\n");
		return failed;
	}

	table->size += size;

	return success;
}


/**
 * @fn       Table *initTable(Type type, int size)
 * @brief    初始化顺序表
 * 
 * @param[in]          Type type  
 * @param[in]        int size   
 * @return         
 */
Table *initTable(Type type, U32 size)
{
	table = (Table *)malloc(sizeof(Table));	//为顺序表指针申请动态内存

	switch (type)		//为顺序表元素申请动态内存
	{
		case INT:
			table->data = (int *)malloc(sizeof(int) * size);
			memset(table->data, 0, sizeof(int) * size);
			break;
		case CHAR:
			table->data = (char *)malloc(sizeof(char) * size);
			memset(table->data, 0, sizeof(char) * size);
			break;
		default:
			break;
	}

	if((!table) || (!table->data))	//申请内存失败
	{
		printf("初始化顺序表失败\n");
		exit(0);
	}
	
	table->count = 0;
	table->size = size;

	return table;
}
#if 1
/**
 * @fn       void printfTable(Type Type)
 * @brief    打印顺序表元素
 *   
 * @param[in]        Type type    
 * @return         
 */
void printfTable(Type type)
{
	U32 i = 0;
	U32 *data1;
	U8 *data2;
	
	switch (type)
	{
		case INT:
		#if 0
			for(; i < table->count; i++)
			{												//table.data声明为void *类型。
				data1 = (int *)table->data++;				//此处编译不通过，报错void *未知大小。
				printf("getTableData(%d) = %d\n", i, *data1);//原因是指针大小未知，不能进行++运算。
			}												//但是我做了强制转换为int型指针了，还是报错
			break;											//此时报错原因不知。
		#endif
			data1 = (int *)table->data;
			for(; i < table->count; i++)
			{
				printf("getTableData(%d) = %d\n", i, *data1);
				data1++;
			}
			break;
		case CHAR:
			data2 = (char *)table->data;
			for(; i < table->count; i++)
			{
				//data2 = (char *)table->data++;
				printf("getTableData(%d) = %c\n", i, *data2);
				data2++;
			}

			if(table->count > 0)
			{
				printf("the full string is [%s]", (char *)table->data);
			}
			break;
		default:
			break;
	}
	printf("\n");
}
#endif

/**
 * @fn       void freememory(Table * table)
 * @brief    释放顺序表占用的堆内存
 * 
 * @param[in]          Table * table  
 * @return         
 */
void freememory(Table * table)
{
	free(table->data);
	free(table);
}

/**
 * @fn       status insertTable(U16 index, void * pdata)
 * @brief    插入1个数据到index位置，返回是否插入成功状态值
 * 
 * @param[in]          U32 index     
 * @param[in]        void * pdata  
 * @return         
 */
status insertTable(Type type, U32 index, void * pdata)
{
	if((index > (table->size + 1)) || (index < 1))		//插入位置不存在
	{
		return failed;
	}

	if(table->count == table->size)
	{
		if(!reallocTable(type, 1))	//再申请一个存放type类型数据的空间
		{
			return failed;
		}
	}
	//当插入元素index小于count时，默认index前从count起的元素为0
	if(table->count < index)
	{
		table->count = index - 1;
	}

	//插入数据前，先后移插入位置后的所有元素
	switch (type)
	{
		case INT:
			/* 此处发现一个bug，不应从index的后一个元素开始后移!应该从
			最后一个size处开始后移，保证前面的数都会后移而不会被覆盖！ */
			#if 0
			for(U32 i = index; i <= table->size; i++)
			{
				((int *)(table->data))[i] = ((int *)(table->data))[i - 1];
			}
			(((int *)(table->data))[index - 1]) = *((int *)pdata);
			#endif
			for(U32 i = table->size - 1; i > index - 1; i--)
			{
				((int *)(table->data))[i] = ((int *)(table->data))[i - 1];
			}
			(((int *)(table->data))[index - 1]) = *((int *)pdata);
			break;
		case CHAR:
			#if 0
			for(U32 i = index; i <= table->size; i++)
			{
				((char *)(table->data))[i] = ((char *)(table->data))[i - 1];
			}
			(((char *)(table->data))[index - 1]) = *((char *)pdata);
			#endif
			for(U32 i = table->size - 1; i > index - 1; i--)
			{
				((char *)(table->data))[i] = ((char *)(table->data))[i - 1];
			}
			(((char *)(table->data))[index - 1]) = *((char *)pdata);
			break;
		default:
			break;
	}
	
	table->count++;

	return success;
}

/**
 * @fn       status deleteTable(Type type, U32 index)
 * @brief    删除指定位置的元素，删除后，index后的元素都-
             前移
 * 
 * @param[in]          Type type  
 * @param[in]        U32 index  
 * @return         
 */
status deleteTable(Type type, U32 index)
{
	if((index < 1) || (index >table->size))
	{
		return failed;
	}

	switch (type)
	{
		case INT:
			for(U32 i = index; i <= table->size; i++)//删除元素后，size没变，顺序表占用的内存长度不变
			{
				((int *)(table->data))[i - 1] = ((int *)(table->data))[i];
			}
			break;
		case CHAR:
			for(U32 i = index; i <= table->size; i++)
			{
				((char *)(table->data))[i - 1] = ((char *)(table->data))[i];
			}
			break;
		default:
			break;
	}

	table->count--;

	return success;
}

/**
 * @fn       status selectTable(HowToFind way, U32 index, void * elem)
 * @brief    按照位置或者指定元素值来查询顺序表中的元素
             
 * 
 * @param[in]          HowToFind way  
 * @param[in]        U32 index      
 * @param[in]        void * elem    
 * @return         
 */
 /* 此函数有待优化，最好将通过位置和元素值两种方式分开写，在通过元素值查找时多次调用通过位置查找
 的函数，从而返回所有元素相同的顺序表中的元素位置 */
TableElem selectTable(Type type, HowToFind way, U32 index, void * elem)
{
	U32 record_position[100];	//为简单起见，默认顺序表中相同元素个数不超过100个
	U32 same_number = 0;		//顺序表相同元素计数
	TableElem temp;
	temp.position = -1;
	temp.element = NULL;
	
	switch (way)
	{
		case POSITION:
			if((index > table->size) || (index < 1))
			{
				temp.position = -1;		//若位置错误，返回位置-1，元素地址NULL
				temp.element = NULL;
			}
			else
			{
				if(INT == type)
				{
					temp.position = index;
					temp.element = (((int *)(table->data)) + index);
				}
				else if(CHAR == type)
				{
					temp.position = index;
					temp.element = (((char *)(table->data)) + index);
				}
				else
				{
					temp.position = -1;		//若数据类型错误，返回位置-1，元素地址NULL
					temp.element = NULL;
				}
			}
			break;
		case ELEMENT:
			if(INT == type)
			{
				for(U32 i = 0; i < table->size; i++)//遍历查找元素位置
				{
					if(*((int *)elem) == ((int *)table->data)[i])//找到元素位置了，但是如果后面
					{									 		  //还有和元素相等的位置时，temp
						//temp.position = i + 1;			 		  //将被覆盖，如果在if分支内返回temp，
						//temp.element = (((int *)table->data) + i);//那么后面如果有相等的elem
						same_number += 1;						  //时，将不能再返回此时的位置了
						record_position[same_number - 1] = i + 1;
					}//添加了两个变量，用于记录相同元素个数
				}
				for(U32 j = 0; j <= same_number; j++)
				{
					selectTable(INT, POSITION, record_position[j], elem);//递归，返回多个元素值
				}
			}
			else if(CHAR == type)
			{
				for(U32 m = 0; m < table->size; m++)//遍历查找元素位置
				{
					if(*((char *)elem) == ((char *)table->data)[m])
					{									 		  
						//temp.position = i + 1;			 		  
						//temp.element = (((char *)table->data) + i);
						same_number += 1;						 
						record_position[same_number - 1] = m + 1;
					}
				}
				for(U32 n = 0; n <= same_number; n++)
				{
					selectTable(CHAR, POSITION, record_position[n], elem);//递归，返回多个元素值
				}
			}
			else
			{
				temp.position = -1;
				temp.element = NULL;
			}
			break;
		default:
			break;
	}

	return temp;
}



