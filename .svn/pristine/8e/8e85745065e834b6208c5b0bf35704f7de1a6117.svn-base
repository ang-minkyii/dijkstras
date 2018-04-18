#include<stdio.h>
#include<stdlib.h>


//structure to represent an adjacency list node
struct ajnode
{
	int dest;
	struct ajnode* next;	
};

typedef struct ajnode node_t;

//a structure to represent an adjacency list
struct ajlist
{
	struct ajnode *head;
};

typedef struct ajlist list_t;

//a structure to represent a graph. An array of adjacency lists.
struct graph
{
	int v; // number of  vertices in graph
	struct ajlist* array;
};

typedef struct graph graph_t;



void printgraph(graph_t* graph);
void addedge(graph_t* graph, int src, int dest);
node_t* newnode(int dest);
graph_t* createGraph(int V);


//function to create a new adjacency list node
node_t* newnode(int dest)
{
	node_t* nnode = (node_t*)malloc(sizeof(node_t));
	nnode->dest = dest;
	nnode->next = NULL;
	return nnode;     //pointer returned
}

//function that creates a graph
graph_t* createGraph(int V)
{
	int i;
	graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
	graph->v = V;

	//creata an array of adjacency lists
	graph->array = (list_t*)malloc(V*sizeof(list_t));

	//initialize each adjacency list as empty
	for(i=0;i<V;i++)
	{
		graph->array[i].head = NULL;
	}
	return graph;
}

//function to add an edge to an undirected graph
void addedge(graph_t* graph, int src, int dest)
{
	node_t* nnode = newnode(dest);
	nnode->next = graph->array[src].head;
	graph->array[src].head = nnode;
	nnode = newnode(src);
	nnode->next = graph->array[dest].head;
	graph->array[dest].head = nnode;
}


void printgraph(graph_t* graph)
{
	int c;
	for(c = 0; c < graph->v; c++)
	{
		node_t* pcrawl = graph->array[c].head;
		printf("\n%d",c);
		while(pcrawl)
		{
			printf(" -> %d",pcrawl->dest);
			pcrawl = pcrawl->next;
		}
		printf("\n");
	}
}


int main()
{
	int V = 5;
	graph_t* graph = createGraph(V);
	addedge(graph,0,4);
	addedge(graph,1,4);
	addedge(graph,1,3);
	addedge(graph,2,4);
	addedge(graph,4,3);

	printgraph(graph);

	return 0;


}












