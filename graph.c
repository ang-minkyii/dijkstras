#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "graph.h"
#include "binheap.h"




wrap_t** parsingData(char *filename, int *a)
{
	char *str;
	FILE *fp;
	int numstring = -1;			/*count number of incoming strings*/
	int c = 0;					/*the index for cities*/			
	int i,j;					
	int friends = 0;			/*record the number of neighbours*/
	int flag = 1;
	int value;					/*the first line in the input*/
	int cityid;					/*city ID*/
	int num;					/*integer from atoi*/
	int count;					/*another integer from atoi*/
	char string[MAX];
	wrap_t **city;



	fp = fopen(filename,"r");

	if(fp == NULL)
	{
		printf("ERROR opening file\n");
		exit(EXIT_FAILURE);
	}
	
	while(fscanf(fp,"%s",string) == 1)
	{
		if(numstring>-1)							/* -1 because the first string in the data input isn't city information*/
		{
			printf("String %2d is << %s >>\n",numstring,string);
		}
		numstring++;								/*count the number of incoming string*/

		if(flag)
		{
			value = atoi(string);
			*a = value;								/*the number in the first line of data*/
			wrap_t **cityarr = (wrap_t**)malloc(sizeof(wrap_t*)*value);
			city = cityarr;
			for(i=0;i<value;i++)					/*allocating memory for all incoming cities*/
			{
				city[i]=(wrap_t*)malloc(sizeof(wrap_t));
				city_t *info = (city_t*)malloc(sizeof(city_t));
				city[i]->cityinfo = info;
				int *travelarr = (int*)malloc(sizeof(int)*value);
				city[i]->travel = travelarr;
				for(j=0;j<value;j++)
				{
					city[i]->travel[j] = -1;		/*initialising all to -1 which indicates this city has no neighbour yet*/
				}
			}
			flag = 0;
		}else
		{

			str = strtok(string,"|");
			cityid = atoi(str);
			city[c]->cityinfo->ID = cityid;

			str = strtok(NULL,"|");
			strcpy(city[c]->cityinfo->cityname,str);
			
			str = strtok(NULL,"|");
			strcpy(city[c]->cityinfo->relief,str);
			
			str = strtok(NULL,":");

			if(str != NULL)
			{
				friends = friends + 1;
				num = atoi(str);
			}
		
			while(str != NULL)
			{
				str = strtok(NULL,",");
				count = atoi(str);
				city[c]->travel[num] = count;
				str = strtok(NULL,":");
				if(str != NULL)
				{
					friends = friends + 1;
					num = atoi(str);
				}
			}
			city[c]->cityinfo->num_neighbours = friends;
			c++;
			friends=0;
		}
	}
	return city;						/*a pointer pointing to all cities is returned*/
}



wrap_t** citylink(wrap_t** city, int c)				/*function to link cities together*/
{
	int i,j,k,l,b,z;								/*loop variables*/
	link_t **link;
	int x = 0;										/*index of the link pointer*/
	int travelnum;									/*number of neighbours*/

	for(i=0;i<c;i++)
	{
		travelnum = city[i]->cityinfo->num_neighbours;
		city[i]->cityinfo->next = (link_t**)malloc(sizeof(link_t*)*travelnum);		/*allocating memory for array pointing to neighbours*/
		link = city[i]->cityinfo->next;
		for(l=0;l<travelnum;l++)
		{
			link[l]=(link_t*)malloc(sizeof(link_t));						
		}

		for(j=0;j<c;j++)
		{
			if(city[i]->travel[j] > -1)						/*more than -1 means there's a neighbour with city ID j*/
			{
				for(k=0;k<c;k++)
				{
					if(city[k]->cityinfo->ID == j)
					{
						link[x]->citytown = (city_t*)city[k]->cityinfo;
						link[x]->traveltime = city[i]->travel[j];
						link[x]->ischecked = 0;
						x++;
					}
				}
			}
		}
		x = 0;
	}
	printf("\n");
	printf("Connection list\n----------------------------------------------\n");			/*print the list of connections*/
	for(b=0;b<c;b++)
	{
		if(city[b]->cityinfo->num_neighbours != 0)
		{
			printf("%12s",city[b]->cityinfo->cityname);
			for(z=0;z<city[b]->cityinfo->num_neighbours;z++)
			{
				city_t *temp = (city_t*)city[b]->cityinfo->next[z]->citytown;
				printf(" --> %12s",temp->cityname);
			}
			printf("\n");
		}
	}
	printf("-----------------------------------------------\nEnd of Report\n\n");
	return city;
}


