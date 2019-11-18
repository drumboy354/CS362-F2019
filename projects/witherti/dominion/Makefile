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

testBaron: randomtestcard1.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testBaron -g randomtestcard1.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	
testMinion: randomtestcard2.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testMinion -g randomtestcard2.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	
testTrib: randomtestcard3.c dominionHelperFuncs.o dominion.o rngs.o
	gcc -o testTrib -g randomtestcard3.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)
	
randomtestresults: testBaron testMinion testTrib
	./testBaron &> randomtestresults.out
	./testTrib >> randomtestresults.out
	./testMinion >> randomtestresults.out
	gcov dominion.c -f -b >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe testBaron testBaron.exe
	rm -f testAmbas testAmbas.exe testTrib testTrib.exe testMine testMine.exe testMinion.exe testMinion
