#ifndef Dealer_h
#define Dealer_h

#include "Hand.h"
#include "Deck.h"

class Player;

class Dealer {
private:
    Hand hand;

public: 
    void dealInitial(Deck& deck, Player& player);
    void playTurn(Deck& deck);
    void revealHiddenCard();
    Hand& getHand();
    

    

};
#endif
