#include <cards_logic/klondike.h>
#include <cards_logic/basics.h>
#include <tests/test-utilities.h>
#include <string.h> // memcmp


void test_check_pool_and_waste() {

  TEST_DESCRIPTION("Pool and waste with no cards are valid");
  card no_cards[] = {};
  struct s_pool *empty_pool = utl_create_pool(no_cards, 0);
  struct s_waste *empty_waste = utl_create_waste(no_cards, 0);

  assert(1 == check_pool_and_waste(empty_pool, empty_waste));

  TEST_DESCRIPTION("A full pool OR a full waste is valid");
  TEST_ADDED_INFOS("However, both at the same time is invalid");
  card full_set[] = {
    __CARTE(queen, diamond),
    __CARTE(queen, spade),
    __CARTE(seven, club),
    __CARTE(three, club),
    __CARTE(five, diamond),
    __CARTE(four, heart),
    __CARTE(four, spade),
    __CARTE(eight, diamond),
    __CARTE(three, diamond),
    __CARTE(ace, spade),
    __CARTE(six, spade),
    __CARTE(ace, heart),
    __CARTE(two, club),
    __CARTE(six, club),
    __CARTE(two, spade),
    __CARTE(jack, heart),
    __CARTE(nine, spade),
    __CARTE(king, club),
    __CARTE(three, spade),
    __CARTE(ten, diamond),
    __CARTE(jack, spade),
    __CARTE(seven, spade),
    __CARTE(jack, club),
    __CARTE(eight, club)
  };

  struct s_pool *full_pool = utl_create_pool(full_set, 24);
  struct s_waste *full_waste = utl_create_waste(full_set, 24);

  assert(1 == check_pool_and_waste(full_pool, empty_waste));
  assert(1 == check_pool_and_waste(empty_pool, full_waste));
  assert(0 == check_pool_and_waste(full_pool, full_waste));

  TEST_DESCRIPTION("One card waste or One card pool are valid");
  TEST_DESCRIPTION("As always, the sum of cards in the pool and \n"
                   "waste must not be over 24 !");
  card one_card[] = {
    __CARTE(seven, diamond)
  };

  struct s_pool *one_card_pool = utl_create_pool(one_card, 1);
  struct s_waste *one_card_waste = utl_create_waste(one_card, 1);

  assert(1 == check_pool_and_waste(one_card_pool, one_card_waste));
  assert(1 == check_pool_and_waste(one_card_waste, one_card_pool));
  assert(1 == check_pool_and_waste(empty_pool, one_card_waste));
  assert(1 == check_pool_and_waste(one_card_pool, empty_waste));
  assert(0 == check_pool_and_waste(full_pool, one_card_waste));
  assert(0 == check_pool_and_waste(one_card_pool, full_waste));

  TEST_DESCRIPTION("Turned cards are not allowed");
  card one_turned_card[] = {
    __CARTE(~seven, diamond)
  };

  struct s_pool *one_turned_card_pool = utl_create_pool(one_turned_card, 1);
  struct s_waste *one_turned_card_waste = utl_create_waste(one_turned_card, 1);

  assert(0 == check_pool_and_waste(one_turned_card_pool, one_turned_card_waste));
  assert(0 == check_pool_and_waste(one_turned_card_pool, empty_waste));
  assert(0 == check_pool_and_waste(empty_pool, one_turned_card_waste));

  TEST_DESCRIPTION("12 cards in the pool and waste, at the same time, is valid");
  struct s_pool *half_pool = utl_create_pool(full_set, 12);
  struct s_waste *half_waste = utl_create_waste(full_set+12, 12);

  assert(1 == check_pool_and_waste(half_pool, half_waste));
  assert(1 == check_pool_and_waste(empty_pool, half_waste));
  assert(1 == check_pool_and_waste(one_card_pool, half_waste));
  assert(1 == check_pool_and_waste(half_pool, empty_waste));
  assert(1 == check_pool_and_waste(half_pool, one_card_waste));
  assert(0 == check_pool_and_waste(half_pool, full_waste));
  assert(0 == check_pool_and_waste(full_pool, half_waste));

  free(half_waste);
  free(half_pool);
  free(one_turned_card_waste);
  free(one_turned_card_pool);
  free(one_card_waste);
  free(one_card_pool);
  free(full_waste);
  free(full_pool);
  free(empty_pool);
  free(empty_waste);





}

