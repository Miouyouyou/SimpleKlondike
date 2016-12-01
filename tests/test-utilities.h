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


void utl_set_cards_of(struct s_zone* zone, const carte *cartes, unsigned int placees) {
  carte *zone_cards = (carte *) &(zone->cartes);

  for (unsigned int c = 0; c < placees; c++) zone_cards[c] = cartes[c];

  for (unsigned int c = 0; c < placees; c++) {
    assert(zone_cards[c].famille == cartes[c].famille);
    assert(zone_cards[c].valeur  == cartes[c].valeur);
    LOG("[Card %2d] %2d%s\n", c, cartes[c].valeur, families_symbols[cartes[c].famille]);
  }
  LOG("[%d Cards set]\n", placees);
  zone->placees = placees;
}

void utl_prepare_zone
(struct s_zone* zone, const carte *cartes, unsigned int placees, unsigned int max) {

  zone->max     = max;
  utl_set_cards_of(zone, cartes, placees);
  assert(zone->placees == placees);
  assert(zone->max     == max);
}

#define GENERATOR_HEADER(type) LOG("[utl_create_"type"] Generating "type" with %d cards\n", placees)

struct s_pioche* utl_create_pool(carte *cartes, unsigned int placees) {
  GENERATOR_HEADER("pool");
  struct s_pioche* pool = malloc(sizeof(struct s_pioche));
  utl_prepare_zone((struct s_zone *) pool, cartes, placees, placees);
  return pool;
}

struct s_piochees* utl_create_waste(carte *cartes, unsigned int placees) {
  GENERATOR_HEADER("waste");

  struct s_piochees* waste = malloc(sizeof(struct s_piochees));
  utl_prepare_zone((struct s_zone *) waste, cartes, placees, MAX_CARDS_IN_WASTE);
  return waste;
}

struct s_suites* utl_create_pile(carte *cartes, unsigned int placees) {
  GENERATOR_HEADER("pile");
  struct s_suites* pile = malloc(sizeof(struct s_suites));
  utl_prepare_zone((struct s_zone *) pile, cartes, placees, MAX_CARDS_PER_PILE);
  return pile;
}

struct s_tas* utl_create_stack(carte *cartes, unsigned int placees) {
  GENERATOR_HEADER("stack");
  struct s_tas* stack = malloc(sizeof(struct s_tas));
  utl_prepare_zone((struct s_zone *) stack, cartes, placees, REMAINING_DECK);
  return stack;
}

struct s_tas* utl_create_stacks
(const carte *spade_cards, const unsigned int spades,
 const carte *heart_cards, const unsigned int hearts,
 const carte *diamond_cards, const unsigned int diamonds,
 const carte *club_cards, const unsigned clubs) {
  LOG("[utl_create_stacks] Generating 4 stacks with :\n"
      "  ♠ : %d cards\n"
      "  ♡ : %d cards\n"
      "  ♢ : %d cards\n"
      "  ♣ : %d cards\n",
      spades, hearts, diamonds, clubs);

  struct s_tas* stacks = malloc(sizeof(struct s_tas)*4);
  utl_prepare_zone((struct s_zone *)  stacks, spade_cards, spades, MAX_CARDS_PER_STACK);
  utl_prepare_zone((struct s_zone *) (stacks+1), heart_cards, hearts, MAX_CARDS_PER_STACK);
  utl_prepare_zone((struct s_zone *) (stacks+2), diamond_cards, diamonds, MAX_CARDS_PER_STACK);
  utl_prepare_zone((struct s_zone *) (stacks+3), club_cards, clubs, MAX_CARDS_PER_STACK);
  return stacks;
}

