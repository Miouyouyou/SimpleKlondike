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
#define MAX_CARDS_IN_WASTE 1
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


struct s_pioche   {
  struct byte_point_2D position, cards_offsets; uint8_t animating;
  uint8_t placees, max; carte cartes[REMAINING_DECK];
};
struct s_piochees {
  struct byte_point_2D position, cards_offsets; uint8_t animating;
  uint8_t placees, max; carte cartes[REMAINING_DECK];
};
struct s_tas      {
  struct byte_point_2D position, cards_offsets; uint8_t animating;
  uint8_t placees, max; carte cartes[MAX_CARDS_PER_STACK];
};
struct s_suites   {
  struct byte_point_2D position, cards_offsets; uint8_t animating;
  uint8_t placees, max; carte cartes[MAX_CARDS_PER_PILE];
};

struct s_elements_du_jeu {
 struct s_pioche   pioche;
 struct s_piochees piochees;
 struct s_tas      tas[4];
 struct s_suites   suites[7];
};

enum e_elements_du_jeu {
  e_pool, e_waste, e_spade_stack, e_heart_stack,
  e_diamond_stack, e_club_stack, e_pile_1, e_pile_2, e_pile_3,
  e_pile_4, e_pile_5, e_pile_6, e_pile_7, n_game_elements
};

unsigned int add_card_to_stack
(struct s_zone* , struct s_zone*, struct s_selection* );
unsigned int add_card_to_pile
(struct s_zone* , struct s_zone*, struct s_selection* );

void put_waste_back_in_pool
(struct s_pioche *pioche, struct s_piochees *piochees);

unsigned int draw_cards
(unsigned int max_fished_cards, struct s_pioche *pioche,
 struct s_piochees *piochees);

unsigned int reset_pool
(struct s_pioche* pioche, struct s_piochees* piochees);

void generate_new_deck();

unsigned int save_state
(const struct s_zone * const * const cards_zones,
 uint8_t * const buffer);

unsigned int load_state
(struct s_elements_du_jeu * const game_elements,
 const uint8_t * const buffer,
 struct s_elements_du_jeu * const temporary_elements);

unsigned int quick_move
(struct s_zone * const from_src,
 struct s_elements_du_jeu * const elements);

#endif
