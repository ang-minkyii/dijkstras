#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define P 0.5
#define MAX 256

struct node 
{
	int number;
	char string[MAX];
	struct node **next;
};
typedef struct node node_t;

struct head 
{
	node_t *header;
	int level;	
};
typedef struct head header_t;

int main(int argc, char **argv)
{

	FILE *fp;

	fp = fopen(filename,"r");
	

	while(fscanf(fp,"%d %s",&value,string)==2)
	{

	}




}

float randf()
{
	return (float)rand()/RAND_MAX;
}

void seed_rand()
{
	srand((unsigned)time(NULL));
}

int random_level()
{
	int lvl =0;

	while(randf() < P && lvl < MAX_LEVEL)
	{
		lvl++;
	}
	return lvl;
}

node_t *createnode(int level, value, char *str)
{
	node_t *temp;
	temp = (node_t*)malloc(sizeof(node_t));
	temp->next = (node_t**)malloc(sizeof(node_t*)*level+1);
	temp->number = value;
	strncpy(temp->string,str,MAX);

	return temp;
}

void insertion(header_t *head, int key, char *str)
{	
	node_t *temp = head->header;
	node_t *update[MAX_LEVEL +1];
	memset(update,0,MAX_LEVEL+1);


	for(int i = head->level;i>=0;i--)
	{
		while(temp->next[i] != NULL && temp->next[i]->number < key)
		{
			temp = temp->next[i];
		}
		update[i]=temp;
	}
	temp = temp->next[0];

	if(temp!=NULL)
	{
		if(temp->number == key)
		{
			return;
		}
	}
	lvl = random_level();

	if(lvl > head->level)
	{
		for(i=head->level+1;i<=lvl;i++)
		{
			update[i] = head->header;
		}
		head->level = lvl;
	}
	temp = createnode(lvl,key,str);
	for(int i=0;i<=lvl;i++)
	{
		temp->next[i] = update[i]->next[i];
		update[i]->next[i] = temp;
	}
}


header_t *createheader()
{
	header_t *head = (header_t*)malloc(sizeof(header_t));
	head->header = createnode(MAX_LEVEL,0,"\0");
	head->level = 0;

	return head;
}

void search(header_t *head, int key)
{
	node_t *head = head->header;
	node_t *temp;
	node_t *update[MAX_LEVEL+1];
	memset(update,0,MAX_LEVEL+1);


	temp = head;
	for(int k=head->level;k>=0;k--)
	{
		while(temp->next[k] != NULL && temp->next[k]->number != key)
		{
			temp = temp->next[k];
		}
	}
	temp = temp->next[0];

	if(temp != NULL)
	{
		if(temp->number == key)
		{
			printf("found\n");
		}else
		{
			printf("not found\n");
		}
	}else
	{
		printf("not found\n");
	}
}


