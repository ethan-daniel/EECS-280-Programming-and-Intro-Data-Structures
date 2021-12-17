// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());

    Card c1;
    ASSERT_EQUAL(Card::RANK_TWO, c1.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c1.get_suit());
    
}

// Add more test cases here
TEST(test_card_suit_and_rank) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(jack_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);

    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_HEARTS), Card::SUIT_SPADES);
}

TEST(test_card_type) {
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(king_hearts.is_face());
    ASSERT_TRUE(king_hearts.is_trump(Card::SUIT_HEARTS));
    ASSERT_FALSE(king_hearts.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(king_hearts.is_left_bower(Card::SUIT_CLUBS));

    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(jack_spades.is_face());
    ASSERT_TRUE(jack_spades.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_SPADES));

    ASSERT_FALSE(jack_spades.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(jack_spades.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(jack_spades.is_trump(Card::SUIT_HEARTS));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    
    ASSERT_FALSE(ten_clubs < three_spades);
    ASSERT_FALSE(ten_clubs <= three_spades);
    ASSERT_TRUE(ten_clubs > three_spades);
    ASSERT_TRUE(ten_clubs >= three_spades);
    ASSERT_FALSE(ten_clubs == three_spades);
    ASSERT_TRUE(ten_clubs != three_spades);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card three_diamonds = Card(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);

    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);

    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);

    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS)); // equal
    ASSERT_FALSE(Card_less(jack_clubs, ace_diamonds, Card::SUIT_CLUBS)); // right bower a
    ASSERT_TRUE(Card_less(ace_diamonds, jack_clubs, Card::SUIT_CLUBS)); // right bower b
    ASSERT_TRUE(Card_less(ace_diamonds, ten_clubs, Card::SUIT_CLUBS)); // suit < suit
    ASSERT_TRUE(Card_less(ten_spades, ten_clubs, Card::SUIT_CLUBS)); // suit < suit
    ASSERT_TRUE(Card_less(three_spades, ten_clubs, Card::SUIT_CLUBS)); // a < b
    ASSERT_FALSE(Card_less(ten_clubs, ace_diamonds, Card::SUIT_CLUBS)); // trump v not trump
    ASSERT_FALSE(Card_less(jack_clubs, jack_spades, Card::SUIT_CLUBS)); // right v left bower
    ASSERT_TRUE(Card_less(ace_diamonds, jack_spades, Card::SUIT_CLUBS)); // left bower
    ASSERT_TRUE(Card_less(three_spades, ten_spades, Card::SUIT_SPADES)); // trump v trump
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_clubs, ace_spades, Card::SUIT_SPADES));

    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(jack_spades, ace_diamonds, ten_diamonds,
                           Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, ten_clubs,
                           Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_clubs, ace_spades, ten_clubs,
                           Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(ace_spades, ace_diamonds, ten_diamonds,
                           Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(ten_spades, ace_diamonds, three_diamonds,
                           Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(ten_spades, ace_diamonds, three_spades,
                           Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(ten_hearts, ten_clubs, three_diamonds,
                           Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(jack_diamonds, ace_diamonds, ten_diamonds,
                           Card::SUIT_SPADES));
}

TEST_MAIN()
