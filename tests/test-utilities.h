#include <cards_logic/basics.h>
#include <cards_logic/klondike.h>
#include <helpers/log.h>

#include <assert.h>

#include <stdlib.h>

#define TEST_DESCRIPTION(description) LOG("\n\n### %s\n", description)
#define TEST_ADDED_INFOS(infos) LOG("## %s\n", infos)

char *families_symbols[255] = {
  "🂠", "♠", "♡", "♣", "♢", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
  "?", "?", "?", "?", "?", "?", "?", "?"
};

void utl_select_and_deselect
(struct s_zone *zone, enum zones zone_type, struct s_selection* selection) {
  start_selection_from(zone, zone_type, selection);
  assert(selection->done == 1);
  remove_selection(selection);
  assert(selection->done == 0);

  LOG("Selected and deselected zone : %d\n", zone_type);
}

struct s_selection * utl_create_selection() {
  struct s_selection *new_selection = malloc(sizeof(struct s_selection));
  new_selection->zone = 0;
  new_selection->done = 0;
  new_selection->move_only_top_card = 0;

  assert(new_selection->zone == 0);
  assert(new_selection->done == 0);
  assert(new_selection->move_only_top_card == 0);

  LOG("New selection created.\n");

  return new_selection;
}


void utl_set_cards_of(struct s_zone* zone, const card *cards, unsigned int placed) {
  card *zone_cards = (card *) &(zone->cards);

  for (unsigned int c = 0; c < placed; c++) zone_cards[c] = cards[c];

  for (unsigned int c = 0; c < placed; c++) {
    assert(zone_cards[c].suit == cards[c].suit);
    assert(zone_cards[c].value  == cards[c].value);
    LOG("[Card %2d] %2d%s\n", c, cards[c].value, families_symbols[cards[c].suit]);
  }
  LOG("[%d Cards set]\n", placed);
  zone->placed = placed;
}

void utl_prepare_zone
(struct s_zone* zone, const card *cards, unsigned int placed, unsigned int max) {

  zone->max     = max;
  utl_set_cards_of(zone, cards, placed);
  assert(zone->placed == placed);
  assert(zone->max     == max);
}

#define GENERATOR_HEADER(type) LOG("[utl_create_"type"] Generating "type" with %d cards\n", placed)

struct s_pool* utl_create_pool(card *cards, unsigned int placed) {
  GENERATOR_HEADER("pool");
  struct s_pool* pool = malloc(sizeof(struct s_pool));
  utl_prepare_zone((struct s_zone *) pool, cards, placed, placed);
  return pool;
}

struct s_waste* utl_create_waste(card *cards, unsigned int placed) {
  GENERATOR_HEADER("waste");

  struct s_waste* waste = malloc(sizeof(struct s_waste));
  utl_prepare_zone((struct s_zone *) waste, cards, placed, MAX_CARDS_PER_DRAW);
  return waste;
}

struct s_piles* utl_create_pile(card *cards, unsigned int placed) {
  GENERATOR_HEADER("pile");
  struct s_piles* pile = malloc(sizeof(struct s_piles));
  utl_prepare_zone((struct s_zone *) pile, cards, placed, MAX_CARDS_PER_PILE);
  return pile;
}

struct s_stack* utl_create_stack(card *cards, unsigned int placed) {
  GENERATOR_HEADER("stack");
  struct s_stack* stack = malloc(sizeof(struct s_stack));
  utl_prepare_zone((struct s_zone *) stack, cards, placed, REMAINING_DECK);
  return stack;
}

