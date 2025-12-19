#ifndef Deck_h
#define Deck_h

#include <vector>
#include "Card.h"

class Deck {
private:
    std::vector<Card> cards;
    int currentIndex;

public:
    Deck();
    void shuffle();
    Card dealCard();
    int cardsleft() const;
};
#endif 