void test_check_stacks_cards() {
  TEST_DESCRIPTION("Stacks without the bottom 'no_value' card are invalid");
  const card no_card[] = {};

  struct s_stack *invalid_stacks = utl_create_stacks(
    no_card, 0,
    no_card, 0,
    no_card, 0,
    no_card, 0
  );

  assert(0 == check_stacks_cards(invalid_stacks));

  TEST_DESCRIPTION("Empty stacks (with the no_value card at bottom) are valid");
  const card bottom_card_only[] = {
    __CARTE(no_value, spade),
    __CARTE(no_value, heart),
    __CARTE(no_value, diamond),
    __CARTE(no_value, club)
  };

  struct s_stack *stacks = utl_create_stacks(
    bottom_card_only, 1,
    bottom_card_only+1, 1,
    bottom_card_only+2, 1,
    bottom_card_only+3, 1
  );

  struct s_stack *spade_stack   = stacks;
  struct s_stack *heart_stack   = stacks+1;
  struct s_stack *diamond_stack = stacks+2;
  struct s_stack *club_stack    = stacks+3;

  assert(1 == check_stacks_cards(stacks));

  TEST_DESCRIPTION("Even if cards are valid, if the number of cards is 0, the check should fail");
  stacks[0].placed = 0;
  assert(0 == check_stacks_cards(stacks));
  stacks[0].placed = 1;
  stacks[1].placed = 0;
  assert(0 == check_stacks_cards(stacks));
  stacks[1].placed = 1;
  stacks[2].placed = 0;
  assert(0 == check_stacks_cards(stacks));
  stacks[2].placed = 1;
  stacks[3].placed = 0;
  assert(0 == check_stacks_cards(stacks));
  stacks[3].placed = 1;

  TEST_DESCRIPTION("Empty stacks (with the no_value card at bottom) are valid (AGAIN)");
  assert(1 == check_stacks_cards(stacks));

  TEST_DESCRIPTION("Putting cards of the wrong suit in a stack is not allowed");
  utl_set_cards_of((struct s_zone *) spade_stack, bottom_card_only+1, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) spade_stack, bottom_card_only+2, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) spade_stack, bottom_card_only+3, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) spade_stack, bottom_card_only, 1);
  assert(1 == check_stacks_cards(stacks));

  utl_set_cards_of((struct s_zone *) heart_stack, bottom_card_only+2, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) heart_stack, bottom_card_only+3, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) heart_stack, bottom_card_only+0, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) heart_stack, bottom_card_only+1, 1);
  assert(1 == check_stacks_cards(stacks));

  utl_set_cards_of((struct s_zone *) diamond_stack, bottom_card_only+3, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) diamond_stack, bottom_card_only+0, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) diamond_stack, bottom_card_only+1, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) diamond_stack, bottom_card_only+2, 1);
  assert(1 == check_stacks_cards(stacks));

  utl_set_cards_of((struct s_zone *) club_stack, bottom_card_only+0, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) club_stack, bottom_card_only+1, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) club_stack, bottom_card_only+2, 1);
  assert(0 == check_stacks_cards(stacks));
  utl_set_cards_of((struct s_zone *) club_stack, bottom_card_only+3, 1);
  assert(1 == check_stacks_cards(stacks));

  TEST_DESCRIPTION("Full stack with the appropriate families are ok");
  const card all_cards[56] = {
    __CARTE(no_value,spade),
    __CARTE(ace,spade),
    __CARTE(two,spade),
    __CARTE(three,spade),
    __CARTE(four,spade),
    __CARTE(five,spade),
    __CARTE(six,spade),
    __CARTE(seven,spade),
    __CARTE(eight,spade),
    __CARTE(nine,spade),
    __CARTE(ten,spade),
    __CARTE(jack,spade),
    __CARTE(queen,spade),
    __CARTE(king,spade),
    __CARTE(no_value,heart),
    __CARTE(ace,heart),
    __CARTE(two,heart),
    __CARTE(three,heart),
    __CARTE(four,heart),
    __CARTE(five,heart),
    __CARTE(six,heart),
    __CARTE(seven,heart),
    __CARTE(eight,heart),
    __CARTE(nine,heart),
    __CARTE(ten,heart),
    __CARTE(jack,heart),
    __CARTE(queen,heart),
    __CARTE(king,heart),
    __CARTE(no_value,diamond),
    __CARTE(ace,diamond),
    __CARTE(two,diamond),
    __CARTE(three,diamond),
    __CARTE(four,diamond),
    __CARTE(five,diamond),
    __CARTE(six,diamond),
    __CARTE(seven,diamond),
    __CARTE(eight,diamond),
    __CARTE(nine,diamond),
    __CARTE(ten,diamond),
    __CARTE(jack,diamond),
    __CARTE(queen,diamond),
    __CARTE(king,diamond),
    __CARTE(no_value,club),
    __CARTE(ace,club),
    __CARTE(two,club),
    __CARTE(three,club),
    __CARTE(four,club),
    __CARTE(five,club),
    __CARTE(six,club),
    __CARTE(seven,club),
    __CARTE(eight,club),
    __CARTE(nine,club),
    __CARTE(ten,club),
    __CARTE(jack,club),
    __CARTE(queen,club),
    __CARTE(king,club),
  };


  utl_set_cards_of((struct s_zone *) spade_stack,   all_cards, 14);
  utl_set_cards_of((struct s_zone *) heart_stack,   all_cards+14, 14);
  utl_set_cards_of((struct s_zone *) diamond_stack, all_cards+28, 14);
  utl_set_cards_of((struct s_zone *) club_stack,    all_cards+42, 14);

  assert(1 == check_stacks_cards(stacks));

  TEST_DESCRIPTION("Stack with cards not in ascending order are not allowed");

  spade_stack->cards[5].value = nine;
  assert(0 == check_stacks_cards(stacks));
  spade_stack->cards[5].value = five;
  assert(1 == check_stacks_cards(stacks));

  heart_stack->cards[0].value = ~no_value;
  assert(0 == check_stacks_cards(stacks));
  heart_stack->cards[0].value = no_value;
  assert(1 == check_stacks_cards(stacks));

  diamond_stack->cards[13].value = ace;
  assert(0 == check_stacks_cards(stacks));
  diamond_stack->cards[13].value = king;
  assert(1 == check_stacks_cards(stacks));

  club_stack->cards[10].value = -ten;
  assert(0 == check_stacks_cards(stacks));
  club_stack->cards[10].value = ten;
  assert(1 == check_stacks_cards(stacks));

  free(stacks);
  free(invalid_stacks);
}

