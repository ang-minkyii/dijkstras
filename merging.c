#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int* merge(int A[],int B[],int a, int b);
int* mergesorting(int A[],int first,int last);
void debug(char *name);

int main(int argc, char **argv)
{
	int arr3[MAX];
	int i=1,k=0;
	int num;

	printf("Enter number\n");

	while(scanf("%d",&num)==1 && i != 10)
	{
		arr3[k] = num;
		i++;
		k++;
	}
	debug("hello");

	mergesorting(arr3,0,i-1);

/*	for(int v=0;v<i+i;v++)
	{
		printf("%d\n",arr3[v]);
	}*/
	return 0;
}


int* merge(int A[],int B[],int a, int b)
{
	int i=0,j=0;
	int k;
	int *ptr;
	int C[MAX];

	//ptr = (int**)malloc(sizeof(int*)*(a+b));
	for(int v=0;v<a+b;v++)
	{
		ptr=(int*)malloc(sizeof(int)*(a+b));
	}

	for(k=0;k<a+b;k++)
	{
		if(i==a)
		{
			C[k]=B[j++];
			continue;
		}
		if(j==b)
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
	for(int v=0;v<a+b;v++)
	{
		ptr[v]=C[v];
	}
	return ptr;
}


int* mergesorting(int A[],int first,int last)
{
	int *C;
	int *B;
	int mid = (last-first)/2;
	//printf("%d\n",mid);
	


	A = mergesorting(A,first,mid);	
	B = mergesorting(A,mid+1,last);
	C = merge(A,B,(mid-first),(last-mid+1));
	

	for(int i=0;i<last;i++)
	{
		A[i] = C[i];
	}
	return A;
}

void debug(char *name)
{
	fprintf(stdout,"%s\n",name);
	fflush(stdout);
}


