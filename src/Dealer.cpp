#include "Dealer.h"
#include "Deck.h"
#include "Player.h"
#include <iostream>

void Dealer::dealInitial(Deck& deck, Player& player) {
    std::cout << "\n--- Dealing Initial Cards ---" << std::endl;
    
    std::cout << "Dealer gives player: ";
    player.hit(deck);
    std::cout << player.getHand().getCard(0).toString() << std::endl;
    
    std::cout << "Dealer deals to themselves: ";
    hand.addCard(deck.dealCard());
    std::cout << hand.getCard(0).toString() << " (face up)" << std::endl;
    
    std::cout << "Dealer gives player: ";
    player.hit(deck);
    std::cout << player.getHand().getCard(1).toString() << std::endl;
    
    std::cout << "Dealer deals hidden card to themselves" << std::endl;
    hand.addCard(deck.dealCard());
}

void Dealer::playTurn(Deck& deck) {
    std::cout << "\n--- Dealer's Turn ---" << std::endl;
    while (hand.getValue() < 17) {
        std::cout << "Dealer hits: ";
        hand.addCard(deck.dealCard());
        std::cout << hand.getCard(hand.getValue() - 1).toString() << " (Total: " << hand.getValue() << ")" << std::endl;
    }
    if (hand.getValue() >= 17) {
        std::cout << "Dealer stands with " << hand.getValue() << std::endl;
    }
}

void Dealer::revealHiddenCard() {
    // In text, just display
    std::cout << "Dealer's hand: ";
    hand.display();
}

Hand& Dealer::getHand() {
    return hand;
}
