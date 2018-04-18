#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "binheap.h"

heapnode_t* newheapnode(int v, int dist)			/*create a new node*/
{
	heapnode_t* newnode = (heapnode_t*)malloc(sizeof(heapnode_t));
	newnode->v = v;
	newnode->distance = dist;

	return newnode;
}

heap_t* heaptree(int numnode)				/*create a new tree*/
{
	heap_t *tree = (heap_t*)malloc(sizeof(heap_t));
	tree->numberheaps = numnode;
	tree->array = (heapnode_t**)malloc(sizeof(heapnode_t)*numnode);

	return tree;
}


void heapify(heap_t* tree, int i)			/*function to rearrange the nodes in the tree*/
{
	int smallest,left,right;
	smallest = i;
	left = 2*i + 1;
	right = 2*i + 2;

	if(left < tree->size && tree->array[left]->distance < tree->array[smallest]->distance)
	{
		smallest = left;				/*if left is smaller than the smallest node*/
	}

	if(right < tree->size && tree->array[right]->distance < tree->array[smallest]->distance)
	{
		smallest = right;				/*if right is smaller than the smalles node*/
	}

	if(smallest != i)
	{
		heapnode_t *smallestnode = tree->array[smallest];
		heapnode_t *inode = tree->array[i];

		tree->position[smallestnode->v] = i;			/*update the position*/
		tree->position[inode->v] = smallest;

		swapnode(&tree->array[smallest],&tree->array[i]);		/*swap node*/
		heapify(tree,smallest);								/*rearrange the tree*/
	}
}

bool isinheap(heap_t *tree, int d)
{
	if(tree->position[d] < tree->size)
	{
		return true;
	}
	return false;
}

heapnode_t* extractmin(heap_t* tree)			/*function to extract the minimum node*/
{
	if(isEmpty(tree))
	{	
		return NULL;
	}

	heapnode_t* root = tree->array[0];					/*the first node is set to be the root*/
	heapnode_t* lastnode = tree->array[tree->size - 1];		/*last node is set*/

	tree->array[0] = lastnode;
	tree->position[root->v] = tree->size-1;			/*update position*/
	tree->position[lastnode->v] = 0;
	tree->size = tree->size - 1;		/*reduce the size by 1*/
	heapify(tree,0);

	return root;
}



void decreasekey(heap_t* tree, int src, int dist)		/*function to decrease key*/
{
	int i = tree->position[src];

	tree->array[i]->distance = dist;				/*update the time*/

	while(i && tree->array[i]->distance < tree->array[(i-1)/2]->distance)		/*rearrange the node so min is at the highest priority*/
	{
		tree->position[tree->array[i]->v] = (i-1)/2;
		tree->position[tree->array[(i-1)/2]->v] = i;
		heapnode_t **p1 = &tree->array[i];
		heapnode_t **p2 = &tree->array[(i-1)/2];
		swapnode(p1, p2);
		i=(i-1)/2;
	}
}

int isEmpty(heap_t* tree)		/*check if tree is empty*/
{
	return tree->size==0;
}


void swapnode(heapnode_t **a, heapnode_t **b)			/*function to swap node*/
{
	heapnode_t *tmp = *a;
	*a = *b;
	*b = tmp;
}

void intswap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}



