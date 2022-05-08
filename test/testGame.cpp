/**
* @author Justin Alho <alhoj@uleth.ca>
* @date 2022-04
*/

#include <string>
#include "Game.h"
#include "Uno.h"
#include "gtest/gtest.h"

TEST(TestGame, LowercaseConvertTest) {
  Uno* u = new Uno();
  u->initDeck();
  std::string up = "TEST";
  std::string low = "test";
  EXPECT_NE(up, low);
  EXPECT_EQ(u->convertToLowercase(up), low);
  delete u;
}
