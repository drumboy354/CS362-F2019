#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "dominionHelperFuncs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main () {
	// Setup random seed
	srand(time(NULL));
	
	// Cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

	// Test variables
	int numPlayers = 3;
	int seed = 1000;
	int currentPlayer = 0;
	int rand1, rand2, rand3;
	int numTests = 1000;

	int	numActions1, numCoins, choice1, choice2, randCard, randNumCards, handPos;
	int handCount[numPlayers], discardCount[numPlayers];
	int eDiscCount[numPlayers], eHandCount[numPlayers]; // Expected discard/hand count
	int eNumCoins;							// Expected num coins

	// Game state
    struct gameState G, testG;	

	// Start tests
    printf ("*****************\nInitializing tests for CARD MINION\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 
	
	for(int i = 0; i < numTests; i++){	
		// Copy game state
		memcpy(&testG, &G, sizeof(struct gameState));

		// Set cards for p1
		testG.hand[0][0] = baron;
		testG.hand[0][1] = silver;
		testG.hand[0][2] = copper;
		testG.hand[0][3] = copper;
		testG.hand[0][4] = gold;
	
		for(int i = 1; i < numPlayers; i++){
			// Set cards for everyone but p1
			randNumCards = rand()%8+1;	// Random number of cards, between 1 and 8

			for(int j = 0; j < randNumCards; j++){	
				randCard = rand()%10;	// Pick random card from k, 0-9
				gainCard(k[randCard], &testG, 2, i);
			}
		}
		
		// Set random test vars
		choice1 = rand()%2;							// Generate number between 0 and 1
		choice2 = (choice1 == 0) ? 1 : 0;			// If choice1 == 0, choice2 = 1 (make choice2 opposite of choice1)
		rand1 = rand()%100+1;						// Generate number between 1 and 100
		rand2 = rand()%100+1;						// Generate number between 1 and 100	
		handPos = rand()%5;							// Random position of minion card in p1 hand

		// Replace one card to be minion
		testG.hand[currentPlayer][handPos] = minion;	

		// Set assert vars	
		for(int i = 0; i < numPlayers; i++){
			handCount[i] = testG.handCount[i];
			discardCount[i] = testG.discardCount[i];
			
			// Set specific vars for p1
			if(i == 0){
				numActions1 = testG.numActions;
				numCoins = testG.coins;
			}
		}

		// ----------TESTS 
		printf("\n------TEST %d, choice1: %d, choice2: %d, p2 handCard count: %d, p3 handCard count: %d------\n", i+1, choice1, choice2, testG.handCount[1], testG.handCount[2]);

		// Call function
		cardMinion(&testG, choice1, choice2, handPos, currentPlayer);
		
		// Test results					
		for(int i = 0; i < numPlayers; i++){
			// p1 specific 
			if(i == 0){
				eHandCount[i] = (choice1 == 0) ? 4 : handCount[i]-1;				// If player discards hand, +4 cards
				eDiscCount[i] = (choice1 == 0) ? discardCount[i]+handCount[i] : discardCount[i]+1;
				eNumCoins = (choice1 == 1) ? 2 : 0;									// If player chooses not to discard, +2 coins
			}
			else{ // Not player 1
				eHandCount[i] = (choice1 == 1 && handCount[i] > 4) ? 4 : handCount[i]; // If p1 discards hand and this p has > 4 cards, +4 cards 
				eDiscCount[i] = (choice1 == 1 && handCount[i] > 4) ? discardCount[i]+handCount[i] : discardCount[i];
			}
		
			// Print p1 specific asserts
			if(i == 0){
				printf("number of actions for p1 = %d, expected = %d\n", testG.numActions, numActions1+1);
				printf("number of coins for p1 = %d, expected = %d\n", testG.coins, numCoins+eNumCoins);
			}
			printf("number of cards in p%d hand = %d, expected = %d\n", i+1, testG.handCount[i], eHandCount[i]);
			printf("number of cards in p%d discard = %d, expected = %d\n", i+1, testG.discardCount[i], eDiscCount[i]);
			printf("---\n");
			
		}

		printf("\n");
	}	

    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