city_t** unwrapper(wrap_t** city, int c)				/*function to get rid of the wrapping structure and left with the actual city struct*/
{
	city_t **town;
	int i;

	town = (city_t**)malloc(sizeof(city_t*)*c);
	for(i=0;i<c;i++)
	{
		town[i] = city[i]->cityinfo;
		free(city[i]);
	}
	return town;
}

graph_t* creategraph(city_t** town, int c)			/*function to create a graph with the city pointers in it*/
{
	graph_t *graph;

	graph = (graph_t*)malloc(sizeof(graph_t));
	graph->city = town;
	graph->numcities = c;
	return graph;
}


int disaster_location(graph_t* graph)
{
	int i;
	int src=0;										/*disaster location ID*/
	char *name = malloc(MAX * sizeof(char));

	printf("Enter City name : ");
	name = fgets(name, MAX, stdin);
	if(name[strlen(name) - 1] == '\n')
	{
		name[strlen(name) - 1] = '\0';
	}

	if(strlen(name)>MAX)							/*to prevent buffer overflow*/
	{
		fprintf(stderr,"ERROR! Name entered exceeded the number of characters this program can accept.\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<graph->numcities;i++)
	{
		if(strncmp(graph->city[i]->cityname,name,MAX) == 0)
		{
			printf("\nDisaster Location :\nCity ID = %d\nCityname = %s\n\n",graph->city[i]->ID,graph->city[i]->cityname);
			src = graph->city[i]->ID;
			break;
		}else if(i == graph->numcities-1)
		{
			printf("Error! City doesn't exist!\n");  
			exit(EXIT_FAILURE);
		}
	}
	return src;							/*return the disaster location's ID*/
}


int* dijkstras(graph_t *graph, int src, int *distance)			/*function to find shortest path*/
{
	int vertices = graph->numcities;
	int i,j,k,d,g,v;								/*looping variables*/
	int length;										/*distance from the extracted city to its neighbours*/
	int *dist;										/*a pointer to an array storing the shortest time*/
	int *parents;									/*a pointer to an array tracking the path taken*/

	heap_t* tree = heaptree(vertices);				/*create a binary heap*/

	tree->array = (heapnode_t**)malloc(sizeof(heapnode_t*)*vertices);		/*allocate memory for array of pointers to all the heap node*/
	tree->position = (int*)malloc(sizeof(int)*vertices);				/*needed for decreasekey*/
	dist = (int*)malloc(sizeof(int)*vertices);							/*allocate memory for dist array*/
	parents = (int*)malloc(sizeof(int)*vertices);						/*allocate memory for parents array*/

	for(i=0;i<vertices;i++)
	{
		dist[i] = INT_MAX;											/*set distance as int max*/
		tree->array[i] = newheapnode(i,dist[i]);					/*create heap node*/
		tree->position[i] = i;										/*update the position*/
	}

	dist[src] = 0;											/*distance set to zero*/
	tree->position[src] = src;
	decreasekey(tree,src,dist[src]);						/*decrease the dist/timetaken value from int max to what it should be*/
	tree->size = vertices;

	for(g = 0;g<vertices;g++)
	{
		parents[g] = INT_MAX;								/*setting the path tracker to int max*/
	}

	parents[src] = -1;									/*set the disaster location to -1*/
	while(!isEmpty(tree))
	{
		heapnode_t *minnode = extractmin(tree); 			/*extract the node with minimum distance based on the dist array*/
		int u = minnode->v;		
		for(j=0;j<vertices;j++)
		{
			if(graph->city[j]->ID == u)		
			{
				if(graph->city[j]->num_neighbours != 0)		/*check if this city has any neighbours*/
				{
					for(k=0;k<graph->city[j]->num_neighbours;k++)     
					{
						length = graph->city[j]->next[k]->traveltime;			/*time taken to travel to its neighbour*/
						city_t *neighbours =(city_t*)graph->city[j]->next[k]->citytown;
						d = neighbours->ID;										/*the neighbour's city id*/
						if(isinheap(tree,d) && dist[u] != INT_MAX && length + dist[u] < dist[d])
						{
							dist[d] = dist[u] + length;						/*update the time taken*/
							decreasekey(tree,d,dist[d]);					/*decrease from int max to dist[d]*/
							parents[d] = u;									/*track the path*/
						}
					}
				}
			}
		}
	}

	for(v=0;v<vertices;v++)
	{
		distance[v] = dist[v];					/*as a function can't return two arrays. one is passed in as a pointer from the main*/
	}
	return parents;							/*one is returned*/
}
		

void debug(char *string)
{
	if(DEBUG)
	{
		fprintf(stdout,"%s\n",string);
		fflush(stdout);
	}
}


graph_t* graphflipper(graph_t* graph)				/*function to flip the graph direction*/
{
	int u = graph->numcities;
	int i,j,k,a,z,g,v;				/*loop variables*/
	int code, time1, time2, temp; /* code - ID time 1 & 2 and temp are the time swapping variable*/
		

	for(i=0;i<u;i++)
	{
		z = graph->city[i]->num_neighbours;
		for(j=0;j<z;j++)
		{
			city_t *neighb = (city_t*)graph->city[i]->next[j]->citytown;
			time1 = graph->city[i]->next[j]->traveltime;      /*time taken to get to neighbours*/
			code = neighb->ID;
			for(k=0;k<u;k++)
			{
				if(graph->city[k]->ID == code)
				{
					if(graph->city[k]->num_neighbours != 0)
					{
						for(a=0;a<graph->city[k]->num_neighbours;a++)
						{	
							city_t *flip = (city_t*)graph->city[k]->next[a]->citytown;
							if(graph->city[i]->next[j]->ischecked != 1)					/*check if the direction has been flipped*/
							{															/*ischecked 1 means already checked*/
								if(flip->ID == graph->city[i]->ID && graph->city[k]->next[a]->ischecked != 1)
								{
									time2 = graph->city[k]->next[a]->traveltime;
									temp = time2;							/*swap time*/
									time2 = time1;
									time1 = temp;
									graph->city[i]->next[j]->traveltime = time1;			/*update time*/
									graph->city[k]->next[a]->traveltime = time2;			/*update time*/
									graph->city[k]->next[a]->ischecked = 1;					/*update ischecked*/
									graph->city[i]->next[j]->ischecked = 1;					/*update ischecked*/
									break;
								}
								if(a == graph->city[k]->num_neighbours - 1)			/*after the loop and still cant find the direction from neighbour city back to this city*/
								{	
									graph->city[k]->num_neighbours = graph->city[k]->num_neighbours + 1; 
									link_t **exchange = (link_t**)malloc(sizeof(link_t*)*(graph->city[k]->num_neighbours));		/*create a new array of pointers*/
									for(v=0;v<graph->city[k]->num_neighbours;v++)
									{
										exchange[v] = (link_t*)malloc(sizeof(link_t));
									}
									for(g=0;g<graph->city[k]->num_neighbours-1;g++)				/*reallocate the array of pointers it already has*/
									{
										exchange[g] = graph->city[k]->next[g];
									}
									
									int h = graph->city[k]->num_neighbours-1;
									exchange[h]->citytown =(city_t*)graph->city[i];				/*add in the new direction into the array*/
									graph->city[k]->next = exchange;
									graph->city[k]->next[h]->traveltime = time1;
									
									graph->city[i]->next[j]->traveltime = INT_MAX;				/*since this is a one way direction*/
																								/*the opposite/original direction is set to int max and to be removed later*/
									graph->city[i]->next[j]->ischecked = 1;						/*update the ischecked value*/
									graph->city[k]->next[h]->ischecked = 1;
									break;
								}
							}
						}
					}else
					{	/*this is for city with any neighbours and other cities point to it*/
						graph->city[k]->num_neighbours = graph->city[k]->num_neighbours + 1;		/*if pointer is added, number of neighbours +1*/
						link_t **replace = (link_t**)malloc(sizeof(link_t*));
						replace[0] = (link_t*)malloc(sizeof(link_t));							/*allocate memory for an array of pointers*/
						replace[0]->citytown = (city_t*)graph->city[i];
						graph->city[k]->next = replace;
						graph->city[k]->next[0]->traveltime = time1;						/*update time*/
					
						graph->city[i]->next[j]->traveltime = INT_MAX;						/*set original pointer to int max*/			
						graph->city[i]->next[j]->ischecked = 1;
						graph->city[k]->next[0]->ischecked = 1;								/*update the ischecked value*/
						break;
					}
				}
			}
		}
	}	
	return graph;
}



graph_t* neutralise(graph_t* graph)				/*this function is to free the unused pointers wiht int max before*/
{
	int a,b,c,z;							/*loop variable*/
	int x = 0;

	c=graph->numcities;						/*number of cities*/

	for(a=0;a<c;a++)
	{
		z=graph->city[a]->num_neighbours;
		link_t **reallocate_array = (link_t**)malloc(sizeof(link_t)*z);
		for(b=0;b<z;b++)
		{
			if(graph->city[a]->next[b]->traveltime < INT_MAX)				/*if its int max ignore it*/
			{
				reallocate_array[x] = (link_t*)malloc(sizeof(link_t));
				reallocate_array[x] = graph->city[a]->next[b];
				x++;
			}
		}
		free(graph->city[a]->next);								/*free the array of pointers*/
		graph->city[a]->next = reallocate_array;					/*reallocate new set of pointers to the city*/
		graph->city[a]->num_neighbours = x;						/*update the number of neighbours*/
		x=0;
	}
	return graph;
}


void findsupply(graph_t *graph, int parents[],int dist[])			/*this function is to find cities with supply*/
{

	char *supply = (char*)malloc(sizeof(char) * (MAX + 1));
	int len;
	int a,k,i,j;
	int min = INT_MAX;
	int storeid = -1;
	int flag=0;

	menu();

	supply = fgets(supply, MAX, stdin);


	len = strlen(supply);								/*return the number of chars in string*/

	if(supply[0] == '\n')								/*if user didn't specify what supply is needed which is determined by just a new line*/
	{
		for(i=0;i<graph->numcities;i++)
		{
			if(dist[i] < min && dist[i] != INT_MAX && dist[i] != 0) 		/*find the closest city from the dist array*/
			{
				for(j=0;j<graph->numcities;j++)
				{
					if(graph->city[j]->ID == i)
					{
						if(graph->city[j]->relief[0] != 'X')			/*find if this city has any supply*/
						{
							min = dist[i];								/*update the minumum time taken of available city with supply*/
							storeid = j;								/*store the index of the city*/
						}
					}
				}
			}
		}
		printf("USER didn't specify any relief needed\n");
		printf("Below is the available supply from the closest city\n");
		retrieve(graph,graph->city[storeid]->relief[0],parents,dist);		/*retrieve the path and supply*/
		flag = 1;	
	}
	
	if(flag == 0)
	{
		printf("Finding closest city with relief %s\n",supply);
	}
	
	for(a=0;a<len;a++)
	{
		k=supply[a];
		if(k != 'X')
		{
			if(checksupply(k,'B','F','W','M','D') == 1)				/*check if the relief entered is available*/
			{
				retrieve(graph,k,parents,dist);						/*find the shortest time to deliver specified supply*/
			}
		}else
		{												/*if user didn't specify any supply but said X*/
			retrieve(graph,'B',parents,dist);
			retrieve(graph,'F',parents,dist);
			retrieve(graph,'W',parents,dist);
			retrieve(graph,'D',parents,dist);
			retrieve(graph,'M',parents,dist);
		}
	}
}


int checksupply(char a, char b, char c, char d, char e, char f)	/*check if supply is available*/
{
	char supply[5];
	supply[0] = b;
	supply[1] = c;
	supply[2] = d;
	supply[3] = e;
	supply[4] = f;
	int flag = 0;
	int i;


	for(i=0;i<5;i++)
	{
		if(a == supply[i])
		{
			flag = 1;
		}
	}

	if(flag == 1)
	{
		return 1;
	}else
	{
		return 0;
	}
}


void retrieve(graph_t *graph,char supply, int parents[], int dist[])	/*function to retrieve the path*/
{
	int i,j,x;						/*loop variable*/
	int distance = INT_MAX;			/*variable to get the closest city*/
	int updateid;
	char name[MAX];

	for(i=0;i<graph->numcities;i++)
	{
		x = strlen(graph->city[i]->relief);
		for(j=0;j<x;j++)
		{
			if(graph->city[i]->relief[j] == supply)			/*if supply is found*/
			{
				if(dist[graph->city[i]->ID] < distance)			/*if a shorter time is found*/
				{
					updateid = graph->city[i]->ID;				/*update the city id*/
					distance = dist[updateid];					/*update the time*/
					strcpy(name,graph->city[i]->cityname);
					break;
				}
			}
		}
	}

	if(distance != 0 && distance != INT_MAX)	/*closest city found*/
	{
		printf("\n%c",supply);
		printf("%5d %10s",updateid,name);
		printf("%5d hrs\n",distance);
		printf("		%d    %s\n",updateid,name);
		trackpath(graph,parents,updateid,supply);			/*retrieve/track the path taken*/
	}else
	{
		printf("WARNING! - ");
		printf("Supply %c can't be delivered\n",supply);
	}
	printf("\n");
}
	
void trackpath(graph_t *graph, int parents[], int id, char supply)	/*function to retrieve the path taken*/
{

	int i,j;
	int hours,travelhours=0,path;
	int cityid = id;

	path = parents[cityid];							/*get the next city's ID*/

	while(path != -1 && path != INT_MAX)				/*while the target hasn't been reached*/
	{
		for(i=0;i<graph->numcities;i++)
		{
			if(graph->city[i]->ID == path)
			{
				printf("		%d    %s\n",path,graph->city[i]->cityname);
				for(j=0;j<graph->city[i]->num_neighbours;j++)
				{
					city_t* temp = (city_t*)graph->city[i]->next[j]->citytown;
					hours = graph->city[i]->next[j]->traveltime;			/*record the time taken to get to next city*/
					if(temp->ID == cityid)									/*next city found*/
					{
						travelhours = travelhours + hours;					/*update the time*/
						path = parents[path];								/*go to the next city*/
						cityid = graph->city[i]->ID;
					}
				}
			}
		}
	}
	printf("\n");
}


void menu()
{
	printf("List of Available Supplies\n--------------------------\n");
	printf(" B - Blanket\n");
	printf(" F - Food\n");
	printf(" W - Water\n");
	printf(" D - Digging Equipment\n");
	printf(" M - Medicine\n--------------------------\n");
	printf("What supplies do you need?\n");
}



int* initialisedist(int *dist, int c)				/*function to initialise dist array*/
{
	dist = (int*)malloc(sizeof(int)*c);
	return dist;
}









