#include <stdio.h>


void print_n(int* arr, int n);


void swap(int* a, int*b)
{  //一个内存地址的别名。    可以赋值给一个指向函数的指针变量（函数指针）。//指针数组 int* a[]，数组指针 int (* a)[3]  a+1.      
    int tmp = *a;
    *a      = *b;
    *b      = tmp;
}

int put_first(int*arr, int left ,int right)
{
    int i=left,j=right,tmp=arr[i];
    while(i<j)
    {
        while(i<j&&arr[j]>=tmp){j--;}; arr[i]=arr[j];
        while(i<j&&arr[i]<=tmp){i++;}; arr[j]=arr[i];
    }
    arr[i]=tmp;
    return i;
}

void quick_sort(int* arr, int left,int right)
{
    if(right==16&&left==0)
        printf("Applying quicksort!\n");
    if(left<right)
    {
        int b = put_first(arr,left,right); // arr中第一个元素的位置k，arr[]    arr[0~k-1] arr[k+1,n]
        quick_sort(arr,left,b-1);
        quick_sort(arr,b+1,right);   //非递归实现，
    }
}

void print_n(int* arr, int n)
{
    for(int i=0;i<n;i++)
        printf("%d  ",arr[i]);
    printf("\n");
}

void adjust_heap(int* arr, int top,int N)
{
    int tmp = arr[top];

    for(int j=top*2+1;j<N;j=j*2+1)
    {
        if(arr[j]<arr[j+1]&&(j+1)<N)
            j++;
        if(tmp<arr[j])
        { 
            arr[top]=arr[j];
            top = j;
        }
        else
            break;
    }

    arr[top] = tmp;
}

void create_heap(int* arr, int N)
{
    for(int i=N/2-1;i>=0;i--) 
        adjust_heap(arr,i,N);
}

void heap_sort(int* arr,int left,int right)
{
    printf("Applying heapsort!\n");
    int length=right+1;
    create_heap(arr,length);
    for(int n=length;n>1;n--)
    {
        swap(&arr[0],&arr[n-1]);
        adjust_heap(arr,0,n-1);
    }
}


//选择排序
void selectn(int* arr,int n)
{
    for(int i=0;i<n;i++)
        if(arr[i]>arr[n])
        {
            int temp = arr[i];
            arr[i]   = arr[n];
            arr[n]   = temp;
        } 
}

//插入排序
void insertn(int* arr,int n,int N)
{
    for(int j=n;j<(N-1);j++)
        if(arr[j]>arr[j+1])
            swap(&arr[j],&arr[j+1]);
}

void insertsort(int* arr, int N)
{
    for(int n=16;n>=0;n--)
        insertn(arr,n,17);
}

//冒泡排序 //O(n^2)
void bubble(int* arr,int n)
{
    for(int i=0;i<n;i++)
    if(arr[i]>arr[i+1])
        swap(&arr[i],&arr[i+1]);
}


int main()
{
    int arr1[17]={45,23,12,-15,76,34,77,23,-66,34,89,20,33,56,79,-21,-3};
    int arr2[17]={45,23,12,-15,76,34,77,23,-66,34,89,20,33,56,79,-21,-3};
    /*
    void (* funcp)(int* arr,int left,int right);
    funcp=quick_sort;
    (funcp)(arr1,0,16);
    print_n(arr1,17);
    funcp=heap_sort;
    (funcp)(arr2,0,16);
    print_n(arr2,17);
    */
    /*
    void (* funcps[2])(int* arr,int left,int right);
    funcps[0]=quick_sort;
    funcps[1]=heap_sort;
    int* aptr[2];aptr[0]=arr1,aptr[1]=arr2;
    for(int i=0;i<2;i++){
         (funcps[i])(aptr[i],0,16);
         print_n(aptr[i],17);
    }*/
    
    void (*funcps[2])(int* arr,int left,int right)={quick_sort,heap_sort};
    int* aptr[2];
    aptr[0]=arr1,aptr[1]=arr2;

    for(int i=0;i<2;i++)
    {
         funcps[i](aptr[i],0,16);
         print_n(aptr[i],17);
    }



	//添加其他的排序方法，利用函数指针的方式调用
	int arr3[] = {45,23,12,-15,76,34,77,23,-66,34,89,20,33,56,79,-21,-3};
	int arr4[] = {45,23,12,-15,76,34,77,23,-66,34,89,20,33,56,79,-21,-3};
	int arr5[] = {45,23,12,-15,76,34,77,23,-66,34,89,20,33,56,79,-21,-3};
	int *p_arr[3];
	int size[] = {sizeof(arr3)/sizeof(int),sizeof(arr4)/sizeof(int),sizeof(arr5)/sizeof(int)};

	p_arr[0] = arr3;
	p_arr[1] = arr4;
	p_arr[2] = arr5;

	void (*pfun[3])(int *arr, int N) = {selectn, insertsort, bubble};//定义函数指针并使其指向三个排序函数

	printf("Applying selectnsort!\n");
	for(int j=size[0]-1; j>0; j--)
	{
		pfun[0](p_arr[0], j);
	}
	print_n(p_arr[0], size[0]);
	
	printf("Applying insertsort!\n");
	pfun[1](p_arr[1], size[1]);
	print_n(p_arr[1], size[1]);

	printf("Applying bubblesort!\n");
	for(int k=size[2]-1; k>0; k--)
	{
		pfun[2](p_arr[2], k);
	}
	print_n(p_arr[2], size[2]);
       
    return -1;
}