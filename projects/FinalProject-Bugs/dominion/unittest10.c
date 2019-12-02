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

	printf("########### UNIT TEST: BUG #10 ###########\n");
	printf("**Test: Incorrect checking of amount of cards returned to supply from Ambassador**\n\n");

	// Setup: initialize game state, player and cards
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G1);

	G1.handCount[player_1] = 4;
	G1.hand[player_1][0] = ambassador;						// player 1 will play Ambassador card
	G1.hand[player_1][1] = cutpurse;						// player 1 will have 3 Cutpurses in hand
	G1.hand[player_1][2] = cutpurse;
	G1.hand[player_1][3] = tribute;							// Player 1 will have 1 tribute card
	G1.hand[player_1][3] = cutpurse;

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
	int result = cardEffect(ambassador, 1, 2, 0, &G1, handPos, &bonus);

	for (int i = 0; i < G1.handCount[player_1]; i++) {
		if (G1.hand[player_1][i] == cutpurse) {
			cutpurseCount2++;
		}
	}
	printf("Number of cutpurse cards in hand after Ambassador card played is: %d\n\n", cutpurseCount2);
	
	Validate("Player 1 should have 3 less cards in hand (-1 tribute, -2 curpurse)", G1.handCount[0] == G2.handCount[0] - 3);
	Validate("Player 1 should have 2 cutpurse cards removed from hand", cutpurseCount2 == 1);


	printf("########### END TEST ###########\n\n");
	return 0;
}

