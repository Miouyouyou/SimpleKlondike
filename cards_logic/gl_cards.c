#include <cards_logic/gl_cards.h>
#include <helpers/log.h>

#include <signal.h> // trap
#include <string.h> // memset

#define GLCARD STXYZ_QUAD

#define CARD_FIRST_LAYER 64
#define CARD_WIDTH 11 // ~174px - ~Bridge ratio
#define CARD_HEIGHT 32 // ~270px - ~Bridge ratio
#define CARD_ALPHA_PART_HEIGHT 7 // 13.5px * 2 (Two parts)

#define CARD_TEX_LEFT 24
#define CARD_TEX_RIGHT 4071
#define CARD_TEX_ALPHA_BOTTOM_BOTTOM 60
#define CARD_TEX_ALPHA_BOTTOM_TOP 1639
#define CARD_TEX_ALPHA_TOP_BOTTOM 14745
#define CARD_TEX_ALPHA_TOP_TOP 16323

#define CARD_LEFT   (-CARD_WIDTH)
#define CARD_RIGHT   (CARD_WIDTH)
#define CARD_BOTTOM (-CARD_HEIGHT)
#define CARD_TOP     (CARD_HEIGHT)

#define CARD_LEFT_FROM(x)   (x+CARD_LEFT)
#define CARD_RIGHT_FROM(x)  (x+CARD_RIGHT)
#define CARD_TOP_FROM(y)    (y+CARD_TOP)
#define CARD_BOTTOM_FROM(y) (y+CARD_BOTTOM)

#define CARD_HITBOX(L,R,U,D) .range = {\
  {.x = L, .y = U}, \
  {.x = R, .y = D}  \
}

#define CARD_WIDTH_IN_PIXELS ((11/127.0)*1920.0)
#define CARD_HEIGHT_IN_PIXELS ((32/127.0)*1080.0)
#define BORDER_IN_PIXELS 12
#define SELECTION_WIDTH ((CARD_WIDTH_IN_PIXELS + BORDER_IN_PIXELS) / 1920.0)
#define SELECTION_HEIGHT ((CARD_HEIGHT_IN_PIXELS + BORDER_IN_PIXELS) / 1080.0)
#define SELECTION_LEFT ((int16_t) -(SELECTION_WIDTH * 32768))
#define SELECTION_RIGHT ((int16_t) (SELECTION_WIDTH * 32767))
#define SELECTION_TOP ((int16_t) (SELECTION_HEIGHT * 32767))
#define SELECTION_BOTTOM ((int16_t) -(SELECTION_HEIGHT * 32768))
#define SELECTION_ALPHA_BOTTOM_TOP (SELECTION_BOTTOM+1638)
#define SELECTION_ALPHA_TOP_BOTTOM (SELECTION_TOP-1638)
#define SELECTION_LAYER 23220

#define CARD_BACK_TILE_NUMBER 14

struct {
  GLCard GLcards_parts[CARDS_IN_TOTAL*2], GLcards[CARDS_IN_TOTAL];
  BUS_two_tris_3D_quad background;
  struct GLSelection GLselection;
} gl_coords = {
  .GLcards_parts = {0},
  .GLcards = {0},
  .background =
    STXYZ_QUAD(
      -128, 127, -128, 127, 100,
      0, 65535, 0, 65535
    ),
  .GLselection = {0}
};

struct { GLCard top, bottom, opaque; } gl_cards_parts = {
  .top = GLCARD(
    CARD_LEFT, CARD_RIGHT,
    (CARD_TOP-CARD_ALPHA_PART_HEIGHT), CARD_TOP, CARD_FIRST_LAYER,
    CARD_TEX_LEFT, CARD_TEX_RIGHT,
    CARD_TEX_ALPHA_TOP_BOTTOM,
    CARD_TEX_ALPHA_TOP_TOP
  ),
  .bottom = GLCARD(
    CARD_LEFT, CARD_RIGHT,
    CARD_BOTTOM, (CARD_BOTTOM+CARD_ALPHA_PART_HEIGHT), CARD_FIRST_LAYER,
    CARD_TEX_LEFT, CARD_TEX_RIGHT,
    CARD_TEX_ALPHA_BOTTOM_BOTTOM,
    CARD_TEX_ALPHA_BOTTOM_TOP
  ),
  .opaque = GLCARD(
    /* Coords : Left, Right, Down, Up - Tex : Left, Right, Down Up */
    CARD_LEFT, CARD_RIGHT,
    (CARD_BOTTOM+CARD_ALPHA_PART_HEIGHT),
    (CARD_TOP-CARD_ALPHA_PART_HEIGHT),
    CARD_FIRST_LAYER,
    CARD_TEX_LEFT, CARD_TEX_RIGHT,
    CARD_TEX_ALPHA_BOTTOM_TOP,
    CARD_TEX_ALPHA_TOP_BOTTOM
  )
};

