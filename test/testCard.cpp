/**
* @author Liam Boogaart <liam.boogaart@uleth.ca>
* @date 2022-04
*/

#include "Card.h"
#include "gtest/gtest.h"

TEST(TestCard, WildEqualityTest) {
  Card twoHearts(Card::Two, Card::Hearts);
  Card aceWild(Card::Ace, Card::Wild);
  EXPECT_TRUE(aceWild == twoHearts);
  EXPECT_TRUE(twoHearts == aceWild);
}

TEST(TestCard, ValueEqualityTest) {
  Card twoClubs(Card::Two, Card::Clubs);
  Card twoDiamonds(Card::Two, Card::Diamonds);
  Card noneHearts(Card::None, Card::Hearts);
  Card threeSpades(Card::Three, Card::Spades);
  EXPECT_TRUE(twoClubs == twoDiamonds);
  EXPECT_TRUE(twoDiamonds == twoClubs);
  EXPECT_FALSE(twoClubs == noneHearts);
  EXPECT_FALSE(threeSpades == twoDiamonds);
}

TEST(TestCard, SuitEqualityTest) {
  Card twoClubs(Card::Two, Card::Clubs);
  Card threeClubs(Card::Three, Card::Clubs);
  EXPECT_TRUE(twoClubs == threeClubs);
  EXPECT_TRUE(threeClubs == twoClubs);
}
