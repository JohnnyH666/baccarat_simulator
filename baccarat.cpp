/*
Author: Johnny
Date: 22 Feburary 2025
Readme: To complie, please run "g++ -std=c++20 -Wall -o baccarat *.cpp" to include all the head and cpp files
*/

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <random>
#include <algorithm>
#include "Card.h"

// Function to initialize and shuffle the shoe of 8 decks
std::vector<Card> initializeShoe() {
  std::vector<Card> shoe;
  std::array<std::string, 4> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
  // Loop through 8 decks
  for (int deck = 0; deck < 8; ++deck) {
    // Loop through each suits
    for (const auto &suit : suits) {
      // Loop through 13 card in a suit
      for (int value = 1; value <= 13; ++value) {
        shoe.push_back({value, suit});
      }
    }
  }
  // Create random number generator and shuffle shoe
  std::random_device random_seed;
  std::mt19937 rng(random_seed());
  std::shuffle(shoe.begin(), shoe.end(), rng);
  return shoe;
}

// Function to simulate drawing a card from the shoe
Card drawCard(std::vector<Card> &shoe) {
  // Draw and the remove the last card for less complexity to manage array
  Card card = shoe.back();
  shoe.pop_back();
  return card;
}

// Function to calculate the Baccarat value of a hand
int calculateHandValue(const std::vector<Card> &hand) {
  int total = 0;
  for (const auto &card : hand) {
    int cardValue = card.value;
    // 10, J, Q, K are worth 0
    if (cardValue >= 10) {
      cardValue = 0;
    }
    total += cardValue;
  }
  // Only the last digit matters
  return total % 10;
}

int main() {
  // Initialize and shuffle the shoe
  std::vector<Card> shoe = initializeShoe();

  // Initialize an array to record Player and Banker hands
  std::vector<Card> playerHand;
  std::vector<Card> bankerHand;

  // Deal initial two cards to Player and Banker base on rules，Player first then alternately
  playerHand.push_back(drawCard(shoe));
  bankerHand.push_back(drawCard(shoe));
  playerHand.push_back(drawCard(shoe));
  bankerHand.push_back(drawCard(shoe));

  // Calculate initial hand values
  int playerValue = calculateHandValue(playerHand);
  int bankerValue = calculateHandValue(bankerHand);

  // If neither the player nor the banker is dealt a total of 8 or 9 in the first two cards (natural), then consider player's rule first
  if (playerValue < 8 && bankerValue < 8)
  {
    // Check if a third card is needed for Player, no draw for 6 or 7, draw for 5 or less
    bool playerDrawsThirdCard = (playerValue <= 5);

    // Situation to draw third card for Player
    if (playerDrawsThirdCard) {
      playerHand.push_back(drawCard(shoe));
      playerValue = calculateHandValue(playerHand);
    }

    // Checks if a third card is needed for Banker
    bool bankerDrawsThirdCard = false;
    if (!playerDrawsThirdCard) {
      // The banker draws a third card with hands value less than 5, stand for 6 or 7 or more
      if (bankerValue <= 5) {
        bankerDrawsThirdCard = true;
      }
    }
    else {
      int playerThirdCardValue = playerHand[2].value;
      if (playerThirdCardValue >= 10) {
        playerThirdCardValue = 0;
      }
      // If the banker total is 2 or less, they draw a third card regardless of what the player's third card is.
      if (bankerValue <= 2) {
        bankerDrawsThirdCard = true;
      }
      // If the banker total is 3, they draw a third card unless the player's third card is an 8.
      else if (bankerValue == 3 && playerThirdCardValue != 8) {
        bankerDrawsThirdCard = true;
      }
      // If the banker total is 4, they draw a third card if the player's third card is 2, 3, 4, 5, 6, or 7.
      else if (bankerValue == 4 && (playerThirdCardValue >= 2 && playerThirdCardValue <= 7)) {
        bankerDrawsThirdCard = true;
      }
      // If the banker total is 5, they draw a third card if the player's third card is 4, 5, 6, or 7.
      else if (bankerValue == 5 && (playerThirdCardValue >= 4 && playerThirdCardValue <= 7)) {
        bankerDrawsThirdCard = true;
      }
      // If the banker total is 6, they draw a third card if the player's third card is a 6 or 7.
      else if (bankerValue == 6 && (playerThirdCardValue == 6 || playerThirdCardValue == 7)) {
        bankerDrawsThirdCard = true;
      }
    }

    // Draw third card for Banker if necessary
    if (bankerDrawsThirdCard) {
      bankerHand.push_back(drawCard(shoe));
      bankerValue = calculateHandValue(bankerHand);
    }
  }

  // Determine the outcome and print the results
  std::string outcome;
  if (playerValue > bankerValue) {
    outcome = "PLAYER";
  }
  else if (bankerValue > playerValue) {
    outcome = "BANKER";
  }
  else {
    outcome = "TIE";
  }

  std::cout << "PHand - BHand - Outcome" << std::endl;

  std::cout << cardToString(playerHand[0].value) << "," << cardToString(playerHand[1].value);
  if (playerHand.size() > 2) {
    std::cout << "," << cardToString(playerHand[2].value);
  }
  std::cout << " - " << cardToString(bankerHand[0].value) << "," << cardToString(bankerHand[1].value);
  if (bankerHand.size() > 2) {
    std::cout << "," << cardToString(bankerHand[2].value);
  }
  std::cout << " - " << outcome << std::endl;

  return 0;
}