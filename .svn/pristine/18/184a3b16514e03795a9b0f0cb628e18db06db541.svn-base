#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpme.h"



int main(int argc, char **argv)
{
	//read the data such that the first line is separated as it determines the number of vertices for my graph
	
	char filename[MAX];


	if(argc != 2)
	{
		printf("Usage: helpme [insert file]\n");
		exit(EXIT_FAILURE);
	}

	strcpy(filename,argv[1]);
	printf("FILENAME : %s\n",filename);
	parsingData(filename);

	return 0;
}


void parsingData(char *filename)
{
	char *str;
	FILE *fp;
	int x = 0;
	int i = 0;
	int flag = 0;
	int val;
	char string[MAX];
	int count = 0;
	char A[MAX][MAX];
	int j;


	fp = fopen(filename,"r");

	if(fp == NULL)
	{
		printf("ERROR opening file\n");
		exit(EXIT_FAILURE);
	}
	
	while(fscanf(fp,"%s",string) == 1)
	{
		x++;
		printf("String %d is << %s >>\n",x,string);
		str = strtok(string,DELIM);
		strcpy(A[count],str);
		while(str != NULL)
		{
			if(flag == 0)
			{	
				i++;
				printf("flagged,part %d is %s\n",i,str);
				val = atoi(str);
				printf("int = %d\n",val);
				str = strtok(NULL,DELIM);
				flag = 1;
			}else
			{
				strcpy(A[count],str);
				printf("string stored = %s\n",A[count]);
				i++;
				count++;
				printf("part %d is %s\n",i,str);
				str = strtok(NULL,DELIM);
			}
		}
		i = 0;

		
		//storing the data
	}
}

