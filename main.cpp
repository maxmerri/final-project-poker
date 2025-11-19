#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
using namespace std;

//maybe use this for tracking players
int playerNumber = 0;
int getPlayerNumber() {
    playerNumber++;
    return playerNumber;
}

//this is from geeks for geeks. checks if a string is only digits
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

string makeLowerCase(string s) {
    for (int i = 0; i<s.length(); i++) { // test to run is i less than the length of name
        s[i] = tolower(s[i]); // convert letter in name to lower case form
    }
    return s;

}



//defines the cards
class Card {
    public:
        int value;
        int suit;
        Card(int x, int y) {
            value = x;
            suit = y;
        }

        bool operator<(const Card& other) const {
            return value < other.value;
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

class PlayerActions {
    public:
        string action;
        int player;
        PlayerActions(string x, int y) {
            action = x;
            player = y;
        }
};

//main makes an information packet that contains the info everyone has.
//Each turn it adds to that packet
//At the start it also gives each player their cards

//info each player knows
//who's the dealer, small blind, large blind
//how many chips everyone has
//how many chips everyone is betting
//river
//your own cards
//valid actions
bool isStraight(vector<Card> cards) {
    //sorts cards in order
    sort(cards.begin(), cards.end());
    int numOfCards = 0;

    for (int i = 0; i < cards.size() - 1; i++) {
        //checks if the next card is one higher
        if (cards[i].value == cards[i+i].value + 1) {
            numOfCards++;
        }else if (cards[i].value == cards[i+i].value) {
            continue;
        }else if (cards[i].value == 13 && cards[0].value == 1) {
            continue;
        }else {
            return false;
        }

    }
    return true;
}


/*
int handType(vector<Card> cards) {
    if (isRoyalFlush(cards)) {
        return 1;
    }
}
*/
class GameInfo {
    private:
        vector<Card> river;
        int round;
        int minbet;

    public:
        GameInfo(vector<Card> a, int b, int c) {
            river = a;
            round = b;
            minbet = c;
        }
        GameInfo() {

        }
        int getMinBet() {
            return minbet;
        }
        int getRound() {
            return round;
        }
        vector<Card> getRiver() {
            return river;
        }

};

//Class that every player, both bots and people, derive from
class Player {
    private:
        //chips and hand are private so that children of players can't change it.
        //Main can change it since it's a friend class
        int chips;
        vector<Card> hand;
        GameInfo gameinfo;
        void setChips(int x) {
            chips = x;
        }
        void setGameInfo(GameInfo x) {
            gameinfo = x;
        }
        void addChips(int x) {
            chips = chips + x;
        }
        void setHand(vector<Card> x) {
            hand = x;
        }
        void addHand(Card x) {
            hand.emplace_back(x);
        }
    public:
        friend int main();
        int getChips() {
            return chips;
        }
        GameInfo getGameInfo() {
            return gameinfo;
        }
        virtual string action() {
            return "test";
        }
    protected:
        //I think this can just be public?
        vector<Card> getHand() {
            return hand;
        }
};

// set up user
class User : public Player {
    public:
        //prompt the user decided their actions. Also show their hand
        string action() override{
            while (true) {
                cout << "your hand is a " << getHand()[0].name() << " and a " << getHand()[1].name() << endl;
                cout << "You can call, check, raise, or fold. To raise type the number to raise by\n";
                string input;

                //Input validation
                while (true){
                    cin >> input;

                    if (makeLowerCase(input) == "call" or makeLowerCase(input) == "fold") {
                        break;
                    }else if (makeLowerCase(input) == "check" ) {
                        if (getGameInfo().getMinBet() == 0) {
                            break;
                        }
                        cout << "Can't check when min bet is not 0";
                    }else if (is_digits(input)) {
                        if (0 < stoi(input) && stoi(input) <= getChips()) {
                            break;
                        }
                        cout << "Invalid raise number";
                    }else {
                        cout << "Invalid input";
                    }
                }
                return input;
            }
        }
};




//shuffle deck
vector<Card> shuffleDeck() {
    //makes the deck vector
    vector<Card> deck;

    //adds the cards
    for (int i = 1; i < 14; i++) {
        for (int j = 1; j < 5; j++) {
            deck.emplace_back(i,j);
        }
    }

    //sets up randomization
    random_device rd;
    mt19937 g(rd());
    //shuffles
    std::shuffle(deck.begin(), deck.end(), g);
    return deck;
}


int main() {
    //I don't fully understand pointers but having this vector set up in this way allows the objects in it to override their parent class
    vector<unique_ptr<Player>> players;
    //adds players to the game
    players.push_back(make_unique<Player>());
    players.push_back(make_unique<User>());

    vector<Card> testHand = {Card(1,1),Card(2,1),Card(3,1),Card(4,1),Card(5,1)};
    cout << isStraight(testHand) << endl;



    //main game loop
    bool gameState = true;
    while (gameState) {

        int defualtChips = 25;
        for (auto & player : players) {
            player->setChips(defualtChips);
        }

        //hand loop
        bool handState = true;
        while (handState) {

            int round = 0;
            int minbet = 2;

            vector<Card> deck = shuffleDeck();
            vector<Card> river;
            vector<PlayerActions> handActions;



            //maybe replace card drawing with a function?
            //draws cards and places them in each players hand
            for (auto & player : players) {
                player->addHand(deck[deck.size() - 1]);
                deck.pop_back();
                player->addHand(deck[deck.size() - 1]);
                deck.pop_back();
            }


            //Need to figure out how to do action validation. Main program should tell players valid actions.
            //preflop actions
            for (auto & player : players) {
                string action = player->action();
                if (action == "call") {
                    //removes chips from player
                    player->addChips(-minbet);
                }else if (action == "check" && minbet == 0) {
                    continue;

                }else if (action == "fold") {



                }else {
                    if (is_digits(action)) {


                    }else {
                        //does not handle a bot making repeatedly making an invalid action
                        cout << action << " is not a valid action\n";

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
