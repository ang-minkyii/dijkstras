#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define INT_MAX 9999


int **readfile(char *filename, int **array, int *k);
void debug(char *message);
void printmatrix(int **dist, int nrows, int ncols);
void floydwarshall(int **A,int num);

int main(int argc, char **argv)
{
	int **graph;
	char filename[MAX];
	int j;

	if(argc != 2)
	{
		fprintf(stdout,"Usage : Program [File]\n");
		exit(EXIT_FAILURE);
	}

	strcpy(filename,argv[1]);
	graph = readfile(filename,graph,&j);
	printmatrix(graph,j,j);
	floydwarshall(graph,j);
	return 0;
}

int **readfile(char *filename, int **array, int *k)
{
	int flag = 1;
	int num;
	FILE *fp;
	char string[MAX];
	fp = fopen(filename,"r");
	char *token;
	int cityid; 
	int neighboursid;


	while(fscanf(fp,"%s",string)==1)
	{
		if(flag)
		{
			num = atoi(string);
			*k = num;
			array = (int**)malloc(sizeof(int*)*num);
			for(int v=0;v<num;v++)
			{
				array[v] = (int*)malloc(sizeof(int));
			}
			for(int i=0;i<num;i++)
			{
				for(int j=0;j<num;j++)
				{
					array[i][j] = INT_MAX;
				}
			}
			flag = 0;
		}else
		{
			token = strtok(string,"|");
			//printf("%s\n",token);
			cityid = atoi(token);
			array[cityid][cityid] = 0;
			token = strtok(NULL,"|");
			//printf("%s\n",token);
			token = strtok(NULL,"|");
			//printf("%s\n",token);
			while(token != NULL)
			{
				token = strtok(NULL,",|:");
				if(token != NULL)
				{
					neighboursid = atoi(token);
				}
				token = strtok(NULL,",|:");
				if(token != NULL)
				{
					array[cityid][neighboursid] = atoi(token);
				}
			}
		}
	}
	return array;
}

void debug(char *message)
{
	fprintf(stdout,"%s\n",message);
	fflush(stdout);
}

void printmatrix(int **dist, int nrows, int ncols)
{
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < nrows; j++)
        {
            if (dist[i][j] == INT_MAX || dist[i][j] > INT_MAX || dist[i][j] < 0)
            {
                printf("%7s", "INF");
            }else
            {
                printf ("%7d", dist[i][j]);
            }
        }
        printf("\n");
    }
}

void floydwarshall(int **A,int num)
{
	int **dist,i,j,k;

	dist = (int**)malloc(sizeof(int*)*num);
	for(int v=0;v<num;v++)
	{
		dist[v]=(int*)malloc(sizeof(int));
	}

	for(i=0;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
			dist[i][j] = A[i][j];
		}
	}


	for(k=0;k<num;k++)
	{
		for(i=0;i<num;i++)
		{
			for(j=0;j<num;j++)
			{
				if((dist[i][k]*dist[k][j] < dist[i][j] != 0) && (i!=j))
				{
					if(dist[i][k] + dist[k][j] < dist[i][j] || (dist[i][j] == 0))
					{
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
	}
	printf("Printing using function:\n");
	printmatrix(dist,num,num);
	printf("Printing in calling function:\n");
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (dist[i][j] == INT_MAX || dist[i][j] > INT_MAX || dist[i][j] < 0)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

