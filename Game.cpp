#include "Game.h"
#include <iostream>

Game::Game() : deck(), dealer(), player() {}

void Game::startRound() {
    deck.shuffle();
    player.resetHand();
    dealer = Dealer(); // Reset dealer hand
    std::cout << "Your money: $" << player.getMoney() << std::endl;
    double betAmount;
    std::cout << "Place your bet: " << std::flush;
    std::cin >> betAmount;
    player.placeBet(betAmount);
    dealer.dealInitial(deck, player);
    std::cout << "Your hand: ";
    player.getHand().display();
    std::cout << "Value: " << player.getHand().getValue() << std::endl;
    std::cout << "Dealer's up card: " << dealer.getHand().getCard(0).toString() << std::endl;
    playerTurn();
    if (!player.getHand().isBust()) {
        dealerTurn();
    }
    determineWinner();
    showProb();
}

void Game::playerTurn() {
    char action;
    while (true) {
        if (player.getHand().isBust()) break;
        std::cout << "\nHit (h), Stand (s)";
        if (player.canSplit()) std::cout << ", Split (p)";
        std::cout << "? " << std::flush;
        std::cin >> action;
        std::cin.ignore(10000, '\n'); // Clear input buffer
        if (action == 'h' || action == 'H') {
            std::cout << "You hit! Dealer gives you a card." << std::endl;
            player.hit(deck);
            std::cout << "Your hand: ";
            player.getHand().display();
            std::cout << "Value: " << player.getHand().getValue() << std::endl;
            if (player.getHand().isBust()) {
                std::cout << "BUST! You went over 21!" << std::endl;
                break;
            }
        } else if (action == 's' || action == 'S') {
            std::cout << "You stand with " << player.getHand().getValue() << std::endl;
            break;
        } else if ((action == 'p' || action == 'P') && player.canSplit()) {
            player.split(deck);
            std::cout << "You split! Cards separated." << std::endl;
            std::cout << "First hand: ";
            player.getHand().display();
            std::cout << "Value: " << player.getHand().getValue() << std::endl;
            std::cout << "Second hand: ";
            player.getSecondHand().display();
            std::cout << "Value: " << player.getSecondHand().getValue() << std::endl;
            // Play first hand
            while (true) {
                std::cout << "First hand: Hit (h) or Stand (s)? " << std::flush;
                std::cin >> action;
                std::cin.ignore(10000, '\n');
                if (action == 'h' || action == 'H') {
                    std::cout << "Dealer gives you a card." << std::endl;
                    player.getHand().addCard(deck.dealCard());
                    std::cout << "First hand: ";
                    player.getHand().display();
                    std::cout << "Value: " << player.getHand().getValue() << std::endl;
                    if (player.getHand().isBust()) break;
                } else break;
            }
            // Play second hand
            while (true) {
                std::cout << "Second hand: Hit (h) or Stand (s)? " << std::flush;
                std::cin >> action;
                std::cin.ignore(10000, '\n');
                if (action == 'h' || action == 'H') {
                    std::cout << "Dealer gives you a card." << std::endl;
                    player.getSecondHand().addCard(deck.dealCard());
                    std::cout << "Second hand: ";
                    player.getSecondHand().display();
                    std::cout << "Value: " << player.getSecondHand().getValue() << std::endl;
                    if (player.getSecondHand().isBust()) break;
                } else break;
            }
            break;
        }
    }
}

void Game::dealerTurn() {
    dealer.playTurn(deck);
    dealer.revealHiddenCard();
    std::cout << "Value: " << dealer.getHand().getValue() << std::endl;
}