struct s_suites* utl_create_piles
(const carte *pile1, const unsigned int pile1_cards,
 const carte *pile2, const unsigned int pile2_cards,
 const carte *pile3, const unsigned int pile3_cards,
 const carte *pile4, const unsigned int pile4_cards,
 const carte *pile5, const unsigned int pile5_cards,
 const carte *pile6, const unsigned int pile6_cards,
 const carte *pile7, const unsigned int pile7_cards) {

  struct s_suites* piles = malloc(sizeof(struct s_suites)*7);

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


void utl_empty_elements(struct s_elements_du_jeu *elements) {
  memset(elements, 0, sizeof(struct s_elements_du_jeu));
  carte stacks_cards[] = {
    __CARTE(no_value, spade),
    __CARTE(no_value, heart),
    __CARTE(no_value, diamond),
    __CARTE(no_value, club)
  };
  utl_set_cards_of((struct s_zone *)  elements->tas,    stacks_cards,   1);
  utl_set_cards_of((struct s_zone *) (elements->tas+1), stacks_cards+1, 1);
  utl_set_cards_of((struct s_zone *) (elements->tas+2), stacks_cards+2, 1);
  utl_set_cards_of((struct s_zone *) (elements->tas+3), stacks_cards+3, 1);
}

void assert_zone_cards(struct s_zone *zone, carte *cards, unsigned int n_cards) {

  carte *zone_cards = (carte *) &(zone->cartes);
  for (unsigned int c = 0; c < n_cards; c++) {
    assert( SAME_CARDS(zone_cards[c], cards[c]) );
    LOG("[P Card %d] %2d %s <-> ", c, zone_cards[c].valeur, families_symbols[zone_cards[c].famille]);
    LOG("[C Card %d] %2d %s\n", c, cards[c].valeur, families_symbols[cards[c].famille]);
  }
  if (n_cards < zone->placees) {
    LOG("Superfluous cards !!\n");
    for (unsigned int c = n_cards; c < zone->placees; c++) {
      LOG("[O Card %d] %2d %s\n", c, zone_cards[c].valeur, families_symbols[zone_cards[c].famille]);
    }
  }
  assert(zone->placees == n_cards);
}

void assert_reverse_zone_cards
(struct s_zone *zone, carte *cards,
 unsigned int n_cards, unsigned int total_cards) {
  carte *zone_cards = (carte *) &(zone->cartes);
  int z_c = 0,
      cartes_c = total_cards - 1;
  for (z_c = 0; z_c < n_cards; z_c++, cartes_c--) {

    LOG("[P Card %d] %2d %s <-> ", z_c, zone_cards[z_c].valeur, families_symbols[zone_cards[z_c].famille]);
    LOG("[C Card %d] %2d %s\n", cartes_c, cards[cartes_c].valeur, families_symbols[cards[cartes_c].famille]);
    assert( SAME_CARDS(zone_cards[z_c], cards[cartes_c]) );
  }
  if (n_cards < zone->placees) {
    LOG("Superfluous cards !!\n");
    for (unsigned int c = n_cards; c < zone->placees; c++) {
      LOG("[O Card %d] %2d %s\n", c, zone_cards[c].valeur, families_symbols[zone_cards[c].famille]);
    }
  }
  assert(zone->placees == n_cards);
}

void assert_pool_cards
(struct s_pioche *pool, carte *cards, unsigned int n_cards, unsigned int max) {
  LOG("Checking pool cards... %2d (%2d) cards (max : %2d)\n",
       n_cards, pool->placees, max);
  assert_zone_cards((struct s_zone *) pool, cards, n_cards);
  assert(pool->max == max);
}
void assert_pile_cards(struct s_suites *pile, carte *cards, unsigned int n_cards) {
  LOG("Checking pile with... %2d (%2d) cards\n", n_cards, pile->placees);
  assert_zone_cards((struct s_zone *) pile, cards, n_cards);
}
void assert_waste_cards(struct s_piochees *waste, carte *cards, unsigned int n_cards) {
  LOG("Checking waste with... %2d (%2d) cards\n", n_cards, waste->placees);
  assert_zone_cards((struct s_zone *) waste, cards, n_cards);
}

void assert_waste_cards_inverse_of
(struct s_piochees *waste, carte *cards, unsigned int n_cards, unsigned int total_cards) {
  LOG("Checking waste with... %2d (%2d) cards\n", n_cards, waste->placees);
  assert_reverse_zone_cards((struct s_zone *) waste, cards, n_cards, total_cards);
}

void assert_stack_cards(struct s_tas *tas, carte *cards, unsigned int n_cards) {
  LOG("Checking stack with... %2d (%2d) cards\n", n_cards, tas->placees);
  assert_zone_cards((struct s_zone *) tas, cards, n_cards);
}

unsigned int select_src_then_dst
(struct s_zone* src, struct s_zone* dst, enum zones src_type, enum zones dst_type,
 struct s_selection* selection) {
  start_selection_from(src, src_type, selection);
  return move_selected_cards_to(dst, dst_type, selection);
}

unsigned int utl_move_from_pile_to_pile
(struct s_suites* src, struct s_suites* dst, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) src, (struct s_zone *) dst,
    zone_pile, zone_pile, selection
  );
}

unsigned int utl_move_from_pile_to_stack
(struct s_suites* pile, struct s_tas* stack, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) pile, (struct s_zone *) stack, zone_pile, zone_stack,
    selection
  );
}

unsigned int utl_move_from_waste_to_pile
(struct s_piochees* waste, struct s_suites* pile, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) waste, (struct s_zone *) pile,
    zone_waste, zone_pile, selection
  );
 }

unsigned int utl_move_from_waste_to_stack
(struct s_piochees* waste, struct s_tas* stack, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) waste, (struct s_zone *) stack, zone_waste, zone_stack,
    selection
  );
}

unsigned int utl_move_from_stack_to_pile
(struct s_tas* stack, struct s_suites *pile, struct s_selection* selection) {
  return select_src_then_dst(
    (struct s_zone *) stack, (struct s_zone *) pile, zone_stack, zone_pile,
    selection
  );
}
