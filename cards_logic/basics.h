#ifndef MYY_CARDS_LOGIC_BASICS_H
#define MYY_CARDS_LOGIC_BASICS_H 1

#include <stdint.h>
#include <helpers/base_gl.h>

#define IS_RED(card) card.suit & 1 == 1
#define IS_BLACK(card) card.suit & 1 == 0
#define TOP_CARD_IN(zone_ptr) zone_ptr->cards[zone_ptr->placed-1]
#define SAME_COLOR(first_card, second_card) (first_card.suit & 1) == (second_card.suit & 1)
#define SAME_FAMILY(first_card, second_card) (first_card.suit == second_card.suit)
#define DIFFERENT_COLOR(first_card, second_card) (first_card.suit & 1) != (second_card.suit & 1)
#define NEXT_DESCENDING_VALUE(first_card, second_card) first_card.value == (second_card.value + 1)
#define NEXT_ASCENDING_VALUE(first_card, second_card) (first_card.value + 1) == second_card.value
#define SAME_VALUE(first_card, second_card) (first_card.value == second_card.value)
#define SAME_CARDS(first_card, second_card) SAME_VALUE(first_card, second_card) && SAME_FAMILY(first_card, second_card)
#define IS_FACE_DOWN(card_struct) card_struct.value < 0
#define IS_FACE_UP(card_struct) card_struct.value >= 0
#define TURN_CARD(card_struct) card_struct.value = ~(card_struct.value)
#define BLANK_CARD(card_struct) card_struct.value = no_value; card_struct.suit = no_suit
#define IS_BLANK_CARD(card_struct) (card_struct.value == no_value && card_struct.suit == no_suit)
#define IS_NOT_BLANK_CARD(card_struct) (card_struct.value != no_value || card_struct.suit != no_suit)
#define VALID_FACE_UP_CARD(card_struct) (card_struct.value > no_value && \
  card_struct.value < last_cards_values && \
  card_struct.suit > no_suit && \
  card_struct.suit < last_cards_families)
#define VALID_FACE_DOWN_CARD(card_struct) (card_struct.value < ~no_value && \
  card_struct.value > ~last_cards_values && \
  card_struct.suit > no_suit && \
  card_struct.suit < last_cards_families)

enum cards_families {
  no_suit, spade, heart, club, diamond, last_cards_families
};
enum cards_values {
  no_value, ace, two, three, four, five, six, seven, eight, nine, ten,
  jack, queen, king, last_cards_values
};
struct s_card { int8_t value; uint8_t suit; }
((__packed__)) __attribute__((aligned(2)));
typedef struct s_card card;
#define __CARTE(card_value,card_suit) {.value = (int8_t) card_value, .suit = (uint8_t) card_suit}
#define __TURNED_CARD(card_value,card_suit) {.value = (int8_t) ~card_value, .suit = (uint8_t) card_suit}


struct s_zone {
  struct byte_point_2D position, cards_offsets;
  uint8_t placed, max; card cards[];
};
enum zones { zone_deck, zone_waste, zone_stack, zone_pile, zone_unknown };
struct s_selection {
  struct s_zone *zone;
  uint8_t  done, move_only_top_card;
};

struct s_selection* start_selection_from
(struct s_zone *card_zone, enum zones zone, struct s_selection* selection);
unsigned int move_selected_cards_to
(struct s_zone *new_zone, enum zones type, struct s_selection* selection);
void remove_selection(struct s_selection* );

void check_if_won();
void game_won();

void print_deck(card *deck_to_print, unsigned int n);
void shuffled_deck_from_base_deck
(card *deck, const card *base_deck,
 unsigned int deck_size, unsigned int passes);
unsigned int distribute_n_cards_from_deck
(unsigned int start_from, unsigned int n, struct s_zone *zone, card *src);
void distribute_deck();

void turn_cards_face_down(unsigned int n, card *pile);

#endif
