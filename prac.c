#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


#define MAX 256

struct tree
{
	int id;
	struct tree **next;
};

typedef struct tree node_t;

struct queue
{
	int number;
	struct queue *next;
};

typedef struct queue queue_t;

node_t *createnode(int id);
node_t **rotation(node_t *a, node_t *b, node_t **tmp, int num);
void debug(char *name);
void preorder(node_t *node);
void inorder(node_t *node);
void postorder(node_t *node);
queue_t *deQ(queue_t *Q, int *j);
queue_t *enQ(queue_t *Q, node_t *node);
int isempty(queue_t *Q);
queue_t *createqueue();
void breadth(node_t *node, node_t **tmp, int num);
node_t **readfile(int *i, char *filename);
void menu();
void printfunc(node_t **tmp, int num);




int main(int argc, char **argv)
{
	int choice;
	char c;
	node_t **tmp;
	int j,num1,num2;
	char filename[MAX];

	if(argc != 2)
	{
		fprintf(stderr,"Usage : Program [file]\n");
		exit(EXIT_FAILURE);
	}

	strcpy(filename,argv[1]);
	tmp = readfile(&j,filename);
	
	do
	{
		menu();
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				debug("Preorder dfs initiating...");
				debug("");
				preorder(tmp[1]);
				break;
			case 2:
				debug("Inorder dfs initiating...");
				debug("");
				inorder(tmp[1]);
				break;
			case 3:
				debug("Postorder dfs initiating...");
				debug("");
				postorder(tmp[1]);
				break;
			case 4:
				debug("Breadth first search initiating...");
				debug("");
				breadth(tmp[1],tmp,j);
				break;
			case 5:
				printf("Enter two nodes to be rotated\n");
				scanf("%d %d",&num1,&num2);
				debug("\nBefore rotation");
				printfunc(tmp,j);
				printf("\nRotating node %d and %d...\n",num1,num2);
				tmp = rotation(tmp[num1],tmp[num2],tmp,j);
				printfunc(tmp,j);
				breadth(tmp[1],tmp,j);
				break;
			default:
				printf("Wrong Choice\n");
		}
	}while(choice != 0);

	return 0;	
}

void printfunc(node_t **tmp, int num)
{
	debug("Begin printing");
	for(int v=1; v<num;v++)
	{
		if(tmp[v]->next[0] != NULL && tmp[v]->next[1] != NULL)
		{
			printf("%d is connected to %d and ",tmp[v]->id,tmp[v]->next[0]->id);
			printf("%d\n",tmp[v]->next[1]->id);
		}else
		{
			printf("%d does not have children\n",tmp[v]->id);
		}
	}
}

void menu()
{
	debug("");
	debug("-----Menu-----");
	debug("|1.Preorder  |");
	debug("|2.Inorder   |");
	debug("|3.Postorder |");
	debug("|4.BFS       |");
	debug("|5.Rotation  |");
	debug("--------------");
	debug("Pick One :)");
}

node_t *createnode(int id)
{
	node_t *ptr;
	ptr = (node_t*)malloc(sizeof(node_t));
	ptr->id = id;
	ptr->next = (node_t**)malloc(sizeof(node_t*)*2);

	for(int i=0;i<2;i++)
	{
		ptr->next[i]=(node_t*)malloc(sizeof(node_t));
		ptr->next[i]=NULL;
	}

	return ptr;
}

node_t **rotation(node_t *a, node_t *b, node_t **tmp, int num)
{

	a->next[0] = b->next[1];
	b->next[1] = a;


	for(int i=1;i<num;i++)
	{
		if(tmp[i]->next[0]->id == a->id)
		{
			tmp[i]->next[0] = b;
			break;
		}
		if(tmp[i]->next[1]->id == a->id)
		{
			tmp[i]->next[1] = b;
			break;
		}
	}
	return tmp;
}

