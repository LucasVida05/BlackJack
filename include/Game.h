#ifndef Game_h
#define Game_h

#include "Deck.h"
#include "Dealer.h"
#include "Player.h"
#include "Probability.h"

class Game{
private:
    Deck deck;
    Dealer dealer;
    Player player;
public:
    Game();
    void startRound();
    void playerTurn();
    void dealerTurn();
    void determineWinner();
    void showProb();
    double getMoney() const;
};
#endif