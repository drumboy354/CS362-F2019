#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominionHelperFuncs.h"

#define DEBUG 1
#define NOISY_TEST 1

int main () {
	
	// Cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

	// Test variables
	int numPlayers = 2;
	int seed = 1000;
	int currentPlayer;
	int nextPlayer;
	int tributeRevealedCards[2];

	int handCount1;
	int discardCount1;
	int coincount1;
	int numActions1;
	struct gameState G, testG;	 
	int handCount2;
	int discardCount2;
	int deckCount2;

	// Start tests
    printf ("*****************\nInitializing tests for CARD TRIBUTE\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 

	// ----------TEST 1:
	// Two different treasure cards, +4 coins for p1
	// No extra actions or cards gained.

	printf("----------TEST 1: Two different treasure cards. +4 coins for p1 ONLY---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = gold;
	tributeRevealedCards[1] = silver;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[1];
	discardCount2 = testG.discardCount[1];

	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1+4);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);
	
	// ----------TEST 2:
	// Two of the same treasure cards, +2 coins for p1
	// No extra actions or cards gained.

	printf("\n----------TEST 2: Two same treasure cards. +2 coins for p1 ONLY---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = silver;
	tributeRevealedCards[1] = silver;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[1];
	discardCount2 = testG.discardCount[1];

	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1+2);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);

	// ----------TEST 3:
	// Two different victory cards
	// +4 cards

	printf("\n----------TEST 3: Two different victory cards. p1 gains +4 cards in hand---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = duchy;
	tributeRevealedCards[1] = estate;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[1];
	discardCount2 = testG.discardCount[1];

	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1+4);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);

	// ----------TEST 4:
	// Two same victory cards
	// +2 cards

	printf("\n----------TEST 4: Two same victory cards. p1 gains +2 cards in hand---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = estate;
	tributeRevealedCards[1] = estate;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[1];
	discardCount2 = testG.discardCount[1];

	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1+2);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);

	// ----------TEST 5:
	// Two different action cards
	// +4 actions
	// Also have deckCount == 0

	printf("\n----------TEST 5: Two different action cards. p1 gains +4 actions---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = council_room;
	tributeRevealedCards[1] = feast;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[1];
	discardCount2 = testG.discardCount[1];
	deckCount2 = testG.deckCount[nextPlayer];

	// Set deck count of p2 to 0
	for(int i = 0; i < deckCount2 ; i++){
		testG.deck[nextPlayer][i] = -1;
		testG.deckCount[nextPlayer]--;
	}

	// Gain card to discard pile
	gainCard(copper, &testG, 0, nextPlayer);
	gainCard(copper, &testG, 0, nextPlayer);
	gainCard(copper, &testG, 0, nextPlayer);
	gainCard(copper, &testG, 0, nextPlayer);	

	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1+4);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);

	// ----------TEST 6:
	// Two same action cards
	// +2 actions

	printf("\n----------TEST 6: Two same action cards. p1 gains +2 actions---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = feast;
	tributeRevealedCards[1] = feast;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[1];
	discardCount2 = testG.discardCount[1];
	deckCount2 = testG.deckCount[1];
	
	// Set deck count of p2 to 0
	for(int i = 0; i < deckCount2 ; i++){
		testG.deck[nextPlayer][i] = -1;
		testG.deckCount[nextPlayer]--;
	}
	
	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1+2);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);

	// ----------TEST 7:
	// 1 treasure, 1 action card
	// +2 coins and +2 actions
	// Also have discardCount + deckCount <= 1

	printf("\n----------TEST 7: 1 treasure, 1 action. +2 coins/actions to p1---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = council_room;
	tributeRevealedCards[1] = copper;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
		
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[nextPlayer];
	discardCount2 = testG.discardCount[nextPlayer];
	
	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1+2);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1+2);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);

	// ----------TEST 8:
	// 1 treasure, 1 victory card
	// +2 coins and +2 cards
	// Also have discardCount + deckCount <= 1, where discardCount = 1

	printf("\n----------TEST 8: 1 treasure, 1 victory. +2 coins/cards to p1---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = estate;
	tributeRevealedCards[1] = silver;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[nextPlayer];
	discardCount2 = testG.discardCount[nextPlayer];
	deckCount2 = testG.deckCount[nextPlayer];

	// Set deck count of p2 to 1
	for(int i = 1; i < deckCount2 ; i++){
		testG.deck[nextPlayer][i] = -1;
		testG.deckCount[nextPlayer]--;
	}

	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1+2);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1+2);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);

	// ----------TEST 9:
	// 1 action, 1 victory card
	// +2 actions and +2 cards
	// Also have discardCount + deckCount <= 1, where deckCount = 1

	printf("\n----------TEST 9: 1 treasure, 1 victory. +2 actions/cards to p1---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	nextPlayer = 1;

	// Set hand for second player
	tributeRevealedCards[0] = feast;
	tributeRevealedCards[1] = gold;

	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(tributeRevealedCards[0], &testG, 2, 1);
	gainCard(tributeRevealedCards[1], &testG, 2, 1);
	
	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	coincount1 = testG.coins;
	numActions1 = testG.numActions;

	handCount2 = testG.handCount[nextPlayer];
	discardCount2 = testG.discardCount[nextPlayer];
	deckCount2 = testG.deckCount[nextPlayer];

	// Set deck count of p2 to 0
	for(int i = 0; i < deckCount2 ; i++){
		testG.deck[nextPlayer][i] = -1;
		testG.deckCount[nextPlayer]--;
	}

	// Gain card to discard pile
	gainCard(copper, &testG, 0, nextPlayer);
		
	// Call function
	cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);
	
	printHandCards(&testG, nextPlayer);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1+2);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1);
	printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1+2);

	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);


    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
