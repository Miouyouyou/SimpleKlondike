#ifndef MYY_CARDS_LOGIC_KLONDIKE_H
#define MYY_CARDS_LOGIC_KLONDIKE_H 1

#include <cards_logic/basics.h>
#include <helpers/base_gl.h>

#define DECK_SIZE 52
#define CARDS_IN_TOTAL 56 // 52 + 4 trick cards due to stack tricks
#define SHUFFLE_PASSES 20
#define MAX_CARDS_PER_PILE 19 // Simple hard limit : 6 🂠 + Full suite (13 🃟)
#define MAX_CARDS_PER_STACK 14 // +1 : Stack holder as a Card trick
#define REMAINING_DECK 24
#define MAX_CARDS_PER_DRAW 1
#define PILES 7
#define VALID_ON_PILE(first_card, second_card) \
  (DIFFERENT_COLOR(first_card,second_card)) && \
  (NEXT_DESCENDING_VALUE(first_card,second_card))
#define POS_UPPER_ELEMENTS 81
#define POS_LOWER_ELEMENTS 0

#define POS_WASTE_OFFSET_X 4
#define POS_SUIT_OFFSET_Y -6

#define POS_DECK_X -102
#define POS_WASTE_X -70
#define POS_SPADE_STACK_X -13
#define POS_HEART_STACK_X 19
#define POS_DIAMOND_STACK_X 51
#define POS_CLUB_STACK_X 83

#define POS_SUIT_1 -102
#define POS_SUIT_2 -70
#define POS_SUIT_3 -38
#define POS_SUIT_4 -6
#define POS_SUIT_5 26
#define POS_SUIT_6 58
#define POS_SUIT_7 90


struct s_pool   {
  struct byte_point_2D position, cards_offsets;
  uint8_t placed, max; card cards[REMAINING_DECK];
};
struct s_waste {
  struct byte_point_2D position, cards_offsets;
  uint8_t placed, max; card cards[REMAINING_DECK];
};
struct s_stack      {
  struct byte_point_2D position, cards_offsets;
  uint8_t placed, max; card cards[MAX_CARDS_PER_STACK];
};
struct s_piles   {
  struct byte_point_2D position, cards_offsets;
  uint8_t placed, max; card cards[MAX_CARDS_PER_PILE];
};

struct s_klondike_elements {
 struct s_pool   pool;
 struct s_waste  waste;
 struct s_stack  stack[4];
 struct s_piles  piles[7];
};

enum e_klondike_elements {
  e_pool, e_waste, e_spade_stack, e_heart_stack,
  e_diamond_stack, e_club_stack, e_pile_1, e_pile_2, e_pile_3,
  e_pile_4, e_pile_5, e_pile_6, e_pile_7, n_game_elements
};

void klondike_reset_game_elements
(struct s_klondike_elements * const game_elements);

unsigned int add_card_to_stack
(struct s_zone* , struct s_zone*, struct s_selection* );
unsigned int add_card_to_pile
(struct s_zone* , struct s_zone*, struct s_selection* );

unsigned int draw_cards
(unsigned int const max_fished_cards,
 struct s_pool * restrict const pool,
 struct s_waste * restrict const waste);

unsigned int reset_pool
(struct s_pool * restrict const pool,
 struct s_waste * restrict const waste);

unsigned int pool_still_useful
(struct s_pool * restrict const pool,
 struct s_waste * restrict const waste,
 unsigned int const max_cards_per_draw);

void generate_new_deck();

unsigned int save_state
(const struct s_zone * const * const cards_zones,
 uint8_t * const buffer);

unsigned int load_state
(struct s_klondike_elements * const game_elements,
 const uint8_t * const buffer,
 struct s_klondike_elements * const temporary_elements);

unsigned int quick_move
(struct s_zone * const from_src,
 struct s_klondike_elements * const elements);

#endif
