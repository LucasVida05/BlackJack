#ifndef Probability_h
#define Probability_h

#include "Deck.h"
#include "Hand.h"

class Probability {
public:
    static double chanceOfPlayerBust(const Hand&, const Deck&);
    static double chancePlayerBeatsDealer(const Hand&, const Deck&);

};
#endif