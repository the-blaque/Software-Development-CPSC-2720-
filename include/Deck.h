/**
* @author Oluwaseeni Ajayi <oluwaseeni.ajayi@uleth.ca>
* @author Justin Alho <alhoj@uleth.ca>
* @date 2022-04
*/

#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <iostream>
#include <vector>

class Deck {
 public:
  /**
  *@brief Deck Constructor
  */
  Deck();

  /**
  *@brief Deck Destructor
  */
  ~Deck();

  /**
  *@param Card
  *@return nothing
  */
  void insertCard(Card* c);

  /**
  *@param Card
  *@param Deck
  *@return nothing
  */
  void moveCard(Deck* receiver, Card* c);

  /**
  *@brief Returns the first card in the deck
  */
  Card* draw();

  /**
  *@brief Shuffles the cards vector
  */
  void shuffle();

  /**
  *@return bool
  */
  bool isEmpty();

  /**
  *@param Deck
  *@param Ostream
  *@return Ostream
  */
  friend std::ostream& operator << (std::ostream& out, Deck& d);

  /**
  *@return the size of the cards vector
  */
  int getSize() const;

  /**
  *@brief Returns all cards that are valid to play on topCard.
  *@param topCard The top card of the discard pile
  *@return vector<Card*> A vector containing all valid cards
  */
  std::vector<Card*> findValid(Card* topCard);

  /**
  *@brief Returns the top card of the discard
  *@return Card* The top card of the deck
  */
  Card* returnTop();

 private:
  int deckSize;
  std::vector<Card*> cards;
};

#endif
