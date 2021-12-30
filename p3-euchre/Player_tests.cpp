// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
TEST(basic_test_SimplePlayer_make_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  // TEST: (round 1) there are no "two or more trump face cards" in bob's hand
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));

  // Bob makes trump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  Player * bob1 = Player_factory("Bob", "Simple");
  // TEST: (round 1) 2 trump cards, (king spades and left bowery)
  bob1->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob1->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob1->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob1->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  bob1->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));

  // Bob makes trump
  Card nine_spades1(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump1;
  bool orderup1 = bob1->make_trump(
    nine_spades1,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump1           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup1);
  ASSERT_EQUAL(trump1, Card::SUIT_SPADES);

  Player * bob2 = Player_factory("Bob", "Simple");
  // TEST: (round 1) bob is not dealer + hearts is the trump
  bob2->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob2->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob2->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob2->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob2->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes trump
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump2;
  bool orderup2 = bob2->make_trump(
    nine_hearts,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump2           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup2);

  Player * bob3 = Player_factory("Bob", "Simple");
  // TEST: (round 2) bob will orderup SPADES on a CLUB upcard
  bob3->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob3->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob3->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob3->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob3->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes trump
  Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
  string trump3;
  bool orderup3 = bob3->make_trump(
    nine_clubs,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump3           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup3);
  ASSERT_EQUAL(trump3, Card::SUIT_SPADES);

  Player * bob4 = Player_factory("Bob", "Simple");
  // TEST: (round 2) bob will orderup diamonds on 
  bob4->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob4->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob4->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob4->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob4->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes trump
  Card nine_hearts4(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump4;
  bool orderup4 = bob4->make_trump(
    nine_hearts4,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump4           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup4);
  ASSERT_EQUAL(trump4, Card::SUIT_DIAMONDS);

  Player * bob5 = Player_factory("Bob", "Simple");
  // TEST: (round 2) bob will not orderup
  bob5->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob5->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob5->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob5->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob5->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes trump
  Card nine_hearts5(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump5;
  bool orderup5 = bob5->make_trump(
    nine_hearts5,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump5           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup5);

  Player * bob6 = Player_factory("Bob", "Simple");
  // TEST: (round 2) bob will orderup because he is dealer
  // screw the dealer is invoked here
  bob6->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob6->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob6->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob6->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob6->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes trump
  Card nine_hearts6(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump6;
  bool orderup6 = bob6->make_trump(
    nine_hearts6,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump6          // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup6);
  ASSERT_EQUAL(trump6, Card::SUIT_DIAMONDS); // color of the upcard

  delete bob;
  delete bob1;
  delete bob2;
  delete bob3;
  delete bob4;
  delete bob5;
  delete bob6;
}

TEST(basic_test_SimplePlayer_add_and_discard){
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  ASSERT_EQUAL(bob->get_card(0).get_suit(), Card::SUIT_HEARTS);
  ASSERT_EQUAL(bob->get_card(0).get_rank(), Card::RANK_NINE);

  ASSERT_EQUAL(bob->get_card(1).get_suit(), Card::SUIT_HEARTS);
  ASSERT_EQUAL(bob->get_card(1).get_rank(), Card::RANK_TEN);

  ASSERT_EQUAL(bob->get_card(2).get_suit(), Card::SUIT_HEARTS);
  ASSERT_EQUAL(bob->get_card(2).get_rank(), Card::RANK_QUEEN);

  ASSERT_EQUAL(bob->get_card(3).get_suit(), Card::SUIT_HEARTS);
  ASSERT_EQUAL(bob->get_card(3).get_rank(), Card::RANK_KING);

  ASSERT_EQUAL(bob->get_card(4).get_suit(), Card::SUIT_HEARTS);
  ASSERT_EQUAL(bob->get_card(4).get_rank(), Card::RANK_ACE);


  bob->add_and_discard(
  Card(Card::RANK_JACK, Card::SUIT_HEARTS) // upcard
  );

  // shows that all previous cards are shifted down an index
  // and new card is pushed to the back of the hand
  ASSERT_EQUAL(bob->get_card(0).get_suit(), Card::SUIT_HEARTS);
  ASSERT_EQUAL(bob->get_card(0).get_rank(), Card::RANK_TEN);

  ASSERT_EQUAL(bob->get_card(4).get_suit(), Card::SUIT_HEARTS);
  ASSERT_EQUAL(bob->get_card(4).get_rank(), Card::RANK_JACK);

  delete bob;
}

// TEST(basic_test_SimplePlayer_lead_card) {
//   // Bob's hand
//   // TESTING: highest trump card (check for ace and jack)
//   Player * bob = Player_factory("Bob", "Simple");
//   bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

//   // Bob leads
//   Card card_led = bob->lead_card(Card::SUIT_SPADES);

//   // Verify the card Bob selected to lead
//   Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
//   ASSERT_EQUAL(card_led, ace_spades); //check led card

//   bob->add_and_discard(
//   Card(Card::RANK_JACK, Card::SUIT_SPADES) // upcard
//   );

//   card_led = bob->lead_card(Card::SUIT_SPADES);

//   Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
//   ASSERT_EQUAL(card_led, jack_spades);

//   delete bob;
// }

TEST(basic_test_SimplePlayer_play_card) {
  // Bob's hand
  // TESTING: Bob will follow suit
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(basic_test_HumanPlayer_get_name) {
  Player * alice = Player_factory("Alice", "Human");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

//============================================================//
// Below are tests for Human Player. 
// (Uncomment to use, requires the user's input.)
//============================================================//


// TEST(basic_test_HumanPlayer_make_trump) {
//   Player * bob = Player_factory("Bob", "Human");
//   bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

//   Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
//   string trump;
//   bool orderup = bob->make_trump(
//     nine_spades,    // Upcard
//     true,           // Bob is also the dealer
//     1,              // First round
//     trump           // Suit ordered up (if any)
//   );

//   ASSERT_TRUE(orderup);
//   ASSERT_EQUAL(trump, Card::SUIT_SPADES);

// }

// TEST(basic_test_HumanPlayer_add_and_discard_card) {
//   // Bob's hand
//   Player * bob = Player_factory("Bob", "Human");
//   bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

//   bob->add_and_discard(
//   Card(Card::RANK_JACK, Card::SUIT_SPADES) // upcard
//   );

//   // 1st card is discarded (erase())
//   ASSERT_NOT_EQUAL(bob->get_card(0).get_rank(), Card::RANK_NINE);

//   // last card is Jack of Spades (push_back())
//   ASSERT_EQUAL(bob->get_card(4).get_rank(), Card::RANK_JACK);

//   delete bob;
// }

// // same code for lead and play functions
// TEST(basic_test_HumanPlayer_lead_and_play_card) {
//   // Bob's hand
//   Player * bob = Player_factory("Bob", "Human");
//   bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

//   // Bob leads
//   Card card_led = bob->lead_card(Card::SUIT_HEARTS);

//   // Verify the card Bob selected to lead
//   Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
//   ASSERT_EQUAL(card_led, ace_spades); //check led card

//   delete bob;
// }

TEST_MAIN()
