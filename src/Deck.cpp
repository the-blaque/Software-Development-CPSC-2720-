/**
* @author Oluwaseeni Ajayi <oluwaseeni.ajayi@uleth.ca>
* @author Justin Alho <alhoj@uleth.ca>
* @date 2022-04
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include "Deck.h"
#include "Card.h"
#include "Exceptions.h"

Deck::Deck():deckSize(0) {}

Deck::~Deck() {
  for (int i = 0; i < cards.size(); i++) {
    delete cards[i];
    cards[i] = nullptr;
  }
}

void Deck::insertCard(Card* c) {
  if (c == nullptr) {
    throw pointer_cannot_be_null("Card cannot be null.");
  }
  this -> cards.push_back(c);
  this -> deckSize++;
}

void Deck::moveCard(Deck* receiver, Card* c) {
  for (int i = 0; i < this->deckSize; i++) {
    if (receiver == nullptr || c == nullptr) {
      throw pointer_cannot_be_null("Cards and decks cannot be null.");
    }
    if (c->getSuit() == cards[i]->getSuit() &&
     c->getRank() == cards[i]->getRank()) {
      cards.erase(cards.begin()+i);
      receiver->cards.push_back(c);
      this->deckSize--;
      receiver->deckSize++;
      break;
    }
  }
}

Card* Deck::draw() {
  return cards[0];
}

void Deck::shuffle() {
  std::random_shuffle(cards.begin(), cards.end());
}

bool Deck::isEmpty() {
  return cards.empty();
}

std::ostream& operator<<(std::ostream& out, Deck& d) {
  for (int i = 0; i < d.deckSize; i++) {
    out << i << " -- " << *(d.cards[i]) << std::endl;
  }
  return out;
}

int Deck::getSize() const {
  return deckSize;
}

std::vector<Card*> Deck::findValid(Card* topCard) {
  std::vector<Card*> output;
  //Check every card
  for (std::vector<Card*>::iterator
    it = std::begin(cards); it != std::end(cards); ++it) {
      if (*(*it) == *topCard) {
        output.push_back(*it);
      }
    }
  return output;
}

Card* Deck::returnTop() {
  return cards[cards.size() - 1];
}