struct GLSelection gl_selection_parts = {
  .opaque = GLCARD(
    SELECTION_LEFT, SELECTION_RIGHT,
    SELECTION_ALPHA_BOTTOM_TOP,
    SELECTION_ALPHA_TOP_BOTTOM,
    SELECTION_LAYER,
    CARD_TEX_LEFT, CARD_TEX_RIGHT,
    CARD_TEX_ALPHA_BOTTOM_TOP,
    CARD_TEX_ALPHA_TOP_BOTTOM
  ),
  .top = GLCARD(
    SELECTION_LEFT, SELECTION_RIGHT,
    SELECTION_ALPHA_TOP_BOTTOM, SELECTION_TOP,
    SELECTION_LAYER,
    CARD_TEX_LEFT, CARD_TEX_RIGHT,
    CARD_TEX_ALPHA_TOP_BOTTOM,
    CARD_TEX_ALPHA_TOP_TOP
  ),
  .bottom = GLCARD(
    SELECTION_LEFT, SELECTION_RIGHT,
    SELECTION_BOTTOM, SELECTION_ALPHA_BOTTOM_TOP,
    SELECTION_LAYER,
    CARD_TEX_LEFT, CARD_TEX_RIGHT,
    CARD_TEX_ALPHA_BOTTOM_BOTTOM,
    CARD_TEX_ALPHA_BOTTOM_TOP
  )
};

struct hitbox zones_hitboxes[13] = {
  {CARD_HITBOX(CARD_LEFT_FROM(POS_DECK_X), CARD_RIGHT_FROM(POS_DECK_X),
               CARD_TOP_FROM(POS_UPPER_ELEMENTS),
               CARD_BOTTOM_FROM(POS_UPPER_ELEMENTS)
               )},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_WASTE_X),
               CARD_RIGHT_FROM(POS_WASTE_X)+MAX_CARDS_IN_WASTE*POS_WASTE_OFFSET_X,
               CARD_TOP_FROM(POS_UPPER_ELEMENTS),
               CARD_BOTTOM_FROM(POS_UPPER_ELEMENTS)
               )},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_SPADE_STACK_X),
               CARD_RIGHT_FROM(POS_SPADE_STACK_X),
               CARD_TOP_FROM(POS_UPPER_ELEMENTS),
               CARD_BOTTOM_FROM(POS_UPPER_ELEMENTS)
               )},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_HEART_STACK_X),
               CARD_RIGHT_FROM(POS_HEART_STACK_X),
               CARD_TOP_FROM(POS_UPPER_ELEMENTS),
               CARD_BOTTOM_FROM(POS_UPPER_ELEMENTS)
               )},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_DIAMOND_STACK_X),
               CARD_RIGHT_FROM(POS_DIAMOND_STACK_X),
               CARD_TOP_FROM(POS_UPPER_ELEMENTS),
               CARD_BOTTOM_FROM(POS_UPPER_ELEMENTS)
               )},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_CLUB_STACK_X),
               CARD_RIGHT_FROM(POS_CLUB_STACK_X),
               CARD_TOP_FROM(POS_UPPER_ELEMENTS),
               CARD_BOTTOM_FROM(POS_UPPER_ELEMENTS)
               )},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_SUIT_1),
               CARD_RIGHT_FROM(POS_SUIT_1),
               CARD_TOP_FROM(POS_LOWER_ELEMENTS),
               128)},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_SUIT_2),
               CARD_RIGHT_FROM(POS_SUIT_2),
               CARD_TOP_FROM(POS_LOWER_ELEMENTS),
               128)},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_SUIT_3),
               CARD_RIGHT_FROM(POS_SUIT_3),
               CARD_TOP_FROM(POS_LOWER_ELEMENTS),
               128)},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_SUIT_4),
               CARD_RIGHT_FROM(POS_SUIT_4),
               CARD_TOP_FROM(POS_LOWER_ELEMENTS),
               128)},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_SUIT_5),
               CARD_RIGHT_FROM(POS_SUIT_5),
               CARD_TOP_FROM(POS_LOWER_ELEMENTS),
               128)},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_SUIT_6),
               CARD_RIGHT_FROM(POS_SUIT_6),
               CARD_TOP_FROM(POS_LOWER_ELEMENTS),
               128)},
  {CARD_HITBOX(CARD_LEFT_FROM(POS_SUIT_7),
               CARD_RIGHT_FROM(POS_SUIT_7),
               CARD_TOP_FROM(POS_LOWER_ELEMENTS),
               128)}
};

