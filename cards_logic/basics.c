#include <cards_logic/basics.h>
#include <helpers/log.h>

#include <string.h> // memcpy
#include <stdlib.h> // random
#include <time.h>

struct s_selection selection = {
  .zone = 0,
  .done = 0,
  .move_only_top_card = 0
};

void print_deck(card *deck_to_print, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    LOG("[Card %d] Family : %d, Value : %d\n", i,
        deck_to_print[i].suit, deck_to_print[i].value);
  }
}

void shuffled_deck_from_base_deck
(card *deck, const card *base_deck,
 unsigned int deck_size, unsigned int passes) {

  memcpy(deck, base_deck, sizeof(card)*deck_size);

  /* rand works "as intended" on Android, which mean it always provides
   * the same random values if you do not set the seed.
   * This is BRILLIANT !
   * Every time I ask for a random value, I want to receive the same
   * value as the other time ! Of course !
   */

  // Garbage : The best source of entropy ! © HopunEshEshEll
  // If you're a package maintainer, please don't initialise this.
  volatile unsigned int garbage_entropy;
  srand(garbage_entropy + (unsigned int) time((time_t *) NULL));

  while(passes--) {
    for (int n = 0; n < deck_size; n++) {
      unsigned int random_i = (unsigned int) (rand() % deck_size);
      card swapped = deck[random_i];
      deck[random_i] = deck[n];
      deck[n] = swapped;
    }
  }
}

unsigned int distribute_n_cards_from_deck
(unsigned int cursor, unsigned int n, struct s_zone *zone, card *src) {
  /*LOG("start from : %d, n : %d\n", cursor, n);*/
  card *dst = zone->cards;
  for (unsigned int i = 0; i < n; i++, cursor++) dst[i] = src[cursor];
  zone->placed += n;
  /*LOG("Distributed %d cards\n", n);
  LOG("Cards in zone : %d\n", zone->placed);
  LOG("Destination deck :\n");*/
  print_deck(dst, n);
  return cursor;
}

void turn_cards_face_down(unsigned int n, card *pile) {
  for (unsigned int card_i = 0; card_i < n; card_i++)
    if(IS_FACE_UP(pile[card_i])) TURN_CARD(pile[card_i]);
}
