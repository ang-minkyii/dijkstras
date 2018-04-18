#include <stdio.h>
#include <string.h>


int main()
{
	
	char str[]="he|is|stupid";
	char *pch;

	printf("The string is |%s|\n",str);

	pch = strtok (str,"|");

	while(pch != NULL)
	{
		printf("%s\n",pch);
		pch = strtok(NULL, "|");
	}
	return 0;
}

