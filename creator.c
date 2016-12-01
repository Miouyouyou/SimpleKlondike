#include "myy.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <helpers/base_gl.h>
#include <helpers/struct.h>
#include <helpers/log.h>

#include <cards_logic/basics.h>
#include <cards_logic/klondike.h>

// memcpy
#include <string.h>

// random
#include <stdlib.h>

typedef union two_textured_layered_triangles_quad_representations GLCard;

#define GLCARD TWO_TRIANGLES_TEX_QUAD

#define CARD_WIDTH 0.090625 // 174px - ~Bridge ratio
#define CARD_TEX_WIDTH 1.0f

#define CARD_HEIGHT 0.25f // 270px - An exact height is important
#define CARD_TRANSPARENT_PART_HEIGHT 0.05f // 27px - Same for the part height
#define CARD_TEX_HEIGHT 1.0f
#define CARD_TRANSPARENT_PART_TEX_HEIGHT 0.1f

two_tris_quad sample_card =
  GLCARD(-CARD_WIDTH, CARD_WIDTH,
         -(CARD_HEIGHT-CARD_TRANSPARENT_PART_HEIGHT),
         (CARD_HEIGHT-CARD_TRANSPARENT_PART_HEIGHT),
         0, CARD_TEX_WIDTH,
         CARD_TRANSPARENT_PART_TEX_HEIGHT,
         (CARD_TEX_HEIGHT-CARD_TRANSPARENT_PART_TEX_HEIGHT));
two_tris_quad sample_card_top_part =
  GLCARD(-CARD_WIDTH, CARD_WIDTH,
         (CARD_HEIGHT-CARD_TRANSPARENT_PART_HEIGHT), CARD_HEIGHT,
         0, CARD_TEX_WIDTH,
         (CARD_TEX_HEIGHT-CARD_TRANSPARENT_PART_TEX_HEIGHT), CARD_TEX_HEIGHT);
two_tris_quad sample_card_bottom_part =
  GLCARD(-CARD_WIDTH, CARD_WIDTH,
         -CARD_HEIGHT, -(CARD_HEIGHT-CARD_TRANSPARENT_PART_HEIGHT),
         0, CARD_TEX_WIDTH,
         0, CARD_TRANSPARENT_PART_TEX_HEIGHT);

GLCard GLcards[56];
GLCard GLcards_parts[112];

unsigned int n_cards = 0;
unsigned int n_parts = 0;

void print_GLcards(unsigned int n, GLCard *cards) {
  LOG("-----------PRINT_CARDS---------------\n");
  LOG("CARD_REL_WIDTH = %f\n", CARD_TEX_WIDTH);
  LOG("CARD_REL_HEIGHT = %f\n", CARD_TEX_HEIGHT);
  for (int i = 0; i < n; i++) {
    struct textured_point_3D *corners = cards[i].points;
    /*LOG("[Card %d] ul: %f,%f (%f,%f), dl: %f,%f (%f,%f),\n"
        "          ur: %f,%f (%f,%f), dr: %f,%f (%f,%f)\n",
        i,
        corners[0].x, corners[0].y, corners[0].s, corners[0].t,
        corners[1].x, corners[1].y, corners[1].s, corners[1].t,
        corners[2].x, corners[2].y, corners[2].s, corners[2].t,
        corners[3].x, corners[3].y, corners[3].s, corners[3].t);*/
    LOG("[Card %d] x: %f, y: %f s↔: %f -- %f, t↕: %f -- %f\n",
        i,
        corners[upleft_corner].x+CARD_WIDTH, corners[upleft_corner].y-CARD_HEIGHT,
        corners[upleft_corner].s, corners[upleft_corner].s+CARD_TEX_WIDTH,
        corners[upleft_corner].t-CARD_TEX_HEIGHT, corners[upleft_corner].t);
  }
  LOG("------------###----------------------\n\n");
}



#define TOP_CARD n_cards-1
#define BELOW_TOP_CARD n_cards-2
/* NOTE : Remember that the (cast) operator has top-most priority.
          Meaning that :
          (GLfloat *) struct s+x and (GLfloat *) (struct s+x) are completely
          different.
          So, if float are encoded on 4 bytes, and struct s are encoded on
          24 bytes
          The first example add x*4 to addr
          The second example add x*24 to addr
 */
