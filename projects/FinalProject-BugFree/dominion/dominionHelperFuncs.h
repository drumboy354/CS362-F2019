#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/***************************
 * Function will return number of cards that match "card" in the 
 * player's hand.
 ***************************/
int cardsInHand(const struct gameState *G, int card, int player);

/***************************
 * Function will return number of cards that match "card" in the 
 * player's deck.
 ***************************/
int cardsInDeck(const struct gameState *G, int card, int player);

/***************************
 * Function will return number of cards that match "card" in the 
 * player's discard.
 ***************************/
int cardsInDiscard(const struct gameState *G, int card, int player);

/***************************
 * Function will return number of cards that match "card" in the 
 * playedCards deck.
 ***************************/
int cardsInPlayed(const struct gameState *G, int card);

/***************************
 * Function will print all cards in "player" hand
 ***************************/
void printHandCards(const struct gameState *G, int player);

/***************************
 * Function will print all cards in "player" deck
 ***************************/
void printDeckCards(const struct gameState *G, int player);

/***************************
 * Function will print all cards in "player" discard
 ***************************/
void printDiscardCards(const struct gameState *G, int player);

/***************************
 * Function will print all cards in playedCards
 ***************************/
void printPlayedCards(const struct gameState *G);
