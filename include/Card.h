/**
* @author Liam Boogaart <liam.boogaart@uleth.ca>, Oluwaseeni Ajayi <oluwaseeni.ajayi@uleth.ca>
* @date 2022-04
*/

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card {
 public:
  /**
  *@brief Enumeration for card ranks
  **/
  enum Rank {Ace = 0, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
    Jack, Queen, King, None, Zero, One, DrawTwo, Skip, Reverse, DrawFour};
  /**
  *@brief Enumeration for card Suits
  **/
  enum Suit {Hearts = 0, Clubs, Spades, Diamonds,
    Red, Blue, Green, Yellow, Wild};

  /**
  *@brief Card Constructor
  *@param Rank The card's rank
  *@param Suit The card's Suit
  **/
  Card(Rank cardRank, Suit cardSuit);

  /**
  *@return The rank of the card
  **/
  Rank getRank() const;

  /**
  *@return The suit of the card
  **/
  Suit getSuit() const;

  /**
  *@return True if the suit or rank is the same, wild suit always matches
  **/
  bool operator==(const Card& card) const;

  /**
  *@param out an output stream
  *@param card a reference to a card
  *@return Output stream containing the card description
  **/
  friend std::ostream& operator<<(std::ostream& out, Card& card);

 private:
  const Rank cardRank;
  const Suit cardSuit;
};

#endif
