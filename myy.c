#include "myy.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <helpers/base_gl.h>
#include <helpers/struct.h>
#include <helpers/log.h>

#include <cards_logic/basics.h>
#include <cards_logic/klondike.h>
#include <cards_logic/gl_cards.h>

// memcpy
#include <string.h>

// random
#include <stdlib.h>

// offsetof
#include <stddef.h>

#include <sys/types.h> // read, write, fstat, open
#include <sys/stat.h> // fstat, open
#include <unistd.h> // read, write, fstat, get_current_dir_name
#include <stdlib.h> // exit
#include <fcntl.h> // open

extern struct s_elements_du_jeu elements_du_jeu;
extern struct gl_elements gl_elements;
extern struct s_selection selection;
extern struct GLModelSelection gl_selection_parts;
extern carte base_deck[];
extern carte deck[];
extern uint8_t scratch[];

enum gl_attributes { attr_xyz, attr_st, attrs_n };
enum gl_uniforms { unif_background };
void myy_display_initialised(unsigned int width, unsigned int height) {
  gl_elements.width = width; gl_elements.height = height;
}

GLuint cards_tex[2] = {0};
GLuint GLprogram = 0;

void myy_cleanup_drawing() {
  glFinish();
  glDeleteBuffers(2, gl_elements.coords_buffers);
  glDeleteTextures(2, cards_tex);
  glDeleteProgram(GLprogram);
}

void myy_generate_new_state() {
  generate_new_deck(deck, base_deck, DECK_SIZE, SHUFFLE_PASSES);
  distribute_deck(deck, &elements_du_jeu);
}

void myy_save_state(struct myy_game_state *state) {
  unsigned int save_size =
    save_state(gl_elements.zones_du_jeu, state->state);
  state->saved = (save_size == 228) ;
  state->size = save_size;
}

unsigned int myy_load_state(struct myy_game_state *state) {
  return load_state(&elements_du_jeu, state->state,
                    (struct s_elements_du_jeu *) scratch);
}

void myy_resume_state(struct myy_game_state *state) {
  if (!state->saved ||
      (state->saved && state->size != 228) ||
      !myy_load_state(state))
    myy_generate_new_state();
}

void myy_init_drawing() {
  struct generated_parts parts_generated =
    generer_coordonnees_elements_du_jeu(gl_elements.zones_du_jeu,
      gl_elements.transparent_quads_address,
      gl_elements.sample_card_top_address,
      gl_elements.opaque_quads_address,
      gl_elements.sample_card_body_address
    );

  glGenBuffers(2, gl_elements.coords_buffers);
  /* The 52 cards + 4 stack marks + 2 pool marks +
     Background + Selection (3 parts) */
  unsigned int gpu_buf_size =
    (58*3)*sizeof(GLCard) +
    sizeof(BUS_two_tris_3D_quad) +
    sizeof(struct GLSelection);
  glBindBuffer(GL_ARRAY_BUFFER, gl_elements.coords_buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, gpu_buf_size, NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, gl_elements.coords_buffers[1]);
  glBufferData(GL_ARRAY_BUFFER, gpu_buf_size, NULL, GL_DYNAMIC_DRAW);

  // Double buffering flip-flop switch
  unsigned int current_buffer_id = gl_elements.current_buffer_id;
  /*current_buffer_id ^= 1;*/
  glBindBuffer(GL_ARRAY_BUFFER,
               gl_elements.coords_buffers[current_buffer_id]);
  /*gl_elements.current_buffer_id = current_buffer_id;*/

  stocker_coordonnees_elements_du_jeu(
    gl_elements.opaque_quads_address,
    parts_generated.opaque_quads,
    gl_elements.transparent_quads_address,
    parts_generated.transparent_quads,
    gl_elements.background_address
  );

  gl_elements.n_opaque_points =
    parts_generated.opaque_quads * two_triangles_corners;
  gl_elements.n_transparent_points =
    parts_generated.transparent_quads * two_triangles_corners;

  regen_and_store_selection_quad(&selection,
                                 gl_elements.n_opaque_points,
                                 gl_elements.sample_selection_address,
                                 gl_elements.selection_quads_address);

  uploadTextures("textures/all_cards_tex.raw\0"
                 "textures/table_background.raw\0", 2, cards_tex);
  glhActiveTextures(cards_tex, 2);
  GLprogram =
    glhSetupAndUse("shaders/standard.vert", "shaders/standard.frag",
                   2, "xyz\0st");


  glEnableVertexAttribArray(attr_xyz);
  glEnableVertexAttribArray(attr_st);
  GLint background_uniform =
    glGetUniformLocation(GLprogram, "s");
  glUniform1i(background_uniform, 0);
  gl_elements.uniforms[unif_background] = background_uniform;
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glDepthFunc(GL_LESS);
}