extern struct s_elements_du_jeu elements_du_jeu;
extern struct s_selection selection;

struct gl_elements gl_elements = {
  .width = 1280,
  .height = 720,
  .transparent_quads_address = gl_coords.GLcards_parts,
  .opaque_quads_address      = gl_coords.GLcards,
  .selection_quads_address   = &(gl_coords.GLselection),
  .background_address        = &(gl_coords.background),
  .n_opaque_points           = 0,
  .n_transparent_points      = 0,
  .current_buffer_id = 0,
  .uniforms = {0},
  .coords_buffers    = {0, 0},
  .sample_card_top_address    = &(gl_cards_parts.top),
  .sample_card_bottom_address = &(gl_cards_parts.bottom),
  .sample_card_body_address   = &(gl_cards_parts.opaque),
  .sample_selection_address   = &(gl_selection_parts),
  .zones_du_jeu = {
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
  }
};

#define FACE_DOWN_INDEX 14
#define CARD_TEX_S_STRIDE 4096 // << 12
#define CARD_TEX_T_STRIDE 16384 // << 14 - 1

static unsigned int generate_card_quads
(const GLushort s_offset, const GLushort t_offset,
 const GLshort x_offset, const GLshort y_offset,
 const GLshort z_offset, GLCard *mdl,
 const unsigned int n_mdl, GLCard *cpy) {

  for (unsigned int parts = 0; parts < n_mdl; parts++) {
    for (unsigned int i = 0; i < two_triangles_corners; i++) {
      cpy->points[i].s = mdl->points[i].s + s_offset;
      cpy->points[i].t = mdl->points[i].t + t_offset;
      cpy->points[i].x = mdl->points[i].x + x_offset;
      cpy->points[i].y = mdl->points[i].y + y_offset;
      cpy->points[i].z = mdl->points[i].z + z_offset;
    }
    mdl++;
    cpy++;
  }
  return n_mdl;
}

static unsigned int generate_card
(carte *card, int current_card_x_offset, int current_card_y_offset,
 int z_layer, GLCard *models, unsigned int quads, GLCard *cpy) {

  int8_t card_value = card->valeur;
  uint16_t current_card_s_offset =
    card_value >= 0 ? card_value * CARD_TEX_S_STRIDE
                    : CARD_BACK_TILE_NUMBER * CARD_TEX_S_STRIDE;
  uint16_t current_card_t_offset =
    (card->famille - 1) * CARD_TEX_T_STRIDE;

  return
     generate_card_quads(current_card_s_offset, current_card_t_offset,
                         current_card_x_offset, current_card_y_offset,
                         z_layer, models, quads, cpy);

}

static unsigned int generate_opaque_parts
(struct s_zone *zone, const unsigned int from_card_c,
 const unsigned int to_card_c, GLCard *models,
 const unsigned int quads, GLCard *cpy) {
  /* Traiter toutes les cartes placées et générer des coordonées dans
     GLCard */

  unsigned int
    total_quads = 0,
    c = to_card_c;
  const int8_t
    first_pos_x      = zone->position.x,
    first_pos_y      = zone->position.y,
    card_offset_x    = zone->cards_offsets.x,
    card_offset_y    = zone->cards_offsets.y;
  int8_t
    current_card_x_offset = first_pos_x + card_offset_x * (to_card_c - from_card_c),
    current_card_y_offset = first_pos_y + card_offset_y * (to_card_c - from_card_c);

  do {
    unsigned int generated_quads =
      generate_card(&zone->cartes[c], current_card_x_offset,
                    current_card_y_offset, -c, models, quads, cpy);
    total_quads += generated_quads;
    cpy += generated_quads;
    current_card_x_offset -= card_offset_x;
    current_card_y_offset -= card_offset_y;

  } while (c-- > from_card_c);

  return total_quads;

}

