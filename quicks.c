#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);
void swap(int *a, int *b);
void printarr(int A[], int a);

int main()
{
	int value, i;
	int array[MAX];


	printf("Enter number\n");

	while(scanf("%d",&value)==1)
	{
		array[i] = value;
		i++;
	}
	quicksort(array,0,i-1);
	printarr(array,i);

	return 0;
}

void printarr(int A[], int a)
{
	for(int i=0;i<a;i++)
	{
		printf("\n%d\n",A[i]);
	}
}

/*int partition(int arr[], int low, int high)
{
	int x = arr[high]; //last element
	int i = (low-1);

	for(int j=low; j<= high-1;j++)
	{
		if(arr[j] <= x)
		{
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	swap(&arr[i+1],&arr[high]);

	return (i+1);
}
*/
void quicksort(int arr[], int low, int high)
{
	if(low<high)
	{
		int p = partition(arr,low,high);
		quicksort(arr,low,p-1);
		quicksort(arr,p+1,high);
	}
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}