void test_check_pile_cards() {
  TEST_DESCRIPTION("Empty piles are allowed");
  card no_card[] = {};

  struct s_piles* piles = utl_create_piles(
    no_card, 0,
    no_card, 0,
    no_card, 0,
    no_card, 0,
    no_card, 0,
    no_card, 0,
    no_card, 0
  );

  assert(1 == check_piles_cards(piles));

  TEST_DESCRIPTION("Only a specific amount of turned cards is allowed in each pile");

  card turned_cards[] = {
    __CARTE(~three,heart),
    __CARTE(~two,spade),
    __CARTE(~ten,diamond),
    __CARTE(~eight,club),
    __CARTE(~two,club),
    __CARTE(~jack,spade),
    __CARTE(~five,heart)
  };
  card other_turned_cards[] = {
    __CARTE(~king,spade),
    __CARTE(~four,club),
    __CARTE(~six,heart),
    __CARTE(~six,diamond),
    __CARTE(~four,heart),
    __CARTE(~eight,diamond),
  };

  utl_set_cards_of((struct s_zone *) piles,   turned_cards, 0);
  utl_set_cards_of((struct s_zone *) (piles+1), turned_cards, 1);
  utl_set_cards_of((struct s_zone *) (piles+2), turned_cards, 2);
  utl_set_cards_of((struct s_zone *) (piles+3), turned_cards, 3);
  utl_set_cards_of((struct s_zone *) (piles+4), turned_cards, 4);
  utl_set_cards_of((struct s_zone *) (piles+5), turned_cards, 5);
  utl_set_cards_of((struct s_zone *) (piles+6), turned_cards, 6);

  assert(1 == check_piles_cards(piles));

  for (unsigned int p = 0; p < 7; p++) {
    utl_set_cards_of((struct s_zone *) (piles+p), turned_cards, p+1);
    assert(0 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), other_turned_cards, p);
    assert(1 == check_piles_cards(piles));
  }

  TEST_DESCRIPTION("Piles with only one face up card are valid");

  card one_card[] = {
    __CARTE(five, spade)
  };

  for (unsigned int p = 0; p < 7; p++) {
    utl_set_cards_of((struct s_zone *) (piles+p), one_card, 1);
    assert(1 == check_piles_cards(piles));
  }

  TEST_DESCRIPTION("Face up cards must be in descending order, alternate colors");
  TEST_ADDED_INFOS("A single faced up card can follow any turned cards without problems");
  card turned_cards_bad_suit[] = {
    __CARTE(~king,spade),
    __CARTE(~jack,heart),
    __CARTE(~nine,club),
    __CARTE(~three,club),
    __CARTE(~five,diamond),
    __CARTE(~queen,diamond),
    __CARTE(nine,diamond),
    __CARTE(eight,heart),
  };

  card turned_face_up_turned[] = {
    __CARTE(~king,spade),
    __CARTE(~jack,heart),
    __CARTE(~nine,club),
    __CARTE(~three,club),
    __CARTE(~five,diamond),
    __CARTE(~queen,diamond),
    __CARTE(nine,diamond),
    __CARTE(~seven,club),
  };

  card turned_cards_good_suit[] = {
    __CARTE(~king,spade),
    __CARTE(~jack,heart),
    __CARTE(~nine,club),
    __CARTE(~three,club),
    __CARTE(~five,diamond),
    __CARTE(~queen,diamond),
    __CARTE(nine,diamond),
    __CARTE(eight,club),
  };

  for (unsigned int p = 0; p < 7; p++) {
    utl_set_cards_of((struct s_zone *) (piles+p), turned_cards_bad_suit+(6-p), 2+p);
    assert(0 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), turned_cards_bad_suit+(6-p), 1+p);
    assert(1 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), turned_face_up_turned+(6-p), 2+p);
    assert(0 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), turned_face_up_turned+(6-p), 1+p);
    assert(1 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), turned_cards_good_suit+(6-p), 2+p);
    assert(1 == check_piles_cards(piles));
  }

  card bad_card[] = {
    __CARTE(38, 26),
    __CARTE(27, spade),
    __CARTE(eight, 5)
  };

  for (unsigned int p = 0; p < 7; p++) {
    utl_set_cards_of((struct s_zone *) (piles+p), bad_card, 1);
    assert(0 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), bad_card+1, 1);
    assert(0 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), bad_card+2, 1);
    assert(0 == check_piles_cards(piles));
  }

  card bad_turned_card[] = {
    __CARTE(~45, 87),
    __CARTE(~14, heart),
    __CARTE(~two, -1)
  };

  for (unsigned int p = 1; p < 7; p++) {
    utl_set_cards_of((struct s_zone *) (piles+p), bad_turned_card, 1);
    assert(0 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), bad_turned_card+1, 1);
    assert(0 == check_piles_cards(piles));
    utl_set_cards_of((struct s_zone *) (piles+p), bad_turned_card+2, 1);
    assert(0 == check_piles_cards(piles));
  }

  free(piles);
}

