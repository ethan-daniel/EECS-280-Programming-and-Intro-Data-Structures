// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());

    Card second = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, second.get_suit());

    for (int i = 0; i != 7; ++i){
        pack.deal_one();
    }
    Card tenth = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_QUEEN, tenth.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, tenth.get_suit());

    for (int i = 0; i != 13; ++i){
        pack.deal_one();
    }
    Card last = pack.deal_one(); // 24th card (starting with 1st)
    ASSERT_EQUAL(Card::RANK_ACE, last.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, last.get_suit());
}

// Add more tests here

TEST_MAIN()
