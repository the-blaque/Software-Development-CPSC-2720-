/**
* @author Liam Boogaart <liam.boogaart@uleth.ca>
* @date 2022-04
*/

#include "Card.h"
#include "Deck.h"
#include "Menu.h"
#include <iostream>

int main() {
  Menu* m = new Menu();
  m->chooseGame();

  return 0;
}
