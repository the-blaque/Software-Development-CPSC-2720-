/**
* @author Justin Alho <alhoj@uleth.ca>, Liam Boogaart <liam.boogaart@uleth.ca>
* @date 2022-04
*/

#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include <string>

class Game {
 public:
  /**
  *@brief generic Game Constructor
  **/
  Game();

  /**
  *@brief generic Game destructor
  **/
  virtual ~Game();

  /**
  *@brief function to set up the game
  **/
  virtual void startGame() = 0;

  /**
  *@brief function to set up the cards and decks
  **/
  virtual void initDeck() = 0;

  /**
  *@brief function to allow the player to take their turn
  *@return true if the player has won
  **/
  virtual bool playerTurn() = 0;

  /**
  *@brief function to allow the AI player to take their turn
  *@return true if the player has won
  **/
  virtual bool aiTurn() = 0;

  /**
  *@brief function to show help text to the player
  **/
  virtual void help() = 0;

  /**
  *@brief function to end the game when someone wins
  **/
  virtual void endGame() = 0;

  /**
  *@brief function to reset the game after it ends
  **/
  virtual void reset() = 0;

  /**
  *@brief gets an integer from user between min and max inclusive
  *@return int The input from the user
  */
  int getInput(int min, int max);

  /**
  *@brief converts a string to lowercase
  *@return a lowercase version of the string
  */
  std::string convertToLowercase(std::string input);

 protected:
  Deck* playerHand;
  Deck* aiPlayerHand;
};
#endif
