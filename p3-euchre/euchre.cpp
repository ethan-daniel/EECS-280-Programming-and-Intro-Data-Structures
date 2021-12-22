// Project UID 1d9f47bfc76643019cfbf037641defe1

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

    void score_increment(){
        ++score;
    }

    void score_decrement(){
        --score;
    }

    int get_score(){
        return score;
    }

    void init_players(string& name_1, string& type_1, string& name_2, string& type_2,
        string& name_3, string& type_3, string& name_4, string& type_4) {

            players.push_back(Player_factory(name_1, type_1));
            players.push_back(Player_factory(name_2, type_2));
            players.push_back(Player_factory(name_3, type_3));
            players.push_back(Player_factory(name_4, type_4));
    }

    void init_pack(std::istream& pack_input, string& shuffle) {
        Pack cards(pack_input);
        if (shuffle == "shuffle") {
            cards.shuffle();
        }
    }

    void deal_to_players() {
        int player_to_deal = dealer + 1;
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
    }



    Game(string& name_1, string& type_1, string& name_2, string& type_2,
        string& name_3, string& type_3, string& name_4, string& type_4,
        std::istream& pack_input, string& shuffle) {
            init_players(name_1, type_1, name_2, type_2,
                             name_3, type_3, name_4, type_4);
            init_pack(pack_input, shuffle);
    }

    void delete_players(){
        for (int i = 0, size = players.size(); i != size; ++i){
            delete players[i];
        }
    }

private:
    vector<Player*> players;
    Pack deck;
    int score = 0;
    int dealer = 0;
    
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

    string pack_filename = argv[1];
    string inShuffle = argv[2];
    string inPointsWin = argv[3];

    string player_1_name = argv[4];
    string player_1_type = argv[5];
    string player_2_name = argv[6];
    string player_2_type = argv[7];
    string player_3_name = argv[8];
    string player_3_type = argv[9];
    string player_4_name = argv[10];
    string player_4_type = argv[11];

    cout << argv[0] << pack_filename << inShuffle << inPointsWin << player_1_name
        << player_1_type << player_2_name << player_2_type << player_3_name
        << player_3_type << player_4_name << player_4_type << "\n";

    ifstream fin(pack_filename);
    if (! fin.is_open() ) {
        cout << "Error opening " << pack_filename << endl;
    }



    return 0;
}