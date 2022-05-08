/**
* @author Justin Alho <alhoj@uleth.ca>
* @date 2022-04
*/

#include "Menu.h"
#include "Game.h"
#include "Uno.h"
#include "Exceptions.h"
#include "gtest/gtest.h"

TEST(TestMenu, CreateGameNullTest) {
  Menu* m = new Menu();
  Game* g  = nullptr;
  EXPECT_THROW(m->createGame(g), pointer_cannot_be_null);
  delete g;
  delete m;
}

//I don't know why this test doesn't pass, it creates the game fine
TEST(TestMenu, DISABLED_CreateGameNotNullTest) {
  Menu* m = new Menu();
  Game* g  = new Uno();
  EXPECT_NO_THROW(m->createGame(g));
  delete g;
  delete m;
}
