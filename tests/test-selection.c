// Tester le système de sélection !

#include <cards_logic/basics.h>
#include <cards_logic/klondike.h>
#include <helpers/log.h>
#include <tests/test-utilities.h>

#include <assert.h>

#include <stdlib.h>

void test_selection() {
  struct s_selection *my_selection = utl_create_selection();

  card standard_cards[] = {
    __CARTE(two, heart), __CARTE(three, spade), __CARTE(four, diamond)
  };
  card standard_stack_cards[] = {
    __CARTE(no_value, club), // Card trick...
    __CARTE(ace, club),
    __CARTE(two, club),
    __CARTE(three, club)
  };

  struct s_waste *test_waste = utl_create_waste(standard_cards, 3);
  struct s_piles *test_pile = utl_create_pile(standard_cards, 3);
  struct s_stack *test_stack = utl_create_stack(standard_stack_cards, 4);

  TEST_DESCRIPTION("Testing selecting cards from the waste");
  start_selection_from((struct s_zone *) test_waste, zone_waste, my_selection);
  assert(my_selection->zone == (struct s_zone *) test_waste);
  assert(my_selection->done == 1);
  assert(my_selection->move_only_top_card == 1);
  utl_reset_selection(my_selection);

  TEST_DESCRIPTION("Testing selecting cards from the stack");
  start_selection_from((struct s_zone *) test_stack, zone_stack, my_selection);
  assert(my_selection->zone == (struct s_zone *) test_stack);
  assert(my_selection->done == 1);
  assert(my_selection->move_only_top_card == 1);
  utl_reset_selection(my_selection);

  TEST_DESCRIPTION("Testing selecting cards from piles");
  start_selection_from((struct s_zone *) test_pile, zone_pile, my_selection);
  assert(my_selection->zone == (struct s_zone *) test_pile);
  assert(my_selection->done == 1);
  assert(my_selection->move_only_top_card == 0);
  utl_reset_selection(my_selection);

  free(my_selection);
  free(test_waste);
  free(test_pile);
  free(test_stack);

  LOG("OK !\n");
}

void test_remove_selection() {
  struct s_selection *my_selection = utl_create_selection();

  card standard_cards[] = {
    __CARTE(two, heart), __CARTE(three, spade), __CARTE(four, diamond)
  };
  card standard_stack_cards[] = {
    __CARTE(no_value, club), // Card trick...
    __CARTE(ace, club),
    __CARTE(two, club),
    __CARTE(three, club)
  };
  struct s_waste *test_waste = utl_create_waste(standard_cards, 3);
  struct s_piles *test_pile = utl_create_pile(standard_cards, 3);
  struct s_stack *test_stack = utl_create_stack(standard_stack_cards, 4);

  utl_select_and_deselect((struct s_zone *) test_waste, zone_waste, my_selection);
  utl_select_and_deselect((struct s_zone *) test_stack, zone_stack, my_selection);
  utl_select_and_deselect((struct s_zone *) test_pile, zone_pile, my_selection);

  // Already deselected
  remove_selection(my_selection);
  assert(my_selection->done == 0);

  free(my_selection);
  free(test_waste);
  free(test_pile);
  free(test_stack);

  LOG("OK !\n");
}

