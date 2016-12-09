#include <cards_logic/basics.h>
#include <cards_logic/klondike.h>
#include <tests/test-utilities.h>
#include <assert.h>

void test_quickmove() {
  struct s_klondike_elements *test_elements =
    malloc(sizeof(struct s_klondike_elements));
  utl_empty_elements(test_elements);
  card test_waste[] = {
    __CARTE(five, spade),
    __CARTE(ace, heart),
    __CARTE(ace, spade)
  };
  card test_pile1[] = {
    __CARTE(three, heart),
    __CARTE(two, spade)
  };
  card test_pile2[] = {
    __CARTE(three, spade),
    __CARTE(two, heart)
  };

  card test_spade_stack[] = {
    __CARTE(no_value, spade),
    __CARTE(ace, spade),
    __CARTE(two, spade),
    __CARTE(three, spade)
  };

  card test_heart_stack[] = {
    __CARTE(no_value, heart),
    __CARTE(ace, heart),
    __CARTE(two, heart),
    __CARTE(three, heart)
  };


  TEST_DESCRIPTION("Quick-move to stacks automatically work with aces\n");
  TEST_ADDED_INFOS("Quick-move with other cards only work if there's "
                   "the corresponding preceding card in the appropriate "
                   "stack ");
  utl_set_cards_of((struct s_zone *) &test_elements->waste, test_waste, 3);
  utl_set_cards_of((struct s_zone *) &test_elements->piles[0], test_pile1, 2);
  utl_set_cards_of((struct s_zone *) &test_elements->piles[1], test_pile2, 2);

  assert_pile_cards(&test_elements->piles[0], test_pile1, 2);
  assert_pile_cards(&test_elements->piles[1], test_pile2, 2);
  assert_waste_cards(&test_elements->waste, test_waste, 3);
  assert_stack_cards(&test_elements->stack[0], test_spade_stack, 1);
  assert_stack_cards(&test_elements->stack[1], test_heart_stack, 1);
  LOG("test_elements->stack[0] address : %p\n", &test_elements->stack[0]);
  LOG("test_elements->stack[1] address : %p\n", &test_elements->stack[1]);

  TEST_ADDED_INFOS("Moving the A♠ of the waste to the ♠ stack with Quick-move");
  assert(0 == quick_move((struct s_zone *) &test_elements->piles[0], test_elements));
  assert_pile_cards(&test_elements->piles[0], test_pile1, 2);
  assert(0 == quick_move((struct s_zone *) &test_elements->piles[1], test_elements));
  assert_pile_cards(&test_elements->piles[1], test_pile2, 2);
  // Moving the A♠ from the waste to the ♠ stack
  assert(1 == quick_move((struct s_zone *) &test_elements->waste, test_elements));
  // Now, the ♠ stack has 2 cards (+1), the waste has 2 cards (-1)
  assert_waste_cards(&test_elements->waste, test_waste, 2);
  assert_stack_cards(&test_elements->stack[0], test_spade_stack, 2);
  assert_stack_cards(&test_elements->stack[1], test_heart_stack, 1);

  TEST_ADDED_INFOS("Moving the 2♠ of the first-pile to the ♠ stack with Quick-move");
  TEST_ADDED_INFOS("Moving the A♡ of the ♡ stack with Quick-move");
  // Moving the 2♠ from the first pile to the ♠ stack
  assert(1 == quick_move((struct s_zone *) &test_elements->piles[0], test_elements));
  // Now, the ♠ stack has 3 cards (+1), the first pile has 1 cards (-1)
  assert_pile_cards(&test_elements->piles[0], test_pile1, 1);
  assert_stack_cards(&test_elements->stack[0], test_spade_stack, 3);
  assert(0 == quick_move((struct s_zone *) &test_elements->piles[1], test_elements));
  assert_pile_cards(&test_elements->piles[1], test_pile2, 2);
  // Moving the A♡ from the waste to the ♡ stack
  assert(1 == quick_move((struct s_zone *) &test_elements->waste, test_elements));
  // Now, the ♡ stack has 2 cards (+1), the waste has 1 cards (-1)
  assert_waste_cards(&test_elements->waste, test_waste, 1);
  assert_stack_cards(&test_elements->stack[0], test_spade_stack, 3);
  assert_stack_cards(&test_elements->stack[1], test_heart_stack, 2);

  TEST_ADDED_INFOS("Moving the 3♠ of the first-pile to the ♠ stack with Quick-move");
  TEST_ADDED_INFOS("Moving the 2♡ of the ♡ stack with Quick-move");

  // Cannot move the 3 of heart as the 2 has not been placed yet
  assert(0 == quick_move((struct s_zone *) &test_elements->piles[0], test_elements));
  assert_pile_cards(&test_elements->piles[0], test_pile1, 1);

  // Moving the 2♡ from the second pile to the ♡ stack
  assert(1 == quick_move((struct s_zone *) &test_elements->piles[1], test_elements));
  // Now, the ♡ stack has 3 cards (+1), the second pile has 1 card (-1)
  assert_pile_cards(&test_elements->piles[1], test_pile2, 1);
  assert_stack_cards(&test_elements->stack[1], test_heart_stack, 3);

  // Moving the 3♠ from the second pile to the ♠ stack
  assert(1 == quick_move((struct s_zone *) &test_elements->piles[1], test_elements));
  // Now the ♠ stack has 4 cards (+1), the second pile has 0 card (-1)
  assert_pile_cards(&test_elements->piles[1], test_pile2, 0);
  assert_stack_cards(&test_elements->stack[0], test_spade_stack, 4);

  // Cannot move the 5 of spade as the 4 has not been placed yet
  assert(0 == quick_move((struct s_zone *) &test_elements->waste, test_elements));
  assert_waste_cards(&test_elements->waste, test_waste, 1);

  assert_waste_cards(&test_elements->waste, test_waste, 1);
  assert_pile_cards(&test_elements->piles[0], test_pile1, 1);
  assert_pile_cards(&test_elements->piles[1], test_pile2, 0);
  assert_stack_cards(&test_elements->stack[0], test_spade_stack, 4);
  assert_stack_cards(&test_elements->stack[1], test_heart_stack, 3);

  TEST_ADDED_INFOS("Moving the 3♡ of the first-pile to the ♡ stack with Quick-move");

  // Moving the 3♡ from the first pile to the ♡ stack
  assert(1 == quick_move((struct s_zone *) &test_elements->piles[0], test_elements));
  // Now, the ♡ stack has 4 cards (+1), the first pile has 0 card (-1)
  assert_stack_cards(&test_elements->stack[1], test_heart_stack, 4);
  assert_pile_cards(&test_elements->piles[0], test_pile1, 0);
  // Cannot move nothing from an empty pile
  assert(0 == quick_move((struct s_zone *) &test_elements->piles[0], test_elements));
  assert(0 == quick_move((struct s_zone *) &test_elements->piles[1], test_elements));
  assert_pile_cards(&test_elements->piles[0], test_pile1, 0);
  assert_pile_cards(&test_elements->piles[1], test_pile2, 0);
  // Cannot move the 5 of spade as the 4 has not been placed yet
  assert(0 == quick_move((struct s_zone *) &test_elements->waste, test_elements));
  assert_waste_cards(&test_elements->waste, test_waste, 1);

  assert_waste_cards(&test_elements->waste, test_waste, 1);
  assert_pile_cards(&test_elements->piles[0], test_pile1, 0);
  assert_pile_cards(&test_elements->piles[1], test_pile2, 0);
  assert_stack_cards(&test_elements->stack[0], test_spade_stack, 4);
  assert_stack_cards(&test_elements->stack[1], test_heart_stack, 4);
}

int main() {
  test_quickmove();
  return 0;
}
