#include "../piezasjDominion/CS362-F2019/projects/piezasj/dominion/dominion.h"
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

	int handCount1, discardCount1;
	int numCopper, numSilver, numGold;
	int playCount, handPos, choice1, choice2;

	struct gameState G, testG;	 

	// Start tests
    printf ("*****************\nInitializing tests for CARD MINE\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 

	// ----------TEST 1:
	// -1 copper, +1 silver 
	
	printf("----------TEST 1: -1 copper, +1 silver---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	playCount = testG.playedCardCount;
	handPos = 0;
	currentPlayer = 0;
	choice1 = 2; 		// index of money to trash
	choice2 = silver;	// money to gain in hand
	
	// Call function
//	cardMine(&testG, handPos, currentPlayer, choice1, choice2);
	handleMineEffect(&testG, currentPlayer, choice1, choice2, handPos);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1-1);	// Discarding mine and treasure, gaining extra treasure
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver-1);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold+1);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);
	
	// ----------TEST 2:
	// -1 silver, +1 gold 
	
	printf("\n----------TEST 2: -1 silver, +1 gold---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	playCount = testG.playedCardCount;
	handPos = 0;		// pos of Mine card we're playing
	currentPlayer = 0;
	choice1 = 1; 		// index of money to trash
	choice2 = gold;	// money to gain in hand
	
	// Call function
//	cardMine(&testG, handPos, currentPlayer, choice1, choice2);
	handleMineEffect(&testG, currentPlayer, choice1, choice2, handPos);

	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1-1);  // Discarding mine and treasure, gaining extra treasure
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver-1);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold+1);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);

	// ----------TEST 3:
	// Try to trash copper for gold, not valid
	
	printf("\n----------TEST 3: Trash copper for gold, not valid, nothing should happen---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	playCount = testG.playedCardCount;
	handPos = 0;		// pos of Mine card we're playing
	currentPlayer = 0;
	choice1 = 2; 		// index of money to trash
	choice2 = gold;	// money to gain in hand
	
	// Call function
//	cardMine(&testG, handPos, currentPlayer, choice1, choice2);
	handleMineEffect(&testG, currentPlayer, choice1, choice2, handPos);

	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);  // Discarding mine and treasure, gaining extra treasure
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);

	// ----------TEST 4:
	// Try to trash random action card for a treasure card, invalid
	
	printf("\n----------TEST 4: Trash random action card, nothing should happen---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = feast;

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	playCount = testG.playedCardCount;
	handPos = 0;		// pos of Mine card we're playing
	currentPlayer = 0;
	choice1 = 4; 		// index of money to trash
	choice2 = gold;	// money to gain in hand
	
	// Call function
//	cardMine(&testG, handPos, currentPlayer, choice1, choice2);
	handleMineEffect(&testG, currentPlayer, choice1, choice2, handPos);

	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);  // Discarding mine and treasure, gaining extra treasure
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);

	// ----------TEST 5:
	// Try to gain a card out of bounds, choice2 = 2000
	
	printf("\n----------TEST 5: choice2 = 2000, invalid---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = feast;

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	playCount = testG.playedCardCount;
	handPos = 0;		// pos of Mine card we're playing
	currentPlayer = 0;
	choice1 = 2; 		// index of money to trash
	choice2 = 2000;	// money to gain in hand
	
	// Call function
//	cardMine(&testG, handPos, currentPlayer, choice1, choice2);
	handleMineEffect(&testG, currentPlayer, choice1, choice2, handPos);

	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);  // Discarding mine and treasure, gaining extra treasure
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);


    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
