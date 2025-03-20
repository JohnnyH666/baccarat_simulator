/*
Author: Johnny Huang
Date: 22 Feburary 2025
*/

#ifndef CARD_H
#define CARD_H

#include <string>

// Create a Card structure for a playing card
struct Card {
  int value;
  std::string suit;
};

// Function to convert a card value to its actual card representation and return in string
std::string cardToString(int value);

#endif