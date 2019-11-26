#include "dominionHelperFuncs.h"

/***************************
 * Function will return number of cards that match "card" in the 
 * player's hand.
 ***************************/
int cardsInHand(const struct gameState *G, int card, int player){
	int numCards = 0;

	// List cards
	for(int i = 0; i < G->handCount[player]; i++){

		if(G->hand[player][i] == card){
			numCards++;
		}
	}

	return numCards;
}

/***************************
 * Function will return number of cards that match "card" in the 
 * player's deck.
 ***************************/
int cardsInDeck(const struct gameState *G, int card, int player){
	int numCards = 0;

	// List cards
	for(int i = 0; i < G->deckCount[player]; i++){

		if(G->deck[player][i] == card){
			numCards++;
		}
	}

	return numCards;
}

/***************************
 * Function will return number of cards that match "card" in the 
 * player's discard.
 ***************************/
int cardsInDiscard(const struct gameState *G, int card, int player){
	int numCards = 0;

	// List cards
	for(int i = 0; i < G->discardCount[player]; i++){

		if(G->discard[player][i] == card){
			numCards++;
		}
	}

	return numCards;
}

/***************************
 * Function will return number of cards that match "card" in the 
 * playedCards deck.
 ***************************/
int cardsInPlayed(const struct gameState *G, int card){
	int numCards = 0;

	// List cards
	for(int i = 0; i < G->playedCardCount; i++){

		if(G->playedCards[i] == card){
			numCards++;
		}
	}

	return numCards;
}

/***************************
 * Function will print all cards in "player" hand
 ***************************/
void printHandCards(const struct gameState *G, int player){
	printf("Cards in p%d hand: ", player+1);
	for(int i = 0; i < G->handCount[player]; i++){
		printf("%d, ", G->hand[player][i]);

	}
	printf("\n");
}

/***************************
 * Function will print all cards in "player" deck
 ***************************/
void printDeckCards(const struct gameState *G, int player){
	printf("Cards in p%d deck: ", player+1);
	for(int i = 0; i < G->deckCount[player]; i++){
		printf("%d, ", G->deck[player][i]);

	}
	printf("\n");
}

/***************************
 * Function will print all cards in "player" discard
 ***************************/
void printDiscardCards(const struct gameState *G, int player){
	printf("Cards in p%d discard: ", player+1);
	for(int i = 0; i < G->discardCount[player]; i++){
		printf("%d, ", G->discard[player][i]);

	}
	printf("\n");
}

/***************************
 * Function will print all cards in playedDeck
 ***************************/
void printPlayedCards(const struct gameState *G){
	printf("Cards in played deck: ");
	for(int i = 0; i < G->playedCardCount; i++){
		printf("%d, ", G->playedCards[i]);
	}
	printf("\n");
}