void test_move_pile_to_pile() {

  TEST_DESCRIPTION("Moving a king between empty piles");
  struct s_selection *new_selection = utl_create_selection();

  card first_set[] = { __CARTE(king, spade) };
  //LOG("King : %d - Spade : %d\n", king, spade);
  struct s_piles *first_pile = utl_create_pile(first_set, 1);
  struct s_piles *second_pile = utl_create_pile(0, 0);

  assert(1 == utl_move_from_pile_to_pile(first_pile, second_pile, new_selection));

  assert(first_pile->placed == 0);
  assert_pile_cards(second_pile, first_set, 1);

  assert(1 == utl_move_from_pile_to_pile(second_pile, first_pile, new_selection));

  assert(second_pile->placed == 0);
  assert_pile_cards(first_pile, first_set, 1);

  free(first_pile);
  free(second_pile);

  /*-----*/
  TEST_DESCRIPTION("Moving a King pile to another empty pile");
  card second_set[] = {
    __CARTE(king, spade), __CARTE(queen, diamond), __CARTE(jack, club),
    __CARTE(ten, heart)
  };

  first_pile = utl_create_pile(second_set, 4);
  second_pile = utl_create_pile(0, 0);

  assert(4 == utl_move_from_pile_to_pile(first_pile, second_pile, new_selection));

  assert(first_pile->placed == 0);
  assert_pile_cards(second_pile, second_set, 4);

  assert(4 == utl_move_from_pile_to_pile(second_pile, first_pile, new_selection));

  assert(second_pile->placed == 0);
  assert_pile_cards(first_pile, second_set, 4);

  free(first_pile);
  free(second_pile);

  /*------*/
  TEST_DESCRIPTION("Moving a King suite below turned cards to an empty pile");
  TEST_ADDED_INFOS("The moved pile cannot return below the turned cards");
  card third_set[] = {
    __TURNED_CARD(ace, heart), __TURNED_CARD(six, heart),
    __CARTE(king, club), __CARTE(queen, heart), __CARTE(jack, club)
  };

  first_pile = utl_create_pile(third_set, 5);
  second_pile = utl_create_pile(0, 0);

  assert(3 == utl_move_from_pile_to_pile(first_pile, second_pile, new_selection));

  assert_pile_cards(first_pile, third_set, 2);
  assert_pile_cards(second_pile, third_set+2, 3);

  // Move not possible since the top card is returned
  assert(0 == utl_move_from_pile_to_pile(second_pile, first_pile, new_selection));

  assert_pile_cards(first_pile, third_set, 2);
  assert_pile_cards(second_pile, third_set+2, 3);

  free(first_pile);
  free(second_pile);

  TEST_DESCRIPTION("Cannot move a card below another valid but turned card");
  TEST_ADDED_INFOS("Once the turned card is face up, the move is allowed");
  card fourth_set_first_pile[]  = { __TURNED_CARD(five, heart) };
  card fourth_set_second_pile[] = { __CARTE(four, spade) };
  card fourth_set_after_turn_result[] = {
    __CARTE(five, heart),
    __CARTE(four, spade)
  };

  first_pile = utl_create_pile(fourth_set_first_pile, 1);
  second_pile = utl_create_pile(fourth_set_second_pile, 1);

  // That CANNOT happen. Clicking turned cards should put them face up !
  // Still checking, just in case...
  assert(0 == utl_move_from_pile_to_pile(first_pile, second_pile, new_selection));

  assert_pile_cards(first_pile, fourth_set_first_pile, 1);
  assert_pile_cards(second_pile, fourth_set_second_pile, 1);

  // Not possible, the Five of heart is still turned
  assert(0 == utl_move_from_pile_to_pile(second_pile, first_pile, new_selection));

  assert_pile_cards(first_pile, fourth_set_first_pile, 1);
  assert_pile_cards(second_pile, fourth_set_second_pile, 1);

  TURN_CARD(first_pile->cards[0]);
  assert(1 == utl_move_from_pile_to_pile(second_pile, first_pile, new_selection));

  assert_pile_cards(first_pile, fourth_set_after_turn_result, 2);
  assert(second_pile->placed == 0);

  free(first_pile);
  free(second_pile);

  TEST_DESCRIPTION("Testing one card move between almost full piles");
  TEST_ADDED_INFOS("The pile receiving the card becomes full");
  card sixth_set_first_pile[] = {
    __TURNED_CARD(jack, heart),
    __TURNED_CARD(seven, heart),
    __TURNED_CARD(eight, club),
    __TURNED_CARD(four, spade),
    __TURNED_CARD(nine, diamond),
    __TURNED_CARD(four, club),
    __CARTE(king, spade),
    __CARTE(queen, heart),
    __CARTE(jack, spade),
    __CARTE(ten, heart),
    __CARTE(nine, club),
    __CARTE(eight, heart),
    __CARTE(seven, spade),
    __CARTE(six, diamond),
    __CARTE(five, spade),
    __CARTE(four, diamond),
    __CARTE(three, spade),
    __CARTE(two, heart),
    __CARTE(ace, spade)
  };

  card sixth_set_second_pile[] = {
    __TURNED_CARD(two, spade),
    __TURNED_CARD(five, spade),
    __TURNED_CARD(nine, club),
    __TURNED_CARD(two, club),
    __TURNED_CARD(ace, heart),
    __CARTE(king, club),
    __CARTE(queen, diamond),
    __CARTE(jack, club),
    __CARTE(ten, diamond),
    __CARTE(nine, spade),
    __CARTE(eight, diamond),
    __CARTE(seven, club),
    __CARTE(six, heart),
    __CARTE(five, club),
    __CARTE(four, heart),
    __CARTE(three, club),
    __CARTE(two, diamond)
  };
  card sixth_set_second_pile_after_move[] = {
    __TURNED_CARD(two, spade),
    __TURNED_CARD(five, spade),
    __TURNED_CARD(nine, club),
    __TURNED_CARD(two, club),
    __TURNED_CARD(ace, heart),
    __CARTE(king, club),
    __CARTE(queen, diamond),
    __CARTE(jack, club),
    __CARTE(ten, diamond),
    __CARTE(nine, spade),
    __CARTE(eight, diamond),
    __CARTE(seven, club),
    __CARTE(six, heart),
    __CARTE(five, club),
    __CARTE(four, heart),
    __CARTE(three, club),
    __CARTE(two, diamond),
    __CARTE(ace, spade)
  };

  first_pile = utl_create_pile(sixth_set_first_pile, 19);
  second_pile = utl_create_pile(sixth_set_second_pile, 17);

  assert(1 == utl_move_from_pile_to_pile(first_pile, second_pile, new_selection));

  assert_pile_cards(first_pile, sixth_set_first_pile, 18);
  assert_pile_cards(second_pile, sixth_set_second_pile_after_move, 18);

  assert(0 == utl_move_from_pile_to_pile(first_pile, second_pile, new_selection));

  assert_pile_cards(first_pile, sixth_set_first_pile, 18);
  assert_pile_cards(second_pile, sixth_set_second_pile_after_move, 18);

  assert(1 == utl_move_from_pile_to_pile(second_pile, first_pile, new_selection));

  assert_pile_cards(first_pile, sixth_set_first_pile, 19);
  assert_pile_cards(second_pile, sixth_set_second_pile, 17);
  LOG("OK !\n");
}

