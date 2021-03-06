all: helpme

helpme: helpme.o graph.o binheap.o
	gcc helpme.o graph.o binheap.o -o helpme

helpme.o: helpme.c helpme.h
	gcc -c -Wall helpme.c

graph.o: graph.c graph.h
	gcc -c -Wall graph.c

binheap.o: binheap.c binheap.h
	gcc -c -Wall binheap.c

clean:
	rm *.o helpme