node_t **readfile(int *i, char *filename)
{
	int value;
	int num=0;
	node_t **tmp;
	int array[MAX];
	int j=1;
	char string[MAX];
	char *token;
	FILE *fp;

	fp = fopen(filename,"r");
	while(fscanf(fp,"%d",&value)==1)
	{
		num++;
		array[j]=value;
		j++;
	}
	array[j]=INT_MAX;

	tmp = (node_t**)malloc(sizeof(node_t*)*j);

	for(int a=1;a<j;a++)
	{
		tmp[a] = (node_t*)malloc(sizeof(node_t));
		tmp[a] = createnode(array[a]);
	}

	for(int b=1;b<j;b++)
	{
		if(tmp[b*2] != NULL && b*2 < j)
		{
			tmp[b]->next[0] = tmp[b*2];
		}
		if(tmp[b*2+1] != NULL && b*2+1 < j)
		{	
			tmp[b]->next[1] = tmp[b*2+1];
		}
	}

	
	printf("\n");
	for(int v=1; v<j;v++)
	{
		if(tmp[v]->next[0] != NULL && tmp[v]->next[1] != NULL)
		{
			printf("%d is connected to %d and ",tmp[v]->id,tmp[v]->next[0]->id);
			printf("%d\n",tmp[v]->next[1]->id);
		}else
		{
			printf("%d does not have children\n",tmp[v]->id);
		}
	}
	*i = j;
	return tmp;
}

void debug(char *name)
{
	fprintf(stdout,"%s\n",name);
	fflush(stdout);
}

void preorder(node_t *node)
{
	if(node == NULL)
	{
		return;
	}
	printf("%d visited\n",node->id);
	preorder(node->next[0]);
	preorder(node->next[1]);
}

void inorder(node_t *node)
{
	if(node == NULL)
	{
		return;
	}
	inorder(node->next[0]);
	printf("%d visited\n",node->id);
	inorder(node->next[1]);
}

void postorder(node_t *node)
{
	if(node == NULL)
	{
		return;
	}
	postorder(node->next[0]);
	postorder(node->next[1]);
	printf("%d visited\n",node->id);
}

int isempty(queue_t *head)
{
	if(head == NULL)
	{
		return 0;
	}
	return 1;
}

queue_t *createqueue()
{
	queue_t *head = (queue_t*)malloc(sizeof(queue_t));
	head = NULL;

	return head;
}

void breadth(node_t *node, node_t **tmp, int num)
{
	queue_t *head;
	int key;

	head = createqueue();
	head = enQ(head,node);
	while(isempty(head)==1)
	{
		head = deQ(head,&key);
		printf("%d visited\n",key);
		for(int i=1; i<num;i++)
		{
			if(tmp[i]->id == key)
			{
				if(tmp[i]->next[0]!=NULL)
				{
					head = enQ(head,tmp[i]->next[0]);
					break;
				}
			}
		}
		for(int i=1; i<num;i++)
		{
			if(tmp[i]->id == key)
			{
				if(tmp[i]->next[1]!=NULL)
				{
					head = enQ(head,tmp[i]->next[1]);
					break;
				}
			}
		}
	}
}

queue_t *enQ(queue_t *head, node_t *node)
{
	queue_t *temp;
	temp = (queue_t*)malloc(sizeof(queue_t));

	temp->number = node->id;

	temp->next = head;
	head = temp;
	return head;
}

queue_t *deQ(queue_t *head, int *j)
{
	int lol;
	queue_t *ptr;
	queue_t *curr;
	ptr = head;

	if(ptr->next!=NULL)
	{
		while(ptr->next!=NULL)
		{
			curr = ptr;
			ptr = ptr->next;
		}
		lol = ptr->number;
		curr->next = ptr->next;
		free(ptr);
	}else
	{
		if(ptr->next == NULL)
		{
			lol = ptr->number;
			head = ptr->next;
			free(ptr);
		}
	}
	*j = lol;
	return head;
}