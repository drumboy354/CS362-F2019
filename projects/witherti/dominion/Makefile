CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c ../piezasjDominion/CS362-F2019/projects/piezasj/dominion/dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

dominionHelperFuncs.o: dominionHelperFuncs.h dominionHelperFuncs.c
	gcc -c dominionHelperFuncs.c -g -std=c99 -Wall -fpic -lm

testBaron: unittest1.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testBaronUnit -g unittest1.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	gcc  -o testBaronRandom -g randomtestcard1.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)

testAmbas: unittest2.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testAmbas -g unittest2.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)

testTrib: unittest3.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testTribUnit -g unittest3.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	gcc  -o testTribRandom -g randomtestcard3.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)

testMine: unittest4.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testMine -g unittest4.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)

testMinion: unittest5.c dominionHelperFuncs.o dominion.o rngs.o
	gcc  -o testMinionUnit -g unittest5.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)
	gcc  -o testMinionRandom -g randomtestcard3.c dominion.o dominionHelperFuncs.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

alltests: testBaron testAmbas testTrib testMine testMinion
	./testBaronUnit &> unittestresult.out
	./testBaronRandom >> unittestresult.out
	./testAmbas	>> unittestresult.out
	./testTribUnit >> unittestresult.out
	./testTribRandom >> unittestresult.out
	./testMine >> unittestresult.out
	./testMinionUnit >> unittestresult.out
	./testMinionRandom >> unittestresult.out
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
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe testBaron testBaron.exe
	rm -f testAmbas* testTrib* testMine* testBaron* testMinion*
