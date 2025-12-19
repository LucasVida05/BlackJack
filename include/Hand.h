#ifndef Hand_h
#define Hand_h

#include <vector>
#include <string>
#include <cstddef>
#include "Card.h"

class Hand {
private:
    std::vector<Card> cards;

public: 
    void addCard(const Card &card);

    int getValue() const;
    bool isBlackjack() const;
    bool isBust() const;
    bool isSoft() const;
    bool canSplit() const;
    Card removeCard(size_t index);
    const Card& getCard(size_t index) const;
    void display () const;

    std::string toString() const;
};
#endif