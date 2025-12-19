#include "Probability.h"

double Probability::chanceOfPlayerBust(const Hand& hand, const Deck& deck) {
    int currentValue = hand.getValue();
    if (currentValue > 21) return 1.0;
    if (currentValue == 21) return 0.0;
    // Simple approximation: assume uniform distribution
    int remainingCards = deck.cardsleft();
    if (remainingCards == 0) return 0.0;
    int badCards = 0;
    for (int r = 1; r <= 13; ++r) {
        Card temp(r, Card::CLUBS);
        if (currentValue + temp.getValue() > 21) badCards++;
    }
    return static_cast<double>(badCards) / 13.0; // Approximate
}

double Probability::chancePlayerBeatsDealer(const Hand& hand, const Deck& deck) {
    // Simplified: assume dealer stands on 17, etc.
    // For now, return 0.5
    return 0.5;
}
