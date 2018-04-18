char *ptr;

// declares an array of size strlen("trolo....");
char *string = "troloololol";
ptr = string;

int size = get_size(char *line1);

int *ptr;
int *int_array = malloc(size * sizeof(int));
int_array[0] = 1;
int_array[1] = 2;

ptr = int_array;
printf("%d\n",ptr[0]); // 1
printf("%d\n",ptr[1]); // 2


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct ajdlistnode
{
	int ID;
	char cityname[MAX];
	char relief[MAX];
	struct ajdlistnode* next;
};

typedef struct ajdlistnode node_t;

struct tempnode
{
	node_t cityinfo;
	int *travel;
}

typedef struct tempnode city_t;

int size = get_size(char *line1); //size = 6

int *ptr;
int *int_array = malloc(size * sizeof(int)); // declare space for 6 int

city_t *city1 = malloc(sizeof(city_t));
city1->travel = int_array;
memset(int_array, -1, size); //or something like that
city1->travel[1] = 36 // from the file

int i;
for(i=0; i < size; i++){
	printf("%d ",city1->travel[i]);
}
printf("\n");
/* prints:
*		-1 36 -1 -1 -1 -1
*/






