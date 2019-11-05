CFLAGS= -Wall -fpic -coverage -lm -std=c99

all: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	./testme
	gcov testme.c -b -f
	cat testme.c.gcov

clean:
	rm -f testme testme.exe *.o *.gcov *.gcda *.gcno *.so *.out 