static unsigned int generate_transparent_parts
(struct s_zone *zone, const unsigned int from_card_c,
 const unsigned int to_card_c, GLCard *models,
 const unsigned int quads, GLCard *cpy) {
  /* Traiter toutes les cartes placées et générer des coordonées dans
     GLCard */

  // Set cards_to_display to 0 if the next cards are not offseted.
  // 'do { ... } while ()' always execute at least once


  unsigned int total_quads = 0;
  const int8_t
    first_pos_x      = zone->position.x,
    first_pos_y      = zone->position.y,
    card_offset_x    = zone->cards_offsets.x,
    card_offset_y    = zone->cards_offsets.y;

  int8_t
    current_card_x_offset = first_pos_x,
    current_card_y_offset = first_pos_y;

  for (unsigned int c = from_card_c; c <= to_card_c; c++) {
    unsigned int generated_quads =
      generate_card(&zone->cartes[c], current_card_x_offset,
                    current_card_y_offset, -c, models, quads, cpy);
    total_quads += generated_quads;
    cpy += generated_quads;
    current_card_x_offset += card_offset_x;
    current_card_y_offset += card_offset_y;
  }


  return total_quads;

}

#define GENERATOR_SIGNATURE (struct s_zone *zone, \
                             const unsigned int from_card_c, \
                             const unsigned int to_card_c, \
                             GLCard *models, \
                             const unsigned int quads, \
                             GLCard *cpy)

static unsigned int generate_stack_parts
(unsigned int (*generator_func)GENERATOR_SIGNATURE,
  struct s_zone *zone, GLCard *models, unsigned int quads, GLCard *cpy) {
  return generate_card(&zone->cartes[zone->placees-1], zone->position.x,
                       zone->position.y, 0, models, quads, cpy);
}

static unsigned int generate_pile_parts
(unsigned int (*generator_func)GENERATOR_SIGNATURE,
 struct s_zone *zone, GLCard *models, unsigned int quads, GLCard *cpy) {
  unsigned int cards_in_pile = zone->placees;
  if (cards_in_pile)
    return generator_func(zone, 0, zone->placees-1, models, quads, cpy);
  else return 0;
}

static unsigned int generate_waste_parts
(unsigned int (*generator_func)GENERATOR_SIGNATURE,
 struct s_zone *zone, GLCard *models, unsigned int quads, GLCard *cpy) {
  unsigned int cards_in_waste = zone->placees;

  if (cards_in_waste) {

    unsigned int
      end_i = (cards_in_waste > 0 ? cards_in_waste - 1 : 0),
      start_i = end_i >= MAX_CARDS_IN_WASTE ? end_i - MAX_CARDS_IN_WASTE + 1
                                            : 0;

    return generator_func(zone, start_i, end_i, models, quads, cpy);
  }
  else return 0;
}

static unsigned int generate_pool_parts
(unsigned int (*generator_func)GENERATOR_SIGNATURE,
 struct s_zone *pool, GLCard *models, unsigned int n_models, GLCard *cpy) {
  const GLushort
    s_offset = 14 * CARD_TEX_S_STRIDE,
    t_offset = (0 + (pool->placees == 0) + (pool->max == 0)) * CARD_TEX_T_STRIDE;
  const GLshort
    x_offset = pool->position.x,
    y_offset = pool->position.y;

  return generate_card_quads(s_offset, t_offset, x_offset, y_offset, 0,
                             models, n_models, cpy);
}





