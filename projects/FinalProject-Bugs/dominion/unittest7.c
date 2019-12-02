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
	int player_2 = 1;				// other player
	int handPos = 0;
	int bonus = 0;
	struct gameState G1, G2;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, seed, &G1);

	printf("########### UNIT TEST: BUG #7 ###########\n");
	printf("**Test: Unexpected gain in action cards from Tribute card**\n\n");

	// Setup: initialize game state, player and cards
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G1);

	G1.handCount[player_1] = 1;
	G1.hand[player_1][handPos] = tribute;					// player 1 will play tribute card
	G1.deckCount[player_1] = 3;								// player 1 has deck count of 3

	int i;
	for (i = 0; i < G1.deckCount[player_1]; i++) {			// fill rest of the hand of player 1 with copper
		G1.deck[player_1][i] = copper;
	}

	G1.deckCount[player_2] = 3;								// player 2 has copper, silver and gardens
	G1.deck[player_2][0] = copper;
	G1.deck[player_2][1] = silver;
	G1.deck[player_2][2] = gold;

	G1.numActions = 0;										// reset number of action cards to see effect of tribute card
	memcpy(&G2, &G1, sizeof(struct gameState));

	printf("Number of action cards before tribute card played is: %d\n", G1.numActions);
	printf("Number of coins before tribute card played is: %d\n\n", G1.coins);

	int result = cardEffect(tribute, -1, -1, -1, &G1, handPos, &bonus);
	
	printf("Number of action cards after tribute card played is: %d\n", G1.numActions);
	printf("Number of coins after tribute card played is: %d\n\n", G1.coins);
	
	Validate("player 1 should not gain any action cards", G1.numActions == G2.numActions);
	Validate("player 1 should gain 4 coins", G1.coins == G2.coins + 4);

	printf("########### END TEST ###########\n\n");
	return 0;
}
