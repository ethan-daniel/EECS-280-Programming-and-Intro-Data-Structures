// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <cassert>
#include "Player.h"
#include <algorithm>

using std::cout;    using std::cin;
using std::endl;

class Simple : public Player {
public:

    // Returns the Card in Player's hand
    Card get_card(int i = 0) override {
        return hand[i];
    }

    Simple(const std::string &in_name) {
        name = in_name;
    }

    const std::string & get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
        assert(round == 1 || round == 2);

        if (round == 1) {
            int numTrumpFace = 0;

            for (int i = 0, size = hand.size(); i != size; ++i){
                if ((hand[i].is_trump(upcard.get_suit()) && hand[i].is_face())
                || hand[i].is_left_bower(upcard.get_suit())) {
                    ++numTrumpFace;
                }
            }
            if (numTrumpFace >= 2){
                order_up_suit = upcard.get_suit();
                return true;  
            }
            else{
                return false;
            }
        }

        else if (round == 2) {
            std::string next_suit = Suit_next(upcard.get_suit());

            if (is_dealer){
                order_up_suit = next_suit;
                return true;
            }

            for (int i = 0, size = hand.size(); i != size; ++i){
                if ((hand[i].is_trump(next_suit) && hand[i].is_face())
                || hand[i].is_left_bower(next_suit)) {
                    order_up_suit = next_suit;
                    return true;
                }
            } 
        }
        return false;
    }

    void add_and_discard(const Card &upcard) override {
        assert(hand.size() >= 1);

        int hand_index = 0;
        hand.push_back(upcard);
        Card lowest = hand[0];

        for (int i = 0, size = hand.size(); i != size; ++i){
            if (Card_less(hand[i], lowest, upcard.get_suit())) { 
                lowest = hand[i];
                hand_index = i;
            }
        }
        hand.erase(hand.begin() + hand_index);
    }

    Card lead_card(const std::string &trump) override {
        Card highest;
        int exist_non_trump = 0, hand_index = 0;
        for (int i = 0, size = hand.size(); i != size; ++i) {
            if (exist_non_trump == 0){
                if (!hand[i].is_trump(trump)){
                    highest = hand[i];
                    hand_index = i;
                    exist_non_trump = 1;
                }
            }
                if (!hand[i].is_trump(trump) && hand[i] > highest) {
                    highest = hand[i];
                    hand_index = i;
                }
        }
        if (exist_non_trump == 0){
            for (int i = 0, size = hand.size(); i != size; ++i) {
                if (!Card_less(hand[i], highest, trump)){
                    highest = hand[i];
                    hand_index = i;
                }
            }
        }
        hand.erase(hand.begin() + hand_index);

        return highest;
    }   

    Card play_card(const Card &led_card, const std::string &trump) override {
        Card highest, lowest;
        int exist_comparison_high = 0, exist_comparison_low = 0, 
            hand_index_high = 0, hand_index_low = 0;

        for (int i = 0, size = hand.size(); i != size; ++i) {

            if (exist_comparison_low == 0){
                if (hand[i].get_suit() != led_card.get_suit()){
                    lowest = hand[i];
                    exist_comparison_low = 1;
                    hand_index_low = i;
                    continue;
                }
            }

            if (exist_comparison_high == 0){
                if (hand[i].get_suit() == led_card.get_suit()
                    && !hand[i].is_left_bower(trump)){
                    highest = hand[i];
                    exist_comparison_high = 1;
                    hand_index_high = i;
                    continue;
                }
            }

            if (exist_comparison_low == 1) {
                if (Card_less(hand[i], lowest, led_card, trump)){
                    lowest = hand[i];
                    hand_index_low = i;
                }
            }
            
            if (exist_comparison_high == 1) {
                if (hand[i] > highest 
                    && hand[i].get_suit() == led_card.get_suit()) {
                    highest = hand[i];
                    hand_index_high = i;
                }
            }
        }

        if (exist_comparison_high == 1){
            //cout << "\t\t\t\t\t\t\t\t\t\thighest: "<<highest << endl;
            hand.erase(hand.begin() + hand_index_high);
            return highest;
        }
        //cout << "\t\t\t\t\t\t\t\t\t\tlowest: " << lowest << endl;
        hand.erase(hand.begin() + hand_index_low);
        return lowest;
    }

private:
    std::string name;
    std::vector<Card> hand;

};

class Human : public Player {
public:
    // Prints the Cards in ascending order, as defined by the < operator in Card.h
    void printHand() const {
        std::vector<Card> temp = hand;
        std::sort(temp.begin(), temp.end());

        for (int i = 0, size = temp.size(); i != size; ++i) {
            cout << "Human player " << name << "'s hand: "
                << "[" << i << "] " << temp[i] << '\n';
        }
    }

    // Returns the Card in Player's hand
    Card get_card(int i = 0) override {
        return hand[i];
    }

    Human(const std::string &in_name) {
        name = in_name;
    }

    const std::string & get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
    
        assert(round == 1 || round == 2);

        std::string decision;      
        printHand();

        cout << "Human player "<< name << ", please enter a suit, or \"pass\":" << "\n";
        cin >> decision;

        if (decision == "Spades"){
            cout << name << " orders up Spades" << "\n\n";
            order_up_suit = Card::SUIT_SPADES;
            return true;
        }
        
        else if (decision == "Hearts"){
            cout << name << " orders up Hearts" << "\n\n";
            order_up_suit = Card::SUIT_HEARTS;
            return true;
        }

        else if (decision == "Clubs"){
            cout << name << " orders up Clubs" << "\n\n";
            order_up_suit = Card::SUIT_CLUBS;
            return true;
        }

        else if (decision == "Diamonds"){
            cout << name << " orders up Diamonds" << "\n\n";
            order_up_suit = Card::SUIT_DIAMONDS;
            return true;
        }

        cout << name << " passes" << endl;
        return false;

    } // MUST TEST

    void add_and_discard(const Card &upcard) override {
        int card_number;
        std::sort(hand.begin(), hand.end());

        for (int i = 0, size = hand.size(); i != size; ++i){
            cout << "Human player "<< name << "'s hand: " << "[" << i << "] " << hand[i] << endl;
        }
        hand.push_back(upcard);

        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name << ", please select a card to discard:" <<endl;
        cin >> card_number;

        if (card_number == -1){
            hand.pop_back();
        }
        else {
            hand.erase(hand.begin() + card_number);
        }
    } // MUST TEST

    Card lead_card(const std::string &trump) override {
        int card_number;
        Card card_to_lead;
        std::sort(hand.begin(), hand.end());

        for (int i = 0, size = hand.size(); i != size; ++i){
            cout << "Human player "<< name << "'s hand: " << "[" << i << "] " << hand[i] << endl;
        }
        cout << "Human player " << name << ", please select a card:" <<endl;
        cin >> card_number;
        cout << hand[card_number] << " led by " << name << endl;
        
        card_to_lead = hand[card_number];
        hand.erase(hand.begin() + card_number);
        
        return card_to_lead;
    }   

    Card play_card(const Card &led_card, const std::string &trump) override {
        return lead_card(trump);
    }
    
private:
    std::string name;
    std::vector<Card> hand;
};


Player * Player_factory(const std::string &name, const std::string &strategy){ 

    if (strategy == "Simple"){
        return new Simple(name);
    }

    if (strategy == "Human"){
        return new Human(name);
    }

    assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();

    return os;
}
