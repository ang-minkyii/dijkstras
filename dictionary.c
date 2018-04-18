#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 256

struct node
{
	int number;
	char string[MAX];
	struct node *next;
};

typedef struct node node_t;


node_t* createnode(int num, char *string);
void traverse(node_t *head);
void insertion(node_t *head);
void deletion(node_t *head);




int main(int argc, char **argv)
{
	int number;
	FILE *fp;
	char string[MAX];
	node_t *head;
	node_t *temp;
	head = NULL;
	node_t *ptr;

	if(argc != 2)
	{
		fprintf(stdout,"Usage : program [file]\n");
		exit(EXIT_FAILURE);
	}
	fp=fopen(argv[1],"r");
	if(fp == NULL)
	{
		fprintf(stdout,"ERROR opening file\n");
		exit(EXIT_FAILURE);
	}

	while(fscanf(fp,"%d %s",&number,string)==2)
	{
		temp = createnode(number,string);
		if(head == NULL)
		{
			temp->next = head;
			head = temp;
		}else if(temp->number <= head->number)
		{
			ptr = head;
			while(ptr->next != NULL)
			{
				if(temp->number <= ptr->next->number)
				{
					ptr = ptr->next;
					if(ptr->next == NULL)
					{
						temp->next = NULL;
						ptr->next = temp;
						break;
					}
				}else
				{
					temp->next = ptr->next;
					ptr->next = temp;
					break;
				}
			}
		}else
		{
			temp->next = head;
			head = temp;
		}
	}
	fclose(fp);

	traverse(head);
	insertion(head);
	traverse(head);
	deletion(head);




	return 0;


}

node_t* createnode(int num, char *string)
{
	node_t *tmp;

	tmp=(node_t*)malloc(sizeof(node_t));
	tmp->number = num;
	strcpy(tmp->string,string);

	return tmp;
}

void traverse(node_t *head)
{
	node_t *p = head;

	while(p!=NULL)
	{
		printf("%d\n",p->number);
		p=p->next;
	}
}

void insertion(node_t *head)
{

	char filename[MAX];
	printf("Enter file name : ");
	scanf("%s",filename);
	FILE *fp;
	node_t *temp;
	int number;
	char string[MAX];
	node_t *ptr;


	fp = fopen(filename,"r");

	while(fscanf(fp,"%d %s",&number,string)==2)
	{
		temp = createnode(number,string);
		if(head == NULL)
		{
			temp->next = head;
			head = temp;
		}else if(temp->number <= head->number)
		{
			ptr = head;
			while(ptr->next != NULL)
			{
				if(temp->number <= ptr->next->number)
				{
					ptr = ptr->next;
					if(ptr->next == NULL)
					{
						temp->next = NULL;
						ptr->next = temp;
						break;
					}
				}else
				{
					temp->next = ptr->next;
					ptr->next = temp;
					break;
				}
			}
		}else
		{
			temp->next = head;
			head = temp;
		}
	}
}

void deletion(node_t *head)
{

	int value;

	printf("which node to do you want to delete?\n");
	scanf("%d",&value);

	/*delete code*/x

}
