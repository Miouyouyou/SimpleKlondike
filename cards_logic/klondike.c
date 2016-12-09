#include <cards_logic/basics.h>
#include <cards_logic/klondike.h>

#include <helpers/log.h>
#include <opengl/menus.h>


struct s_klondike_elements klondike_elements = {
  .pool = {
    .position = {.x = POS_DECK_X, .y = POS_UPPER_ELEMENTS},
    .cards_offsets = {.x = 0, .y = 0},
    .placed = 0, .max = REMAINING_DECK, .cards = {0}
  },
  .waste = {
    .position = {.x = POS_WASTE_X, .y = POS_UPPER_ELEMENTS},
    .cards_offsets = {.x = POS_WASTE_OFFSET_X, .y = 0},
    .placed = 0, .max = REMAINING_DECK, .cards = {0}
  },
  .stack = {
    {
      .position = {.x = POS_SPADE_STACK_X, .y = POS_UPPER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = 0},
      .placed = 1, .max = MAX_CARDS_PER_STACK,
      .cards = {__CARTE(no_value, spade)}
    },
    {
      .position = {.x = POS_HEART_STACK_X, .y = POS_UPPER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = 0},
      .placed = 1, .max = MAX_CARDS_PER_STACK,
      .cards = {__CARTE(no_value, heart)}
    },
    {
      .position = {.x = POS_DIAMOND_STACK_X, .y = POS_UPPER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = 0},
      .placed = 1, .max = MAX_CARDS_PER_STACK,
      .cards = {__CARTE(no_value, diamond)}
    },
    {
      .position = {.x = POS_CLUB_STACK_X, .y = POS_UPPER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = 0},
      .placed = 1, .max = MAX_CARDS_PER_STACK,
      .cards = {__CARTE(no_value, club)}
    }
  },
  .piles = {
    {
      .position = {.x = POS_SUIT_1, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .placed = 0, .max = MAX_CARDS_PER_PILE, .cards = {0}
    },
    {
      .position = {.x = POS_SUIT_2, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .placed = 0, .max = MAX_CARDS_PER_PILE, .cards = {0}
    },
    {
      .position = {.x = POS_SUIT_3, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .placed = 0, .max = MAX_CARDS_PER_PILE, .cards = {0}
    },
    {
      .position = {.x = POS_SUIT_4, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .placed = 0, .max = MAX_CARDS_PER_PILE, .cards = {0}
    },
    {
      .position = {.x = POS_SUIT_5, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .placed = 0, .max = MAX_CARDS_PER_PILE, .cards = {0}
    },
    {
      .position = {.x = POS_SUIT_6, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .placed = 0, .max = MAX_CARDS_PER_PILE, .cards = {0}
    },
    {
      .position = {.x = POS_SUIT_7, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .placed = 0, .max = MAX_CARDS_PER_PILE, .cards = {0}
    }
  }
};

struct s_zone *klondike_zones[] = {
  (struct s_zone *) &(klondike_elements.pool),
  (struct s_zone *) &(klondike_elements.waste),
  (struct s_zone *)   klondike_elements.stack,
  (struct s_zone *)  (klondike_elements.stack+1),
  (struct s_zone *)  (klondike_elements.stack+2),
  (struct s_zone *)  (klondike_elements.stack+3),
  (struct s_zone *)   klondike_elements.piles,
  (struct s_zone *)  (klondike_elements.piles+1),
  (struct s_zone *)  (klondike_elements.piles+2),
  (struct s_zone *)  (klondike_elements.piles+3),
  (struct s_zone *)  (klondike_elements.piles+4),
  (struct s_zone *)  (klondike_elements.piles+5),
  (struct s_zone *)  (klondike_elements.piles+6)
};
card base_deck[DECK_SIZE] = {
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

card deck[DECK_SIZE];

static void reset_stacks_trick
(struct s_klondike_elements * const game_elements) {

  game_elements->stack[0].placed = 1;
  game_elements->stack[0].cards[0].value  = no_value;
  game_elements->stack[0].cards[0].suit = spade;

  game_elements->stack[1].placed = 1;
  game_elements->stack[1].cards[0].value  = no_value;
  game_elements->stack[1].cards[0].suit = heart;

  game_elements->stack[2].placed = 1;
  game_elements->stack[2].cards[0].value  = no_value;
  game_elements->stack[2].cards[0].suit = diamond;

  game_elements->stack[3].placed = 1;
  game_elements->stack[3].cards[0].value  = no_value;
  game_elements->stack[3].cards[0].suit = club;
}

void klondike_reset_game_elements
(struct s_klondike_elements * const game_elements) {
  game_elements->pool.placed = 0;
  memset(game_elements->pool.cards, 0,
         game_elements->pool.max);
  game_elements->waste.placed = 0;
  memset(game_elements->waste.cards, 0,
         game_elements->waste.max);
  for (unsigned int s = 0; s < 4; s++) {
    game_elements->stack[s].placed = 0;
    memset(game_elements->stack[s].cards, 0,
           game_elements->stack[s].max);
  }
  reset_stacks_trick(game_elements);

  for (unsigned int p = 0; p < 7; p++) {
    game_elements->piles[p].placed = 0;
    memset(game_elements->piles[p].cards, 0,
           game_elements->piles[p].max);
  }
}

void generate_new_deck
(card *target_deck, const card *not_shuffled_deck,
 unsigned int not_shuffled_deck_size, unsigned int shuffle_passes) {
  shuffled_deck_from_base_deck(target_deck, not_shuffled_deck,
                               not_shuffled_deck_size, shuffle_passes);
}

void distribute_deck
(card *shuffled_deck, struct s_klondike_elements *game_elements) {

  unsigned int distributed = distribute_n_cards_from_deck(
    0, REMAINING_DECK, (struct s_zone *) &(game_elements->pool),
    shuffled_deck);

  reset_stacks_trick(game_elements);

  for (unsigned int p = 0; p < 7; p++) {
    struct s_piles *pile = game_elements->piles+p;
    distributed = distribute_n_cards_from_deck(
      distributed, p+1, (struct s_zone *) pile, shuffled_deck
    );
    turn_cards_face_down(p, pile->cards);
  }
}

void check_if_won() {
  int win_check = (
    klondike_elements.stack[0].placed == klondike_elements.stack[0].max &&
    klondike_elements.stack[1].placed == klondike_elements.stack[1].max &&
    klondike_elements.stack[2].placed == klondike_elements.stack[2].max &&
    klondike_elements.stack[3].placed == klondike_elements.stack[3].max
  );
  if (win_check) game_won();
}

struct s_selection* start_selection_from
(struct s_zone *card_zone, enum zones zone, struct s_selection* selection) {

  unsigned int
    trick_zone = (zone == zone_stack),
    min_cards_for_selection = (1 * trick_zone);

  selection->zone = card_zone;
  selection->done = card_zone->placed > min_cards_for_selection;
  selection->move_only_top_card = (zone != zone_pile);

  return selection;
}

void remove_selection(struct s_selection* selection) { selection->done = 0; }

unsigned int move_selected_cards_to
(struct s_zone *new_zone, enum zones type, struct s_selection* selection) {

  unsigned int cards_moved = 0;
  struct s_zone *selected_zone = selection->zone;
  if (selection->done) {
    switch(type) {
      // The player can only move elements to stack or piles.
      case zone_stack:
        cards_moved = add_card_to_stack(new_zone, selected_zone, selection);
        break;
      case zone_pile:
        cards_moved = add_card_to_pile(new_zone, selected_zone, selection);
      // If he doesn't, cards_moved stays at 0
      // However, this should not happen anyway.
    }

    selected_zone->placed -= cards_moved;
  }
  /*if (cards_moved) remove_selection(selection);
  else start_selection_from(new_zone, type, selection);*/

  return cards_moved;
}

// move procedures
unsigned int add_card_to_stack
(struct s_zone* stack, struct s_zone* src, struct s_selection* selection) {
  card card_to_move   = TOP_CARD_IN(src);
  card stack_top_card = TOP_CARD_IN(stack);
  // First card trick !
  // The first card of the stack has the value 0 and the family of the stack
  // The next value of the same family will be 1, in this case.
  // So if there's no other cards
  //   the next valid card is the next value of the same family : top_card + 1
  // And if there's other cards
  //   the next valid card is the next value of the same family : top_card + 1
  // This special card will be represented as a stack holder graphically
  // The trick avoids multiple checks

  if (SAME_FAMILY(stack_top_card, card_to_move) &&
      NEXT_ASCENDING_VALUE(stack_top_card, card_to_move)) {
    stack->cards[stack->placed++] = card_to_move;
    return 1;
  }

  return 0;
}

/**
  When using the simple selection mecanism, the user can select a zone,
  then select another one and cards will be moved if it's possible.
  That means that if the user click on a pile, then click on another pile,
  the cards that can be moved from the first pile will be moved to the other
  if it's possible.

  This system is used on mobile phones where the drag & drop mechanism cannot
  be used efficiently, due to the small screen space and, therefore, high
  precision required in the touch gesture to get the right cards.

  In order to implement this mechanism, we scan the cards of the selected
  zone in order to find a possible candidate for the card move.
  If the selected zone is a pile, the scan starts from the beginning.
  Else, the scan starts from the last card.
  When a candidate is found, all the cards between the candidate index and
  the last index are moved to the pile.
 **/
unsigned int add_card_to_pile
(struct s_zone* dst, struct s_zone* src, struct s_selection* selection) {

  LOG("[add_card_to_pile]  \n");
  unsigned int cards_in_src = src->placed;
  unsigned int moved_cards = 0;
  if (cards_in_src) {
    int src_i = selection->move_only_top_card * (cards_in_src - 1);

    /*LOG("Starting from [%d/%d]\n", src_i, cards_in_src);*/

    // Search the first valid card index in the source cards.
    // The card trick cannot be used here.
    unsigned int cards_in_dst = dst->placed;
    card
      *dst_cards = (card *) &(dst->cards),
      *src_cards = (card *) &(src->cards);

    if (cards_in_dst) {
      card top_dst_card = dst_cards[cards_in_dst-1];

      for(; src_i < cards_in_src; src_i++) {

        card current_card = src_cards[src_i];

        LOG("[%d/%d] Top card : %d %d - Last card found %d %d\n",
            src_i, cards_in_src,
            top_dst_card.value, top_dst_card.suit,
            current_card.value, current_card.suit);

        if (!(NEXT_DESCENDING_VALUE(top_dst_card, current_card) &&
              DIFFERENT_COLOR(top_dst_card, current_card)))
          continue;
        else break;
      }
      /*LOG("src_i : %d -- cards_in_src : %d\n", src_i, cards_in_src);*/

    }
    else while(src_cards[src_i].value != king && src_i < cards_in_src) src_i++;

    LOG("  cards_in_src - src_i : %d - %d\n", cards_in_src, src_i);
    // Copy the cards from the source cards, starting from the index found.
    // Worst case : src_i == cards_in_src, therefore we will move 0 cards.
    moved_cards = cards_in_src - src_i;

    while (src_i < cards_in_src) {
      LOG("  src_cards[src_i] : %d - %d\n",
          src_cards[src_i].value,
          src_cards[src_i].suit);
      dst_cards[cards_in_dst++] = src_cards[src_i++];
    }

    /*LOG("Moved cards : %d\n", moved_cards);*/
    dst->placed += moved_cards;
  }
  LOG(" Moved card : %d\n", moved_cards);

  return moved_cards;
}

unsigned int draw_cards
(unsigned int const max_fished_cards,
 struct s_pool * restrict const pool,
 struct s_waste * restrict const waste) {

  unsigned int cards_in_pool = pool->placed;

  int pool_bottom = cards_in_pool - max_fished_cards;
  pool_bottom *= (pool_bottom > -1);

  card
    *pool_cards = pool->cards,
    *waste_cards = waste->cards;

  int p_i, w_i;
  for (p_i = cards_in_pool - 1, w_i = waste->placed;
       p_i >= pool_bottom; p_i--, w_i++)
    waste_cards[w_i] = pool_cards[p_i];

  waste->placed = w_i;
  pool->placed = pool_bottom;

  return w_i;
}

unsigned int reset_pool
(struct s_pool * restrict const pool,
 struct s_waste * restrict const waste) {
  unsigned int cards_in_pool  = pool->placed,
               cards_in_waste = waste->placed;
  card
    * const pool_cards = pool->cards,
    * const waste_cards = waste->cards;
  int p_i = cards_in_pool,
      w_i = cards_in_waste;
  while(w_i--) pool_cards[p_i++] = waste_cards[w_i];

  pool->placed = p_i;
  waste->placed = 0;

  return p_i;
}

unsigned int pool_still_useful
(struct s_pool * restrict const pool,
 struct s_waste * restrict const waste,
 unsigned int const max_cards_per_draw) {
  return (pool->placed > 0 ||
          waste->placed > max_cards_per_draw);
}

/* Save data format :
 * Header :
 * [     32 bits    ]
 * [ Cards in waste ]
 * ------------------
 * Body :
 * [ 8 bits  |   8 bits   |  8 bits   | 8 bits  ]
 * [ Zone id | card value | card suit | padding ] * 56
 * Total : 228 bytes
 */

/* TODO: Generate zone pointers on the stack */

inline unsigned int store_card_from
(const struct s_zone * const current_zone, uint8_t * const buffer,
 unsigned int cursor, const unsigned int z) {
  LOG("[store_card_from]\n"
      "  cursor : %d\n", cursor);
  uint8_t cards_in_zone = current_zone->placed;
  card const * const current_zone_cards = current_zone->cards;

  for (unsigned int c = 0; c < cards_in_zone; c++, cursor += 4) {
    LOG("  [z:%d - %d/%d] v: %2d, f: %d\n",
        z, c, cards_in_zone,
        current_zone_cards[c].value, current_zone_cards[c].suit);
    buffer[cursor]   = z;
    buffer[cursor+1] = current_zone_cards[c].value;
    buffer[cursor+2] = current_zone_cards[c].suit;
    buffer[cursor+3] = 0;
  }
  return cursor;
}

extern unsigned int store_card_from
(const struct s_zone * const current_zone, uint8_t * const buffer,
 const unsigned int cursor, const unsigned int z);

unsigned int save_state
(const struct s_zone * const * const cards_zones,
 uint8_t * const buffer) {

  ((uint32_t *) buffer)[0] = 0;
  unsigned int cursor = 4;

  for (enum e_klondike_elements z = e_pool; z < n_game_elements; z++)
    cursor = store_card_from(cards_zones[z], buffer, cursor, z);

  return cursor;
}


unsigned int check_pool_and_waste
(const struct s_pool * const pool,
 const struct s_waste * const waste) {
  unsigned int
    cards_in_pool  = pool->placed,
    cards_in_waste = waste->placed,
    total_cards = cards_in_pool + cards_in_waste;

  const card
    *pool_cards  = pool->cards,
    *waste_cards = waste->cards;
  unsigned int p_i = 0, w_i = 0;
  if (total_cards <= REMAINING_DECK) {

    while(p_i < cards_in_pool && VALID_FACE_UP_CARD(pool_cards[p_i]))
      p_i++;
    while(w_i < cards_in_waste && VALID_FACE_UP_CARD(waste_cards[w_i]))
      w_i++;
  }
  return (p_i == cards_in_pool & w_i == cards_in_waste);

}

unsigned int check_stacks_cards(const struct s_stack *const stacks) {

  const unsigned int expected_families[4] =
    { spade, heart, diamond, club };

  for (enum e_klondike_elements s = 0; s < 4; s++) {

    const struct s_stack *current_stack = stacks+s;
    const uint8_t cards_in_stack = current_stack->placed;
    const card* stack_cards = current_stack->cards;

    if (cards_in_stack && cards_in_stack <= MAX_CARDS_PER_STACK) {
      const uint8_t expected_family = expected_families[s];
      unsigned int c = 0;
      while (c < cards_in_stack) {
        if (stack_cards[c].value == c &&
            stack_cards[c].suit == expected_family) c++;
        else return 0;
      }
    }
    else return 0;
  }
  return 1;
}

unsigned int check_piles_cards(const struct s_piles * const piles) {
  LOG("[check_piles_cards]\n");
  for (unsigned int p = 0; p < 7; p++) {
    const struct s_piles *current_pile = piles+p;
    const unsigned int cards_in_pile = current_pile->placed;
    unsigned int returned_cards = 0;
    const card *pile_cards = current_pile->cards;

    /* You cannot pile more than 13 face up cards in Klondike.
     * However, there's returned cards in piles during the beginning.
     * Pile 0 cannot hold more than 13 cards.
     * Pile 1 cannot hold more than 14 cards (13 + 1 turned card) */
    if (cards_in_pile > 13+p) return 0;

    /* Check face down cards */
    unsigned int c = 0;
    for (; c < cards_in_pile; c++) {
      if (VALID_FACE_DOWN_CARD(pile_cards[c])) returned_cards++;
      else if (VALID_FACE_UP_CARD(pile_cards[c])) break;
      else return 0;
    }
    if (returned_cards > p) return 0;

    /* Pile 0 cannot hold more than 0 returned cards.
     * Pile 1 cannot hold more than 1 returned cards.
     * ...
     * Pile 6 cannot hold more than 6 returned cards
     * This matches the pile index exactly.
     */

    /* Check face up cards if everything is ok. */
    if (c < cards_in_pile) {
      // Skip the first face up card
      // If we got there, pile_cards[c] is a VALID_FACE_UP_CARD
      c++;
      while (c < cards_in_pile) {
        int prev = c-1;
        if (VALID_FACE_UP_CARD(pile_cards[c]) &&
            DIFFERENT_COLOR(pile_cards[prev], pile_cards[c]) &&
            NEXT_DESCENDING_VALUE(pile_cards[prev], pile_cards[c]))
          c++;
        else return 0;
      } // while
    } // if (c < cards_in_pile)

  }

  return 1;
}

unsigned int check_all_cards_unique
(const struct s_zone * const * const card_zones) {

  /* Stack card trick :
   * - Add 4 cards to the 52 playing cards.
   * - Add 1 card per suit, which makes 14 cards per suit. */
  uint8_t cards[56] = {0};

  for (enum e_klondike_elements z = e_pool; z < n_game_elements; z++) {
    const struct s_zone* current_zone = card_zones[z];
    const unsigned int cards_in_zone = current_zone->placed;
    const card *zone_cards = current_zone->cards;

    for (unsigned int c = 0; c < cards_in_zone; c++) {

      int8_t value = zone_cards[c].value;
      value = value >= 0 ? value : ~value;

      const unsigned int cards_i =
        value + (zone_cards[c].suit - 1) * 14;

      if (cards_i <= 56) cards[cards_i] = 1;
      else return 0;
    }
  }

  unsigned int return_value = 1;
  for (unsigned int c = 0; c < 56; c++) return_value &= cards[c];

  return return_value;
}

unsigned int load_state
(struct s_klondike_elements * const game_elements, const uint8_t * const buffer,
 struct s_klondike_elements * const temporary_elements) {

  memcpy(temporary_elements, game_elements, sizeof(struct s_klondike_elements));
  struct s_zone * const temporary_zones[] = {
    (struct s_zone *) &(temporary_elements->pool),
    (struct s_zone *) &(temporary_elements->waste),
    (struct s_zone *)   temporary_elements->stack,
    (struct s_zone *)  (temporary_elements->stack+1),
    (struct s_zone *)  (temporary_elements->stack+2),
    (struct s_zone *)  (temporary_elements->stack+3),
    (struct s_zone *)   temporary_elements->piles,
    (struct s_zone *)  (temporary_elements->piles+1),
    (struct s_zone *)  (temporary_elements->piles+2),
    (struct s_zone *)  (temporary_elements->piles+3),
    (struct s_zone *)  (temporary_elements->piles+4),
    (struct s_zone *)  (temporary_elements->piles+5),
    (struct s_zone *)  (temporary_elements->piles+6)
  };
  uint8_t placed_cards[13] = {0};
  /* Skipping the number of cards drawn */
  unsigned int
    cursor = 4,
    cards = 56; // 52 + 4 cards trick

  while(cards--) {
    const uint8_t z = buffer[cursor];
    const card card = {
      .value = buffer[cursor+1],
      .suit = buffer[cursor+2]
    };

    if (z < n_game_elements) {
      struct s_zone * const identified_zone = temporary_zones[z];
      uint8_t next_c = placed_cards[z]++;
      identified_zone->cards[next_c] = card;
      cursor += 4;
    }
    else return 0;
  }

  for (enum e_klondike_elements z = e_pool; z < n_game_elements; z++)
    temporary_zones[z]->placed = placed_cards[z];

  if (check_pool_and_waste(&temporary_elements->pool,
                           &temporary_elements->waste) &&
      check_stacks_cards(temporary_elements->stack) &&
      check_piles_cards(temporary_elements->piles) &&
      check_all_cards_unique(temporary_zones)) {
    memcpy(game_elements, temporary_elements, sizeof(struct s_klondike_elements));
    return 1;
  }

  return 0;
}

unsigned int quick_move
(struct s_zone * const from_src,
 struct s_klondike_elements * const elements) {

  unsigned int moved_cards = 0;
  unsigned int cards_in_src = from_src->placed;
  card *src_cards = from_src->cards;


  if (cards_in_src) {

    // Should have followed the same convention for stacks and
    // families.
    unsigned int stack_i = 0;
    switch (src_cards[cards_in_src-1].suit) {
    case 1: stack_i = 0; break;
    case 2: stack_i = 1; break;
    case 3: stack_i = 3; break;
    case 4: stack_i = 2; break;
    }


    moved_cards =
      add_card_to_stack((struct s_zone *) (elements->stack+stack_i),
                        from_src, (struct s_selection *) 0);

  }
  from_src->placed -= moved_cards;
  return moved_cards;
}
