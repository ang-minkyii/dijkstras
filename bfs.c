#include <stdio.h>
#include <stdlib.h.>

struct node
{
	int capacity;
	int size;
	int front;
	int rear;
	int **elements;
};

typedef struct node tree_t;


int main(int argc, char **argv)
{









}


tree_t **createtree(int number)
{
	tree_t *tree;
	tree = (tree_t*)malloc(sizeof(tree_t));
	tree->capacity = number;
	tree->size = 0;
	tree->front = 0;
	tree->rear = -1;
	tree->elements = (int**)malloc(sizeof(int*)*number);
	for(int i=0;i<number;i++)
	{
		tree->elements[i]=(int*)malloc(sizeof(int));
	}

	return tree;
}

void Dequeue(tree_t *tree)
{
	if(tree->size == 0)
	{
		printf("Queue is empty\n");
		return;
	}else
	{
		tree->size--;
		tree->front++;
		











	}





}

