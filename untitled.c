#include <stdio.h>
#include <stdlib.h>

#define MAX 256



int main(int argc, char **argv)
{
	int arr1[MAX];
	int arr2[MAX];
	int arr3[MAX];
	int i=0,j;
	int value;

	printf("Enter number = ");
	while(scanf("%d",&value)==1 && i != 10)
	{
		arr1[i] = value;
		i++;
	}
	return 0;
}


void merge(A[],B[],C[],int a, int b)
{
	int i=0,j=0;
	int k;

	for(k=0;k<m+n;k++)
	{
		if(i==n)
		{
			C[k]=B[j++];
			continue;
		}
		if(j==m)
		{
			C[k]=A[i++];
			continue;
		}
		if(A[i]<=B[j])
		{
			C[k]=A[i++];
		}else
		{
			C[k]=B[j++];
		}
	}
}