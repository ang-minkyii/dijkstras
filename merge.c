#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 256

void printarr(int arr[], int a);
int sort(int arr[],int first, int last);
int merge(int arr[], int low, int mid, int high);

int main()
{
	int num;
	int array[MAX];
	int i=0;
	int k;

	printf("Enter an array of number\n");
	while(scanf("%d",&num)==1)
	{
		array[i]=num;
		i++;
	}
	printf("i=%d\n",i);
	//printarr(array,i);
	sort(array,0,i-1);
	
	for(k=0;k<i;k++)
	{
		printf("%d\n",array[k]);
	}
	return 0;

}

void printarr(int arr[], int a)
{
	int i;

	for(i=0;i<a;i++)
	{
		printf("%d\n",arr[i]);
	}
}

int sort(int arr[],int first, int last)
{
	int mid;

	if(first<last)
	{
		mid = (first+last)/2;
		sort(arr,first,mid);
		sort(arr,mid+1,last);
		merge(arr,first,mid,last);
	}
	return 0;
}

int merge(int arr[], int low, int mid, int high)
{
	int i,j,k;
	int arr1[10];
	int arr2[10];
	int p1 = mid-low+1;
	int p2 = high-mid;

	for(i=0;i<p1;i++)
	{
		arr1[i] = arr[low+i];
	}
	for(j=0;j<p2;j++)
	{
		arr2[j] = arr[mid+j+1];
	}

	arr1[i]=INT_MAX;
	arr2[j]=INT_MAX;

	i=0;
	j=0;

	for(k=low;k<=high;k++)
	{
		if(arr1[i]<=arr2[j])
		{
			arr[k] = arr1[i++];
		}else
		{
			arr[k] = arr2[j++];
		}
	}
	return 0;
}













