/**
* @author Justin Alho <alhoj@uleth.ca>, Liam Boogaart <liam.boogaart@uleth.ca>
* @date 2022-04
*/

#include "Game.h"
#include "Card.h"
#include "CrazyEights.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

CrazyEights::CrazyEights(): activeCard(nullptr) {}

CrazyEights::~CrazyEights() {
  delete drawDeck;
  delete playDeck;
  delete playerHand;
  delete aiPlayerHand;
  delete activeCard;
}

void CrazyEights::startGame() {
  std::cout << "Starting Crazy Eights.\n";

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

void CrazyEights::initDeck() {
  drawDeck = new Deck();
  playDeck = new Deck();
  playerHand = new Deck();
  aiPlayerHand = new Deck();

  //Create the deck of cards
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      Card* x = new Card(static_cast<Card::Rank>(i),
      static_cast<Card::Suit>(j));
      drawDeck->insertCard(x);
    }
  }
  drawDeck->shuffle();
  //Debugging
  //std::cout << *drawDeck << std::endl;
  for (int i = 0; i < 5; i++) {
    drawDeck->moveCard(playerHand, drawDeck->draw());
    drawDeck->moveCard(aiPlayerHand, drawDeck->draw());
  }
  while (drawDeck->draw()->getRank() == Card::Eight) {
    drawDeck->shuffle();
    std::cout << *drawDeck << std::endl;
  }
  drawDeck->moveCard(playDeck, drawDeck->draw());
}

bool CrazyEights::playerTurn() {
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
  //Check if the Player has won
  if (playerHand->isEmpty()) {
    std::cout << "You have played all the cards in your hand." << std::endl;
    std::cout << "You have won the game!" << std::endl;
    return true;
  }
  //Check if it was an eight
  if (valid[play-1]->getRank() == Card::Eight) changeSuit();
  return false;
}

bool CrazyEights::aiTurn() {
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
  //Check if it was an eight
  if (valid[0]->getRank() == Card::Eight) aiChangeSuit();
  return false;
}

void CrazyEights::help() {
  //Stolen straight from the small project -- Liam
  //Location of the help file
  const std::string FILE_LOCATION = "include/helpCrazyEights.txt";
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

void CrazyEights::endGame() {
  std::cout << "The game is over." << std::endl;
  std::cout << "Press 1 to play again, or 2 to quit:" << std::endl;
  int playAgain = getInput(1, 2);
  if (playAgain == 1) {
    reset();
  }
}

void CrazyEights::reset() {
  startGame();
}

void CrazyEights::changeSuit() {
  std::cout << "You played an 8, please select which suit you would like ";
  std::cout << "to set as the current suit." << std::endl;
  std::cout << "1. Hearts" << std::endl << "2. Spades" << std::endl;
  std::cout << "3. Clubs" << std::endl << "4. Diamonds" << std::endl;
  int input = getInput(1, 4);
  switch (input) {
    case 1:
      activeCard = new Card(Card::Eight, Card::Hearts);
      std::cout << "You set the suit to Hearts." << std::endl;
      break;
    case 2:
      activeCard = new Card(Card::Eight, Card::Spades);
      std::cout << "You set the suit to Spades." << std::endl;
      break;
    case 3:
      activeCard = new Card(Card::Eight, Card::Clubs);
      std::cout << "You set the suit to Clubs." << std::endl;
      break;
    case 4:
      activeCard = new Card(Card::Eight, Card::Diamonds);
      std::cout << "You set the suit to Diamonds." << std::endl;
      break;
  }
}

void CrazyEights::aiChangeSuit() {
  Card* card = aiPlayerHand->draw();
  std::cout << "The AI set the suit to ";
  switch (card->getSuit()) {
    case Card::Hearts:
      std::cout << "Hearts.\n";
      break;
    case Card::Spades:
      std::cout << "Spades.\n";
      break;
    case Card::Clubs:
      std::cout << "Clubs.\n";
      break;
    case Card::Diamonds:
      std::cout << "Diamonds.\n";
      break;
    default:
      std::cout << "Uhhh, something broke :(";
      break;
  }
  activeCard = new Card(Card::Eight, card->getSuit());
}

void CrazyEights::refillDraw() {
  if (drawDeck->isEmpty()) {
    //Move every card but the top from the discard to the draw pile
    while (playDeck->getSize() > 1) {
      playDeck->moveCard(drawDeck, playDeck->draw());
    }
    drawDeck->shuffle();
  }
}
