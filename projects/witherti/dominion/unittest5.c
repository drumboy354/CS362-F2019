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
    int k[10] = {minion, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

	// Test variables
	int numPlayers = 3;
	int seed = 1000;
	int choice1, choice2;
	int handPos;
	int currentPlayer;

	int handCount1; 
	int deckCount1; 
	int discardCount1;
	int numActions1;
	int numCoins;
	                 
	int handCount2;	
	int deckCount2;    
	int discardCount2;
	                 	
	int handCount3;  
	int deckCount3; 
	int discardCount3;	

	struct gameState G, testG;	 

	// Start tests
    printf ("*****************\nInitializing tests for CARD MINION\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 

	// ----------TEST 1:  
	// choice1 = 1, +2 coins
	// choice2 = 0, we are not redrawing
	// handPos = 0, position of the minion card we're playing
	printf("----------TEST 1: choice1 = 1, choice2 = 0, +2 coins, +1 action, no player should gain any cards---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 1;
	choice2 = 0;
	currentPlayer = 0;

	// Replace first card to be minion card for first player
	testG.hand[currentPlayer][0] = minion;	

	// Set hand for second player
	gainCard(minion, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	deckCount1 = testG.deckCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numActions1 = testG.numActions;
	numCoins = testG.coins;

	handCount2 = testG.handCount[1];
	deckCount2 = testG.deckCount[1];
	discardCount2 = testG.discardCount[1];

	handCount3 = testG.handCount[2];
	deckCount3 = testG.deckCount[2];
	discardCount3 = testG.discardCount[2];
	
	// Call function
//	cardMinion(&testG, choice1, choice2, handPos, currentPlayer);
	handleMinionEffect(&testG, handPos, currentPlayer, choice1, choice2);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1-1);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1+1);
	printf("number of actions for p1 = %d, expected = %d\n", testG.numActions, numActions1+1);
	printf("number of coins for p1 = %d, expected = %d\n", testG.coins, numCoins+2);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], handCount2);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], handCount3);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3);

	// ----------TEST 2:  
	// choice1 = 0, +0 coins
	// choice2 = 1, we are discarding, gain +4 cards
	// handPos = 0, position of the minion card we're playing
	printf("\n----------TEST 2: choice1 = 0, choice2 = 1, +0 coins, +1 action, p1/p2/p3 only 4 cards---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 0;
	choice2 = 1;
	currentPlayer = 0;

	// Replace first card to be minion card for first player
	testG.hand[currentPlayer][0] = minion;	

	// Set hand for second player
	gainCard(minion, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	gainCard(minion, &testG, 2, 2);
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	deckCount1 = testG.deckCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numActions1 = testG.numActions;
	numCoins = testG.coins;

	handCount2 = testG.handCount[1];
	deckCount2 = testG.deckCount[1];
	discardCount2 = testG.discardCount[1];

	handCount3 = testG.handCount[2];
	deckCount3 = testG.deckCount[2];
	discardCount3 = testG.discardCount[2];
	
	// Call function
//	cardMinion(&testG, choice1, choice2, handPos, currentPlayer);
	printf("1\n");
	handleMinionEffect(&testG, handPos, currentPlayer, choice1, choice2);
	printf("2\n");

	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], 4);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1+handCount1);
	printf("number of actions for p1 = %d, expected = %d\n", testG.numActions, numActions1+1);
	printf("number of coins for p1 = %d, expected = %d\n", testG.coins, numCoins);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], 4);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2+handCount2);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], 4);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3+handCount3);

	// ----------TEST 3:  
	// choice1 = 0, +0 coins
	// choice2 = 1, we are discarding, gain +4 cards
	// handPos = 0, position of the minion card we're playing
	printf("\n----------TEST 3: choice1 = 0, choice2 = 1, +0 coins, +1 action, p1/p2 only 4 cards, p3 no change---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 0;
	choice2 = 1;
	currentPlayer = 0;

	// Replace first card to be minion card for first player
	testG.hand[currentPlayer][0] = minion;	

	// Set hand for second player
	gainCard(minion, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	//gainCard(minion, &testG, 2, 2);
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	deckCount1 = testG.deckCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numActions1 = testG.numActions;
	numCoins = testG.coins;

	handCount2 = testG.handCount[1];
	deckCount2 = testG.deckCount[1];
	discardCount2 = testG.discardCount[1];

	handCount3 = testG.handCount[2];
	deckCount3 = testG.deckCount[2];
	discardCount3 = testG.discardCount[2];
	
	// Call function
//	cardMinion(&testG, choice1, choice2, handPos, currentPlayer);
	handleMinionEffect(&testG, handPos, currentPlayer, choice1, choice2);

	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], 4);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1+handCount1);
	printf("number of actions for p1 = %d, expected = %d\n", testG.numActions, numActions1+1);
	printf("number of coins for p1 = %d, expected = %d\n", testG.coins, numCoins);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], 4);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2+handCount2);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], handCount3);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3);

	// ----------TEST 4:  
	// choice1 = 0, +0 coins
	// choice2 = 1, we are discarding, gain +4 cards
	// handPos = 0, position of the minion card we're playing
	printf("\n----------TEST 4: choice1 = 0, choice2 = 1, +0 coins, +1 action, p1/p3 only 4 cards, p2 no change---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 0;
	choice2 = 1;
	currentPlayer = 0;

	// Replace first card to be minion card for first player
	testG.hand[currentPlayer][0] = minion;	

	// Set hand for second player
	//gainCard(minion, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	gainCard(minion, &testG, 2, 2);
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	gainCard(copper, &testG, 2, 2);
	gainCard(copper, &testG, 2, 2);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	deckCount1 = testG.deckCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numActions1 = testG.numActions;
	numCoins = testG.coins;

	handCount2 = testG.handCount[1];
	deckCount2 = testG.deckCount[1];
	discardCount2 = testG.discardCount[1];

	handCount3 = testG.handCount[2];
	deckCount3 = testG.deckCount[2];
	discardCount3 = testG.discardCount[2];
	
	// Call function
//	cardMinion(&testG, choice1, choice2, handPos, currentPlayer);
	handleMinionEffect(&testG, handPos, currentPlayer, choice1, choice2);

	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], 4);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1+handCount1);
	printf("number of actions for p1 = %d, expected = %d\n", testG.numActions, numActions1+1);
	printf("number of coins for p1 = %d, expected = %d\n", testG.coins, numCoins);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], handCount2);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], 4);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3+handCount3);


    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
