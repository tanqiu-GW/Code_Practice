// 1.5.2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"


int main()
{
#if 0
	double nc;
	for (nc = 0; getchar() != EOF; ++nc)
		;
	printf("%.0f\n", nc);
#else
	long nc;
	nc = 0;
	while (getchar() != EOF)
		++nc;
	printf("%ld\n", nc);
#endif
    return 0;
}

