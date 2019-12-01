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
	
unittest1: unittest1.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o unittest1 -g unittest1.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./unittest1

unittest2: unittest2.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o unittest2 -g unittest2.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./unittest2

unittest3: unittest3.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o unittest3 -g unittest3.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./unittest3

unittest4: unittest4.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o unittest4 -g unittest4.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./unittest4

unittest5: unittest5.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o unittest5 -g unittest5.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./unittest5

unittest6: unittest6.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o unittest6 -g unittest6.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	./unittest6

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5 unittest6
	./unittest1 &> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./unittest5 >> unittestresult.out
	./unittest6 >> unittestresult.out
	gcov dominion.c -f -b >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 unittest5 unittest6
	rm -rf *.dSYM
