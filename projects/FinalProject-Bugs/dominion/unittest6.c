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

    printf("######################################## BEGIN TEST: FEAST ########################################\n");

    initializeGame(numPlayers, k, seed, &G);
    G.coins = 3;
    int expectedCoinCount = 3;
    G.hand[thisPlayer][0] = feast;

    int playerLastCard = cardEffect(feast, duchy, NULL, NULL, &G, 0, NULL);

    if (G.coins != expectedCoinCount)
    {
        printf("TEST_COIN_COUNT_AFTER_FEAST_FAILED: Incorrect coin count. Expected coin count: %d. Actual coin count: %d\n", expectedCoinCount, G.coins);
    }
    else
    {
        printf("It should not modify the player's original coin count: %s\n", CHECK_MARK);
        numPassedTests++;
    }

    printf("%d out of %d tests passed\n", numPassedTests, totalTests);

    printf("########################################## END TEST: FEAST ########################################\n\n");
}