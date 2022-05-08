/**
* @author Justin Alho <alhoj@uleth.ca>, Oluwaseeni Ajayi <oluwaseeni.ajayi@uleth.ca>
* @date 2022-04
*/

#ifndef UNO_H
#define UNO_H

#include "Game.h"
#include <string>

class Uno : public Game {
 public:
  /**
  *@brief Uno Constructor
  **/
  Uno();

  /**
  *@brief Uno Destructor
  **/
  ~Uno();

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
  *@brief function to change the colour of the active card when a wild is played
  **/
  void changeColour();

  /**
  *@brief function for the AI to change the colour of the active card
  **/
  void aiChangeColour();


  /**
  *@brief function to draw a certain number of cards
  *@param recipient the deck that will receive the cards
  *@param amount the number of cards to be drawn
  **/
  void drawCards(Deck* recipient, int amount);

  /**
  *@brief reverses the playing order
  **/
  void reverseOrder();

  /**
  *@brief function to add two cards to the AI hand when a draw Two is played
  **/
  void skip();

 /**
  *@brief function to add two cards to the AI hand when a draw Two is played
  **/
  void aiSkip();

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
