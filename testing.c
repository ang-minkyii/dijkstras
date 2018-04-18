#include<stdio.h>





int main()
{
	int *ptr;


	ptr[2] = 10;
	ptr[3] = 12;
	ptr[4] = 14;


	printf("ptr[2] = %d\n",ptr[2]);
	printf("ptr[3] = %d\n",ptr[3]);
	printf("ptr[5] = %d\n",ptr[5]);

	return 0;


}