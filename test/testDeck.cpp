/**
* @author Justin Alho <alhoj@uleth.ca>, Liam Boogaart <liam.boogaart@uleth.ca>
* @date 2022-04
*/

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Exceptions.h"
#include "gtest/gtest.h"

TEST(TestDeck, AddCardTest) {
  Card* aceHearts = new Card(Card::Ace, Card::Hearts);
  Card* twoSpades = new Card(Card::Two, Card::Spades);
  Card* threeWild = new Card(Card::Three, Card::Wild);
  Deck* d = new Deck();
  d->insertCard(aceHearts);
  d->insertCard(twoSpades);
  d->insertCard(threeWild);
  EXPECT_EQ(d->getSize(), 3);

  delete d;
}

TEST(TestDeck, AddNullCardTest) {
  Card* nullCard = nullptr;
  Deck* d = new Deck();
  EXPECT_THROW(d->insertCard(nullCard), pointer_cannot_be_null);

  delete d;
}

TEST(TestDeck, MoveCardTest) {
  Deck* one = new Deck();
  Deck* two = new Deck();
  Card* aceHearts = new Card(Card::Ace, Card::Hearts);
  one->insertCard(aceHearts);
  EXPECT_EQ(one->getSize(), 1);
  EXPECT_EQ(one->returnTop(), aceHearts);
  one->moveCard(two, aceHearts);
  EXPECT_EQ(one->getSize(), 0);
  EXPECT_EQ(two->returnTop(), aceHearts);
  delete one;
  delete two;
}

TEST(TestDeck, MoveCardNullTest) {
  Deck* one = new Deck();
  Deck* two = new Deck();
  Deck* nullDeck  = nullptr;
  Card* nullCard = nullptr;
  Card* aceHearts = new Card(Card::Ace, Card::Hearts);
  one->insertCard(aceHearts);
  EXPECT_THROW(one->moveCard(two, nullCard), pointer_cannot_be_null);
  EXPECT_THROW(one->moveCard(nullDeck, aceHearts), pointer_cannot_be_null);
  delete one;
  delete two;
}

TEST(TestDeck, DrawTest) {
  Deck* one = new Deck();
  Deck* two = new Deck();
  Card* aceHearts = new Card(Card::Ace, Card::Hearts);
  Card* twoSpades = new Card(Card::Two, Card::Spades);
  Card* threeWild = new Card(Card::Three, Card::Wild);
  one->insertCard(aceHearts);
  one->insertCard(twoSpades);
  one->insertCard(threeWild);
  EXPECT_EQ(one->draw(), aceHearts);
  one->moveCard(two, aceHearts);
  EXPECT_EQ(one->draw(), twoSpades);
  one->moveCard(two, twoSpades);
  EXPECT_EQ(one->draw(), threeWild);
  delete one;
  delete two;
}

TEST(TestDeck, ShuffleTest) {
  Deck* d = new Deck();
  //Create a load of cards
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      Card* x = new Card(static_cast<Card::Rank>(i),
      static_cast<Card::Suit>(j));
      d->insertCard(x);
    }
  }

  Card* c = d->draw();
  d->shuffle();
  EXPECT_NE(c, d->draw());
  delete d;
}

TEST(TestDeck, IsEmptyTest) {
  Deck* d = new Deck();
  EXPECT_TRUE(d->isEmpty());
  delete d;
}

TEST(TestDeck, IsNotEmptyTest) {
  Deck* d = new Deck();
  Card* c = new Card(Card::Ace, Card::Hearts);
  d->insertCard(c);
  EXPECT_FALSE(d->isEmpty());
  delete d;
}

//Some/all of these should be for different classes when/if I refactor - Liam
TEST(TestDeck, FindValidTest) {
  Deck* d = new Deck();
  std::vector<Card*> v;
  for (int i = 0; i < 13; i++) {
    Card* x = new Card(static_cast<Card::Rank>(i), Card::Hearts);
    d->insertCard(x);
    v.push_back(x);
  }
  for (int i = 0; i < 13; i++) {
    Card* x = new Card(static_cast<Card::Rank>(i), Card::Spades);
    d->insertCard(x);
    if (i == 0) v.push_back(x);
  }
  Card* t = new Card(Card::Ace, Card::Hearts);
  std::vector<Card*> o = d->findValid(t);
  EXPECT_EQ(o.size(), v.size());
  for (int i = 0; i < o.size(); i++) {
    EXPECT_EQ(o[i], v[i]);
  }
  delete d;
  delete t;
}

TEST(TestDeck, ReturnTopTest) {
  Deck* d = new Deck();
  Card* c;
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      Card* x = new Card(static_cast<Card::Rank>(i),
      static_cast<Card::Suit>(j));
      d->insertCard(x);
      if (i == 12 && j == 3) c = x;
    }
  }
  EXPECT_EQ(d->returnTop(), c);
  delete d;
}
