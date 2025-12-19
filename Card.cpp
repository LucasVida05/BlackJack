#include "Card.h"

Card::Card(int r, Suit s) : rank(r), suit(s) {
    
}

int Card::getValue() const {
    if (rank == 1) return 11; // Ace
    if (rank >= 10) return 10; // Face cards
    return rank;
}

Card::Suit Card::getSuit() const {
    return suit;
}

bool Card::isAce() const {
    return rank == 1;
}

std::string Card::toString() const {
    // ANSI color codes (red for hearts/diamonds, bright white for clubs/spades)
    const std::string RED = "\033[31m";
    const std::string BLACK = "\033[37m";
    const std::string RESET = "\033[0m";

    std::string rankStr;
    switch (rank) {
        case 1: rankStr = "A"; break;
        case 11: rankStr = "J"; break;
        case 12: rankStr = "Q"; break;
        case 13: rankStr = "K"; break;
        default: rankStr = std::to_string(rank); break;
    }

    std::string suitSymbol;
    std::string color;
    switch (suit) {
        case CLUBS:
            suitSymbol = "♣";
            color = BLACK;
            break;
        case DIAMONDS:
            suitSymbol = "♦";
            color = RED;
            break;
        case HEARTS:
            suitSymbol = "♥";
            color = RED;
            break;
        case SPADES:
            suitSymbol = "♠";
            color = BLACK;
            break;
    }

    return "[" + color + rankStr + suitSymbol + RESET + "]";
}