/**
* @author Justin Alho <alhoj@uleth.ca>, Liam Boogaart <liam.boogaart@uleth.ca>
* @author Oluwaseeni Ajayi <oluwaseeni.ajayi@uleth.ca>
* @date 2022-04
*/

#include "Game.h"
#include "Card.h"
#include "Uno.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

Uno::Uno(): activeCard(nullptr) {}

Uno::~Uno() {
  delete drawDeck;
  delete playDeck;
  delete playerHand;
  delete aiPlayerHand;
  delete activeCard;
}

void Uno::startGame() {
  std::cout << "Starting Uno.\n";

  bool gameOver = false;
  initDeck();
  std::cout << "\n";
  while (!gameOver) {
    gameOver = playerTurn();
    //So I can scan the wall of text easier -- Liam
    std::cout << "\n";
    //No AI turn if the player won
    if (!gameOver) gameOver = aiTurn();
    std::cout << "\n";
  }
  endGame();
}

void Uno::initDeck() {
  drawDeck = new Deck();
  playDeck = new Deck();
  playerHand = new Deck();
  aiPlayerHand = new Deck();

  //Create the deck of cards
  for (int i = 4; i < 8; i++) {
    for (int j = 1; j < 9; j++) {
      Card* x = new Card(static_cast<Card::Rank>(j),
      static_cast<Card::Suit>(i));
      drawDeck->insertCard(x);
    }
    for (int j = 1; j < 9; j++) {
      Card* x = new Card(static_cast<Card::Rank>(j),
      static_cast<Card::Suit>(i));
      drawDeck->insertCard(x);
    }
    for (int j = 14; j < 19; j++) {
      Card* x = new Card(static_cast<Card::Rank>(j),
      static_cast<Card::Suit>(i));
      drawDeck->insertCard(x);
    }
    for (int j = 15; j < 19; j++) {
      Card* x = new Card(static_cast<Card::Rank>(j),
      static_cast<Card::Suit>(i));
      drawDeck->insertCard(x);
    }
  }
  for (int i = 0; i < 8; i++) {
    if (i < 4) {
      Card* x = new Card(Card::None, Card::Wild);
      drawDeck->insertCard(x);
    } else {
      Card* x = new Card(Card::DrawFour, Card::Wild);
      drawDeck->insertCard(x);
    }
  }
  //Debugging
  //std::cout << *drawDeck << std::endl;
  drawDeck->shuffle();
  for (int i = 0; i < 7; i++) {
    drawDeck->moveCard(playerHand, drawDeck->draw());
    drawDeck->moveCard(aiPlayerHand, drawDeck->draw());
  }
  while (drawDeck->draw()->getSuit() == Card::Wild) {
    drawDeck->shuffle();
    //std::cout << *drawDeck << std:endl;
  }
  drawDeck->moveCard(playDeck, drawDeck->draw());
}

bool Uno::playerTurn() {
  //Debugging
  //std::cout << "Player turn.\n" << *playerHand;
  std::vector<Card*> valid;
  while (true) {
    if (activeCard != nullptr) {
      valid = playerHand->findValid(activeCard);
    } else {
      valid = playerHand->findValid(playDeck->returnTop());
    }
    if (valid.size() == 0) {
      std::cout << "You have no valid cards to play, drawing another...\n";
      drawDeck->moveCard(playerHand, drawDeck->draw());
      //Check if draw pile is empty
      refillDraw();
    } else {
      break;
    }
  }
  std::cout << "You currently have these cards:\n" << *playerHand;
  //Get player to select card here
  std::cout << "The current top card is: ";
  if (activeCard != nullptr) {
    std::cout << *activeCard;
  } else {
    std::cout << *playDeck->returnTop();
  }
  std::cout << std::endl;
  std::cout << "The AI has " << aiPlayerHand->getSize() << " cards.\n";
  std::cout << "Select which card to play:" << std::endl;
  for (int i = 0; i < valid.size(); i++) {
    std::cout << i+1 << " -- " << *valid[i] << std::endl;
  }
  int play = getInput(1, valid.size());
  playerHand->moveCard(playDeck, valid[play-1]);
  if (activeCard != nullptr) {
    delete activeCard;
    activeCard = nullptr;
  }
  std::cout << "You played the " << *valid[play-1] << std::endl;
  if (playerHand->isEmpty()) {
    std::cout << "You have played all the cards in your hand." << std::endl;
    std::cout << "You have won the game!" << std::endl;
    return true;
  }
  //Check if it was a wild card
  if (valid[play-1]->getSuit() == Card::Wild) changeColour();
  //Check if it was a reverse card
  if (valid[play-1]->getRank() == Card::Reverse) reverseOrder();
  //Check if it was a Draw 2
  if (valid[play-1]->getRank() == Card::DrawTwo) {
    std::cout << "The AI will pick up two cards." << std::endl;
    drawCards(aiPlayerHand, 2);
    skip();
  }
  //Check if it was a Draw 4
  if (valid[play-1]->getRank() == Card::DrawFour) {
    std::cout << "The AI will pick up four cards." << std::endl;
    drawCards(aiPlayerHand, 4);
    skip();
  }
  //Check if it was a Skip
  if (valid[play-1]->getRank() == Card::Skip) skip();
  //Check if the Player has won
  return false;
}