// void add_card(GLfloat x_offset, GLfloat y_offset) {
//   copy_two_triangles_quad_with_offset(sample_card.raw_coords,
//     x_offset, y_offset, GLcards[n_cards].raw_coords);
//   n_cards++;
// }
//
// void add_to_suite() {
//   if (n_cards > 1) {
//     GLCard
//       current_card  = GLcards[TOP_CARD],
//       previous_card = GLcards[BELOW_TOP_CARD];
//     /* These are the xy coordinates of the upper left point */
//     GLfloat
//       previous_x = previous_card.points[upleft_corner].x,
//       previous_y = previous_card.points[upleft_corner].y,
//       current_x  = current_card.points[upleft_corner].x,
//       current_y  = current_card.points[upleft_corner].y,
//       horizontal_space_between_cards = previous_x - current_x,
//       vertical_space_between_cards   = previous_y - current_y,
//       x = current_x - horizontal_space_between_cards + CARD_WIDTH,  // ← => ・
//       y = current_y - vertical_space_between_cards   - CARD_HEIGHT; // ↑ => ・
//     add_card(x, y);
//   }
// }
//
// void move_card_at(unsigned int i, GLfloat x_offset, GLfloat y_offset) {
//   copy_two_triangles_quad_with_offset(sample_card.raw_coords, x_offset,
//     y_offset, GLcards[i].raw_coords);
// }
//
// void move_last_card_at(GLfloat x, GLfloat y) {
//   if (n_cards > 0) move_card_at(n_cards-1, x, y);
//   else LOG("%s\n", "Currently no card in the deck");
// }
//
// void move_last_card_previous_y(GLfloat x) {
//   if (n_cards > 1)
//     move_last_card_at(x, GLcards[TOP_CARD-1].points[upleft_corner].y-CARD_HEIGHT);
// }
//
// void remove_last_card() { if (n_cards) n_cards--; }

void add_card_to(GLCard *card_coords, carte card, float x_offset, float y_offset,
                 float layer) {
  float z = 0.90-(layer*0.01);
  copy_quad_to_offseted_layered_quad(card_coords->raw_coords,
    sample_card.raw_coords, x_offset, y_offset, z);
  n_cards++;
}
GLCard *add_transparent_parts
(GLCard *part_coords, carte card, float x_offset, float y_offset, float layer) {
  float z = 0.90-(layer*0.01);
  copy_quad_to_offseted_layered_quad(part_coords->raw_coords,
    sample_card_top_part.raw_coords, x_offset, y_offset, z);
  part_coords++;
  copy_quad_to_offseted_layered_quad(part_coords->raw_coords,
    sample_card_bottom_part.raw_coords, x_offset, y_offset, z);
  part_coords++;
  n_parts += 2;
  return part_coords;
}


GLCard *generate_transparent_parts
(GLCard *cards_coords, struct s_zone* zone) {

  unsigned int cards_to_draw = zone->placees;

  if (cards_to_draw) {
    float
      current_offset_x = zone->position.x,
      current_offset_y = zone->position.y,
      card_offset_x = zone->cards_offsets.x,
      card_offset_y = zone->cards_offsets.y;

    cards_coords = add_transparent_parts(
      cards_coords, zone->cartes[0], current_offset_x, current_offset_y, 0
    );

    int
      must_draw_other_cards = (card_offset_x != 0 && card_offset_y != 0) << 8,
      remaining_cards_to_draw = (cards_to_draw >> must_draw_other_cards);
    for (unsigned int c = 1; c < remaining_cards_to_draw; c++) {
      current_offset_x += card_offset_x;
      current_offset_y += card_offset_y;
      LOG("[%d/%d] current_offset_x : %f - current_offset_y : %f\n",
           c, remaining_cards_to_draw, current_offset_x, current_offset_y);
      cards_coords = add_transparent_parts(
        cards_coords, zone->cartes[c], current_offset_x, current_offset_y, c
      );

    }
  }

  return cards_coords;
}

GLCard *generer_coordonnees_zone
(GLCard *cards_coords, struct s_zone* zone) {

  if(zone->placees) {
    float
      current_pos_x = zone->position.x,
      current_pos_y = zone->position.y,
      card_offset_x = zone->cards_offsets.x,
      card_offset_y = zone->cards_offsets.y;

    unsigned int c = zone->placees - 1;
    float
      current_offset_x = current_pos_x + card_offset_x * c,
      current_offset_y = current_pos_y + card_offset_y * c;

    /*LOG("current_pos_x : %f * card_offset_x : %f * c : %d\n"
        "current_pos_y : %f * card_offset_y : %f * c : %d\n",
         current_pos_x, card_offset_x, c,
         current_pos_y, card_offset_y, c);*/

    unsigned int
      show_only_top_card = ((card_offset_x + card_offset_y) == 0),
      end_index = c * show_only_top_card - 1;

    /*LOG("Generating coordinates from %d to %d for %p in %p\n",
        c, end_index, zone, cards_coords);*/

    for(; c != end_index; c--) {
      /*LOG("[%d/%d] x: %f, y: %f\n", c, end_index, current_offset_x, current_offset_y);*/
      add_card_to(cards_coords++, zone->cartes[c], current_offset_x, current_offset_y, c);
      current_offset_x -= card_offset_x; current_offset_y -= card_offset_y;
    }
  }

  return cards_coords;
}

