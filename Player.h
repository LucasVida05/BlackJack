#ifndef Player_h
#define Player_h

#include "Hand.h"
#include "Deck.h"


class Player {
private:
    double money;
    double bet;
    Hand hand;
    Hand secondHand;
    bool hasSplit;

public:
    Player(double initialMoney = 100.0);
    void placeBet(double amount);
    void hit(Deck& deck);
    void stand();
    void resetHand();
    Hand& getHand();
    bool canSplit() const;
    void split(Deck& deck);
    Hand& getSecondHand();
    bool getHasSplit() const;
    void win(double multiplier);
    void lose();
    void push();
    double getMoney() const;
    double getBet() const;
};
#endif