#include "Player.h"
#include <iostream>

Player::Player(double initialMoney) : money(initialMoney), bet(0.0), hasSplit(false) {}

void Player::placeBet(double amount) {
    if (amount > 0 && amount <= money) {
        bet = amount;
        money -= amount;
    }
}

void Player::hit(Deck& deck) {
    hand.addCard(deck.dealCard());
}

void Player::stand() {
    // Do nothing, just stand
}

void Player::resetHand() {
    hand = Hand();
    secondHand = Hand();
    hasSplit = false;
    bet = 0.0;
}

Hand& Player::getHand() {
    return hand;
}

bool Player::canSplit() const {
    return !hasSplit && hand.canSplit() && bet * 2 <= money;
}

void Player::split(Deck& deck) {
    if (!canSplit()) return;
    // Move second card to secondHand
    Card secondCard = hand.removeCard(1);
    secondHand.addCard(secondCard);
    // Deal new cards
    hand.addCard(deck.dealCard());
    secondHand.addCard(deck.dealCard());
    hasSplit = true;
    // Deduct additional bet
    money -= bet;
}

Hand& Player::getSecondHand() {
    return secondHand;
}

bool Player::getHasSplit() const {
    return hasSplit;
}

void Player::win(double multiplier) {
    money += bet * multiplier;
    if (hasSplit) money += bet * multiplier; // Assuming same bet for split
}

void Player::lose() {
    // Money already deducted
}

void Player::push() {
    money += bet;
    if (hasSplit) money += bet;
}

double Player::getMoney() const {
    return money;
}

double Player::getBet() const {
    return bet;
}