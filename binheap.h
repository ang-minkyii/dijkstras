#include <stdbool.h>

struct minheapnode
{
	int v;					/*vertex*/
	int distance;				/*travel time from this city to disaster location*/
};

typedef struct minheapnode heapnode_t;


struct minheaptree
{
	int numberheaps;					/*total number of cities*/
	int size;							/*instantaneous number of cities left in the binary heap*/
	int *position;						/*needed for decreasekey*/
	heapnode_t **array;					/*an array of pointers to all the heap nodes*/
};

typedef struct minheaptree heap_t;



int isEmpty(heap_t* tree);					/*check if binary heap is empty*/
heap_t* heaptree(int numnode);					/*create a tree*/
heapnode_t* newheapnode(int v, int dist);			/*create new node*/
heapnode_t* extractmin(heap_t* tree);				/*extract the min node from the tree*/
bool isinheap(heap_t *tree, int d);
void heapify(heap_t* tree, int i);				/*rearrange the tree*/
void swapnode(heapnode_t **a, heapnode_t **b);				/*swap node in tree*/
void decreasekey(heap_t* tree, int src, int dist);			/*decrease the distance of a node*/