void generate_horizontal_selection_around
(struct s_selection *selection,
 struct GLSelection *mdl, struct GLSelection *cpy) {

  if (selection->done) {
    struct s_zone *selected_zone = selection->zone;
    GLshort
      first_x_offset  = selected_zone->position.x * 258,
      first_y_offset  = selected_zone->position.y * 258,
      second_y_offset =
        first_y_offset +
        selected_zone->cards_offsets.y * (selected_zone->placees - 1) * 258,
      s_offset = 14 * CARD_TEX_S_STRIDE,
      t_offset = 1 * CARD_TEX_T_STRIDE;
    GLshort offsets[2] = { first_y_offset, second_y_offset };
    for (int i = 0; i < two_triangles_corners; i ++) {
      cpy->opaque.points[i].s = mdl->opaque.points[i].s + s_offset;
      cpy->opaque.points[i].t = mdl->opaque.points[i].t + t_offset;
      cpy->opaque.points[i].x = mdl->opaque.points[i].x + first_x_offset;
      cpy->opaque.points[i].y = mdl->opaque.points[i].y + offsets[i%2];
      cpy->opaque.points[i].z = mdl->opaque.points[i].z;
    }
    for (int i = 0; i < two_triangles_corners; i ++) {
      cpy->top.points[i].s = mdl->top.points[i].s + s_offset;
      cpy->top.points[i].t = mdl->top.points[i].t + t_offset;
      cpy->top.points[i].x = mdl->top.points[i].x + first_x_offset;
      cpy->top.points[i].y = mdl->top.points[i].y + first_y_offset;
      cpy->top.points[i].z = mdl->opaque.points[i].z;
    }
    for (int i = 0; i < two_triangles_corners; i ++) {
      cpy->bottom.points[i].s = mdl->bottom.points[i].s + s_offset;
      cpy->bottom.points[i].t = mdl->bottom.points[i].t + t_offset;
      cpy->bottom.points[i].x = mdl->bottom.points[i].x + first_x_offset;
      cpy->bottom.points[i].y = mdl->bottom.points[i].y + second_y_offset;
      cpy->bottom.points[i].z = mdl->opaque.points[i].z;
    }
  }
  else memset(cpy, 0, sizeof(struct GLSelection));

}

/*void print_selection(struct GLSelection *selection) {
  for (int p = 0; p < 3; p++) {
    LOG("[print_selection] part : %d\n", p);
    US_two_tris_quad_3D *part = (US_two_tris_quad_3D *) selection+p;
    for (int i = 0; i < two_triangles_corners; i++) {
      LOG("  [%d] s: %d, t: %d\n"
          "  [%d] x: %d, y: %d, z: %d\n"
          "  ----\n",
          i, part->points[i].s, part->points[i].t,
          i, part->points[i].x, part->points[i].y, part->points[i].z
      );
    }
    LOG("---------------------------\n");
  }
}*/

struct generated_parts generer_coordonnees_elements_du_jeu
(struct s_zone **zones, GLCard *transparent_coords,
 GLCard *transparent_models_parts, GLCard *opaque_coords,
 GLCard *opaque_model_parts) {

  unsigned int (*elements_generators[])(
   unsigned int (*generator)GENERATOR_SIGNATURE, struct s_zone *zone,
   GLCard *models, unsigned int n_models, GLCard *cpy) = {
    generate_pool_parts, generate_waste_parts,
    generate_stack_parts, generate_stack_parts, generate_stack_parts,
    generate_stack_parts, generate_pile_parts, generate_pile_parts,
    generate_pile_parts, generate_pile_parts, generate_pile_parts,
    generate_pile_parts, generate_pile_parts
  };

  unsigned int
    generated_quads,
    total_transparent_quads = 0,
    total_opaque_quads = 0;

  unsigned int n = e_pool;

  for (; n < n_game_elements; n++) {
    generated_quads = elements_generators[n](
      generate_transparent_parts, zones[n], transparent_models_parts,
      2, transparent_coords
    );
    transparent_coords += generated_quads;
    total_transparent_quads += generated_quads;
  }
  while(n--) {
    generated_quads = elements_generators[n](
      generate_opaque_parts, zones[n], opaque_model_parts,
      1, opaque_coords
    );
    opaque_coords += generated_quads;
    total_opaque_quads += generated_quads;
  }
  struct generated_parts quads_generated = {
    .transparent_quads = total_transparent_quads,
    .opaque_quads = total_opaque_quads
  };

  return quads_generated;
}

