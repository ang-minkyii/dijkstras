#define MAX 256
#define DEBUG 1
#define DELIM ",:|"
#define SUPPLIES "BFWDM"



struct linknode
{
	int traveltime;					/*time taken to get to its neighbour*/
	void *citytown;					/*pointers to next city*/
	int ischecked;					/*to check if this route's direction has been flipped*/
};

typedef struct linknode link_t;		


struct ajdlistnode
{
	int ID;							/*city ID*/
	char cityname[MAX];				/*city's name*/
	char relief[MAX];				/*relief*/
	link_t **next;					/*points to an array of pointers of the struct above*/
	int num_neighbours;				/*number of neighbours*/
};

typedef struct ajdlistnode city_t;

struct tempnode						/*this a structure wrapping the real city*/
{
	city_t *cityinfo;				/*pointer to the actual city*/
	int *travel;					/*an array storing information to link to other cities*/
};

typedef struct tempnode wrap_t;

struct graphnode

{
	city_t **city;					/*an array of pointers pointing to all cities*/
	int numcities;					/*number of cities*/
};
typedef struct graphnode graph_t;



wrap_t** parsingData(char *filename, int *a);
wrap_t** citylink(wrap_t** city, int c);
city_t** unwrapper(wrap_t** city, int c);
int disaster_location(graph_t* graph);
int checksupply(char a, char b, char c, char d, char e, char f);
int* initialisedist(int *dist, int c);
int* dijkstras(graph_t *graph, int src, int *distance);
graph_t* graphflipper(graph_t* graph);
graph_t* neutralise(graph_t* graph);
graph_t* creategraph(city_t** town, int c);
void findsupply(graph_t *graph, int parents[], int dist[]);
void menu();
void retrieve(graph_t *graph,char supply, int parents[], int dist[]);
void trackpath(graph_t *graph, int parents[], int id, char supply);
void debug(char *string);





