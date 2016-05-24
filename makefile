all:	naive.c large_naive.c interchange.c large_interchange.c
	gcc -O2 -ggdb -g -c naive.c
	gcc -o naive naive.o 
	gcc -O2 -ggdb -g -c interchange.c
	gcc -o interchange interchange.o 
	gcc -O2 -ggdb -g -c large_naive.c
	gcc -o large_naive large_naive.o 
	gcc -O2 -ggdb -g -c large_interchange.c
	gcc -o large_interchange large_interchange.o 
	
clean: 
	rm naive interchange large_naive large_interchange *.o
	