void myy_init() {}


void myy_draw() {
  glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

  //glClearColor(0.2f,0.6f,0.3f,1.0f);

  const unsigned int
    BUS_x_offset = offsetof(struct BUS_textured_point_3D, x),
    US_x_offset  = offsetof(struct US_textured_point_3D, x);
  const unsigned int
    byte_quad_size = sizeof(struct BUS_textured_point_3D),
    short_quad_size = sizeof(struct US_textured_point_3D),
    cards_opaque_points = gl_elements.n_opaque_points,
    selection_opaque_points = two_triangles_corners,
    background_points = two_triangles_corners,
    selection_transparent_points = two_triangles_corners * 2,
    card_transparent_points = gl_elements.n_transparent_points;

  uint8_t *current_offset = 0;
  /*
   * This could be reduced to 6 Vertex + Draw calls and 3 Blending calls.
   * The only reason for all these calls is because Cards coordinates are in
   * bytes and selection coordinates are in short.
   * Two solutions to this :
   * - Convert cards coordinates to GLshort. This will increase the memory
   *   footprint by 4 bytes per point, for a total of 72 bytes per full
   *   quad (opaque + 2 transparent parts).
   * - Encode the selection coordinates in byte and generate the border
   *   inside a shader program. Another program will be needed, though.
   *   Note that, the program is using GLshort instead of GLbyte for
   *   the selection quad, because generating a border with the same
   *   number of pixels in width and height is very difficult with
   *   GLbyte, due to the lack of precision.
   * Avoid :
   * - Using a different buffer for the selection. It won't solve this
   *   problem since, in order to avoid overdraw of opaque quads,
   *   you'll need to display things in the following order.
   */

  /* Disable Blending */
  glDisable(GL_BLEND);

  /* Cards : Opaque parts */
  glVertexAttribPointer(attr_st, 2, GL_UNSIGNED_SHORT, GL_TRUE,
                        byte_quad_size, current_offset);
  glVertexAttribPointer(attr_xyz, 3, GL_BYTE, GL_TRUE,
                        byte_quad_size, current_offset + BUS_x_offset);
  glDrawArrays(GL_TRIANGLES, 0, cards_opaque_points);
  current_offset += cards_opaque_points * byte_quad_size;

  /* Selection : Opaque part */
  glVertexAttribPointer(attr_st, 2, GL_UNSIGNED_SHORT, GL_TRUE,
                        short_quad_size, current_offset);
  glVertexAttribPointer(attr_xyz, 3, GL_SHORT, GL_TRUE,
                        short_quad_size, current_offset + US_x_offset);
  glDrawArrays(GL_TRIANGLES, 0, selection_opaque_points);
  current_offset += selection_opaque_points * short_quad_size;

  /* Background */
  const GLint background_uniform =
    gl_elements.uniforms[unif_background];
  glUniform1i(background_uniform, 1);
  glVertexAttribPointer(attr_st, 2, GL_UNSIGNED_SHORT, GL_TRUE,
                        byte_quad_size, current_offset);
  glVertexAttribPointer(attr_xyz, 3, GL_BYTE, GL_TRUE,
                        byte_quad_size, current_offset + BUS_x_offset);
  glDrawArrays(GL_TRIANGLES, 0, background_points);
  current_offset += background_points * byte_quad_size;
  glUniform1i(background_uniform, 0);

  /* Activate Blending */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Selection : Transparent parts */
  glVertexAttribPointer(attr_st, 2, GL_UNSIGNED_SHORT, GL_TRUE,
                        short_quad_size, current_offset);
  glVertexAttribPointer(attr_xyz, 3, GL_SHORT, GL_TRUE,
                        short_quad_size, current_offset + US_x_offset);
  glDrawArrays(GL_TRIANGLES, 0, selection_transparent_points);
  current_offset += selection_transparent_points * short_quad_size;

  /* Selection : Transparent parts */
  glVertexAttribPointer(attr_st, 2, GL_UNSIGNED_SHORT, GL_TRUE,
                        byte_quad_size, current_offset);
  glVertexAttribPointer(attr_xyz, 3, GL_BYTE, GL_TRUE,
                        byte_quad_size, current_offset + BUS_x_offset);
  glDrawArrays(GL_TRIANGLES, 0, card_transparent_points);

}



inline struct byte_point_2D normalise
(const int x, const int y,
 const float width, const float height) {
  struct byte_point_2D coords = {
    .x = (int8_t) (((x/width)*255)-127),
    .y = (int8_t) (((y/height)*255)-127)
  };
  return coords;
}

extern struct byte_point_2D normalise
(const int x, const int y,
 const float width, const float height);

