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

	int handCountBefore, discardCountBefore;
	int numCopper, numSilver, numGold;
	int numCopperPlayed, numSilverPlayed, numGoldPlayed;
	int playCount, handPos, choice1, choice2, choice3;
	int coin_bonus = 0, card;

	struct gameState G, testG;	 

	// Start tests
    printf ("*****************\nInitializing tests for BUG 2\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 

	// ----------TEST 1:
	// -1 copper, +1 silver 
	
	printf("----------TEST 1: -1 copper (trashed), +1 silver (to hand)---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	numCopperPlayed = cardsInPlayed(&testG, copper);
	numSilverPlayed = cardsInPlayed(&testG, silver);
	numGoldPlayed = cardsInPlayed(&testG, gold);
	playCount = testG.playedCardCount;

	handPos = 0;
	currentPlayer = 0;
	choice1 = 2; 		// index of money to trash
	choice2 = silver;	// money to gain in hand

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore-1);	// Discarding mine, trash copper, gain silver
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore+1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper-1);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver+1);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);
	printf("number of copper cards in played = %d, expected = %d\n", cardsInPlayed(&testG, copper), numCopperPlayed);
	printf("number of silver cards in played = %d, expected = %d\n", cardsInPlayed(&testG, silver), numSilverPlayed);
	printf("number of gold cards in played = %d, expected = %d\n", cardsInPlayed(&testG, gold), numGoldPlayed);
	
//	// ----------TEST 2:
//	// -1 silver, +1 gold 
	printf("\n----------TEST 2: -1 silver (trashed), +1 gold (to hand)---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	numCopperPlayed = cardsInPlayed(&testG, copper);
	numSilverPlayed = cardsInPlayed(&testG, silver);
	numGoldPlayed = cardsInPlayed(&testG, gold);
	playCount = testG.playedCardCount;

	handPos = 0;
	currentPlayer = 0;
	choice1 = 1; 		// index of money to trash
	choice2 = gold;	// money to gain in hand

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore-1);	// Discarding mine, trash copper, gain silver
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore+1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver-1);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold+1);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);
	printf("number of copper cards in played = %d, expected = %d\n", cardsInPlayed(&testG, copper), numCopperPlayed);
	printf("number of silver cards in played = %d, expected = %d\n", cardsInPlayed(&testG, silver), numSilverPlayed);
	printf("number of gold cards in played = %d, expected = %d\n", cardsInPlayed(&testG, gold), numGoldPlayed);

	// ----------TEST 3:
	// -1 copper, +1 gold  INVALID
	printf("\n----------TEST 3: -1 copper (trashed), +1 gold (to hand). INVALID, NOTHING SHOULD HAPPEN---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	numCopperPlayed = cardsInPlayed(&testG, copper);
	numSilverPlayed = cardsInPlayed(&testG, silver);
	numGoldPlayed = cardsInPlayed(&testG, gold);
	playCount = testG.playedCardCount;

	handPos = 0;
	currentPlayer = 0;
	choice1 = 2; 		// index of money to trash
	choice2 = gold;	// money to gain in hand

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore);	
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);
	printf("number of copper cards in played = %d, expected = %d\n", cardsInPlayed(&testG, copper), numCopperPlayed);
	printf("number of silver cards in played = %d, expected = %d\n", cardsInPlayed(&testG, silver), numSilverPlayed);
	printf("number of gold cards in played = %d, expected = %d\n", cardsInPlayed(&testG, gold), numGoldPlayed);

	// ----------TEST 4:
	// -1 gold, +1 copper
	printf("\n----------TEST 4: -1 gold (trashed), +1 copper (to hand)---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	numCopperPlayed = cardsInPlayed(&testG, copper);
	numSilverPlayed = cardsInPlayed(&testG, silver);
	numGoldPlayed = cardsInPlayed(&testG, gold);
	playCount = testG.playedCardCount;

	handPos = 0;
	currentPlayer = 0;
	choice1 = 4; 		// index of money to trash
	choice2 = copper;	// money to gain in hand

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore-1);	
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore+1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper+1);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold-1);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);
	printf("number of copper cards in played = %d, expected = %d\n", cardsInPlayed(&testG, copper), numCopperPlayed);
	printf("number of silver cards in played = %d, expected = %d\n", cardsInPlayed(&testG, silver), numSilverPlayed);
	printf("number of gold cards in played = %d, expected = %d\n", cardsInPlayed(&testG, gold), numGoldPlayed);

	// ----------TEST 5:
	// -1 silver, +1 copper
	printf("\n----------TEST 5: -1 silver (trashed), +1 copper (to hand)---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = mine;
	testG.hand[0][1] = silver;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCopper = cardsInHand(&testG, copper, 0);
	numSilver = cardsInHand(&testG, silver, 0);
	numGold = cardsInHand(&testG, gold, 0);
	numCopperPlayed = cardsInPlayed(&testG, copper);
	numSilverPlayed = cardsInPlayed(&testG, silver);
	numGoldPlayed = cardsInPlayed(&testG, gold);
	playCount = testG.playedCardCount;

	handPos = 0;
	currentPlayer = 0;
	choice1 = 1; 		// index of money to trash
	choice2 = copper;	// money to gain in hand

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore-1);	
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore+1);
	printf("number of copper in p1 hand = %d, expected = %d\n", cardsInHand(&testG, copper, 0), numCopper+1);
	printf("number of silver in p1 hand = %d, expected = %d\n", cardsInHand(&testG, silver, 0), numSilver-1);
	printf("number of gold in p1 hand = %d, expected = %d\n", cardsInHand(&testG, gold, 0), numGold);
	printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, playCount);
	printf("number of copper cards in played = %d, expected = %d\n", cardsInPlayed(&testG, copper), numCopperPlayed);
	printf("number of silver cards in played = %d, expected = %d\n", cardsInPlayed(&testG, silver), numSilverPlayed);
	printf("number of gold cards in played = %d, expected = %d\n", cardsInPlayed(&testG, gold), numGoldPlayed);

    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
