#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIME   7 
#define PRIME2  137
#define MAX 256



struct node 
{
	int id;
	struct node *next;
};

typedef struct node hash_t;

struct table
{
	int size;
	hash_t **numbers;
};

typedef struct table table_t;


table_t *createtable(int size);
int hash(int key);
void printhash(table_t *hashtable);
void debug(char *message);
void searchkeys(table_t *hashtable, int key);
int intlen(int key);

int main(int argc, char **argv)
{

	int tablesize;
	int num, value;
	char val[MAX];
	int array[MAX];
	table_t *hashtable;
	int i=0;
	hash_t *temp;
	char c;

	if(argc != 2)
	{
		fprintf(stdout,"Usage : program [tablesize]\n");
		exit(EXIT_FAILURE);
	}

	tablesize = atoi(argv[1]);

	hashtable = createtable(tablesize);

	for(int i=0; i<tablesize; i++)
	{
		hashtable->numbers[i] = NULL;
	}

	printf("Enter number \n");
	while(scanf("%s",val)==1)
	{	
		if(val[strlen(val)-1] == '\n')
		{
			val[strlen(val)-1] = '\0';
		}
		value = atoi(val);
		if(i<tablesize)
		{
			int hashvalue = hash(value);
			printf("hashed value = %d\n",hashvalue);
			if(hashtable->numbers[hashvalue] == NULL)
			{	
				hashtable->numbers[hashvalue] = (hash_t*)malloc(sizeof(hash_t));
				hashtable->numbers[hashvalue]->id = value;
				hashtable->numbers[hashvalue]->next = NULL;
				i++;
			}else
			{
				temp = hashtable->numbers[hashvalue];
				hash_t *current = (hash_t*)malloc(sizeof(hash_t));
				current->id = value;
				current->next = temp;
				hashtable->numbers[hashvalue] = current;
				i++;
			}
		}else
		{
			printf("value %d is excessive (table size exceeded)\n",value);
		}
	}
	c = getchar();c
	printhash(hashtable);
	printf("Enter value to search\n");
	scanf("%d",&num);
	searchkeys(hashtable,num);

	return 0;
}

int intlen(int key)
{
	int end;

	while(key > 0)
	{
		key = key/10;
		end++;
	}
	return end;
}

int hash(int key)
{
	int newnumber;

	newnumber = ((PRIME2*key)%(PRIME));

	return newnumber;
}

table_t *createtable(int size)
{
	table_t *hashtable = (table_t*)malloc(sizeof(table_t));
	hashtable->size = size;
	hashtable->numbers = (hash_t**)malloc(sizeof(hash_t*)*size);
	return hashtable;
}

void printhash(table_t *hashtable)
{
	int i;

	for(i=0;i<hashtable->size;i++)
	{	
		hash_t *temp = hashtable->numbers[i];
		if(temp != NULL)
		{
			printf("hashtable->numbers[%2d]",i);
			while(temp != NULL)
			{
				printf("-> %3d ",temp->id);
				temp = temp->next;
			}
			printf("\n");
		}else
		{
			printf("hashtable->numbers[%2d]-> NULL\n",i);
		}
	}
}

void debug(char *message)
{
	fprintf(stdout,"%s\n",message);
	fflush(stdout);
}

void searchkeys(table_t *hashtable, int key)
{
	int hashnum;
	hash_t *temp;

	hashnum = hash(key);
	temp = hashtable->numbers[hashnum];

	while(temp != NULL)
	{
		if(temp->id == key)
		{
			printf("Key %d is found at hashtable->numbers[%d]\n",key,hashnum);
		}
		temp = temp->next;
	}
}