void test_check_all_cards_unique() {
  TEST_DESCRIPTION("If all cards are unique, check_all_cards must return 1");

  struct s_klondike_elements *test_elements =
    (struct s_klondike_elements *) malloc(sizeof(struct s_klondike_elements));

  struct s_zone* zones[] = {
    (struct s_zone *) &(test_elements->pool),
    (struct s_zone *) &(test_elements->waste),
    (struct s_zone *)   test_elements->stack,
    (struct s_zone *)  (test_elements->stack+1),
    (struct s_zone *)  (test_elements->stack+2),
    (struct s_zone *)  (test_elements->stack+3),
    (struct s_zone *)   test_elements->piles,
    (struct s_zone *)  (test_elements->piles+1),
    (struct s_zone *)  (test_elements->piles+2),
    (struct s_zone *)  (test_elements->piles+3),
    (struct s_zone *)  (test_elements->piles+4),
    (struct s_zone *)  (test_elements->piles+5),
    (struct s_zone *)  (test_elements->piles+6)
  };

  utl_empty_elements(test_elements);

  card temp_deck[DECK_SIZE] = {
    __CARTE(ace,spade),   __CARTE(two,spade),   __CARTE(three,spade),
    __CARTE(four,spade),  __CARTE(five,spade),  __CARTE(six,spade),
    __CARTE(seven,spade), __CARTE(eight,spade), __CARTE(nine,spade),
    __CARTE(ten,spade),   __CARTE(jack,spade),  __CARTE(queen,spade),
    __CARTE(king,spade),
    __CARTE(ace,heart),   __CARTE(two,heart),   __CARTE(three,heart),
    __CARTE(four,heart),  __CARTE(five,heart),  __CARTE(six,heart),
    __CARTE(seven,heart), __CARTE(eight,heart), __CARTE(nine,heart),
    __CARTE(ten,heart),   __CARTE(jack,heart),  __CARTE(queen,heart),
    __CARTE(king,heart),
    __CARTE(ace,diamond),   __CARTE(two,diamond),   __CARTE(three,diamond),
    __CARTE(four,diamond),  __CARTE(five,diamond),  __CARTE(six,diamond),
    __CARTE(seven,diamond), __CARTE(eight,diamond), __CARTE(nine,diamond),
    __CARTE(ten,diamond),   __CARTE(jack,diamond),  __CARTE(queen,diamond),
    __CARTE(king,diamond),
    __CARTE(ace,club),   __CARTE(two,club),   __CARTE(three,club),
    __CARTE(four,club),  __CARTE(five,club),  __CARTE(six,club),
    __CARTE(seven,club), __CARTE(eight,club), __CARTE(nine,club),
    __CARTE(ten,club),   __CARTE(jack,club),  __CARTE(queen,club),
    __CARTE(king,club)
  };

  distribute_deck(temp_deck, test_elements);
  assert(1 == check_all_cards_unique(zones));

  TEST_DESCRIPTION("If there's doubles, check_all_cards_unique should return 0");


  int8_t original_value = temp_deck[5].value;
  temp_deck[5].value = ace;

  utl_empty_elements(test_elements);
  distribute_deck(temp_deck, test_elements);
  assert(0 == check_all_cards_unique(zones));

  temp_deck[5].value = original_value;

  utl_empty_elements(test_elements);
  distribute_deck(temp_deck, test_elements);
  assert(1 == check_all_cards_unique(zones));

  TEST_DESCRIPTION("If there's not enough cards, checkk_all_cards_unique should return 0");

  utl_empty_elements(test_elements);
  distribute_deck(temp_deck, test_elements);
  utl_set_cards_of((struct s_zone *) &(test_elements->pool), temp_deck, 0);
  assert(0 == check_all_cards_unique(zones));

  TEST_DESCRIPTION("If there's invalid values, check_all_cards_unique should return 0");
  original_value = temp_deck[27].value;
  temp_deck[27].value = 39;

  utl_empty_elements(test_elements);
  distribute_deck(temp_deck, test_elements);
  assert(0 == check_all_cards_unique(zones));

  temp_deck[27].value = original_value;

  utl_empty_elements(test_elements);
  distribute_deck(temp_deck, test_elements);
  assert(1 == check_all_cards_unique(zones));

  original_value = temp_deck[51].suit;
  temp_deck[51].suit = -78;

  utl_empty_elements(test_elements);
  distribute_deck(temp_deck, test_elements);
  assert(0 == check_all_cards_unique(zones));

  temp_deck[51].suit = original_value;

  utl_empty_elements(test_elements);
  distribute_deck(temp_deck, test_elements);
  assert(1 == check_all_cards_unique(zones));

  free(test_elements);
}

