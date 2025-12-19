#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>

Deck::Deck() : currentIndex(0) {
    for (int suit = 0; suit < 4; ++suit) {
        for (int rank = 1; rank <= 13; ++rank) {
            cards.push_back(Card(rank, static_cast<Card::Suit>(suit)));
        }
    }
    shuffle();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
    currentIndex = 0;
}

Card Deck::dealCard() {
    if (currentIndex < cards.size()) {
        return cards[currentIndex++];
    }
    // If deck is empty, reshuffle? But for simplicity, assume not.
    return Card(0, Card::CLUBS); // Error card
}

int Deck::cardsleft() const {
    return cards.size() - currentIndex;
}
