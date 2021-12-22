// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card() 
    : rank(RANK_TWO), suit(SUIT_SPADES) {}

Card::Card(const std::string &rank_in, const std::string &suit_in)
    : rank(rank_in), suit(suit_in) {}

std::string Card::get_rank() const { 
    return rank;
}

std::string Card::get_suit() const { 
    return suit;
}

std::string Card::get_suit(const std::string &trump) const { 
    if (this->is_left_bower(trump)){
        return Suit_next(suit);
    }
    else{
        return suit;
    }
}

bool Card::is_face() const { 
    if (rank == RANK_JACK || rank == RANK_QUEEN
        || rank == RANK_KING || rank == RANK_ACE) {
            return true;
        }

    return false;
}

bool Card::is_right_bower(const std::string &trump) const { 
    return (suit == trump && rank == RANK_JACK);
}

bool Card::is_left_bower(const std::string &trump) const { 
    return (suit == Suit_next(trump) && rank == RANK_JACK);
}

bool Card::is_trump(const std::string &trump) const { 
    return (suit == trump || this->is_left_bower(trump));
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

bool operator<(const Card &lhs, const Card &rhs) {
    int lhs_rank, rhs_rank;
    int lhs_suit, rhs_suit;

    for (int i = 0; i != NUM_RANKS; ++i){
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()){
            lhs_rank = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()){
            rhs_rank = i;
        }
    }

    if (lhs_rank < rhs_rank){
        return true;
    }

    else if (lhs_rank == rhs_rank){
        for (int i = 0; i != NUM_SUITS; ++i){
            if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()){
                lhs_suit = i;
            }
            if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()){
                rhs_suit = i;
            }
        }
        if (lhs_suit < rhs_suit){
            return true;
        }
    }

    return false;
}

bool operator<=(const Card &lhs, const Card &rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Card &lhs, const Card &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Card &lhs, const Card &rhs) {
    return !(lhs < rhs);
}

bool operator==(const Card &lhs, const Card &rhs) {
    int lhs_rank, rhs_rank;
    int lhs_suit, rhs_suit;

    for (int i = 0; i != NUM_RANKS; ++i){
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()){
            lhs_rank = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()){
            rhs_rank = i;
        }
    }

    for (int i = 0; i != NUM_SUITS; ++i){
        if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()){
            lhs_suit = i;
        }
        if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()){
            rhs_suit = i;
        }
    }
    
    if (lhs_rank == rhs_rank && lhs_suit == rhs_suit){
        return true;
    }

    return false;
}

bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);
}

std::string Suit_next(const std::string &suit) {
    if (suit == SUIT_NAMES_BY_WEIGHT[0]){
        return SUIT_NAMES_BY_WEIGHT[2];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[2]){
        return SUIT_NAMES_BY_WEIGHT[0];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[1]){
        return SUIT_NAMES_BY_WEIGHT[3];
    }
    else {
        return SUIT_NAMES_BY_WEIGHT[1];
    }
}

std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    if (a == b || a.is_right_bower(trump)){
        return false;
    }
    else if (b.is_right_bower(trump)){
        return true;
    }
    else if (!a.is_trump(trump)){
        if (!b.is_trump(trump)){
            return a < b;
        }
        else{
            return true;
        }
    }
    else if (a.is_trump(trump)){
        if (!b.is_trump(trump)){
            return false;
        }
        else if (b.is_left_bower(trump)){
            return true;
        }
        else if (a.is_left_bower(trump)){
            return false;
        }
    }

    return a < b;
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    if (trump == led_card.get_suit() || a.is_trump(trump) || b.is_trump(trump)) {
        return Card_less(a, b, trump);
    }
    else if (a.get_suit() == led_card.get_suit()
                && b.get_suit() != led_card.get_suit()){
        return false;
    }
    else if (a.get_suit() != led_card.get_suit()
                && b.get_suit() == led_card.get_suit()){
        return true;
    }

    return a < b;
}