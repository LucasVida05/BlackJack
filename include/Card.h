#ifndef Card_h
#define Card_h

#include <cstddef>
#include <string>

class Card {
public:
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

private:
    int rank; //1 = Ace, 11 = Jack, 12 = Queen, 13 = King
    Suit suit;

public:
    Card(int r, Suit s);

    int getValue() const;
    Suit getSuit() const;
    bool isAce() const; 

    std::string toString() const;
};
#endif 