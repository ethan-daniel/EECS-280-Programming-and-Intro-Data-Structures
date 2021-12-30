// Project UID 1d9f47bfc76643019cfbf037641defe1

// euchre_test00 passes
// euchre_test50 passes
// euchre_test01 partially passes (TO FIX: For some hands, 1 player is dealt 1 wrong card 
// according to the test file. Shuffling was tested in person for odd and even number of shuffles
// and produced the same results as shuffling function. Strange behavior...)

#include <iostream>
#include <fstream>
#include <cstring>
#include "Card.h"
#include "Pack.h"
#include "Player.h"

using std::cout;    using std::cin;
using std::endl;    using std::string;
using std::vector;  using std::ifstream;
using std::ofstream;

class Game {
public:

    Game(string name_0, string type_0, string name_1, string type_1,
        string name_2, string type_2, string name_3, string type_3,
        std::istream& pack_input, string in_shuffle, int pointsToWin) 
        :  players({Player_factory(name_0, type_0), Player_factory(name_1, type_1), 
			Player_factory(name_2, type_2), Player_factory(name_3, type_3)}), 
            deck(pack_input), team_1_score(0), team_2_score(0), score_to_win(pointsToWin),
            do_shuffle(in_shuffle) { }

    int get_score(int& score){
        return score;
    }

    void shuffle() {
        deck.shuffle();
        // cout << "Printing the cards in the deck" << endl;
        // deck.print();
    }

    void print_hand(int n) {
        cout << "Print hand of player " << players[n]->get_name() << endl;
        for (int i = 0; i != 5; ++i){
            cout << players[n]->get_card(i) << endl;
        }
    }

    void deal_to_players_and_get_upcard(int dealer_position) {
        int player_to_deal = dealer_position + 1;
        int pattern = 2;
        for (int i = 0; i != 4; ++i) {
            if (player_to_deal > 3){
                player_to_deal = 0;
            }
            if (pattern%2 == 0) {
            players[player_to_deal]->add_card(deck.deal_one());
            players[player_to_deal]->add_card(deck.deal_one());
            players[player_to_deal]->add_card(deck.deal_one());
            }
            else if (pattern%2 == 1) {
                players[player_to_deal]->add_card(deck.deal_one());
                players[player_to_deal]->add_card(deck.deal_one());
            }

            ++player_to_deal;
            ++pattern;
        }

        pattern = 2;
        for (int i = 0; i != 4; ++i) {

            if (player_to_deal > 3){
                player_to_deal = 0;
            }
            if (pattern%2 == 0) {
            players[player_to_deal]->add_card(deck.deal_one());
            players[player_to_deal]->add_card(deck.deal_one());
            }
            else if (pattern%2 == 1) {
                players[player_to_deal]->add_card(deck.deal_one());
                players[player_to_deal]->add_card(deck.deal_one());
                players[player_to_deal]->add_card(deck.deal_one());
            }

            ++player_to_deal;
            ++pattern;
        }


        // for (int i = 0; i != 4; ++i){
        //     print_hand(i);
        // }

        upcard = deck.deal_one();

        cout << upcard.get_rank() << " of " << upcard.get_suit() << " turned up" << "\n";
    }

    string make_Trump() {
        int eldest_hand = dealer_position + 1;
        bool is_dealer;
        if (eldest_hand > 3){
            eldest_hand = 0;
        }
        for (int round = 1; round != 3; ++round){
            for (int i = 0; i != 4; ++i) {
                if ((eldest_hand+i)%4 == dealer_position){
                    is_dealer = true;
                }
                else {
                    is_dealer = false;
                }
                if (players[(eldest_hand+i)%4]->make_trump(upcard, is_dealer, round, order_up_suit)) {
                        if (is_dealer && round == 1) {
                            players[(eldest_hand+i)%4]->add_and_discard(upcard);
                        }
                        cout << players[(eldest_hand+i)%4]->get_name() << " orders up "
                            << order_up_suit << "\n\n";
                        
                        if ((eldest_hand+i)%4 == 0 || (eldest_hand+i)%4 == 2){
                            ordered_up_team = 1;
                        }
                        else {
                            ordered_up_team = 2;
                        }
                        trump = order_up_suit;
                        return order_up_suit;
                }
                else {
                    cout << players[(eldest_hand+i)%4]->get_name() << " passes\n";
                }
            }
        }
        return order_up_suit;
    }

