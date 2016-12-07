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

void print_deck(carte *deck_to_print, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    LOG("[Card %d] Family : %d, Value : %d\n", i,
        deck_to_print[i].famille, deck_to_print[i].valeur);
  }
}

void shuffled_deck_from_base_deck
(carte *deck, const carte *base_deck,
 unsigned int deck_size, unsigned int passes) {

  memcpy(deck, base_deck, sizeof(carte)*deck_size);

  /* rand works "as intended" on Android, which mean it always provide
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
      carte swapped = deck[random_i];
      deck[random_i] = deck[n];
      deck[n] = swapped;
    }
  }
}

unsigned int distribute_n_cards_from_deck
(unsigned int cursor, unsigned int n, struct s_zone *zone, carte *src) {
  /*LOG("start from : %d, n : %d\n", cursor, n);*/
  carte *dst = zone->cartes;
  for (unsigned int i = 0; i < n; i++, cursor++) dst[i] = src[cursor];
  zone->placees += n;
  /*LOG("Distributed %d cards\n", n);
  LOG("Cards in zone : %d\n", zone->placees);
  LOG("Destination deck :\n");*/
  print_deck(dst, n);
  return cursor;
}

void turn_cards_face_down(unsigned int n, carte *pile) {
  for (unsigned int card_i = 0; card_i < n; card_i++)
    if(IS_FACE_UP(pile[card_i])) TURN_CARD(pile[card_i]);
}
