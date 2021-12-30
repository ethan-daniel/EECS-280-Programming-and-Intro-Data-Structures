// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include "Pack.h"

const int START_POSITION_FOR_ARRAY = 7;
const int FIRST_CARD = 0;
const int LAST_CARD = 23;

Pack::Pack(){
    next = FIRST_CARD;
    int j = START_POSITION_FOR_ARRAY, k = 0;
    for (int i = 0; i != PACK_SIZE; ++i){
        Card card(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[k]);
        cards[i] = card;
        ++j;

        if (j == NUM_RANKS){
            j = START_POSITION_FOR_ARRAY;
            ++k;
        }
    }
}

Pack::Pack(std::istream& pack_input){
    next = FIRST_CARD;
    std::string rank, suit, of;

    for (int i = 0; i != PACK_SIZE; ++i){
        pack_input >> rank >> of >> suit;
        Card card(rank, suit);
        cards[i] = card;
    }
}

Card Pack::deal_one(){
    return cards[next++]; // C++ evaluates "cards[next]", then after "return"
                         // it will do "next++"" (hence, "post-increment")
}

void Pack::reset(){
    next = FIRST_CARD;
}

void Pack::shuffle(){
    int num_shuffles = 7;
    std::array<Card, PACK_SIZE/2> first_half, second_half;

    while (num_shuffles != 0){

        for (int i = 0; i != PACK_SIZE/2; ++i){
            first_half[i] = cards[i];
            second_half[i] = cards[PACK_SIZE/2 + i];
        }

        for (int i = 0, j = 0; i != PACK_SIZE; i+=2, ++j){
            cards[i] = second_half[j];
            cards[i+1] = first_half[j];
        }

        --num_shuffles;
    }
    
    next = 0;

}

bool Pack::empty() const {
    if (next == LAST_CARD + 1){
        return true;
    }

    return false;
}

void Pack::print() {
    for (int i = 0; i != PACK_SIZE; ++i){
        std::cout << "[" <<i << "] "<< cards[i] << std::endl;
    }
}