extern struct s_elements_du_jeu elements_du_jeu;
struct s_zone* gl_zones_du_jeu[] = {
  (struct s_zone *) &(elements_du_jeu.pioche),
  (struct s_zone *) &(elements_du_jeu.piochees),
  (struct s_zone *) elements_du_jeu.tas,
  (struct s_zone *) (elements_du_jeu.tas+1),
  (struct s_zone *) (elements_du_jeu.tas+2),
  (struct s_zone *) (elements_du_jeu.tas+3),
  (struct s_zone *) elements_du_jeu.suites,
  (struct s_zone *) (elements_du_jeu.suites+1),
  (struct s_zone *) (elements_du_jeu.suites+2),
  (struct s_zone *) (elements_du_jeu.suites+3),
  (struct s_zone *) (elements_du_jeu.suites+4),
  (struct s_zone *) (elements_du_jeu.suites+5),
  (struct s_zone *) (elements_du_jeu.suites+6)
};

void generer_coordonnees_elements_du_jeu
(struct s_zone **zones, int n_zones, GLCard *cards_coords, GLCard *parts_coords) {
  unsigned int z = 0;
  for (; z < n_zones; z++)
    parts_coords = generate_transparent_parts(parts_coords, zones[z]);
  while(z--) cards_coords = generer_coordonnees_zone(cards_coords, zones[z]);
}

// TODO :
// - Move cards with check (Simply)
// - Selection space
// - Fishing deck and fished cards

GLfloat menu_bar[8] = {
  0.85f, 1.0f,
  0.85f, -1.0f,
  1.0f, 1.0f,
  1.0f, -1.0f
};

enum attributes { attr_xyz, attr_st, attrs_n };

GLint cards_tex;
GLint z_layer_uniform;

void myy_init() {
  uploadTextures("textures/Card.raw\0", 1, &cards_tex);
  GLuint program =
    glhSetupAndUse("shaders/standard.vert", "shaders/standard.frag",
                   2, "xyz\0st");
  //add_card(-0.2f, 0.4f);
  glEnableVertexAttribArray(attr_xyz);
  glEnableVertexAttribArray(attr_st);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, cards_tex);
  glUniform1i(glGetUniformLocation(program, "s"), 0);
  distribute_deck();
  generer_coordonnees_elements_du_jeu(gl_zones_du_jeu,
    sizeof(gl_zones_du_jeu)/sizeof(struct s_zone*), GLcards, GLcards_parts);

}

void myy_draw() {
  glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glDepthFunc(GL_LESS);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.2f,0.6f,0.3f,1.0f);
  glVertexAttribPointer(attr_xyz, 3, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D), (GLfloat *) GLcards);
  glVertexAttribPointer(attr_st, 2, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D), (GLfloat *) GLcards+3);
  glDrawArrays(GL_TRIANGLES, 0, n_cards*6);
  glVertexAttribPointer(attr_xyz, 3, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D), (GLfloat *) GLcards_parts);
  glVertexAttribPointer(attr_st, 2, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D), (GLfloat *) GLcards_parts+3);
  glDrawArrays(GL_TRIANGLES, 0, n_parts*6);
  /*glVertexAttribPointer(attrs_xyst, 2, GL_FLOAT, GL_FALSE, 0, (GLfloat *) &menu_bar);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);*/
}

void normalise(GLfloat *gx, int x, GLfloat *gy, int y) {
  *gx = (x/640.0f)-1;
  *gy = (y/360.0f)-1;
}

unsigned int lock;
void myy_click(int x, int y, unsigned int button) {

  /*GLfloat norm_x, norm_y;
  normalise(&norm_x, x, &norm_y, y);
  if (norm_x < 0.80f) {
    if (!lock) move_last_card_at(norm_x, norm_y);
    else move_last_card_previous_y(norm_x);
  }*/
}
void myy_move(int x, int y) {

}

// Based on an Azerty keyboard
#define KEY_A 24
#define KEY_Z 25
#define KEY_P 33
#define KEY_L 46
#define KEY_J 44
#define KEY_N 57

void myy_key(unsigned int keycode) {
  /*switch(keycode) {
    case KEY_A: add_card(0,0); break;
    case KEY_Z: remove_last_card(); break;
    case KEY_N: add_to_suite(); break;
    case KEY_L: lock ^= 1; break;
    case KEY_P: print_GLcards(n_cards, GLcards);
  }*/
}

/*void print_GLcards(unsigned int n, GLCard *cards) {
  LOG("-----------PRINT_CARDS---------------\n");
  LOG("CARD_REL_WIDTH = %f\n", CARD_TEX_WIDTH);
  LOG("CARD_REL_HEIGHT = %f\n", CARD_TEX_HEIGHT);
  for (int i = 0; i < n; i++) {
    struct textured_point_3D *corners = cards[i].points;
    LOG("[Card %d] x: %f, y: %f s↔: %f -- %f, t↕: %f -- %f\n",
        i,
        corners[upleft_corner].x+CARD_WIDTH, corners[upleft_corner].y-CARD_HEIGHT,
        corners[upleft_corner].s, corners[upleft_corner].s+CARD_TEX_WIDTH,
        corners[upleft_corner].t-CARD_TEX_HEIGHT, corners[upleft_corner].t);
  }
  LOG("------------###----------------------\n\n");
}*/