    void trick_taking() {
        int eldest_hand = dealer_position + 1; // leader
        if (eldest_hand > 3) {
            eldest_hand = 0;
        }
        int trick_winner = eldest_hand; // init 
        int highest_player = eldest_hand;
        team_1_tricks = 0, team_2_tricks = 0;
        Card led_card;
        Card played_card;
        Card highest_card;

        for (int trick = 0; trick != 5; ++trick) {
            led_card = players[trick_winner]->lead_card(order_up_suit); // order_up_suit == "trump" here
            cout << led_card.get_rank() << " of " << led_card.get_suit() << " led by "
                 << players[trick_winner]->get_name() << "\n"; 
            highest_card = led_card;

            for (int i = 1; i != 4; ++i){
                played_card = players[(trick_winner+i)%4]->play_card(led_card, order_up_suit);
                //cout << "\t\t\t\t\t\t\t\t\t\tled card: " << led_card.get_suit() << endl;
                cout << played_card.get_rank() << " of " << played_card.get_suit() << " played by "
                 << players[(trick_winner+i)%4]->get_name() << "\n";
                
                if (Card_less(highest_card, played_card, led_card, order_up_suit)){
                    highest_card = played_card;
                    highest_player = (trick_winner+i)%4;
                }
            }

            if (highest_player == 0 || highest_player == 2){
                ++team_1_tricks;
            }
            else {
                ++team_2_tricks;
            }

            trick_winner = highest_player;
            cout << players[trick_winner]->get_name() << " takes the trick\n";
            cout << endl;
        }
    }

    void scoring() {
        if (team_1_tricks > team_2_tricks) {
            cout << players[0]->get_name() << " and " << players[2]->get_name()
                << " win the hand\n";

            if (ordered_up_team == 1) {
                if (team_1_tricks == 5){
                    team_1_score = team_1_score + 2;
                    cout << "march!\n";
                }
                else {
                    ++team_1_score;
                }
            }
            else {
                team_1_score = team_1_score + 2;
                cout << "euchred!\n";
            }
        }
        else {
            cout << players[1]->get_name() << " and " << players[3]->get_name()
                << " win the hand\n";

            if (ordered_up_team == 2){
                if (team_2_tricks == 5){
                    team_2_score = team_2_score + 2;
                    cout << "march!\n";
                }
                else {
                    ++team_2_score;
                }
            }
            else {
                team_2_score = team_2_score + 2;
                cout << "euchred!\n";
            }   
        }

        cout << players[0]->get_name() << " and " << players[2]->get_name()
            << " have " << team_1_score << " points\n";
        cout << players[1]->get_name() << " and " << players[3]->get_name()
            << " have " << team_2_score << " points\n\n";

    }

    void run() {
        int hand = 0;
        string trump;
        while (team_1_score < score_to_win && team_2_score < score_to_win) {
            dealer_position = hand%4;
            cout << "Hand " << hand << endl;
            cout << players[dealer_position]->get_name() << " deals\n";

            if (do_shuffle == "shuffle") {
                shuffle();
            }
            deal_to_players_and_get_upcard(dealer_position);
            trump = make_Trump();
            trick_taking();
            scoring();

            ++hand;
        }

        if (team_1_score > team_2_score){
            cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!\n";
        }
        else {
            cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!\n";
        }

    }

    void delete_players(){
        for (int i = 0, size = players.size(); i != size; ++i){
            delete players[i];
        }
    }

private:
    vector<Player*> players;
    Pack deck;
    int team_1_score;
    int team_2_score;
    int score_to_win;
    int team_1_tricks;
    int team_2_tricks;
    int dealer_position;
    int ordered_up_team;
    Card upcard;
    string order_up_suit;
    string trump;
    string do_shuffle;
    
};

int error() {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 1;
}

int main(int argc, char *argv[]) {

    if(argc != 12 ) {
        error();
    } else if (!(atoi(argv[3]) >= 1)) {
        error();
    } else if (!(atoi(argv[3]) <= 100)) {
        error();
    } else if (!(strcmp(argv[2], "shuffle") ^ (strcmp(argv[2], "noshuffle")))) {
        error();
    } else if (!(strcmp(argv[5], "Simple") ^ (strcmp(argv[5], "Human")))) {
        error();
    } else if (!(strcmp(argv[7], "Simple") ^ (strcmp(argv[7], "Human")))) {
        error();
    } else if (!(strcmp(argv[9], "Simple") ^ (strcmp(argv[9], "Human")))) {
        error();
    } else if (!(strcmp(argv[11], "Simple") ^ (strcmp(argv[11], "Human")))) {
        error();
    }

    for (int i = 0; i != argc; ++i){
        cout << argv[i] << " ";
    }
    cout << endl;

    string pack_filename = argv[1];
    ifstream fin(pack_filename);
    if (! fin.is_open() ) {
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }

    Game game(argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11],
                fin, argv[2], atoi(argv[3]));

    game.run();

    fin.close();
    game.delete_players();

    return 0;
}