void Game::determineWinner() {
    int dealerValue = dealer.getHand().getValue();
    bool dealerBust = dealer.getHand().isBust();
    // First hand
    int playerValue = player.getHand().getValue();
    bool playerBust = player.getHand().isBust();
    bool playerBlackjack = player.getHand().isBlackjack();
    double multiplier = 0.0;
    double earnings = 0.0;
    
    std::cout << "\n=== ROUND RESULTS ===" << std::endl;
    if (playerBust) {
        std::cout << "You bust! You lose." << std::endl;
        player.lose();
        earnings = -player.getBet();
        std::cout << "Lost: $" << player.getBet() << std::endl;
    } else if (playerBlackjack) {
        std::cout << "Blackjack! You win!" << std::endl;
        multiplier = 2.0;
        player.win(multiplier);
        earnings = player.getBet() * multiplier;
        std::cout << "Won: $" << earnings << std::endl;
    } else if (dealerBust) {
        std::cout << "Dealer busts! You win!" << std::endl;
        multiplier = 1.5; // Non-blackjack win pays 1.5x
        player.win(multiplier);
        earnings = player.getBet() * multiplier;
        std::cout << "Won: $" << earnings << std::endl;
    } else if (playerValue > dealerValue) {
        std::cout << "You win!" << std::endl;
        multiplier = 1.5; // Non-blackjack win pays 1.5x
        player.win(multiplier);
        earnings = player.getBet() * multiplier;
        std::cout << "Won: $" << earnings << std::endl;
    } else if (playerValue == dealerValue) {
        std::cout << "Push! Bet returned." << std::endl;
        player.push();
        earnings = 0.0;
    } else {
        std::cout << "Dealer wins!" << std::endl;
        player.lose();
        earnings = -player.getBet();
        std::cout << "Lost: $" << player.getBet() << std::endl;
    }
    if (player.getHasSplit()) {
        // Second hand
        int playerValue2 = player.getSecondHand().getValue();
        bool playerBust2 = player.getSecondHand().isBust();
        bool playerBlackjack2 = player.getSecondHand().isBlackjack();
        double multiplier2 = 0.0;
        double earnings2 = 0.0;
        
        std::cout << "\nSecond Hand:" << std::endl;
        if (playerBust2) {
            std::cout << "Second hand busts! You lose." << std::endl;
            earnings2 = -player.getBet();
            std::cout << "Lost: $" << player.getBet() << std::endl;
        } else if (playerBlackjack2) {
            std::cout << "Second hand Blackjack! You win!" << std::endl;
            multiplier2 = 2.0;
            player.win(multiplier2);
            earnings2 = player.getBet() * multiplier2;
            std::cout << "Won: $" << earnings2 << std::endl;
        } else if (dealerBust) {
            std::cout << "Dealer busts! Second hand wins!" << std::endl;
            multiplier2 = 1.5; // Non-blackjack win pays 1.5x
            player.win(multiplier2);
            earnings2 = player.getBet() * multiplier2;
            std::cout << "Won: $" << earnings2 << std::endl;
        } else if (playerValue2 > dealerValue) {
            std::cout << "Second hand wins!" << std::endl;
            multiplier2 = 1.5; // Non-blackjack win pays 1.5x
            player.win(multiplier2);
            earnings2 = player.getBet() * multiplier2;
            std::cout << "Won: $" << earnings2 << std::endl;
        } else if (playerValue2 == dealerValue) {
            std::cout << "Second hand push! Bet returned." << std::endl;
            player.push();
            earnings2 = 0.0;
        } else {
            std::cout << "Dealer wins second hand!" << std::endl;
            earnings2 = -player.getBet();
            std::cout << "Lost: $" << player.getBet() << std::endl;
        }
        std::cout << "\nTotal earnings this round: $" << (earnings + earnings2) << std::endl;
    }
    std::cout << "\n==================" << std::endl;
    std::cout << "Your money: $" << player.getMoney() << std::endl;
}

void Game::showProb() {
    double bustProb = Probability::chanceOfPlayerBust(player.getHand(), deck);
    double winProb = Probability::chancePlayerBeatsDealer(player.getHand(), deck);
    std::cout << "Chance of bust: " << bustProb * 100 << "%" << std::endl;
    std::cout << "Chance to beat dealer: " << winProb * 100 << "%" << std::endl;
}

double Game::getMoney() const {
    return player.getMoney();
}
