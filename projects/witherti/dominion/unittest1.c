#include "../piezasjDominion/CS362-F2019/projects/piezasj/dominion/dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominionHelperFuncs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main () {
	
	// Cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

	// Test variables
	int numPlayers = 2;
	int seed = 1000;
	int funcReturn;
	int choice1, choice2, choice3;
	int currentPlayer;

	// Game state
    struct gameState G, testG;	

	// Start tests
    printf ("*****************\nInitializing tests for CARD BARON\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 

	// ----------TEST 1:  
	// choice1 = 0, don't discard an estate card
	// player should gain an estate card
	printf("----------TEST 1: choice1 = 0, +1 buy, +1 estate to discard pile---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	currentPlayer = 0;

	// Set test vars
	int numBuysBefore = testG.numBuys;
	int numEstateCards = cardsInHand(&testG, estate, currentPlayer);
	int handCount = testG.handCount[currentPlayer];
	int deckCount = testG.deckCount[currentPlayer];
	int discardCount = testG.discardCount[currentPlayer];
	int estateCount = supplyCount(estate, &testG); 
	int estateCountHand = cardsInHand(&testG, estate, currentPlayer);
	int estateCountDeck = cardsInDeck(&testG, estate, currentPlayer);
	int estateCountDiscard = cardsInDiscard(&testG, estate, currentPlayer);

	// Call function
	handleBaronEffect(choice1, &testG, currentPlayer);
	
	// Tests
	printf("number of cards in hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount);
	printf("number of cards in deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount);
	printf("number of cards in discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount+1);
	printf("number of buys = %d, expected = %d\n", testG.numBuys, numBuysBefore+1);
	printf("number of estate cards in hand: %d, expected = %d\n", cardsInHand(&testG, estate, currentPlayer), estateCountHand);
	printf("number of estate cards in deck: %d, expected = %d\n", cardsInDeck(&testG, estate, currentPlayer), estateCountDeck); 
	printf("number of estate cards in discard: %d, expected = %d\n", cardsInDiscard(&testG, estate, currentPlayer), estateCountDiscard+1); 
	printf("supply count estate = %d, expected = %d", supplyCount(estate, &testG), estateCount-1);
	printf("\n");

	// ----------TEST 2:  choice1 = 1
	printf("\n----------TEST 2: choice2 = 1, +1 buy, -1 estate from hand to discard pile, +4 coins---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	currentPlayer = 0;

	// Set test vars
	numBuysBefore = testG.numBuys;
	numEstateCards = cardsInHand(&testG, estate, currentPlayer);
	int moneyBefore = G.coins;
	handCount = testG.handCount[currentPlayer];
	deckCount = testG.deckCount[currentPlayer];
	estateCount = supplyCount(estate, &testG);
	estateCountHand = cardsInHand(&testG, estate, currentPlayer);
	estateCountDeck = cardsInDeck(&testG, estate, currentPlayer);
	estateCountDiscard = cardsInDiscard(&testG, estate, currentPlayer);

	handleBaronEffect(choice1, &testG, currentPlayer);

	printf("number of cards in hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount-1);
	printf("number of cards in deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount);
	printf("number of cards in discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount+1);
	printf("number of buys = %d, expected = %d\n", testG.numBuys, numBuysBefore+1);
	printf("number of estate cards in hand: %d, expected = %d\n", cardsInHand(&testG, estate, currentPlayer), estateCountHand-1);
	printf("number of estate cards in deck: %d, expected = %d\n", cardsInDeck(&testG, estate, currentPlayer), estateCountDeck); 
	printf("number of estate cards in discard: %d, expected = %d\n", cardsInDiscard(&testG, estate, currentPlayer), estateCountDiscard+1); 
	printf("number of coins: %d, expected = %d\n", testG.coins, moneyBefore+4);
	printf("supply count estate = %d, expected = %d", supplyCount(estate, &testG), estateCount);
	
    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