void myy_click
(int x, int y, unsigned int button) {

  struct byte_point_2D norm_coords =
    normalise(x, y, gl_elements.width, gl_elements.height);

  enum hitbox_zones h_z =
    determine_clicked_zone(norm_coords.x, norm_coords.y);

  LOG("norm_coords.x : %d - norm_coords.y : %d\n",
      norm_coords.x, norm_coords.y);
  enum zones z_t = determine_zone_type(h_z);

  LOG("Hitbox : %d\n", h_z);

  unsigned int changed_cards = 0;
  if (h_z != hitbox_unknown) { 
    struct s_zone* const clicked_zone = gl_elements.zones_du_jeu[h_z];
    if (z_t == zone_deck) {
      struct s_pioche * const pioche = (struct s_pioche *) clicked_zone;
      struct s_piochees * const piochees =
        (struct s_piochees *) gl_elements.zones_du_jeu[hitbox_piochees];
      LOG("%p == %p ?\n",
          piochees, gl_elements.zones_du_jeu[hitbox_piochees]);
      if (pioche->max) {
        if (pioche->placees)
          draw_cards(MAX_CARDS_IN_WASTE, pioche, piochees);
        else reset_pool(pioche, piochees);
        changed_cards = 1;
      }
    }
    else {

      if (IS_FACE_UP( TOP_CARD_IN(((struct s_suites *) clicked_zone))) ) {
        if (selection.done) {
          changed_cards = move_selected_cards_to(clicked_zone, z_t, &selection);
          if (changed_cards) remove_selection(&selection);
          else start_selection_from(clicked_zone, z_t, &selection);
        }
        else start_selection_from(clicked_zone, z_t, &selection);
        //regen_selection_around(&selection, clicked_zone);
      } // Turning cards automatically would avoid such stupid checks
      else {
        TURN_CARD(TOP_CARD_IN(((struct s_suites*) clicked_zone)));
        changed_cards = 1;
      }
    }
  }
  else {
    remove_selection(&selection);
    //regen_selection_around(&selection, (struct s_zone *) 0);
  }

  LOG("Selection done ? %d\n", selection.done);
  if (changed_cards) regen_cards_coords(&gl_elements);
  regen_and_store_selection_quad(&selection,
                                 gl_elements.n_opaque_points,
                                 gl_elements.sample_selection_address,
                                 gl_elements.selection_quads_address);


}

void myy_doubleclick(int x, int y, unsigned int button) {
  LOG("Double clicked !\n");
  struct byte_point_2D norm_coords =
    normalise(x, y, gl_elements.width, gl_elements.height);

  enum hitbox_zones h_z =
    determine_clicked_zone(norm_coords.x, norm_coords.y);

  enum zones z_t = determine_zone_type(h_z);
  LOG("norm_coords.x : %d - norm_coords.y : %d -> z_t : %d\n",
      norm_coords.x, norm_coords.y, z_t);

  if ((z_t == zone_pile || z_t == zone_waste) &&
      quick_move(gl_elements.zones_du_jeu[h_z], &elements_du_jeu)) {
    regen_cards_coords(&gl_elements);
    regen_and_store_selection_quad(&selection,
                                   gl_elements.n_opaque_points,
                                   gl_elements.sample_selection_address,
                                   gl_elements.selection_quads_address);
  }
  else myy_click(x, y, button);
}

void myy_resume() {}

void load_game() {
  const unsigned fd = open("test.save", O_RDONLY);
  if (fd != -1) {
    read(fd, scratch, 228);
    memset(scratch+228, 0, sizeof(struct s_elements_du_jeu));
    if (load_state(&elements_du_jeu, scratch,
                   (struct s_elements_du_jeu *) scratch+228)) {
      remove_selection(&selection);
      regen_cards_coords(&gl_elements);
      regen_and_store_selection_quad(&selection,
                                     gl_elements.n_opaque_points,
                                     gl_elements.sample_selection_address,
                                     gl_elements.selection_quads_address);
    }
    close(fd);
  }
  else LOG("Could not open test.save for reading");
}

void save_game() {

  const unsigned int fd =
    open("test.save", O_WRONLY|O_CREAT|O_TRUNC, 00664);
  if (fd != -1) {
    unsigned int bytes_saved = save_state(gl_elements.zones_du_jeu, scratch);
    if (bytes_saved != write(fd, scratch, bytes_saved))
      LOG("Could not write the entire save !\n");
    close(fd);
    return;
  }
  else {
    LOG("Could not open test.save with writing permissions\n");
  }
}

void myy_move(int x, int y) {}

#define KEY_S 39
#define KEY_L 46
void myy_key(unsigned int keycode) {
  if (keycode == KEY_S) save_game();
  if (keycode == KEY_L) load_game();
}
void myy_stop() { myy_cleanup_drawing(); }
void myy_animating() {}
void myy_pause() {}

