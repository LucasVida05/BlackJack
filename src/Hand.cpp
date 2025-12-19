#include "Hand.h"
#include <iostream>

void Hand::addCard(const Card &card) {
    cards.push_back(card);
}

int Hand::getValue() const {
    int value = 0;
    int aces = 0;
    for (const auto& card : cards) {
        value += card.getValue();
        if (card.isAce()) aces++;
    }
    while (value > 21 && aces > 0) {
        value -= 10;
        aces--;
    }
    return value;
}

bool Hand::isBlackjack() const {
    return cards.size() == 2 && getValue() == 21;
}

bool Hand::isBust() const {
    return getValue() > 21;
}

bool Hand::isSoft() const {
    int value = 0;
    int aces = 0;
    for (const auto& card : cards) {
        value += card.getValue();
        if (card.isAce()) aces++;
    }
    return aces > 0 && value <= 21;
}

bool Hand::canSplit() const {
    return cards.size() == 2 && cards[0].getValue() == cards[1].getValue();
}

Card Hand::removeCard(size_t index) {
    if (index >= cards.size()) return Card(0, Card::CLUBS);
    Card c = cards[index];
    cards.erase(cards.begin() + index);
    return c;
}

const Card& Hand::getCard(size_t index) const {
    static Card dummy(0, Card::CLUBS);
    if (index >= cards.size()) return dummy;
    return cards[index];
}

void Hand::display() const {
    for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << cards[i].toString();
        if (i < cards.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

std::string Hand::toString() const {
    std::string str;
    for (size_t i = 0; i < cards.size(); ++i) {
        str += cards[i].toString();
        if (i < cards.size() - 1) str += ", ";
    }
    return str;
}
