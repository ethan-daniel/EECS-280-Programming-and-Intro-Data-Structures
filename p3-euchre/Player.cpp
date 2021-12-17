// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <cassert>
#include "Player.h"

const std::string & Player::get_name() const{
    assert(false);
}

void Player::add_card(const Card &c) {
    assert(false);
}

bool Player::make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
                              assert(false);
                          }

void Player::add_and_discard(const Card &upcard) {
    assert(false);
}

Card Player::lead_card(const std::string &trump) {
    assert(false);
}

Card Player::play_card(const Card &led_card, const std::string &trump) {
    assert(false);
}

Player * Player_factory(const std::string &name, const std::string &strategy){ 
    assert(false);
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    assert(false);
}