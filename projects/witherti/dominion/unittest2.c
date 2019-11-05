#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominionHelperFuncs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main () {
	
	// Cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

	// Test variables
	int numPlayers = 3;
	int seed = 1000;
	int funcReturn;
	int choice1, choice2, choice3;
	int handPos;
	int currentPlayer;

	// Game state
    struct gameState G, testG;	

	// Start tests
    printf ("*****************\nInitializing tests.\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 

	// ----------TEST 1:  
	// choice1 = 4, discard an estate card (there's multiple of these in p1's hand)
	// choice2 = 0, return 0 to supply pile, no player gains any cards
	// handPos = 0, current position is first card
	printf("----------TEST 1: choice2 = 0, return 0 cards, no player should gain any cards---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 4;
	choice1 = 1;
	choice2 = 0;
	currentPlayer = 0;

	// Set hand for second player
	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);

	// Set test vars
	int handCount1 = testG.handCount[currentPlayer];
	int deckCount1 = testG.deckCount[currentPlayer];
	int discardCount1 = testG.discardCount[currentPlayer];
	int handCount2 = testG.handCount[1];
	int deckCount2 = testG.deckCount[1];
	int discardCount2 = testG.discardCount[1];
	int numCardDiscard2 = cardsInDiscard(&testG, testG.hand[1][choice1], 1); // Num of cards in discard for player 2 that matches player1's choice
	int handCount3 = testG.handCount[2];
	int deckCount3 = testG.deckCount[2];
	int discardCount3 = testG.discardCount[2];
	int numCardDiscard3 = cardsInDiscard(&testG, testG.hand[2][choice1], 2); // Num of cards in discard for player 3 that matches player1's choice


	// Call function
	cardAmbassador(&testG, choice1, choice2, currentPlayer, handPos);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1-choice2-1);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1+1);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], handCount2);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2+1);
	printf("number of cards in p2 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 1), numCardDiscard2);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], handCount3);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3+1);
	printf("number of cards in p3 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 2), numCardDiscard3);

	// ----------TEST 2:  
	// choice1 = 1, discard an estate card (there's multiple of these in p1's hand)
	// choice2 = 1, return 1 to supply pile, one player should get this card
	// handPos = 0, current position is first card
	printf("\n----------TEST 2: return 1 estate to supply. Only p2 should gain a card---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 1;
	choice2 = 1;
	currentPlayer = 0;

	// Set hand for second player
	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	deckCount1 = testG.deckCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	handCount2 = testG.handCount[1];
	deckCount2 = testG.deckCount[1];
	discardCount2 = testG.discardCount[1];
	numCardDiscard2 = cardsInDiscard(&testG, testG.hand[1][choice1], 1); // Num of cards in discard for player 2 that matches player1's choice
	handCount3 = testG.handCount[2];
	deckCount3 = testG.deckCount[2];
	discardCount3 = testG.discardCount[2];
	numCardDiscard3 = cardsInDiscard(&testG, testG.hand[2][choice1], 2); // Num of cards in discard for player 3 that matches player1's choice


	// Call function
	cardAmbassador(&testG, choice1, choice2, currentPlayer, handPos);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1-choice2-1);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1+1);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], handCount2);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2+1);
	printf("number of cards in p2 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 1), numCardDiscard2+1);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], handCount3);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3);
	printf("number of cards in p3 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 2), numCardDiscard3);

	// ----------TEST 3:  
	// choice1 = 1, discard an estate card (there's multiple of these in p1's hand)
	// choice2 = 2, return 2 to supply pile, both p2 and p3 should gain card
	// handPos = 0, current position is first card
	printf("\n----------TEST 3: return 2 estates to supply. p2 & p3 should gain a card---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 1;
	choice2 = 2;
	currentPlayer = 0;

	// Set hand for second player
	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	deckCount1 = testG.deckCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	handCount2 = testG.handCount[1];
	deckCount2 = testG.deckCount[1];
	discardCount2 = testG.discardCount[1];
	numCardDiscard2 = cardsInDiscard(&testG, testG.hand[1][choice1], 1); // Num of cards in discard for player 2 that matches player1's choice
	handCount3 = testG.handCount[2];
	deckCount3 = testG.deckCount[2];
	discardCount3 = testG.discardCount[2];
	numCardDiscard3 = cardsInDiscard(&testG, testG.hand[2][choice1], 2); // Num of cards in discard for player 3 that matches player1's choice


	// Call function
	cardAmbassador(&testG, choice1, choice2, currentPlayer, handPos);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1-choice2-1);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1+1);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], handCount2);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2+1);
	printf("number of cards in p2 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 1), numCardDiscard2+1);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], handCount3);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3+1);
	printf("number of cards in p3 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 2), numCardDiscard3+1);

	// ----------TEST 4:
	// choice1 = 1, discard an estate card (there's multiple of these in p1's hand)
	// choice2 = 10, return 10 cards. This should do nothing.
	// handPos = 0, current position is first card
	printf("\n----------TEST 4: return 10 estates to supply. Invalid Choice. Nothing should happen.---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 1;
	choice2 = 10;
	currentPlayer = 0;

	// Set hand for second player
	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	deckCount1 = testG.deckCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	handCount2 = testG.handCount[1];
	deckCount2 = testG.deckCount[1];
	discardCount2 = testG.discardCount[1];
	numCardDiscard2 = cardsInDiscard(&testG, testG.hand[1][choice1], 1); // Num of cards in discard for player 2 that matches player1's choice
	handCount3 = testG.handCount[2];
	deckCount3 = testG.deckCount[2];
	discardCount3 = testG.discardCount[2];
	numCardDiscard3 = cardsInDiscard(&testG, testG.hand[2][choice1], 2); // Num of cards in discard for player 3 that matches player1's choice


	// Call function
	cardAmbassador(&testG, choice1, choice2, currentPlayer, handPos);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], handCount2);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2);
	printf("number of cards in p2 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 1), numCardDiscard2);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], handCount3);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3);
	printf("number of cards in p3 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 2), numCardDiscard3);

	// ----------TEST 5:
	// choice1 = 1, discard an estate card (there's multiple of these in p1's hand)
	// choice2 = -20, invalid choice. Do nothing.
	// handPos = 0, current position is first card
	printf("\n----------TEST 5: return -20 estates to supply. Invalid choice. Nothing should happen.---------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	handPos = 0;
	choice1 = 1;
	choice2 = -20;
	currentPlayer = 0;

	// Set hand for second player
	gainCard(adventurer, &testG, 2, 1);
	gainCard(copper, &testG, 2, 1);
	gainCard(gardens, &testG, 2, 1);
	gainCard(mine, &testG, 2, 1);
	gainCard(feast, &testG, 2, 1);

	// Set hand for third player
	gainCard(council_room, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);
	gainCard(gardens, &testG, 2, 2);
	gainCard(mine, &testG, 2, 2);
	gainCard(feast, &testG, 2, 2);

	// Set test vars
	handCount1 = testG.handCount[currentPlayer];
	deckCount1 = testG.deckCount[currentPlayer];
	discardCount1 = testG.discardCount[currentPlayer];
	handCount2 = testG.handCount[1];
	deckCount2 = testG.deckCount[1];
	discardCount2 = testG.discardCount[1];
	numCardDiscard2 = cardsInDiscard(&testG, testG.hand[1][choice1], 1); // Num of cards in discard for player 2 that matches player1's choice
	handCount3 = testG.handCount[2];
	deckCount3 = testG.deckCount[2];
	discardCount3 = testG.discardCount[2];
	numCardDiscard3 = cardsInDiscard(&testG, testG.hand[2][choice1], 2); // Num of cards in discard for player 3 that matches player1's choice


	// Call function
	cardAmbassador(&testG, choice1, choice2, currentPlayer, handPos);
	
	// Tests
	printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1);
	printf("number of cards in p1 deck = %d, expected = %d\n", testG.deckCount[currentPlayer], deckCount1);
	printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1);
	printf("---\n");
	printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[1], handCount2);
	printf("number of cards in p2 deck = %d, expected = %d\n", testG.deckCount[1], deckCount2);
	printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[1], discardCount2);
	printf("number of cards in p2 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 1), numCardDiscard2);
	printf("---\n");
	printf("number of cards in p3 hand = %d, expected = %d\n", testG.handCount[2], handCount3);
	printf("number of cards in p3 deck = %d, expected = %d\n", testG.deckCount[2], deckCount3);
	printf("number of cards in p3 discard = %d, expected = %d\n", testG.discardCount[2], discardCount3);
	printf("number of cards in p3 discard that match p1 discard = %d, expected = %d\n", cardsInDiscard(&testG, testG.hand[0][choice1], 2), numCardDiscard3);



    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