void test_move_waste_to_pile() {
  struct s_selection *selection = utl_create_selection();

  card first_waste[] = {
    __CARTE(ace, diamond), __CARTE(four, spade), __CARTE(king, diamond)
  };
  card first_pile_after_move[] = {
    __CARTE(king, diamond)
  };

  TEST_DESCRIPTION("Valid moves from the waste to empty piles are OK");
  struct s_piles *pile = utl_create_pile(0,0);
  struct s_waste *waste = utl_create_waste(first_waste, 3);

  assert(1 == utl_move_from_waste_to_pile(waste, pile, selection));

  assert_pile_cards(pile, first_pile_after_move, 1);
  assert_waste_cards(waste, first_waste, 2);

  // This is not possible. You must not be able to put cards back in the waste.
  // The only exception will be cancel moves, once implemented.
  start_selection_from((struct s_zone *) pile, zone_pile, selection);
  assert(0 == move_selected_cards_to((struct s_zone *) waste, zone_waste, selection));

  assert_pile_cards(pile, first_pile_after_move, 1);
  assert_waste_cards(waste, first_waste, 2);

  remove_selection(selection);
  free(waste);
  free(pile);

  TEST_DESCRIPTION("Waste -> Pile : Move only one card a at a time");
  card second_waste[] = {
    __CARTE(six, club), __CARTE(seven, heart), __CARTE(eight, spade)
  };
  card second_pile[] = {
    __CARTE(nine, heart)
  };
  card second_pile_after_all_moves[] = {
    __CARTE(nine, heart),
    __CARTE(eight, spade),
    __CARTE(seven, heart),
    __CARTE(six, club)
  };

  waste = utl_create_waste(second_waste, 3);
  pile = utl_create_pile(second_pile, 1);

  for (unsigned int c = 0; c < 3; c++) {
    assert(1 == utl_move_from_waste_to_pile(waste, pile, selection));

    assert_waste_cards(waste, second_waste, 2-c);
    assert_pile_cards(pile, second_pile_after_all_moves, 2+c);
  }

  remove_selection(selection);
  free(waste);
  free(pile);

  TEST_DESCRIPTION("Waste -> Pile : Invalid moves are not allowed");
  card third_waste[] = { __CARTE(seven, heart) };

  card third_bad_pile_turned[] = { __TURNED_CARD(eight, club) };
  card third_bad_pile[] = { __CARTE(eight, heart) };
  card third_bad_full_pile[] = {
    __TURNED_CARD(jack, diamond),
    __TURNED_CARD(seven, heart),
    __TURNED_CARD(eight, club),
    __TURNED_CARD(four, spade),
    __TURNED_CARD(nine, diamond),
    __TURNED_CARD(four, club),
    __CARTE(king, spade),
    __CARTE(queen, heart),
    __CARTE(jack, spade),
    __CARTE(ten, heart),
    __CARTE(nine, club),
    __CARTE(eight, heart),
    __CARTE(seven, spade),
    __CARTE(six, diamond),
    __CARTE(five, spade),
    __CARTE(four, diamond),
    __CARTE(three, spade),
    __CARTE(two, heart),
    __CARTE(ace, spade)
  };

  waste = utl_create_waste(third_waste, 1);
  pile  = utl_create_pile(third_bad_pile_turned, 1);

  assert(0 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards(waste, third_waste, 1);
  assert_pile_cards(pile, third_bad_pile_turned, 1);

  free(pile);

  pile = utl_create_pile(third_bad_pile, 1);

  assert(0 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards(waste, third_waste, 1);
  assert_pile_cards(pile, third_bad_pile, 1);

  free(pile);

  pile = utl_create_pile(third_bad_full_pile, 19);

  assert(0 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards(waste, third_waste, 1);
  assert_pile_cards(pile, third_bad_full_pile, 19);

  free(selection);
  free(waste);
  free(pile);
}

void test_move_card_to_stack() {
  card waste_cards[] = {
    __CARTE(two, diamond), __CARTE(ace, club), __CARTE(ace, diamond)
  };
  card diamond_stack_cards[] = {
    __CARTE(no_value, diamond)
  };
  card club_stack_cards[] = {
    __CARTE(no_value, club)
  };
  card pile_cards[] = {
    __TURNED_CARD(three, club),
    __CARTE(three, diamond),
    __CARTE(two, club)
  };

  card final_diamond_stack_cards[] = {
    __CARTE(no_value, diamond),
    __CARTE(ace, diamond),
    __CARTE(two, diamond),
    __CARTE(three, diamond)
  };

  card final_club_stack_cards[] = {
    __CARTE(no_value, club),
    __CARTE(ace, club),
    __CARTE(two, club),
    __CARTE(three, club)
  };

  struct s_selection* selection = utl_create_selection();
  struct s_waste* waste      = utl_create_waste(waste_cards, 3);
  struct s_stack* diamond_stack = utl_create_stack(diamond_stack_cards, 1);
  struct s_stack* club_stack    = utl_create_stack(club_stack_cards, 1);
  struct s_piles* pile         = utl_create_pile(pile_cards, 3);

  TEST_DESCRIPTION("Move the ace of diamond to the diamond stack - Must work");
  assert(1 == utl_move_from_waste_to_stack(waste, diamond_stack, selection));
  assert_waste_cards(waste, waste_cards, 2);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 2);
  assert_stack_cards(club_stack, club_stack_cards, 1);
  assert_pile_cards(pile, pile_cards, 3);

  TEST_DESCRIPTION("Move the ace of club to the diamond stack - Must NOT work");
  // Cards are unchanged
  assert(0 == utl_move_from_waste_to_stack(waste, diamond_stack, selection));
  assert_waste_cards(waste, waste_cards, 2);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 2);
  assert_stack_cards(club_stack, club_stack_cards, 1);
  assert_pile_cards(pile, pile_cards, 3);

  TEST_DESCRIPTION("Move the ace of club to the club stack - Must work");
  assert(1 == utl_move_from_waste_to_stack(waste, club_stack, selection));
  assert_waste_cards(waste, waste_cards, 1);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 2);
  assert_stack_cards(club_stack, final_club_stack_cards, 2);
  assert_pile_cards(pile, pile_cards, 3);

  TEST_DESCRIPTION("Move the two of diamond to the club stack - Must NOT work");
  assert(0 == utl_move_from_waste_to_stack(waste, club_stack, selection));
  assert_waste_cards(waste, waste_cards, 1);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 2);
  assert_stack_cards(club_stack, final_club_stack_cards, 2);
  assert_pile_cards(pile, pile_cards, 3);

  TEST_DESCRIPTION("Move the two of diamond to the diamond stack - Must work");
  assert(1 == utl_move_from_waste_to_stack(waste, diamond_stack, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 3);
  assert_stack_cards(club_stack, final_club_stack_cards, 2);
  assert_pile_cards(pile, pile_cards, 3);

  TEST_DESCRIPTION("Move the two of club from the pile to the diamond stack - Must NOT work");
  assert(0 == utl_move_from_pile_to_stack(pile, diamond_stack, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 3);
  assert_stack_cards(club_stack, final_club_stack_cards, 2);
  assert_pile_cards(pile, pile_cards, 3);

  TEST_DESCRIPTION("Move the two of club from the pile to the club stack - Must work");
  assert(1 == utl_move_from_pile_to_stack(pile, club_stack, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 3);
  assert_stack_cards(club_stack, final_club_stack_cards, 3);
  assert_pile_cards(pile, pile_cards, 2);

  TEST_DESCRIPTION("Move the two of club back to the pile - Must work");
  assert(1 == utl_move_from_stack_to_pile(club_stack, pile, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 3);
  assert_stack_cards(club_stack, final_club_stack_cards, 2);
  assert_pile_cards(pile, pile_cards, 3);

  TEST_DESCRIPTION("Move the two of club back to the club stack - Must work again");
  assert(1 == utl_move_from_pile_to_stack(pile, club_stack, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 3);
  assert_stack_cards(club_stack, final_club_stack_cards, 3);
  assert_pile_cards(pile, pile_cards, 2);

  TEST_DESCRIPTION("Move the two of diamond from the diamond stack to the pile - Must NOT work");
  assert(0 == utl_move_from_stack_to_pile(diamond_stack, pile, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 3);
  assert_stack_cards(club_stack, final_club_stack_cards, 3);
  assert_pile_cards(pile, pile_cards, 2);

  TEST_DESCRIPTION("Move the three of diamond from the pile to the diamond stack - Must work");
  assert(1 == utl_move_from_pile_to_stack(pile, diamond_stack, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 4);
  assert_stack_cards(club_stack, final_club_stack_cards, 3);
  assert_pile_cards(pile, pile_cards, 1);

  TEST_DESCRIPTION("Move the three of diamond back to the stack - Must NOT work");
  TEST_ADDED_INFOS("The remaining card is turned and also not the next ascending value");
  assert(0 == utl_move_from_stack_to_pile(diamond_stack, pile, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 4);
  assert_stack_cards(club_stack, final_club_stack_cards, 3);
  assert_pile_cards(pile, pile_cards, 1);

  // Impossible move
  TEST_DESCRIPTION("Move the turned three of club to the club stack - Must NOT work");
  assert(0 == utl_move_from_pile_to_stack(pile, club_stack, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 4);
  assert_stack_cards(club_stack, final_club_stack_cards, 3);
  assert_pile_cards(pile, pile_cards, 1);

  TURN_CARD(pile->cards[0]);

  TEST_DESCRIPTION("Move the three of club to the club stack - Must work");
  assert(1 == utl_move_from_pile_to_stack(pile, club_stack, selection));
  assert_waste_cards(waste, waste_cards, 0);
  assert_stack_cards(diamond_stack, final_diamond_stack_cards, 4);
  assert_stack_cards(club_stack, final_club_stack_cards, 4);
  assert_pile_cards(pile, pile_cards, 0);

  free(waste);
  free(pile);
  free(diamond_stack);
  free(club_stack);

  TEST_DESCRIPTION("Selection test due to the card trick...");
  card empty_stack_cards[] = { __CARTE(no_value, spade) };

  struct s_stack *empty_stack = utl_create_stack(empty_stack_cards, 1);
  start_selection_from((struct s_zone *) empty_stack, zone_stack, selection);

  assert(selection->done == 0);

  free(empty_stack);
  remove_selection(selection);

  TEST_DESCRIPTION("Only check the top card when trying to move cards from a stack");

  card third_stack_cards[] = {
    __CARTE(no_value, heart),
    __CARTE(ace, heart),
    __CARTE(two, heart),
    __CARTE(three, heart),
    __CARTE(four, heart),
    __CARTE(five, heart)
  };
  card third_pile_one_cards[] = {
    __CARTE(five, spade)
  };
  card third_pile_one_cards_after_last_move[] = {
    __CARTE(five, spade),
    __CARTE(four, heart)
  };
  card third_pile_two_cards[] = {
    __CARTE(seven, diamond),
    __CARTE(six, spade)
  };
  card third_pile_two_cards_after_first_move[] = {
    __CARTE(seven, diamond),
    __CARTE(six, spade),
    __CARTE(five, heart)
  };


  struct s_stack* third_stack = utl_create_stack(third_stack_cards, 6);
  struct s_piles* third_pile_one = utl_create_pile(third_pile_one_cards, 1);
  struct s_piles* third_pile_two = utl_create_pile(third_pile_two_cards, 2);

  TEST_DESCRIPTION("Trying to move the 4 ♡ in the heart stack on the 5 ♠ - Must NOT work");
  TEST_ADDED_INFOS("The top card of the heart stack is the 5 ♡");
  assert(0 == utl_move_from_stack_to_pile(third_stack, third_pile_one, selection));
  assert_stack_cards(third_stack, third_stack_cards, 6);
  assert_pile_cards(third_pile_one, third_pile_one_cards, 1);
  assert_pile_cards(third_pile_two, third_pile_two_cards, 2);

  TEST_DESCRIPTION("Trying to move the 5 ♡ in the heart stack on the 6 ♠ - Must work");
  assert(1 == utl_move_from_stack_to_pile(third_stack, third_pile_two, selection));
  assert_stack_cards(third_stack, third_stack_cards, 5);
  assert_pile_cards(third_pile_one, third_pile_one_cards, 1);
  assert_pile_cards(third_pile_two, third_pile_two_cards_after_first_move, 3);
  TEST_ADDED_INFOS("The top card of the heart stack is now the 4 ♡");

  TEST_DESCRIPTION("Trying to move the 4 ♡ in the heart stack on the 5 ♠ again - Must work this time");
  assert(1 == utl_move_from_stack_to_pile(third_stack, third_pile_one, selection));
  assert_stack_cards(third_stack, third_stack_cards, 4);
  assert_pile_cards(third_pile_one, third_pile_one_cards_after_last_move, 2);
  assert_pile_cards(third_pile_two, third_pile_two_cards_after_first_move, 3);

  TEST_DESCRIPTION("Putting the 4 ♡ back in the stack - Must work");
  assert(1 == utl_move_from_pile_to_stack(third_pile_one, third_stack, selection));
  assert_stack_cards(third_stack, third_stack_cards, 5);
  assert_pile_cards(third_pile_one, third_pile_one_cards, 1);
  assert_pile_cards(third_pile_two, third_pile_two_cards_after_first_move, 3);

  TEST_DESCRIPTION("Putting the 5 ♡ back in the stack - Must work");
  assert(1 == utl_move_from_pile_to_stack(third_pile_two, third_stack, selection));
  assert_stack_cards(third_stack, third_stack_cards, 6);
  assert_pile_cards(third_pile_one, third_pile_one_cards, 1);
  assert_pile_cards(third_pile_two, third_pile_two_cards, 2);

  free(third_stack);
  free(selection);
}

extern struct s_klondike_elements klondike_elements;
extern card base_deck[], deck[];
void test_state_after_distribute_deck() {
  TEST_DESCRIPTION("Deck distribution");
  generate_new_deck(deck, base_deck, DECK_SIZE, SHUFFLE_PASSES);
  distribute_deck(deck, &klondike_elements);
  TEST_DESCRIPTION("Checking the amount of cards in the pool and the waste");
  assert(klondike_elements.pool.placed == REMAINING_DECK);
  for (unsigned int c = 0; c < REMAINING_DECK; c++) {
    assert(klondike_elements.pool.cards[c].suit != no_suit &&
           klondike_elements.pool.cards[c].value  != no_value);
  }
  assert(klondike_elements.waste.placed == 0);

  TEST_DESCRIPTION("Checking cards in piles");
  for (unsigned int p = 0; p < 7; p++) {
    TEST_ADDED_INFOS("Checking the amount");
    struct s_piles pile = klondike_elements.piles[p];
    assert(pile.placed == p+1);

    TEST_ADDED_INFOS("Checking if all cards beside the top card are downturned");
    for (unsigned c = 0; c < p; c++) {
      LOG("[%d/%d] %2d %s - IS DOWNTURNED ? %d\n",
           c, p, pile.cards[c].value, families_symbols[pile.cards[c].suit],
           IS_FACE_DOWN(pile.cards[c]));
      assert(IS_FACE_DOWN(pile.cards[c]));
    }
    LOG("[%d/%d] %2d %s - IS DOWNTURNED ? %d\n",
         p, p, pile.cards[p].value, families_symbols[pile.cards[p].suit],
         IS_FACE_DOWN(pile.cards[p]));
  }

  TEST_DESCRIPTION("Checking cards in stacks");
  for (unsigned int s = 0; s < 4; s++) {
    TEST_ADDED_INFOS("Checking the amount");
    assert(klondike_elements.stack[s].placed == 1); // Card trick

    TEST_ADDED_INFOS("Checking the tricked card");
    card stack_top_card = klondike_elements.stack[s].cards[0];
    assert(stack_top_card.value  == no_value);
  }

  TEST_DESCRIPTION("Checking trick cards families");
  assert(klondike_elements.stack[0].cards[0].suit == spade);
  assert(klondike_elements.stack[1].cards[0].suit == heart);
  assert(klondike_elements.stack[2].cards[0].suit == diamond);
  assert(klondike_elements.stack[3].cards[0].suit == club);

  TEST_DESCRIPTION("Checking if every distributed card is unique");
  card distributed_deck[52] = {0};
  struct s_zone *distribution_zones[] = {
    (struct s_zone *) &(klondike_elements.pool),
    (struct s_zone *) (klondike_elements.piles+0),
    (struct s_zone *) (klondike_elements.piles+1),
    (struct s_zone *) (klondike_elements.piles+2),
    (struct s_zone *) (klondike_elements.piles+3),
    (struct s_zone *) (klondike_elements.piles+4),
    (struct s_zone *) (klondike_elements.piles+5),
    (struct s_zone *) (klondike_elements.piles+6)
  };

  for (unsigned int d = 0; d < 8; d++) {
    struct s_zone *current_zone = distribution_zones[d];
    card *zone_cards = (card *) &(current_zone->cards);
    for (unsigned c = 0; c < current_zone->placed; c++) {
      card current_card = zone_cards[c];
      assert(current_card.value != no_value && current_card.suit != no_suit);
      if (IS_FACE_DOWN(current_card)) TURN_CARD(current_card);

      unsigned int deck_i =
       ((current_card.suit - 1) * 13 + current_card.value - 1);
      LOG("[%d/%d] %2d %s : deck_i : %d\n",
          c, current_zone->placed, current_card.value, families_symbols[current_card.suit],
          deck_i);
      distributed_deck[deck_i] = current_card;
    }
  }
  print_deck(distributed_deck, 52);
  for (unsigned int f = 1; f < 5; f++) {
    for (unsigned int v = 1; v < 14; v++) {
      unsigned int deck_i = ((f - 1) * 13 + v - 1);
      assert(distributed_deck[deck_i].value == v);
      assert(distributed_deck[deck_i].suit == f);
    }
  }

}

void test_pool() {
  card pool_cards[] = {
    __CARTE(five, club),
    __CARTE(nine, spade), __CARTE(eight, diamond), __CARTE(jack, club),
    __CARTE(seven, spade), __CARTE(queen, spade), __CARTE(ten, diamond),
    __CARTE(queen, heart), __CARTE(seven, club), __CARTE(two, spade),
  };

  card pool_cards_after_first_move[] = {
    __CARTE(five, club),  __CARTE(nine, spade), __CARTE(eight, diamond),
    __CARTE(jack, club), __CARTE(seven, spade), __CARTE(queen, spade),
    __CARTE(ten, diamond), __CARTE(seven, club), __CARTE(two, spade)
  };
  card pool_cards_after_second_move[] = {
    __CARTE(five, club),  __CARTE(nine, spade),
    __CARTE(eight, diamond), __CARTE(seven, spade), __CARTE(queen, spade),
    __CARTE(ten, diamond), __CARTE(seven, club), __CARTE(two, spade),
  };
  card pool_cards_after_third_move[] = {
    __CARTE(five, club),
    __CARTE(nine, spade), __CARTE(eight, diamond), __CARTE(seven, spade),
    __CARTE(queen, spade), __CARTE(seven, club), __CARTE(two, spade)
  };
  card pool_cards_after_last_moves[] = {
    __CARTE(five, club),
    __CARTE(queen, spade), __CARTE(seven, club), __CARTE(two, spade)
  };
  card pile_cards[] = {
    __CARTE(king, spade)
  };
  card final_pile_cards[] = {
    __CARTE(king, spade),
    __CARTE(queen, heart),
    __CARTE(jack, club),
    __CARTE(ten, diamond),
    __CARTE(nine, spade),
    __CARTE(eight, diamond),
    __CARTE(seven, spade)
  };

  struct s_pool *pool    = utl_create_pool(pool_cards, 10);
  struct s_waste *waste = utl_create_waste(0, 0);
  struct s_piles *pile    = utl_create_pile(pile_cards, 1);
  struct s_selection *selection = utl_create_selection();

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards, 7, 10);
  assert_waste_cards_inverse_of(waste, pool_cards, 3, 10);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards, 4, 10);
  assert_waste_cards_inverse_of(waste, pool_cards, 6, 10);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards, 1, 10);
  assert_waste_cards_inverse_of(waste, pool_cards, 9, 10);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards, 0, 10);
  assert_waste_cards_inverse_of(waste, pool_cards, 10, 10);

  reset_pool(pool, waste);
  assert_pool_cards(pool, pool_cards, 10, 10);
  assert_waste_cards_inverse_of(waste, pool_cards, 0, 10);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards, 7, 10);
  assert_waste_cards_inverse_of(waste, pool_cards, 3, 10);

  assert(1 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards_inverse_of(waste, pool_cards_after_first_move, 2, 9);
  assert_pile_cards(pile, final_pile_cards, 2);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_first_move, 4, 10);
  assert_waste_cards_inverse_of(waste, pool_cards_after_first_move, 5, 9);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_first_move, 1, 10);
  assert_waste_cards_inverse_of(waste, pool_cards_after_first_move, 8, 9);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_first_move, 0, 10);
  assert_waste_cards_inverse_of(waste, pool_cards_after_first_move, 9, 9);

  reset_pool(pool, waste);
  assert_pool_cards(pool, pool_cards_after_first_move, 9, 9);
  assert_waste_cards_inverse_of(waste, pool_cards_after_first_move, 0, 9);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_first_move, 6, 9);
  assert_waste_cards_inverse_of(waste, pool_cards_after_first_move, 3, 9);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_first_move, 3, 9);
  assert_waste_cards_inverse_of(waste, pool_cards_after_first_move, 6, 9);

  assert(1 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards_inverse_of(waste, pool_cards_after_second_move, 5, 8);
  assert_pile_cards(pile, final_pile_cards, 3);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_second_move, 0, 9);
  assert_waste_cards_inverse_of(waste, pool_cards_after_second_move, 8, 8);

  reset_pool(pool, waste);
  assert_pool_cards(pool, pool_cards_after_second_move, 8, 8);
  assert_waste_cards_inverse_of(waste, pool_cards_after_second_move, 0, 8);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_second_move, 5, 8);
  assert_waste_cards_inverse_of(waste, pool_cards_after_second_move, 3, 8);

  assert(1 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 2, 7);
  assert_pile_cards(pile, final_pile_cards, 4);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_third_move, 2, 8);
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 5, 7);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_third_move, 0, 8);
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 7, 7);

  reset_pool(pool, waste);
  assert_pool_cards(pool, pool_cards_after_third_move, 7, 7);
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 0, 7);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_third_move, 4, 7);
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 3, 7);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_third_move, 1, 7);
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 6, 7);

  assert(1 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 5, 7);
  assert_pile_cards(pile, final_pile_cards, 5);

  assert(1 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 4, 7);
  assert_pile_cards(pile, final_pile_cards, 6);

  assert(1 == utl_move_from_waste_to_pile(waste, pile, selection));
  assert_waste_cards_inverse_of(waste, pool_cards_after_third_move, 3, 7);
  assert_pile_cards(pile, final_pile_cards, 7);

  draw_cards(3, pool, waste);
  assert_pool_cards(pool, pool_cards_after_third_move, 0, 7);
  assert_waste_cards_inverse_of(waste, pool_cards_after_last_moves, 4, 4);

  reset_pool(pool, waste);
  assert_pool_cards(pool, pool_cards_after_last_moves, 4, 4);
  assert_waste_cards_inverse_of(waste, pool_cards_after_last_moves, 0, 4);
}

int main() {
  test_selection();
  test_remove_selection();
  test_move_pile_to_pile();
  test_move_waste_to_pile();
  test_move_card_to_stack();
  test_state_after_distribute_deck();
  test_pool();
  return 0;
}
