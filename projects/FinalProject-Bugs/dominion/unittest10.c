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
	int handPos = 2;
	int bonus = 0;
	struct gameState G1, G2;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, seed, &G1);

	printf("########### UNIT TEST: BUG #10 ###########\n");
	printf("**Test: Incorrect checking of amount of cards returned to supply from Ambassador**\n\n");

	// Setup: initialize game state, player and cards
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G1);

	G1.handCount[player_1] = 3;
	G1.hand[player_1][0] = ambassador;						// player 1 will play Ambassador card
	G1.hand[player_1][1] = cutpurse;						// player 1 will have 2 Cutpurses in hand
	G1.hand[player_1][2] = cutpurse;

	memcpy(&G2, &G1, sizeof(struct gameState));

	int i;
	int cutpurseCount1, cutpurseCount2;
	cutpurseCount1 = cutpurseCount2 = 0;

	for (int i = 0; i < G1.handCount[player_1]; i++) {
		if (G1.hand[player_1][i] == cutpurse) {
			cutpurseCount1++;
		}
	}

	printf("Number of cutpurse cards in hand before Ambassador card played is: %d\n", cutpurseCount1);
	int result = cardEffect(ambassador, 0, 2, 0, &G1, handPos, &bonus);

	for (int i = 0; i < G1.handCount[player_1]; i++) {
		if (G1.hand[player_1][i] == cutpurse) {
			cutpurseCount2++;
		}
	}

	printf("Number of cutpurse cards in hand after Ambassador card played is: %d\n", cutpurseCount2);
	Validate("player 1 should not have any cutpurse cards in hand", cutpurseCount1 == 0);

	printf("########### END TEST ###########\n\n");
	return 0;
}