bool Uno::aiTurn() {
  //Debugging
  //std::cout << "AI turn.\n" << *aiPlayerHand;
  std::vector<Card*> valid;
  while (true) {
    if (activeCard != nullptr) {
      valid = aiPlayerHand->findValid(activeCard);
    } else {
      valid = aiPlayerHand->findValid(playDeck->returnTop());
    }
    if (valid.size() == 0) {
      std::cout << "The AI had to draw a card." << std::endl;
      drawDeck->moveCard(aiPlayerHand, drawDeck->draw());
      //Check if draw pile is empty
      refillDraw();
    } else {
      break;
    }
  }
  //Debugging
  //std::cout << "AI After possible draws.\n" << *aiPlayerHand;
  //Play first available card
  aiPlayerHand->moveCard(playDeck, valid[0]);
  if (activeCard != nullptr) {
    delete activeCard;
    activeCard = nullptr;
  }
  std::cout << "The AI played the " << *valid[0] << std::endl;
  //Check if the AI has won
  if (aiPlayerHand->isEmpty()) {
    std::cout << "The AI has played all the cards in their hand." << std::endl;
    std::cout << "The AI has won the game!" << std::endl;
    return true;
  }
  //Check if it was a wild card
  if (valid[0]->getSuit() == Card::Wild) aiChangeColour();
  //Check if it was a Reverse card
  if (valid[0]->getRank() == Card::Reverse) reverseOrder();
  //Check if it was a Draw 2
  if (valid[0]->getRank() == Card::DrawTwo) {
    std::cout << "You pick up two cards." << std::endl;
    drawCards(playerHand, 2);
    aiSkip();
  }
  //Check if it was a Draw 4
  if (valid[0]->getRank() == Card::DrawFour) {
    std::cout << "You pick up four cards." << std::endl;
    drawCards(playerHand, 4);
    aiSkip();
  }
  //Check if it was a Skip
  if (valid[0]->getRank() == Card::Skip) aiSkip();
  return false;
}

void Uno::help() {
  //Stolen straight from the small project -- Liam
  //Location of the help file
  const std::string FILE_LOCATION = "include/helpUno.txt";
  std::ifstream helpFile;
  helpFile.open(FILE_LOCATION);
  //If we can't open the help file, display an error and exit
  if (helpFile.fail()) {
    std::cout << "Couldn't open the help file, sorry." << std::endl;
    return;
  }
  //Otherwise, we should print the help file to the user
  std::string currentline;
  getline(helpFile, currentline);
  do {
    std::cout << currentline << std::endl;
    getline(helpFile, currentline);
  } while (!helpFile.eof());
  //Close the file now that we're done with it
  helpFile.close();
}

void Uno::endGame() {
  std::cout << "The game is over." << std::endl;
  std::cout << "Press 1 to play again, or 2 to quit:" << std::endl;
  int playAgain = getInput(1, 2);
  if (playAgain == 1) {
    reset();
  }
}

void Uno::reset() {
  startGame();
}

void Uno::changeColour() {
  std::cout << "You played a wild, please select which colour you would like ";
  std::cout << "to set as the current colour." << std::endl;
  std::cout << "1. Red" << std::endl << "2. Blue" << std::endl;
  std::cout << "3. Green" << std::endl << "4. Yellow" << std::endl;
  int input = getInput(1, 4);
  switch (input) {
    case 1:
      activeCard = new Card(Card::None, Card::Red);
      std::cout << "You set the colour to Red." << std::endl;
      break;
    case 2:
      activeCard = new Card(Card::None, Card::Green);
      std::cout << "You set the colour to Green." << std::endl;
      break;
    case 3:
      activeCard = new Card(Card::None, Card::Blue);
      std::cout << "You set the colour to Blue." << std::endl;
      break;
    case 4:
      activeCard = new Card(Card::None, Card::Yellow);
      std::cout << "You set the colour to Yellow." << std::endl;
      break;
  }
}

void Uno::aiChangeColour() {
  Card* card = aiPlayerHand->draw();
  std::cout << "The AI set the colour to ";
  switch (card->getSuit()) {
    case Card::Red:
      std::cout << "Red.\n";
      break;
    case Card::Green:
      std::cout << "Green.\n";
      break;
    case Card::Blue:
      std::cout << "Blue.\n";
      break;
    case Card::Yellow:
      std::cout << "Yellow.\n";
      break;
    default:
      std::cout << "Uhhh, something broke :(\n";
      break;
  }
  activeCard = new Card(Card::None, card->getSuit());
}

void Uno::reverseOrder() {
  std::cout << "The playing order has been reversed." << std::endl;
}

void Uno::skip() {
  std::cout << "The AI will now miss a turn." << std::endl;
  if (playerTurn()) endGame();
}

void Uno::aiSkip() {
  std::cout << "You will now miss a turn.\n" << std::endl;
  if (aiTurn()) endGame();
}

void Uno::drawCards(Deck* recipient, int amount) {
  for (int i = 0; i < amount; i++) {
    drawDeck->moveCard(recipient, drawDeck->draw());
    refillDraw();
  }
}

void Uno::refillDraw() {
  if (drawDeck->isEmpty()) {
    //Move every card but the top from the discard to the draw pile
    while (playDeck->getSize() > 1) {
      playDeck->moveCard(drawDeck, playDeck->draw());
    }
    drawDeck->shuffle();
  }
}