void test_check_load_and_save() {
  TEST_DESCRIPTION("Saving and loading a simple game should work");
  struct s_klondike_elements *test_elements =
    (struct s_klondike_elements *) malloc(sizeof(struct s_klondike_elements));

  card temp_deck[DECK_SIZE] = {
    __CARTE(ace,spade),   __CARTE(two,spade),   __CARTE(three,spade),
    __CARTE(four,spade),  __CARTE(five,spade),  __CARTE(six,spade),
    __CARTE(seven,spade), __CARTE(eight,spade), __CARTE(nine,spade),
    __CARTE(ten,spade),   __CARTE(jack,spade),  __CARTE(queen,spade),
    __CARTE(king,spade),
    __CARTE(ace,heart),   __CARTE(two,heart),   __CARTE(three,heart),
    __CARTE(four,heart),  __CARTE(five,heart),  __CARTE(six,heart),
    __CARTE(seven,heart), __CARTE(eight,heart), __CARTE(nine,heart),
    __CARTE(ten,heart),   __CARTE(jack,heart),  __CARTE(queen,heart),
    __CARTE(king,heart),
    __CARTE(ace,diamond),   __CARTE(two,diamond),   __CARTE(three,diamond),
    __CARTE(four,diamond),  __CARTE(five,diamond),  __CARTE(six,diamond),
    __CARTE(seven,diamond), __CARTE(eight,diamond), __CARTE(nine,diamond),
    __CARTE(ten,diamond),   __CARTE(jack,diamond),  __CARTE(queen,diamond),
    __CARTE(king,diamond),
    __CARTE(ace,club),   __CARTE(two,club),   __CARTE(three,club),
    __CARTE(four,club),  __CARTE(five,club),  __CARTE(six,club),
    __CARTE(seven,club), __CARTE(eight,club), __CARTE(nine,club),
    __CARTE(ten,club),   __CARTE(jack,club),  __CARTE(queen,club),
    __CARTE(king,club)
  };

  struct s_zone *test_zones[] = {
    (struct s_zone *) &(test_elements->pool),
    (struct s_zone *) &(test_elements->waste),
    (struct s_zone *)   test_elements->stack,
    (struct s_zone *)  (test_elements->stack+1),
    (struct s_zone *)  (test_elements->stack+2),
    (struct s_zone *)  (test_elements->stack+3),
    (struct s_zone *)   test_elements->piles,
    (struct s_zone *)  (test_elements->piles+1),
    (struct s_zone *)  (test_elements->piles+2),
    (struct s_zone *)  (test_elements->piles+3),
    (struct s_zone *)  (test_elements->piles+4),
    (struct s_zone *)  (test_elements->piles+5),
    (struct s_zone *)  (test_elements->piles+6)
  };

  utl_empty_elements(test_elements);
  distribute_deck(temp_deck, test_elements);
  uint8_t *buffer = malloc(228);
  assert(228 == save_state(test_zones, buffer));

  struct s_klondike_elements *empty_elements =
    (struct s_klondike_elements *) malloc(sizeof(struct s_klondike_elements));
  struct s_klondike_elements *target_elements =
    (struct s_klondike_elements *) malloc(sizeof(struct s_klondike_elements));

  utl_empty_elements(target_elements);

  assert(1 == load_state(target_elements, buffer, empty_elements));

  assert(0 == memcmp(test_elements, target_elements, sizeof(struct s_klondike_elements)));
  free(target_elements);
  free(empty_elements);
  free(buffer);
  free(test_elements);
}

