#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK_MARK "\u2713"
#define TRUE 1
#define FALSE 0

static const struct gameState EmptyStruct;

int main()
{
    int numPassedTests = 0;
    int totalTests = 1;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    printf("######################################## BEGIN TEST: SCOREFOR ########################################\n");

    // Test that isGameOver properly iterates through all cards in the supply to check that the game is over
    initializeGame(numPlayers, k, seed, &G);
    G.deckCount[thisPlayer] = 2;
    G.handCount[thisPlayer] = 0;
    G.deck[thisPlayer][0] = province;
    G.deck[thisPlayer][1] = estate;
    G.discardCount[thisPlayer] = 1;
    G.discard[thisPlayer][0] = great_hall;

    int expectedScore = 8;

    int actualScore = scoreFor(thisPlayer, &G);

    if (actualScore != expectedScore)
    {
        printf("TEST_SCORE_FOR_FAILED: Score for Player 1 did not match. Expected score: %d. Actual score: %d\n", expectedScore, actualScore);
    }
    else
    {
        printf("It should tally the score based on a combination of the player's deck and discard pile: %s\n", CHECK_MARK);
    }

    printf("########################################## END TEST: SCOREFOR ########################################\n\n");
}