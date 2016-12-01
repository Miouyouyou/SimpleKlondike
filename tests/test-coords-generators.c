#include <assert.h>

#include <cards_logic/gl_cards.h>
#include <helpers/log.h>

extern struct gl_elements gl_elements;
extern struct s_elements_du_jeu elements_du_jeu;

void assert_same_coords
(GLCard *expected_coords, GLCard *coords, int n_coords) {
  for (unsigned int i = 0; i < n_coords; i++) {
    for (unsigned p = 0; p < two_triangles_corners; p++) {
      assert(expected_coords[i].points[p].s == coords[i].points[p].s);
      assert(expected_coords[i].points[p].t == coords[i].points[p].t);
      assert(expected_coords[i].points[p].x == coords[i].points[p].x);
      assert(expected_coords[i].points[p].y == coords[i].points[p].y);
      assert(expected_coords[i].points[p].z == coords[i].points[p].z);
    }
  }
}

#define __CARDS_COORDS_OPAQUE(zone_ptr, value, suit, index) = { \
  .x = zone_ptr->position.x + zone_ptr->cards_offsets.x * index, \
  .y = zone_ptr->position.y + zone_ptr->cards_offsets.y * index, \
  .z = zone_ptr->position.z + zone_ptr->cards_offsets.z * index, \
  .s = value * CARD_TEX_S_STRIDE, \
  .t = value * CARD_TEX_y_STRIDE \
}

void test_generate_card_quads() {
  carte one_card_only[] = { __CARTE(ace, diamond) };

  struct s_zone *all_zones_with_same_card =
    utl_zone_copy_with_same_cards_everywhere(one_card_only, 1);

  GLCard expected_opaque_coords[13*OPAQUE_QUADS_PER_CARD] = {
    __CARDS_COORDS_OPAQUE(e_pile_7, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_pile_6, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_pile_5, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_pile_4, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_pile_3, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_pile_2, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_pile_1, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_club_stack, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_diamond_stack, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_heart_stack, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_spade_stack, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_waste, ace, diamond, 0),
    __CARDS_COORDS_OPAQUE(e_pool,  ace, diamond, 0),
  };

  GLCard expected_transparent_coords[13*TRANSPARENT_QUADS_PER_CARD] = {
    __CARDS_COORDS_TRANSP(e_pool,  ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_waste, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_spade_stack, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_heart_stack, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_diamond_stack, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_club_stack, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_pile_1, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_pile_2, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_pile_3, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_pile_4, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_pile_5, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_pile_6, ace, diamond, 0),
    __CARDS_COORDS_TRANSP(e_pile_7, ace, diamond, 0),
  };

  GLCard *transparent_quads =
    malloc(13 * TRANSPARENT_QUADS_PER_CARD * sizeof(GLCard));
  GLCard *opaque_quads =
    malloc(13 * CARDS_IN_TOTAL * OPAQUE_QUADS_PER_CARD * sizeof(GLCard));

  struct generated_parts parts_generated =
    generer_coordonnees_elements_du_jeu(
     &all_zones_with_same_card,
     transparent_quads, gl_elements.sample_card_top_address,
     opaque_quads, gl_elements.sample_card_bottom_address
  );

  assert(26 == parts_generated.transparent_quads);
  assert(13 == parts_generated.opaque_quads);
  assert_same_coords(expected_opaque_coords, opaque_quads, 13);
  assert_same_coords(expected_transparent_coords, transparent_quads, 26);

}
