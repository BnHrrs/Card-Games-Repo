#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include <ctime>

using namespace std;

// Card class to represent individual cards
class Card {
private:
    string suit;
    string rank;
    int value;
public:
    Card(string s, string r, int v) : suit(s), rank(r), value(v) {}

    int getValue() const {
        return value;
    }

    void display() const {
        cout << rank << " of " << suit;
    }
};
//An extra comment! No way~
// //What a dumb comment
// Deck class to represent a deck of cards
class Deck {
private:
    vector<Card> cards;
public:
    Deck() {
        initialize();
    }

    void initialize() {
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
        int values[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
        for (const auto& suit : suits) {
            for (int j = 0; j < 13; ++j) {
                cards.push_back(Card(suit, ranks[j], values[j]));
            }
        }
        shuffle();
    }

    void shuffle() {
        srand(time(0));
        random_shuffle(cards.begin(), cards.end());
    }

    Card drawCard() {
        Card drawnCard = cards.back();
        cards.pop_back();
        return drawnCard;
    }

    bool isEmpty() const {
        return cards.empty();
    }
};

// Player class to represent a player
class Player {
protected:
    vector<Card> hand;
public:
    void addCard(const Card& card) {
        hand.push_back(card);
    }

    int calculateScore() const {
        int score = 0;
        int numAces = 0;
        for (const auto& card : hand) {
            score += card.getValue();
            if (card.getValue() == 11) {
                numAces++;
            }
        }
        while (score > 21 && numAces > 0) {
            score -= 10;
            numAces--;
        }
        return score;
    }

    void displayHand() const {
        for (const auto& card : hand) {
            card.display();
            cout << ", ";
        }
        cout << "\n";
    }

    bool isBusted() const {
        return calculateScore() > 21;
    }

    void clearHand() {
        hand.clear();
    }
};

// Dealer class representing the dealer
class Dealer : public Player {
public:
    void showFirstCard() const {
        cout << "Dealer's Hand: ";
        hand[0].display();
        cout << ", [Hidden Card]\n";
    }

    void displayHand() const {
        cout << "Dealer's Hand: ";
        for (size_t i = 0; i < hand.size(); ++i) {
            hand[i].display();
            if (i != hand.size() - 1)
                cout << ", ";
        }
        cout << "\n";
    }
};

// BlackJack class representing the game itself
class BlackJack {
public:
    Deck deck;
    Dealer dealer;
    Player player;
    void start() {
        cout << "Welcome to Blackjack!\n\n";

        player.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());
        player.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());

        cout << "Your Hand: ";
        player.displayHand();
        dealer.showFirstCard();

        while (true) {
            char choice;
            cout << "Do you want to hit (h) or stand (s)? ";
            cin >> choice;
            if (choice == 'h') {
                player.addCard(deck.drawCard());
                cout << "Your Hand: ";
                player.displayHand();
                if (player.isBusted()) {
                    cout << "Busted! You lose.\n";
                    return;
                }
            }
            else if (choice == 's') {
                break;
            }
            else {
                cout << "Invalid choice. Please enter 'h' or 's'.\n";
            }
        }

        cout << "\nDealer's Turn:\n";
        dealer.displayHand();
        while (dealer.calculateScore() < 17) {
            dealer.addCard(deck.drawCard());
            dealer.displayHand();
            if (dealer.isBusted()) {
                cout << "Dealer busted! You win.\n";
                return;
            }
        }

        int playerScore = player.calculateScore();
        int dealerScore = dealer.calculateScore();
        if (playerScore > dealerScore) {
            cout << "You win!\n";
        }
        else if (playerScore < dealerScore) {
            cout << "Dealer wins!\n";
        }
        else {
            cout << "It's a tie!\n";
        }
    }

    bool replay() {
        char choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        return choice == 'y';
    }
};

class HigherorLower {
public:
    Deck deck;
    Dealer dealer;
    Player player;
    void start() {
        cout << "Welcome to not blackjack!\n\n";




        
        while (true) {
            player.addCard(deck.drawCard());
            dealer.addCard(deck.drawCard());
            char choice;
            cout << "Player's Hand: ";
            player.displayHand();
            cout << "Do you think the next card will be higher (H) or lower (L)? ";
            cin >> choice;
            dealer.displayHand();
            int playerScore = player.calculateScore();
            int dealerScore = dealer.calculateScore();
            if ((char)tolower(choice) == 'l') {
                if (playerScore > dealerScore) {
                    cout << "victory" << endl;
                }
                if (playerScore < dealerScore) {
                    cout << "Failure" << endl;
                }
                else if (playerScore == dealerScore) {
                    cout << "draw???" << endl;
                }

            }
            if ((char)tolower(choice) == 'h') {
                if (playerScore > dealerScore) {
                    cout << "Failure" << endl;
                }
                if (playerScore < dealerScore) {
                    cout << "victory" << endl;
                }
                else if (playerScore==dealerScore){
                    cout << "draw???" << endl;
                }

            }
            player.clearHand();
            dealer.clearHand();
        }
    }
};
int main() {
    while (true) {
        char choice;
        cout << "What would you like to play?" << endl << "Black Jack (a)  or  Higher or Lower (b)" << endl;
        cin >> choice;
        if ((char)tolower(choice) == 'a') {
            BlackJack blackjack;
            BlackJack player;
            BlackJack dealer;
            
            do {
                blackjack.start();
                blackjack.player.clearHand();
                blackjack.dealer.clearHand();
            } while (blackjack.replay());
            break;
        }
        if ((char)tolower(choice) == 'b') {
            cout << "time reversed and this version lacks this option please pick black jack." << endl;
            HigherorLower higherorlower;
            HigherorLower player;
            HigherorLower dealer;
            higherorlower.start();
        }
        else
        {
            cout << "pick a or b those are your only options" << endl;
        }

    }
}
