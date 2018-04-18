//Student Name : Ang Mink Yii
//Student ID : 565604
//Univeristy of Melbourne
//Tutorial time : 2:15pm Thursday

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "helpme.h"


int main(int argc, char **argv)
{
 	int number_of_cities;			/*number of cities*/
 	char filename[MAX+1];
	int src;						/*disaster location*/
	wrap_t **state;					
	city_t **town;
	graph_t *graph;					
	int *pathtracker;				/*an array to track the path taken*/
	int *dist = NULL;				/*an array containing the shortest paths of all cities*/

	if(argc != 2)
	{
		printf("Usage: helpme [insert file]\n");
		exit(EXIT_FAILURE);
	}

	strncpy(filename,argv[1],MAX);
	printf("FILENAME : %s\n",filename);
	state = parsingData(filename,&number_of_cities);	/*read data*/
	state = citylink(state,number_of_cities);			/*link all the cities*/
	town = unwrapper(state,number_of_cities);			/*throw the wrap struct away*/
	graph = creategraph(town,number_of_cities);			/*create a graph*/
	src = disaster_location(graph);						/*read disaster location*/
	graph = graphflipper(graph);						/*flip graph*/
	graph = neutralise(graph);							/*reallocate the pointers*/
	dist = initialisedist(dist,number_of_cities);		/*initialise distance array*/
	pathtracker = dijkstras(graph,src,dist);			/*find shortest path*/
	findsupply(graph,pathtracker,dist);					/*find supply from closest city*/

	return 0;
}








