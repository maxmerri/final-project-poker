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

class Player {
public:
    vector<Card> hand;
    int chips;
    string blind;
    string action() {
        return 0;
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
vector<Player> nextTurn(vector<Player> players) {

}







int main() {
    vector<Player> players;

    //Game Setup
    User user;
    Bot1 bot1;



    players.emplace_back(user);
    players.emplace_back(bot1);

    //main game loop
    bool gameState = true;
    while (gameState) {
        //gives players their chips
        int defualtChips = 25;
        for (int i = players.size(); 0 > players.size(); i--) {
            players[i].chips = defualtChips;
        }

        //hand loop
        bool handState = true;
        while (handState) {
            vector<Card> deck = shuffleDeck();


            bool roundState = true;
            while (roundState) {
                int turn = 0;
                players[0].blind = "big";
                players[1].blind = "small";
                for (int i = 2; i < players.size(); i++) {
                    players[i].blind = "none";
                }


                //end of round
                players = nextTurn(players);
            }
        }
    }
}


