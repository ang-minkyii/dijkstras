#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 256


int main()
{
	char string[MAX];
	char *ptr;
	int j=0;

	while(scanf("%s",string)==1)
	{
		printf("String is < %s >|\n",string);

		ptr = strtok(string,"|");
		printf("Student ID : %s\n",ptr);
		ptr = strtok(NULL,"|");
		printf("Name : %s\n",ptr);
		ptr = strtok(NULL,",:|");

		while(ptr != NULL)
		{
			if(j == 0)
			{
				printf("Subjects :%s\n",ptr);
				ptr = strtok(NULL,",:|");
				j = 1;
			}else
			{
				printf("Marks :%s\n",ptr);
				ptr = strtok(NULL,",:|");
				j = 0;	
			}
		}
		printf("\n");
	}
		return 0;
}