void stocker_coordonnees_elements_du_jeu(GLCard *cards_coords,
  unsigned int n_cards, GLCard *parts_coords, unsigned int n_parts,
  BUS_two_tris_3D_quad *background) {
  const unsigned int
    cards_buffer_size = n_cards * sizeof(GLCard),
    parts_buffer_size = n_parts * sizeof(GLCard),
    selection_element_size = sizeof(US_two_tris_quad_3D),
    background_size = sizeof(BUS_two_tris_3D_quad);

  /* Buffer segmentation
   * - Cards : Opaque part
   * - Selection : Opaque part
   * - Background
   * - Selection : Transparent parts
   * - Cards : Transparent parts
   * The Selection parts are dealt in :
   *   regen_and_store_selection_quad()
   */
  /* Cards : Opaque part */
  GLintptr offset = 0;
  glBufferSubData(GL_ARRAY_BUFFER, offset, cards_buffer_size,
                  cards_coords);
  offset += cards_buffer_size + selection_element_size;
  //LOG("  offset: %d\n", offset);

  /* Background */
  glBufferSubData(GL_ARRAY_BUFFER, offset,
                  background_size, background);
  offset += background_size +
            selection_element_size * 2;
  //LOG("  offset: %d\n", offset);

  /* Cards : Transparent parts */
  glBufferSubData(GL_ARRAY_BUFFER, offset,
                  parts_buffer_size, parts_coords);


}

void regen_cards_coords(struct gl_elements *gl_elements) {
  struct generated_parts parts_generated =
    generer_coordonnees_elements_du_jeu(gl_elements->zones_du_jeu,
      gl_elements->transparent_quads_address,
      gl_elements->sample_card_top_address,
      gl_elements->opaque_quads_address,
      gl_elements->sample_card_body_address
    );
  unsigned int current_buffer_id = gl_elements->current_buffer_id;
  current_buffer_id ^= 1;
  glBindBuffer(GL_ARRAY_BUFFER, gl_elements->coords_buffers[current_buffer_id]);
  gl_elements->current_buffer_id = current_buffer_id;
  stocker_coordonnees_elements_du_jeu(
    gl_elements->opaque_quads_address, parts_generated.opaque_quads,
    gl_elements->transparent_quads_address, parts_generated.transparent_quads,
    gl_elements->background_address
  );
  gl_elements->n_opaque_points = parts_generated.opaque_quads * 6;
  gl_elements->n_transparent_points = parts_generated.transparent_quads * 6;
}

void regen_and_store_selection_quad
(struct s_selection *selection, unsigned int n_opaque_points,
 struct GLSelection *model_selection,
 struct GLSelection *selection_quads) {
  unsigned int
    size_of_GLSelection_part = sizeof(US_two_tris_quad_3D),
    size_of_background_part  = sizeof(BUS_two_tris_3D_quad),
    offset_of_opaque_selection =
      n_opaque_points * sizeof(struct BUS_textured_point_3D),
    offset_of_transparent_selection =
      offset_of_opaque_selection +
      size_of_GLSelection_part +
      size_of_background_part;
  generate_horizontal_selection_around(selection, model_selection,
                                       selection_quads);
  glBufferSubData(GL_ARRAY_BUFFER,
                  offset_of_opaque_selection,
                  size_of_GLSelection_part,
                  selection_quads);
  glBufferSubData(GL_ARRAY_BUFFER,
                  offset_of_transparent_selection,
                  size_of_GLSelection_part*2,
                  &(selection_quads->top));
}

unsigned int determine_hitbox_id_glbyte
(int8_t const x, int8_t const y,
 const struct hitbox * restrict const hitboxes,
 unsigned int const n_hitboxes) {

  unsigned int i = 0;
  while(i < n_hitboxes) {
    struct hitbox *current_hitbox = hitboxes+i;

    if (x < current_hitbox->range[0].x || y > current_hitbox->range[0].y ||
        x > current_hitbox->range[1].x || y < current_hitbox->range[1].y) {
      i++; continue;
    }

    break;
  }
  return i;
}

enum hitbox_zones determine_clicked_zone(int8_t glx, int8_t gly) {
  return
    (enum hitbox_zones)
    determine_hitbox_id_glbyte(glx, gly, zones_hitboxes, hitbox_unknown);
}

enum zones determine_zone_type(enum hitbox_zones z) {
  if (z < hitbox_stack_spade) return (enum zones) z;
  else if (z >= hitbox_stack_spade && z <= hitbox_stack_club) return zone_stack;
  else if (z >= hitbox_suite1 && z <= hitbox_suite7) return zone_pile;
  else return zone_unknown;
}
