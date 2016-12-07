#include <cards_logic/basics.h>
#include <cards_logic/klondike.h>

#include <helpers/log.h>
#include <opengl/menus.h>


struct s_elements_du_jeu elements_du_jeu = {
  .pioche = {
    .position = {.x = POS_DECK_X, .y = POS_UPPER_ELEMENTS},
    .cards_offsets = {.x = 0, .y = 0},
    .animating = 0,
    .placees = 0, .max = REMAINING_DECK, .cartes = {0}
  },
  .piochees = {
    .position = {.x = POS_WASTE_X, .y = POS_UPPER_ELEMENTS},
    .cards_offsets = {.x = POS_WASTE_OFFSET_X, .y = 0},
    .animating = 0,
    .placees = 0, .max = REMAINING_DECK, .cartes = {0}
  },
  .tas = {
    {
      .position = {.x = POS_SPADE_STACK_X, .y = POS_UPPER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = 0},
      .animating = 0,
      .placees = 1, .max = MAX_CARDS_PER_STACK,
      .cartes = {__CARTE(no_value, spade)}
    },
    {
      .position = {.x = POS_HEART_STACK_X, .y = POS_UPPER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = 0},
      .animating = 0,
      .placees = 1, .max = MAX_CARDS_PER_STACK,
      .cartes = {__CARTE(no_value, heart)}
    },
    {
      .position = {.x = POS_DIAMOND_STACK_X, .y = POS_UPPER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = 0},
      .animating = 0,
      .placees = 1, .max = MAX_CARDS_PER_STACK,
      .cartes = {__CARTE(no_value, diamond)}
    },
    {
      .position = {.x = POS_CLUB_STACK_X, .y = POS_UPPER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = 0},
      .animating = 0,
      .placees = 1, .max = MAX_CARDS_PER_STACK,
      .cartes = {__CARTE(no_value, club)}
    }
  },
  .suites = {
    {
      .position = {.x = POS_SUIT_1, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .animating = 0,
      .placees = 0, .max = MAX_CARDS_PER_PILE, .cartes = {0}
    },
    {
      .position = {.x = POS_SUIT_2, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .animating = 0,
      .placees = 0, .max = MAX_CARDS_PER_PILE, .cartes = {0}
    },
    {
      .position = {.x = POS_SUIT_3, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .animating = 0,
      .placees = 0, .max = MAX_CARDS_PER_PILE, .cartes = {0}
    },
    {
      .position = {.x = POS_SUIT_4, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .animating = 0,
      .placees = 0, .max = MAX_CARDS_PER_PILE, .cartes = {0}
    },
    {
      .position = {.x = POS_SUIT_5, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .animating = 0,
      .placees = 0, .max = MAX_CARDS_PER_PILE, .cartes = {0}
    },
    {
      .position = {.x = POS_SUIT_6, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .animating = 0,
      .placees = 0, .max = MAX_CARDS_PER_PILE, .cartes = {0}
    },
    {
      .position = {.x = POS_SUIT_7, .y = POS_LOWER_ELEMENTS},
      .cards_offsets = {.x = 0, .y = POS_SUIT_OFFSET_Y},
      .animating = 0,
      .placees = 0, .max = MAX_CARDS_PER_PILE, .cartes = {0}
    }
  }
};

struct s_zone *zones_du_jeu[] = {
  (struct s_zone *) &(elements_du_jeu.pioche),
  (struct s_zone *) &(elements_du_jeu.piochees),
  (struct s_zone *)   elements_du_jeu.tas,
  (struct s_zone *)  (elements_du_jeu.tas+1),
  (struct s_zone *)  (elements_du_jeu.tas+2),
  (struct s_zone *)  (elements_du_jeu.tas+3),
  (struct s_zone *)   elements_du_jeu.suites,
  (struct s_zone *)  (elements_du_jeu.suites+1),
  (struct s_zone *)  (elements_du_jeu.suites+2),
  (struct s_zone *)  (elements_du_jeu.suites+3),
  (struct s_zone *)  (elements_du_jeu.suites+4),
  (struct s_zone *)  (elements_du_jeu.suites+5),
  (struct s_zone *)  (elements_du_jeu.suites+6)
};
carte base_deck[DECK_SIZE] = {
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

carte deck[DECK_SIZE];

static void reset_stacks_trick
(struct s_elements_du_jeu * const game_elements) {

  game_elements->tas[0].placees = 1;
  game_elements->tas[0].cartes[0].valeur  = no_value;
  game_elements->tas[0].cartes[0].famille = spade;

  game_elements->tas[1].placees = 1;
  game_elements->tas[1].cartes[0].valeur  = no_value;
  game_elements->tas[1].cartes[0].famille = heart;

  game_elements->tas[2].placees = 1;
  game_elements->tas[2].cartes[0].valeur  = no_value;
  game_elements->tas[2].cartes[0].famille = diamond;

  game_elements->tas[3].placees = 1;
  game_elements->tas[3].cartes[0].valeur  = no_value;
  game_elements->tas[3].cartes[0].famille = club;
}

void klondike_reset_game_elements
(struct s_elements_du_jeu * const game_elements) {
  game_elements->pioche.placees = 0;
  memset(game_elements->pioche.cartes, 0, REMAINING_DECK);
  game_elements->piochees.placees = 0;
  memset(game_elements->piochees.cartes, 0, REMAINING_DECK);
  for (unsigned int s = 0; s < 4; s++) {
    game_elements->tas[s].placees = 0;
    memset(game_elements->tas[s].cartes, 0, MAX_CARDS_PER_STACK);
  }
  reset_stacks_trick(game_elements);

  for (unsigned int p = 0; p < 7; p++) {
    game_elements->suites[p].placees = 0;
    memset(game_elements->suites[p].cartes, 0, MAX_CARDS_PER_PILE);
  }
}

void generate_new_deck
(carte *target_deck, const carte *not_shuffled_deck,
 unsigned int not_shuffled_deck_size, unsigned int shuffle_passes) {
  shuffled_deck_from_base_deck(target_deck, not_shuffled_deck,
                               not_shuffled_deck_size, shuffle_passes);
}

void distribute_deck
(carte *shuffled_deck, struct s_elements_du_jeu *game_elements) {

  unsigned int distributed = distribute_n_cards_from_deck(
    0, REMAINING_DECK, (struct s_zone *) &(game_elements->pioche),
    shuffled_deck);

  reset_stacks_trick(game_elements);

  for (unsigned int p = 0; p < 7; p++) {
    struct s_suites *pile = game_elements->suites+p;
    distributed = distribute_n_cards_from_deck(
      distributed, p+1, (struct s_zone *) pile, shuffled_deck
    );
    turn_cards_face_down(p, pile->cartes);
  }
}

void game_won() { show_menu(win_menu); }

void check_if_won() {
  int win_check = (elements_du_jeu.tas[0].placees == MAX_CARDS_PER_STACK &&
                   elements_du_jeu.tas[1].placees == MAX_CARDS_PER_STACK &&
                   elements_du_jeu.tas[2].placees == MAX_CARDS_PER_STACK &&
                   elements_du_jeu.tas[3].placees == MAX_CARDS_PER_STACK);
  if (win_check) game_won();
}

struct s_selection* start_selection_from
(struct s_zone *card_zone, enum zones zone, struct s_selection* selection) {

  unsigned int
    trick_zone = (zone == zone_stack),
    min_cards_for_selection = (1 * trick_zone);

  selection->zone = card_zone;
  selection->done = card_zone->placees > min_cards_for_selection;
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

    selected_zone->placees -= cards_moved;
    check_if_won();
  }
  /*if (cards_moved) remove_selection(selection);
  else start_selection_from(new_zone, type, selection);*/

  return cards_moved;
}

// move procedures
unsigned int add_card_to_stack
(struct s_zone* tas, struct s_zone* src, struct s_selection* selection) {
  carte card_to_move   = TOP_CARD_IN(src);
  carte stack_top_card = TOP_CARD_IN(tas);
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
    tas->cartes[tas->placees++] = card_to_move;
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
  unsigned int cards_in_src = src->placees;
  unsigned int moved_cards = 0;
  if (cards_in_src) {
    int src_i = selection->move_only_top_card * (cards_in_src - 1);

    /*LOG("Starting from [%d/%d]\n", src_i, cards_in_src);*/

    // Search the first valid card index in the source cards.
    // The card trick cannot be used here.
    unsigned int cards_in_dst = dst->placees;
    carte
      *dst_cards = (carte *) &(dst->cartes),
      *src_cards = (carte *) &(src->cartes);

    if (cards_in_dst) {
      carte top_dst_card = dst_cards[cards_in_dst-1];

      for(; src_i < cards_in_src; src_i++) {

        carte current_card = src_cards[src_i];

        LOG("[%d/%d] Top card : %d %d - Last card found %d %d\n",
            src_i, cards_in_src,
            top_dst_card.valeur, top_dst_card.famille,
            current_card.valeur, current_card.famille);

        if (!(NEXT_DESCENDING_VALUE(top_dst_card, current_card) &&
              DIFFERENT_COLOR(top_dst_card, current_card)))
          continue;
        else break;
      }
      /*LOG("src_i : %d -- cards_in_src : %d\n", src_i, cards_in_src);*/

    }
    else while(src_cards[src_i].valeur != king && src_i < cards_in_src) src_i++;

    LOG("  cards_in_src - src_i : %d - %d\n", cards_in_src, src_i);
    // Copy the cards from the source cards, starting from the index found.
    // Worst case : src_i == cards_in_src, therefore we will move 0 cards.
    moved_cards = cards_in_src - src_i;

    while (src_i < cards_in_src) {
      LOG("  src_cards[src_i] : %d - %d\n",
          src_cards[src_i].valeur,
          src_cards[src_i].famille);
      dst_cards[cards_in_dst++] = src_cards[src_i++];
    }

    /*LOG("Moved cards : %d\n", moved_cards);*/
    dst->placees += moved_cards;
  }
  LOG(" Moved card : %d\n", moved_cards);

  return moved_cards;
}

unsigned int draw_cards
(unsigned int max_fished_cards, struct s_pioche *pioche,
 struct s_piochees *piochees) {

  unsigned int cards_in_pool = pioche->placees;

  int pool_bottom = cards_in_pool - max_fished_cards;
  pool_bottom *= (pool_bottom > -1);

  carte
    *pool_cards = pioche->cartes,
    *waste_cards = piochees->cartes;

  int p_i, w_i;
  for (p_i = cards_in_pool - 1, w_i = piochees->placees;
       p_i >= pool_bottom; p_i--, w_i++)
    waste_cards[w_i] = pool_cards[p_i];

  piochees->placees = w_i;
  pioche->placees = pool_bottom;

  return w_i;
}

unsigned int reset_pool
(struct s_pioche* const pioche, struct s_piochees* const piochees) {
  unsigned int cards_in_pool  = pioche->placees,
               cards_in_waste = piochees->placees;
  carte
    * const pool_cards = pioche->cartes,
    * const waste_cards = piochees->cartes;
  int p_i = cards_in_pool,
      w_i = cards_in_waste;
  while(w_i--) pool_cards[p_i++] = waste_cards[w_i];

  pioche->placees = p_i;
  pioche->max = p_i; // Not the best idea...
  piochees->max = p_i; // Not the best idea...
  piochees->placees = 0;

  return p_i;
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
  uint8_t cards_in_zone = current_zone->placees;
  carte const * const current_zone_cards = current_zone->cartes;

  for (unsigned int c = 0; c < cards_in_zone; c++, cursor += 4) {
    LOG("  [z:%d - %d/%d] v: %2d, f: %d\n",
        z, c, cards_in_zone,
        current_zone_cards[c].valeur, current_zone_cards[c].famille);
    buffer[cursor]   = z;
    buffer[cursor+1] = current_zone_cards[c].valeur;
    buffer[cursor+2] = current_zone_cards[c].famille;
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

  for (enum e_elements_du_jeu z = e_pool; z < n_game_elements; z++)
    cursor = store_card_from(cards_zones[z], buffer, cursor, z);

  return cursor;
}


unsigned int check_pool_and_waste
(const struct s_pioche * const pool,
 const struct s_piochees * const waste) {
  unsigned int
    cards_in_pool  = pool->placees,
    cards_in_waste = waste->placees,
    total_cards = cards_in_pool + cards_in_waste;

  const carte
    *pool_cards  = pool->cartes,
    *waste_cards = waste->cartes;
  unsigned int p_i = 0, w_i = 0;
  if (total_cards <= REMAINING_DECK) {

    while(p_i < cards_in_pool && VALID_FACE_UP_CARD(pool_cards[p_i]))
      p_i++;
    while(w_i < cards_in_waste && VALID_FACE_UP_CARD(waste_cards[w_i]))
      w_i++;
  }
  return (p_i == cards_in_pool & w_i == cards_in_waste);

}

unsigned int check_stacks_cards(const struct s_tas *const stacks) {

  const unsigned int expected_families[4] =
    { spade, heart, diamond, club };

  for (enum e_elements_du_jeu s = 0; s < 4; s++) {

    const struct s_tas *current_stack = stacks+s;
    const uint8_t cards_in_stack = current_stack->placees;
    const carte* stack_cards = current_stack->cartes;

    if (cards_in_stack && cards_in_stack <= MAX_CARDS_PER_STACK) {
      const uint8_t expected_family = expected_families[s];
      unsigned int c = 0;
      while (c < cards_in_stack) {
        if (stack_cards[c].valeur == c &&
            stack_cards[c].famille == expected_family) c++;
        else return 0;
      }
    }
    else return 0;
  }
  return 1;
}

unsigned int check_piles_cards(const struct s_suites * const piles) {
  LOG("[check_piles_cards]\n");
  for (unsigned int p = 0; p < 7; p++) {
    const struct s_suites *current_pile = piles+p;
    const unsigned int cards_in_pile = current_pile->placees;
    unsigned int returned_cards = 0;
    const carte *pile_cards = current_pile->cartes;

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

  for (enum e_elements_du_jeu z = e_pool; z < n_game_elements; z++) {
    const struct s_zone* current_zone = card_zones[z];
    const unsigned int cards_in_zone = current_zone->placees;
    const carte *zone_cards = current_zone->cartes;

    for (unsigned int c = 0; c < cards_in_zone; c++) {

      int8_t value = zone_cards[c].valeur;
      value = value >= 0 ? value : ~value;

      const unsigned int cards_i =
        value + (zone_cards[c].famille - 1) * 14;

      if (cards_i <= 56) cards[cards_i] = 1;
      else return 0;
    }
  }

  unsigned int return_value = 1;
  for (unsigned int c = 0; c < 56; c++) return_value &= cards[c];

  return return_value;
}

unsigned int load_state
(struct s_elements_du_jeu * const game_elements, const uint8_t * const buffer,
 struct s_elements_du_jeu * const temporary_elements) {

  memcpy(temporary_elements, game_elements, sizeof(struct s_elements_du_jeu));
  struct s_zone * const temporary_zones[] = {
    (struct s_zone *) &(temporary_elements->pioche),
    (struct s_zone *) &(temporary_elements->piochees),
    (struct s_zone *)   temporary_elements->tas,
    (struct s_zone *)  (temporary_elements->tas+1),
    (struct s_zone *)  (temporary_elements->tas+2),
    (struct s_zone *)  (temporary_elements->tas+3),
    (struct s_zone *)   temporary_elements->suites,
    (struct s_zone *)  (temporary_elements->suites+1),
    (struct s_zone *)  (temporary_elements->suites+2),
    (struct s_zone *)  (temporary_elements->suites+3),
    (struct s_zone *)  (temporary_elements->suites+4),
    (struct s_zone *)  (temporary_elements->suites+5),
    (struct s_zone *)  (temporary_elements->suites+6)
  };
  uint8_t placed_cards[13] = {0};
  /* Skipping the number of cards drawn */
  unsigned int
    cursor = 4,
    cards = 56; // 52 + 4 cards trick

  while(cards--) {
    const uint8_t z = buffer[cursor];
    const carte card = {
      .valeur = buffer[cursor+1],
      .famille = buffer[cursor+2]
    };

    if (z < n_game_elements) {
      struct s_zone * const identified_zone = temporary_zones[z];
      uint8_t next_c = placed_cards[z]++;
      identified_zone->cartes[next_c] = card;
      cursor += 4;
    }
    else return 0;
  }

  for (enum e_elements_du_jeu z = e_pool; z < n_game_elements; z++)
    temporary_zones[z]->placees = placed_cards[z];

  if (check_pool_and_waste(&temporary_elements->pioche,
                           &temporary_elements->piochees) &&
      check_stacks_cards(temporary_elements->tas) &&
      check_piles_cards(temporary_elements->suites) &&
      check_all_cards_unique(temporary_zones)) {
    memcpy(game_elements, temporary_elements, sizeof(struct s_elements_du_jeu));
    return 1;
  }

  return 0;
}

unsigned int quick_move
(struct s_zone * const from_src,
 struct s_elements_du_jeu * const elements) {

  unsigned int moved_cards = 0;
  unsigned int cards_in_src = from_src->placees;
  carte *src_cards = from_src->cartes;


  if (cards_in_src) {

    // Should have followed the same convention for stacks and
    // families.
    unsigned int stack_i = 0;
    switch (src_cards[cards_in_src-1].famille) {
    case 1: stack_i = 0; break;
    case 2: stack_i = 1; break;
    case 3: stack_i = 3; break;
    case 4: stack_i = 2; break;
    }


    moved_cards =
      add_card_to_stack((struct s_zone *) (elements->tas+stack_i),
                        from_src, (struct s_selection *) 0);

  }
  from_src->placees -= moved_cards;
  return moved_cards;
}