struct s_stack* utl_create_stacks
(const card *spade_cards, const unsigned int spades,
 const card *heart_cards, const unsigned int hearts,
 const card *diamond_cards, const unsigned int diamonds,
 const card *club_cards, const unsigned clubs) {
  LOG("[utl_create_stacks] Generating 4 stacks with :\n"
      "  ♠ : %d cards\n"
      "  ♡ : %d cards\n"
      "  ♢ : %d cards\n"
      "  ♣ : %d cards\n",
      spades, hearts, diamonds, clubs);

  struct s_stack* stacks = malloc(sizeof(struct s_stack)*4);
  utl_prepare_zone((struct s_zone *)  stacks, spade_cards, spades, MAX_CARDS_PER_STACK);
  utl_prepare_zone((struct s_zone *) (stacks+1), heart_cards, hearts, MAX_CARDS_PER_STACK);
  utl_prepare_zone((struct s_zone *) (stacks+2), diamond_cards, diamonds, MAX_CARDS_PER_STACK);
  utl_prepare_zone((struct s_zone *) (stacks+3), club_cards, clubs, MAX_CARDS_PER_STACK);
  return stacks;
}

struct s_piles* utl_create_piles
(const card *pile1, const unsigned int pile1_cards,
 const card *pile2, const unsigned int pile2_cards,
 const card *pile3, const unsigned int pile3_cards,
 const card *pile4, const unsigned int pile4_cards,
 const card *pile5, const unsigned int pile5_cards,
 const card *pile6, const unsigned int pile6_cards,
 const card *pile7, const unsigned int pile7_cards) {

  struct s_piles* piles = malloc(sizeof(struct s_piles)*7);

  utl_prepare_zone((struct s_zone *) (piles),   pile1, pile1_cards, MAX_CARDS_PER_PILE);
  utl_prepare_zone((struct s_zone *) (piles+1), pile2, pile2_cards, MAX_CARDS_PER_PILE);
  utl_prepare_zone((struct s_zone *) (piles+2), pile3, pile3_cards, MAX_CARDS_PER_PILE);
  utl_prepare_zone((struct s_zone *) (piles+3), pile4, pile4_cards, MAX_CARDS_PER_PILE);
  utl_prepare_zone((struct s_zone *) (piles+4), pile5, pile5_cards, MAX_CARDS_PER_PILE);
  utl_prepare_zone((struct s_zone *) (piles+5), pile6, pile6_cards, MAX_CARDS_PER_PILE);
  utl_prepare_zone((struct s_zone *) (piles+6), pile7, pile7_cards, MAX_CARDS_PER_PILE);
  return piles;
}

void utl_reset_selection(struct s_selection *selection) {
  selection->zone = selection->done = selection->move_only_top_card = 0;

  assert(selection->zone == 0);
  assert(selection->done == 0);
  assert(selection->move_only_top_card == 0);
}


void utl_empty_elements(struct s_klondike_elements *elements) {
  memset(elements, 0, sizeof(struct s_klondike_elements));
  card stacks_cards[] = {
    __CARTE(no_value, spade),
    __CARTE(no_value, heart),
    __CARTE(no_value, diamond),
    __CARTE(no_value, club)
  };
  utl_set_cards_of((struct s_zone *)  elements->stack,    stacks_cards,   1);
  utl_set_cards_of((struct s_zone *) (elements->stack+1), stacks_cards+1, 1);
  utl_set_cards_of((struct s_zone *) (elements->stack+2), stacks_cards+2, 1);
  utl_set_cards_of((struct s_zone *) (elements->stack+3), stacks_cards+3, 1);
}

void assert_zone_cards(struct s_zone *zone, card *cards, unsigned int n_cards) {

  card *zone_cards = (card *) &(zone->cards);
  for (unsigned int c = 0; c < n_cards; c++) {
    assert( SAME_CARDS(zone_cards[c], cards[c]) );
    LOG("[P Card %d] %2d %s <-> ", c, zone_cards[c].value, families_symbols[zone_cards[c].suit]);
    LOG("[C Card %d] %2d %s\n", c, cards[c].value, families_symbols[cards[c].suit]);
  }
  if (n_cards < zone->placed) {
    LOG("Superfluous cards !!\n");
    for (unsigned int c = n_cards; c < zone->placed; c++) {
      LOG("[O Card %d] %2d %s\n", c, zone_cards[c].value, families_symbols[zone_cards[c].suit]);
    }
  }
  assert(zone->placed == n_cards);
}

