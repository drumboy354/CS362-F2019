#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// Alternative to Assert for Gcov purposes
int Validate(char* msg, int x) {
	printf("Case: %s\n", msg);
	if (x != 1)
		printf(" > Error: Condition Failed!\n");

	else
		printf(" > Passed Successfully!\n");
}

/*******************************************************/
/******************* Tribute UNIT TEST ******************/
/*******************************************************/
int main()
{
	int seed = 1000;
	int numPlayers = 2;
	int player_1 = 0;
	int handPos = 0;
	int bonus = 0;
	struct gameState G1, G2;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, seed, &G1);

	printf("########### UNIT TEST: BUG #8 ###########\n");
	printf("**Test: Incorrect calculation of number of coins gained from Baron card**\n\n");

	// Test 1: playCard() function
	printf("TEST #1: Testing function playCard() with Baron card:\n");
	
	// Setup: initialize game state, player and cards
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G1);

	G1.handCount[player_1] = 1;
	G1.hand[player_1][handPos] = baron;						// player 1 will play Baron card
	G1.deckCount[player_1] = 3;								// player 1 has deck count of 3

	int i;
	for (i = 0; i < G1.deckCount[player_1]; i++) {			// fill rest of the hand of player 1 with estate
		G1.deck[player_1][i] = estate;
	}
	
	G1.coins = 0;
	memcpy(&G2, &G1, sizeof(struct gameState));

	printf("Number of coins before Baron card played is: %d\n", G1.coins);
	int result = playCard(handPos, 1, 0, 0, &G1);
	printf("Number of coins after Baron card played is: %d\n\n", G1.coins);
	Validate("player 1 should gain 4 coins", G1.coins == G2.coins + 4);

	// Test 2: cardEffect() function
	printf("\nTEST #2: Testing function cardEffect() with Baron card:\n");

	// Setup: initialize game state, player and cards
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G1);

	G1.handCount[player_1] = 1;
	G1.hand[player_1][handPos] = baron;						// player 1 will play Baron card
	G1.deckCount[player_1] = 3;								// player 1 has deck count of 3

	for (i = 0; i < G1.deckCount[player_1]; i++) {			// fill rest of the hand of player 1 with estate
		G1.deck[player_1][i] = estate;
	}

	G1.coins = 0;
	memcpy(&G2, &G1, sizeof(struct gameState));

	printf("Number of coins before Baron card played is: %d\n", G1.coins);
	result = cardEffect(baron, 1, 0, 0, &G1, handPos, &bonus);
	printf("Number of coins after Baron card played is: %d\n\n", G1.coins);
	Validate("player 1 should gain 4 coins", G1.coins == G2.coins + 4);

	printf("########### END TEST ###########\n\n");
	return 0;
}

