/**
* @author Liam Boogaart <liam.boogaart@uleth.ca>
* @date 2022-04
*/

#include <iostream>
#include <string>
#include "Card.h"

Card::Card(Rank Rank, Suit Suit):cardRank(Rank), cardSuit(Suit) {}

Card::Rank Card::getRank() const {
  return cardRank;
}

Card::Suit Card::getSuit() const {
  return cardSuit;
}

bool Card::operator==(const Card& card) const {
  if (cardSuit == card.getSuit() ||
    cardSuit == Wild || card.getSuit() == Wild) {
    return true;
  }
  if (cardRank == card.getRank()) {
    return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& out, Card& card) {
  std::string rank = "";
  std::string suit = "";
  switch (card.cardSuit) {
    case Card::Hearts: suit = "Hearts";
    break;
    case Card::Clubs: suit = "Clubs";
    break;
    case Card::Spades: suit = "Spades";
    break;
    case Card::Diamonds: suit = "Diamonds";
    break;
    case Card::Red: suit = "Red";
    break;
    case Card::Blue: suit = "Blue";
    break;
    case Card::Green: suit = "Green";
    break;
    case Card::Yellow: suit = "Yellow";
    break;
    case Card::Wild: suit = "Wild";
    break;
  }
  switch (card.cardRank) {
    case Card::None: rank = "Card";
    break;
    case Card::Zero: rank = "Zero";
    break;
    case Card::Ace: rank = "Ace";
    break;
    case Card::One: rank = "One";
    break;
    case Card::Two: rank = "Two";
    break;
    case Card::Three: rank = "Three";
    break;
    case Card::Four: rank = "Four";
    break;
    case Card::Five: rank = "Five";
    break;
    case Card::Six: rank = "Six";
    break;
    case Card::Seven: rank = "Seven";
    break;
    case Card::Eight: rank = "Eight";
    break;
    case Card::Nine: rank = "Nine";
    break;
    case Card::Ten: rank = "Ten";
    break;
    case Card::Jack: rank = "Jack";
    break;
    case Card::Queen: rank = "Queen";
    break;
    case Card::King: rank = "King";
    break;
    case Card::DrawTwo: rank = "Draw 2";
    break;
    case Card::Skip: rank = "Skip";
    break;
    case Card::Reverse: rank = "Reverse";
    break;
    case Card::DrawFour: rank = "Draw 4";
  }
  if (static_cast<int>(card.cardSuit) < 4) {
    out << rank << " of " << suit;
    return out;
  }
  out << suit << " " << rank;
  return out;
}