void assert_reverse_zone_cards
(struct s_zone *zone, card *cards,
 unsigned int n_cards, unsigned int total_cards) {
  card *zone_cards = (card *) &(zone->cards);
  int z_c = 0,
      cards_c = total_cards - 1;
  for (z_c = 0; z_c < n_cards; z_c++, cards_c--) {

    LOG("[P Card %d] %2d %s <-> ", z_c, zone_cards[z_c].value, families_symbols[zone_cards[z_c].suit]);
    LOG("[C Card %d] %2d %s\n", cards_c, cards[cards_c].value, families_symbols[cards[cards_c].suit]);
    assert( SAME_CARDS(zone_cards[z_c], cards[cards_c]) );
  }
  if (n_cards < zone->placed) {
    LOG("Superfluous cards !!\n");
    for (unsigned int c = n_cards; c < zone->placed; c++) {
      LOG("[O Card %d] %2d %s\n", c, zone_cards[c].value, families_symbols[zone_cards[c].suit]);
    }
  }
  assert(zone->placed == n_cards);
}

void assert_pool_cards
(struct s_pool *pool, card *cards, unsigned int n_cards, unsigned int max) {
  LOG("Checking pool cards... %2d (%2d) cards (max : %2d)\n",
       n_cards, pool->placed, max);
  assert_zone_cards((struct s_zone *) pool, cards, n_cards);
}
void assert_pile_cards(struct s_piles *pile, card *cards, unsigned int n_cards) {
  LOG("Checking pile with... %2d (%2d) cards\n", n_cards, pile->placed);
  assert_zone_cards((struct s_zone *) pile, cards, n_cards);
}
void assert_waste_cards(struct s_waste *waste, card *cards, unsigned int n_cards) {
  LOG("Checking waste with... %2d (%2d) cards\n", n_cards, waste->placed);
  assert_zone_cards((struct s_zone *) waste, cards, n_cards);
}

void assert_waste_cards_inverse_of
(struct s_waste *waste, card *cards, unsigned int n_cards, unsigned int total_cards) {
  LOG("Checking waste with... %2d (%2d) cards\n", n_cards, waste->placed);
  assert_reverse_zone_cards((struct s_zone *) waste, cards, n_cards, total_cards);
}

void assert_stack_cards(struct s_stack *stack, card *cards, unsigned int n_cards) {
  LOG("Checking stack with... %2d (%2d) cards\n", n_cards, stack->placed);
  assert_zone_cards((struct s_zone *) stack, cards, n_cards);
}

unsigned int select_src_then_dst
(struct s_zone* src, struct s_zone* dst, enum zones src_type, enum zones dst_type,
 struct s_selection* selection) {
  start_selection_from(src, src_type, selection);
  return move_selected_cards_to(dst, dst_type, selection);
}

unsigned int utl_move_from_pile_to_pile
(struct s_piles* src, struct s_piles* dst, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) src, (struct s_zone *) dst,
    zone_pile, zone_pile, selection
  );
}

unsigned int utl_move_from_pile_to_stack
(struct s_piles* pile, struct s_stack* stack, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) pile, (struct s_zone *) stack, zone_pile, zone_stack,
    selection
  );
}

unsigned int utl_move_from_waste_to_pile
(struct s_waste* waste, struct s_piles* pile, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) waste, (struct s_zone *) pile,
    zone_waste, zone_pile, selection
  );
 }

unsigned int utl_move_from_waste_to_stack
(struct s_waste* waste, struct s_stack* stack, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) waste, (struct s_zone *) stack, zone_waste, zone_stack,
    selection
  );
}

unsigned int utl_move_from_stack_to_pile
(struct s_stack* stack, struct s_piles *pile, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) stack, (struct s_zone *) pile, zone_stack, zone_pile,
    selection
  );
}

void game_won() {}
