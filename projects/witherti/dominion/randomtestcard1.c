#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "dominionHelperFuncs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main () {
	// Setup random seed
	srand(time(NULL));
	
	// Cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

	// Test variables
	int numPlayers = 2;
	int seed = 1000;
	int currentPlayer = 0;
	int choice1;
	int rand1, rand2, rand3;
	int numTests = 1000;

	int numBuysBefore, numEstateCards, handCount, deckCount, discardCount,
		estateCount, estateCountHand, estateCountDeck, estateCountDiscard,
		moneyBefore, moneyExpected, estateExpected, supplyEstateExpected,
		discardCountExpected, handCountExpected;

	// Game state
    struct gameState G, testG;	

	// Start tests
    printf ("*****************\nInitializing tests for CARD BARON\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 
	
	for(int i = 0; i < numTests; i++){	
		// Copy game state
		memcpy(&testG, &G, sizeof(struct gameState));

		// Set cards for p1
		testG.hand[0][0] = baron;
		testG.hand[0][1] = silver;
		testG.hand[0][2] = copper;
		testG.hand[0][3] = copper;
		testG.hand[0][4] = gold;
		
		// Set random test vars
		choice1 = rand()%2;			// Generate number between 0 and 1
		rand1 = rand()%100+1;		// Generate number between 1 and 100
		rand2 = rand()%100+1;		// Generate number between 1 and 100
		rand3 = rand()%8+1;		// Generate number of estates in supply, between 0 and 8

		if(rand1 < 50){ testG.hand[0][1] = estate; }		// Half the time give the player an estate card
		testG.supplyCount[estate] = rand3; 					

		// Set assert vars
		numBuysBefore = testG.numBuys;
		numEstateCards = cardsInHand(&testG, estate, currentPlayer);
		handCount = testG.handCount[currentPlayer];
		deckCount = testG.deckCount[currentPlayer];
		discardCount = testG.discardCount[currentPlayer];
		estateCount = supplyCount(estate, &testG); 
		estateCountHand = cardsInHand(&testG, estate, currentPlayer);
		estateCountDeck = cardsInDeck(&testG, estate, currentPlayer);
		estateCountDiscard = cardsInDiscard(&testG, estate, currentPlayer);
		moneyBefore = testG.coins;

		// ----------TESTS 
		printf("\n----------TEST %d, estate in hand: %d, choice1: %d, num of supply estate: %d---------\n", i+1, rand1<50, choice1, rand3);

		// Call function
		cardBaron(&testG, currentPlayer, choice1);
		
		// Test results
		// Set expected results. We have to do (rand1<50) because we can't discard an estate that is NOT in our hand
		handCountExpected = (choice1 == 1) ? handCount-1-(rand1<50) : handCount-1;	// If we choose to discard Estate, we should have 2 less cards in hand
		discardCountExpected = (choice1 == 1) ? discardCount+1+(rand1<50) : discardCount+1;	// If we choose to discard Estate, we discard that + this card
		moneyExpected = (choice1 == 1) ? moneyBefore+4 : testG.coins;				// If we chose to discard an estate, we gain +4 coins
		supplyEstateExpected = (choice1 == 0) ? estateCount-1 : estateCount;		// If we chose not to discard an estate, gain one from supply

		printf("number of cards in hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountExpected);
		printf("number of cards in deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount);
		printf("number of cards in discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountExpected);
		printf("number of buys = %d, expected = %d\n", testG.numBuys, numBuysBefore+1);
		printf("number of estate cards in hand: %d, expected = %d\n", cardsInHand(&testG, estate, currentPlayer), estateCountHand);
		printf("number of estate cards in deck: %d, expected = %d\n", cardsInDeck(&testG, estate, currentPlayer), estateCountDeck); 
		printf("number of estate cards in discard: %d, expected = %d\n", cardsInDiscard(&testG, estate, currentPlayer), estateCountDiscard+1); 
		printf("number of coins: %d, expected = %d\n", testG.coins, moneyExpected);
		printf("supply count estate = %d, expected = %d", supplyCount(estate, &testG), supplyEstateExpected);
		printf("\n");
	
	}	

    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
