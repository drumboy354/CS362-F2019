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
    int k[10] = {tribute, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
	
	int tribCards[9] = {copper, silver, gold, council_room, feast, gardens, 
						estate, duchy, province};

	// Test variables
	int numPlayers = 2;
	int seed = 1000;
	int currentPlayer = 0;
	int nextPlayer = 1;
	int randTrib1, randTrib2, randDeck1, randDeck2, randDisc1, randDisc2;
	int numTests = 1000, temp;

	int	numActions1, coincount1, randCard, randNumCards;
	int deckCount, deckCount2;
	int handCount1, handCount2, discardCount1, discardCount2;
	int eHandCount1, eDiscCount1; 			// Expected discard/hand count
	int eNumCoins;							// Expected num coins
	int eActions;							// Expected actions
	int tributeRevealedCards[2];

	// Game state
    struct gameState G, testG;	

	// Start tests
    printf ("*****************\nInitializing tests for CARD TRIBUTE\n********************\n");

	initializeGame(numPlayers, k, seed, &G); 
	
	for(int i = 0; i < numTests; i++){	
		// Copy game state
		memcpy(&testG, &G, sizeof(struct gameState));
	
		// Set cards for p1
		testG.hand[0][0] = minion;
		testG.hand[0][1] = silver;
		testG.hand[0][2] = copper;
		testG.hand[0][3] = copper;
		testG.hand[0][4] = gold;

		// Generate random tribute 1 and 2 revealed cards
		randTrib1 = rand()%9;
		randTrib2 = rand()%9;

		// Set hand for second player
		tributeRevealedCards[0] = tribCards[randTrib1];
		tributeRevealedCards[1] = tribCards[randTrib2];

		// Set nextPlayer's cards
		gainCard(adventurer, &testG, 2, nextPlayer);
		gainCard(copper, &testG, 2, nextPlayer);
		gainCard(gardens, &testG, 2, nextPlayer);
		gainCard(tributeRevealedCards[0], &testG, 2, nextPlayer);
		gainCard(tributeRevealedCards[1], &testG, 2, nextPlayer);	

		// Set assert vars	
		handCount1 = testG.handCount[currentPlayer];
		discardCount1 = testG.discardCount[currentPlayer];
		coincount1 = testG.coins;
		numActions1 = testG.numActions;
	
		handCount2 = testG.handCount[1];
		discardCount2 = testG.discardCount[1];
		deckCount2 = testG.deckCount[nextPlayer];

		// Randomize deck count for p2 (nextPlayer)
		randDeck1 = rand()%2;			// If randDeck1 == 1, make deck count be 0 or 1
		if(randDeck1){
			randDeck2 = rand()%2;		// Value between 0 and 1, will be what deck count will equal after for loop
			for(int i = deckCount2-1; i >= randDeck2; i--){
				testG.deck[nextPlayer][i] = -1;
				testG.deckCount[nextPlayer]--;
			}	
		}

		// Randomize discard count for p2 (nextPlayer)
		randDisc1 = rand()%2; // If randDisc1 == 1, randomize discard count
		if(randDisc1){
			// First, empty discard for p2
			temp = testG.discardCount[nextPlayer];
			for(int i = temp-1; i >= 0; i--){
				testG.discard[nextPlayer][i] = -1;
				testG.discardCount[nextPlayer]--;
			}
			// Put new cards into discard count for p2
			randDisc2 = rand()%3;				 // Make discard count be between 0 and 3
			for(int i = 0; i < randDisc2; i++){
				temp = rand()%10;				// Generate random card to put in discard pile for p2
				testG.discard[nextPlayer][temp];
				testG.discardCount[nextPlayer]++;
			}
		}

		// The following 3 char* are ONLY for printing out more legible readouts for the tests
		char* trib1; 
		char* trib2; 
		char* tempS;

		if(randTrib1 < 3){ trib1 = "treasure"; }
		else if(randTrib1 > 5){ trib1 = "victory"; }
		else{ trib1 = "action"; }

		if(randTrib2 < 3){ trib2 = "treasure"; }
		else if(randTrib2 > 5){ trib2 = "victory"; }
		else{ trib2 = "action"; }

		if(tributeRevealedCards[0] == tributeRevealedCards[1]){ tempS = "yes"; }
		else{ tempS = "no"; }

		// ----------TESTS 
		printf("\n------TEST %d, tribCard[0]: %s, tribCard[1]: %s, tribCard[0] == tribCard[1]? %s------\n", i+1, trib1, trib2, tempS);

		// Call function
		cardTribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);

		// Set assert vars after function call
		// Reset expected counts
		eDiscCount1 = eNumCoins = eActions = 0;

		if(tributeRevealedCards[0] == copper || tributeRevealedCards[0] == silver || tributeRevealedCards[0] == gold){
			eNumCoins = 2;
		}
		else if (tributeRevealedCards[0] == estate || tributeRevealedCards[0] == duchy || tributeRevealedCards[0] == province){
			eDiscCount1 = 2;
		}
		else{
			eActions = 2;
		}
		
		if(tributeRevealedCards[1] == copper || tributeRevealedCards[1] == silver || tributeRevealedCards[1] == gold){
			if(tributeRevealedCards[1] != tributeRevealedCards[0]){
				eNumCoins += 2;
			}
		}
		else if (tributeRevealedCards[1] == estate || tributeRevealedCards[1] == duchy || tributeRevealedCards[1] == province){
			if(tributeRevealedCards[1] != tributeRevealedCards[0]){
				eDiscCount1 += 2;
			}
		}
		else{
			if(tributeRevealedCards[1] != tributeRevealedCards[0]){
				eActions += 2;
			}
		}
		
		// Test results					
		printf("number of cards in p1 hand = %d, expected = %d\n", testG.handCount[currentPlayer], handCount1-1);
		printf("number of cards in p1 discard = %d, expected = %d\n", testG.discardCount[currentPlayer], discardCount1+eDiscCount1);
		printf("number of coins p1 = %d, expected = %d\n", testG.coins, coincount1+eNumCoins);
		printf("number of actions p1 = %d, expected = %d\n", testG.numActions, numActions1+eActions);
	
		printf("---\n");
		printf("number of cards in p2 hand = %d, expected = %d\n", testG.handCount[nextPlayer], handCount2-2);
		printf("number of cards in p2 discard = %d, expected = %d\n", testG.discardCount[nextPlayer], discardCount2+2);

	}	

    printf ("\n*******************\nALL TESTS DONE\n*********************\n");

    exit(0);

}
