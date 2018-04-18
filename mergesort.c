#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int merge(int A[], int B[], int m, int n);
int mergesorting(int A[],int first, int last);
void printarr(int A[],int i);
void debug(char *name);

int main(int argc, char **argv)
{
	int k=0;
	int A[MAX];
	int value;
	int *V;
	while(scanf("%d",&value)==1)
	{
		A[k] = value;
		k++;
	}

	printarr(A,k);

	mergesorting(A,0,k-1);

	printarr(V,k);
	return 0;


}

void printarr(int A[],int i)
{

	for(int j=0;j<i;j++)
	{
	printf("A[%d] = %d\n",j,A[j]);
	}

}

void debug(char *name)
{
	fprintf(stdout,"%s\n",name);
	fflush(stdout);
}







int merge(int A[], int B[], int n, int m)
{
	int i=0,j=0,k;
	int *C = (int*)malloc(sizeof(int)*(m+n));


	for(k=0;k<n+m;k++)
	{
		if(i == n)
		{
			C[k]=B[j];
			j++;
			continue;
		}
		if(j == m)
		{
			C[k]=A[i];
			i++;
			continue;
		}
		if(A[i]<=B[j])
		{
			C[k]=A[i];
			i++;
		}else
		{
			C[k]=B[j];
			j++;
		}
	}
	return 0;
}

int mergesorting(int A[],int first, int last)
{
	int i;
	int mid;
	int *C = (int*)malloc(sizeof(int)*(last-first+1));
	int *B = (int*)malloc(sizeof(int)*(last-first+1));

	if(first < last)
	{
		mid = (first + last)/2;
		mergesorting(A,first,mid);
		mergesorting(A,mid+1,last);
		merge(A,B,mid-first+1,last-mid);
	}

	for(i=first;i<last;i++)
	{
		A[i] = C[i];
		printf("A[%d] = %d\n",i,A[i]);
	}
	return 0;
}


