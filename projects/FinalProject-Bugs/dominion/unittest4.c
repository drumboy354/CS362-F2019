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

    printf("######################################## BEGIN TEST: ISGAMEOVER ########################################\n");

    // Test that isGameOver properly iterates through all cards in the supply to check that the game is over
    initializeGame(numPlayers, k, seed, &G);
    G.supplyCount[gold] = 0;
    G.supplyCount[treasure_map] = 0;
    G.supplyCount[sea_hag] = 0;

    int result = isGameOver(&G);

    if (result == FALSE)
    {
        printf("TEST_IS_GAME_OVER_FAILED: Expected isGameOver status: %d. Actual isGameOverStatus: %d\n", 1, result);
    }
    else
    {
        printf("It should end the game if the supply of at least 3 types of cards are empty: %s\n", CHECK_MARK);
        numPassedTests++;
    }

    printf("%d out of %d tests passed\n", numPassedTests, totalTests);

    printf("########################################## END TEST: ISGAMEOVER ########################################\n\n");
}