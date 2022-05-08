/**
* @author Justin Alho <alhoj@uleth.ca>
* @date 2022-04
*/

#ifndef MENU_H
#define MENU_H

#include "Game.h"

class Menu {
 public:
  /**
  *@brief Menu Constructor
  **/
  Menu();

  /**
  *@brief Menu Destructor
  **/
  ~Menu();

  /**
  *@brief function to get the player's input and choose a game
  **/
  void chooseGame();

  /**
  *@brief function to create a game selected by the player
  **/
  void createGame(Game* g);
 private:
  Game* chosenGame;
};
#endif
