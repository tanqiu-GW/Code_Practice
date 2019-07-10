#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void move(int *array, int n, int m)
{
    int *p = array;
    int *temp = (int *)malloc(n * sizeof(int));
    if(temp == NULL)
    {
        perror("apply memory for array failed!");
        return;
    }
    memset(temp, 0, n);

    memcpy(temp, p, n * sizeof(int)); //复制array数组内容到temp中，temp用于交换数据
    p = p + (n - m);
    memcpy(array, p, m * sizeof(int)); //将最后m个元素复制到array[0]至array[n - m - 1]中
    memcpy(array + m, temp, (n - m) * sizeof(int)); //将temp中的前n-m个元素复制到array[m - 1]至array[n]

    free(temp);
}

int main(void)
{
    int *array_test = NULL; //动态数组
    int n = 0,m = 0;

    printf("input the number of the element in array:");
    scanf("%d", &n);

    array_test = (int *)malloc(sizeof(int) * n);    //申请n个int内存，存放n个整数到数组
    if(array_test == NULL)
    {
        perror("apply memory for array failed!");
        return -1;
    }
    printf("\ninput the elements in array:");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &array_test[i]);
    }

    printf("\ninput the offset value:");
    scanf("%d", &m);

    move(array_test, n, m);

    for(int j = 0; j < n; j++)
    {
        printf("%d ",array_test[j]);
    }

    free(array_test);

    return 0;
}