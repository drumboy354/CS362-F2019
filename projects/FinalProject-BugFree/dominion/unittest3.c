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
                 remodel, smithy, village, baron, province};

	// Test variables
	int numPlayers = 2;
	int seed = 1000;
	int currentPlayer;

	int handCountBefore, discardCountBefore;
	int numCouncil, numAdv, numAdvDiscard, numCouncilDiscard;
	int numProvHand, numProvDiscard;
	int handPos, choice1, choice2, choice3;
	int coin_bonus = 0, card;

	struct gameState G, testG;	 

	// Start tests
    printf ("*****************\nInitializing tests for BUG 3\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 

	// ----------TEST 1:
	// -1 council_room, +1 adventurer 
	
	printf("----------TEST 1: -1 council_room (trashed), +1 adventurer (to discard). VALID PLAY---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = remodel;
	testG.hand[0][1] = council_room;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCouncil = cardsInHand(&testG, council_room, 0);
	numAdv = cardsInHand(&testG, adventurer, 0);
	numAdvDiscard = cardsInDiscard(&testG, adventurer, 0);

	handPos = 0;
	currentPlayer = 0;
	choice1 = 1; 		// index of card to trash
	choice2 = adventurer;	// card to gain

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("council_room cost = %d, expected = %d\n", getCost(council_room), 5);
	printf("adventurer cost = %d, expected = %d\n", getCost(adventurer), 6);
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore-2);	// Discarding remodel, council_room
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore+2); // +1 remodel, +1 card exchanging
	printf("number of council_room in p1 hand = %d, expected = %d\n", cardsInHand(&testG, council_room, 0), numCouncil-1);
	printf("number of adventurer in p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, adventurer, 0), numAdvDiscard+1);

	// ----------TEST 2:
	// -1 adventurer, +1 council 
	
	printf("\n----------TEST 2: -1 adventurer (trashed), +1 council_room (to discard). VALID PLAY---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = remodel;
	testG.hand[0][1] = adventurer;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCouncil = cardsInHand(&testG, council_room, 0);
	numCouncilDiscard = cardsInDiscard(&testG, council_room, 0);
	numAdv = cardsInHand(&testG, adventurer, 0);
	numAdvDiscard = cardsInDiscard(&testG, adventurer, 0);

	handPos = 0;
	currentPlayer = 0;
	choice1 = 1; 			// index of card to trash
	choice2 = council_room;	// card to gain

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore-2);	// Discarding remodel, adventurer
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore+2); // +1 remodel, +1 card exchanging
	printf("number of adventurer in p1 hand = %d, expected = %d\n", cardsInHand(&testG, adventurer, 0), numAdv-1);
	printf("number of council_room in p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, council_room, 0), numCouncilDiscard+1);

	// ----------TEST 3:
	// -1 council_room, +1 province. INVALID.
	
	printf("\n----------TEST 3: -1 council_room (trashed), +1 province (to discard). INVALID PLAY, NOTHING SHOULD HAPPEN.---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = remodel;
	testG.hand[0][1] = council_room;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCouncil = cardsInHand(&testG, council_room, 0);
	numCouncilDiscard = cardsInDiscard(&testG, council_room, 0);
	numProvHand = cardsInHand(&testG, province, 0);
	numProvDiscard = cardsInDiscard(&testG, province, 0);

	handPos = 0;
	currentPlayer = 0;
	choice1 = 1; 			// index of card to trash
	choice2 = province;		// card to gain

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("council_room cost = %d, expected = %d\n", getCost(council_room), 5);
	printf("province cost = %d, expected = %d\n", getCost(province), 8);
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore);	
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore); 
	printf("number of council_room in p1 hand = %d, expected = %d\n", cardsInHand(&testG, council_room, 0), numCouncil);
	printf("number of province in p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, province, 0), numProvDiscard);

	// ----------TEST 4:
	// -1 province, +1 council_room. VALID.
	
	printf("\n----------TEST 4: -1 province (trashed), +1 council_room (to discard). VALID PLAY.---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	
	// Set cards for p1
	testG.hand[0][0] = remodel;
	testG.hand[0][1] = province;
	testG.hand[0][2] = copper;
	testG.hand[0][3] = copper;
	testG.hand[0][4] = gold;

	// Set test vars
	handCountBefore = testG.handCount[currentPlayer];
	discardCountBefore = testG.discardCount[currentPlayer];
	numCouncil = cardsInHand(&testG, council_room, 0);
	numCouncilDiscard = cardsInDiscard(&testG, council_room, 0);
	numProvHand = cardsInHand(&testG, province, 0);
	numProvDiscard = cardsInDiscard(&testG, province, 0);

	handPos = 0;
	currentPlayer = 0;
	choice1 = 1; 				// index of card to trash
	choice2 = council_room;		// card to gain

	// Get the card played
	card = handCard(handPos, &testG);

	// Call function
	cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCountBefore-2);	// Discarding remodel, province
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCountBefore+2); // +1 remodel, +1 card exchanging
	printf("number of province in p1 hand = %d, expected = %d\n", cardsInHand(&testG, province, 0), numProvHand);
	printf("number of council_room in p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, council_room, 0), numCouncilDiscard+1);

    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