/* The load mechanism must do the following :
 * - Check if the data are valid
 * - Check if the data refers to a valid game
 * - Load the game
 * Checking if any data is valid implies :
 * - Checking if provided zones are valid
 * - Checking if provided cards are valid
 * Checking if the game is valid implies :
 * - Only 52 cards loaded. No more, no less.
 *  - Trick cards are not saved
 * - All the cards are unique
 * - No returned cards are placed in the pool, the
 *   waste and the stacks.
 * - Checking that all zones have not too much cards
 * - Checking that there's only (pile n - 1) returned cards in piles.
 * - Checking that cards in stack are of the right suit and in
 *   ascending order.
 * - Checking that returned cards in piles are of the right suit
 *   and in descending order.
 * Load the game implies that :
 * - s_klondike_elements contains the 52 card loaded correctly.
 *
 * load_data still expects that the data are correctly terminated.
 */

/* Save data format :
 * Header :
 * [     8 bits     | 8 bits | 8 bits | 8 bits ]
 * [ Cards in waste | unused | unused | unused ]
 * ------------------
 * Body :
 * [ 8 bits  |   8 bits   |  8 bits   | 8 bits  ]
 * [ Zone id | card value | card suit | padding ] * 52
 * Total : 212 bytes
 */

int main() {
  test_check_pool_and_waste();
  test_check_stacks_cards();
  test_check_pile_cards();
  test_check_all_cards_unique();
  test_check_load_and_save();
}
