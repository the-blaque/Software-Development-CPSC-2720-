/**
* @author Justin Alho <alhoj@uleth.ca>, Liam Boogaart <liam.boogaart@uleth.ca>
* @date 2022-04
*/

#ifndef CRAZYEIGHTS_H
#define CRAZYEIGHTS_H

#include "Game.h"
#include <string>

class CrazyEights : public Game {
 public:
  /**
  *@brief Crazy Eights Constructor
  **/
  CrazyEights();

  /**
  *@brief Crazy Eights Destructor
  **/
  ~CrazyEights();

  /**
  *@brief function to set up the game
  **/
  void startGame();

  /**
  *@brief function to set up the cards and decks
  **/
  void initDeck();

  /**
  *@brief function to allow the player to take their turn
  *@return true if the player has won
  **/
  bool playerTurn();

  /**
  *@brief function to allow the AI player to take their turn
  *@return true if the player has won
  **/
  bool aiTurn();

  /**
  *@brief function to show help text to the player
  **/
  void help();

  /**
  *@brief function to end the game when someone wins
  **/
  void endGame();

  /**
  *@brief function to reset the game after it ends
  **/
  void reset();

  /**
  *@brief function to change the suit of the active card when an eight is played
  **/
  void changeSuit();

  /**
  *@brief function for the AI to change the suit of the active card
  **/
  void aiChangeSuit();

  /**
  *@brief Refills the draw pile if it is empty
  */
  void refillDraw();

 private:
  Deck* drawDeck;
  Deck* playDeck;
  Deck* playerHand;
  Deck* aiPlayerHand;
  Card* activeCard;
};
#endif
