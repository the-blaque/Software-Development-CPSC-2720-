/**
* @author Justin Alho <alhoj@uleth.ca>
* @date 2022-04
*/

#include "Game.h"
#include <string>
#include <iostream>

Game::Game() {}

Game::~Game() {}

int Game::getInput(int min, int max) {
  bool validInput = false;
  std::string input;
  int output;
  while (!validInput) {
    validInput = true;
    std::cin >> input;
    for (char c : input) {
      if (validInput) {
        validInput = std::isdigit(c);
      } else {
        if (convertToLowercase(input) == "help") help();
        break;
      }
    }
    if (validInput) {
      output = stoi(input);
      if (output < min || output > max) validInput = false;
    }
    if (!validInput) std::cout << "Unrecognized input (or help). Try again.\n";
  }
  return output;
}

std::string Game::convertToLowercase(std::string input) {
  //Iterate over every character
  for (int i = 0; i < input.length(); i++) {
    //Convert to lowercase
    input[i] = std::tolower(input[i]);
  }
  return input;
}
