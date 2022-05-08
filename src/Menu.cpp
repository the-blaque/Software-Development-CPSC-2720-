/**
* @author Justin Alho <alhoj@uleth.ca>
* @date 2022-04
*/

#include <iostream>
#include <string>
#include "Menu.h"
#include "Game.h"
#include "Uno.h"
#include "CrazyEights.h"
#include "Exceptions.h"

Menu::Menu():chosenGame(nullptr) {}

Menu::~Menu() {
  delete chosenGame;
  chosenGame = nullptr;
}

void Menu::chooseGame() {
  std::cout << "Enter 1 for Crazy Eights, and 2 for Uno.\n";
  std::string input;
  bool gamePicked = false;
  int gameChoice = 0;
  while (!gamePicked) {
    std::getline(std::cin, input);
    gameChoice = std::stoi(input);
    switch (gameChoice) {
      case 1: chosenGame = new CrazyEights();
      gamePicked = true;
      break;
      case 2: chosenGame = new Uno();
      gamePicked = true;
      break;
      default: break;
    }
  }
  if (chosenGame != nullptr) {
    createGame(chosenGame);
  }
}

void Menu::createGame(Game* g) {
  if (g == nullptr) {
    throw pointer_cannot_be_null("Game pointer cannot be null.");
  }
  g->startGame();
}
