/*
Author: Johnny Huang
Date: 22 Feburary 2025
*/

#include "Card.h"
#include <string>

// Implement function definition for cardToString
std::string cardToString(int value) {
  // 1 = "Ace"
  if (value == 1) {
    return "A";
  }
  if (value >= 2 && value <= 9) {
    return std::to_string(value);
  }
  // 10 = "T"
  if (value == 10) {
    return "T";
  }
  // 11 = "J"
  if (value == 11) {
    return "J";
  }
  // 12 = "Q"
  if (value == 12) {
    return "Q";
  }
  // 13 = "K"
  if (value == 13) {
    return "K";
  }
  return "Out of Scope";
}