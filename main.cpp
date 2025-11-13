#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class Card {
    public:
        int value;
        int suit;
        Card(int x, int y) {
            value = x;
            suit = y;
        }
        //gives you the name of the card
        string name() {
            string name;
            if (value == 1) {
                name = "Ace";
            }else if (value > 1 && value < 11) {
                name = to_string(value);
            }else if (value == 11) {
                name = "Jack";
            }else if (value == 12) {
                name = "Queen";
            }else if (value == 13) {
                name = "King";
            }

            name += " of ";

            switch (suit) {
                case 1:
                    name += "Clubs";
                    break;
                case 2:
                    name += "Diamonds";
                    break;
                case 3:
                    name += "Hearts";
                    break;
                case 4:
                    name += "Spades";
                    break;
            }
            return name;
        }
};

class GameInfo {
    public:

};

class Player {
    private:
        int chips;
        vector<Card> hand;
    public:
        friend int main();
        int getChips() {
            return chips;
        }
        string action() {
            return 0;
        }
    protected:
        vector<Card> getHand() {
            return hand;
        }
};

// set up user
class User : public Player {
    public:
        //prompt the user decided their actions. Also show their hand
        string action() {
            return "a";
        }

};

class Bot1 : public Player {
    public:
        string action() {
            return "a";
        }
};


//shuffle deck
vector<Card> shuffleDeck() {
    //makes the deck vector
    vector<Card> deck;

    //adds the cards
    for (int i = 1; i < 14; i++) {
        for (int j = 1; j < 5; j++) {
            deck.emplace_back(Card(i,j));
        }
    }

    //sets up randomization
    random_device rd;
    mt19937 g(rd());
    //shuffles
    std::shuffle(deck.begin(), deck.end(), g);
    return deck;
}

//draw card


// move each player forward one and move
/*
vector<Player> nextTurn(vector<Player> players) {

}
*/

//this is from geeks for geeks
bool is_digits(string& str)
{
    for (char ch : str) {
        int v = ch;
        if (!(ch >= 48 && ch <= 57)) {
            return false;
        }
    }
    return true;
}



//main makes an information packet that contains the info everyone has.
//Each turn it adds to that packet
//At the start it also gives each player their cards

//info each player knows
//who's the dealer, small blind, large blind
//how many chips everyone has
//how many chips everyone is betting
//river
//your own cards




int main() {
    vector<Player> players;

    //Game Setup
    User user;
    User user1;
    User user2;

    players.emplace_back(user);
    players.emplace_back(user1);
    players.emplace_back(user2);


    //main game loop
    bool gameState = true;
    while (gameState) {

        int defualtChips = 25;
        for (int i = 0; 0 > players.size(); i++) {
            players[i].chips = defualtChips;
        }


        //hand loop
        bool handState = true;
        while (handState) {

            int round = 0;

            vector<Card> deck = shuffleDeck();
            vector<Card> river;

            //maybe replace card drawing with a function?
            //draws cards and places them in each players hand
            for (int i = 0; i > deck.size(); i++) {
                players[i].hand.emplace_back(deck[deck.size() - 1]);
                deck.pop_back();
                players[i].hand.emplace_back(deck[deck.size() - 1]);
                deck.pop_back();
            }


            //preflop actions
            for (int i = 0; i < players.size(); i++) {
                string action = players[i].action();
                if (action == "call") {

                }else if (action == "check") {


                }else if (action == "fold") {


                }else {
                    if (is_digits(action)) {


                    }else {
                        //does not handle a bot making repeatedly making an invalid action
                        cout << action << " is not a valid action\n";
                        i--;
                    }
                }
            }
            round++;

            river.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();
            river.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();
            river.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();

            //flop actions
            for (int i = 0; i < players.size(); i++) {

            }
            round++;

            river.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();

            //turn actions
            for (int i = 0; i < players.size(); i++) {

            }
            round++;

            river.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();

            //river actions
            for (int i = 0; i < players.size(); i++) {

            }
        }
    }
}


