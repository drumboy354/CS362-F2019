CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

dominionHelperFuncs.o: dominionHelperFuncs.h dominionHelperFuncs.c
	gcc -c dominionHelperFuncs.c -g -std=c99 -Wall -fpic -lm

testBaron: unittest1.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testBaron -g unittest1.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./testBaron
	gcov dominion.c -f -b
	vim dominion.c.gcov

testAmbas: unittest2.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testAmbas -g unittest2.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./testAmbas
	gcov dominion.c -f -b
	vim dominion.c.gcov

testTrib: unittest3.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testTrib -g unittest3.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./testTrib
	gcov dominion.c -f -b
	vim dominion.c.gcov

testMine: unittest4.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testMine -g unittest4.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./testMine
	gcov dominion.c -f -b
	vim dominion.c.gcov

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe testBaron testBaron.exe
	rm -f testAmbas testAmbas.exe testTrib testTrib.exe testMine testMine.exe
