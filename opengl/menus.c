#include <GLES2/gl2.h>

#include <helpers/base_gl.h>
#include <helpers/log.h>
#include <opengl/menus.h>
#include <opengl/global.h>

#include <stddef.h> // offsetof

GLuint windows_buffer = 0;

#define GITHUB_URL "https://github.com/Miouyouyou/SimpleKlondike"

void no_action() {}
void pause_menu_restart() {
  LOG("[pause_menu_restart]\n");
  basic_klondike_restart();
}
void pause_menu_continue() {
  LOG("[pause_menu_continue]\n");
  hide_menus();
}

void win_menu_github() {
  LOG("[win_menu_github]\n");
  open_website(GITHUB_URL);
}
void win_menu_restart() {
  LOG("[win_menu_restart]\n");
  basic_klondike_restart();
}

struct menu_hitboxes menus_hitboxes = {
  .pause = {
    {.range = {{.x = -56, .y = 25}, {.x = -28, .y = -24}}}, // restart
    {.range = {{.x =  28, .y = 25}, {.x =  56, .y = -24}}}, // continue
    {.range = {{.x = -68, .y = 60}, {.x =  68, .y = -60}}}, // menu
  },
  .win = {
    {.range = {{.x = -36, .y = -18}, {.x = -8, .y = -67}}}, // github
    {.range = {{.x = 7, .y = -18}, {.x = 35, .y = -67}}} // restart
  }
};

struct menu_actions menus_actions = {
  .pause = {
    pause_menu_restart,
    pause_menu_continue,
    no_action,
    hide_menus
  },
  .win = {
    win_menu_github,
    win_menu_restart,
    no_action,
  }
};

void handle_pause_clicks
(int8_t const x, int8_t const y,
 const struct menu_hitboxes * restrict const hitboxes,
 const struct menu_actions * restrict const actions) {
  unsigned int hitbox_id =
    determine_hitbox_id_glbyte(x, y, hitboxes->pause,
                               pause_menu_n_hitboxes);
  LOG("[handle_pause_clicks]\n");
  LOG("  Hitbox id : %d\n", hitbox_id);
  actions->pause[hitbox_id]();
}

void handle_win_clicks
(int8_t const x, int8_t const y,
 const struct menu_hitboxes * restrict const hitboxes,
 const struct menu_actions * restrict const actions) {
  unsigned int hitbox_id =
    determine_hitbox_id_glbyte(x, y, hitboxes->win,
                               win_menu_n_hitboxes);
  LOG("[handle_win_clicks]\n");
  LOG("  Hitbox id : %d\n", hitbox_id);
  actions->win[hitbox_id]();
}

void prepare_menus_buffers() {

  struct dumb_window windows[n_menus] = { 
  { .parts = {
      STXYZ_QUAD(-MENUS_PAUSE_REL_WIDTH, MENUS_PAUSE_REL_WIDTH,
                 -MENUS_PAUSE_REL_OPAQUE_HEIGHT,
                 MENUS_PAUSE_REL_OPAQUE_HEIGHT,
                 MENUS_LAYER,
                 MENUS_TEX_PAUSE_LEFT, MENUS_TEX_PAUSE_RIGHT,
                 MENUS_TEX_PAUSE_ALPHA_BOTTOM_TOP,
                 MENUS_TEX_PAUSE_ALPHA_TOP_BOTTOM),

      STXYZ_QUAD(-MENUS_PAUSE_REL_WIDTH, MENUS_PAUSE_REL_WIDTH,
                 MENUS_PAUSE_REL_HEIGHT, MENUS_PAUSE_REL_OPAQUE_HEIGHT,
                 MENUS_LAYER,
                 MENUS_TEX_PAUSE_LEFT, MENUS_TEX_PAUSE_RIGHT,
                 MENUS_TEX_PAUSE_TOP, MENUS_TEX_PAUSE_ALPHA_TOP_BOTTOM),

      STXYZ_QUAD(-MENUS_PAUSE_REL_WIDTH, MENUS_PAUSE_REL_WIDTH,
                 -MENUS_PAUSE_REL_HEIGHT, -MENUS_PAUSE_REL_OPAQUE_HEIGHT,
                 MENUS_LAYER,
                 MENUS_TEX_PAUSE_LEFT, MENUS_TEX_PAUSE_RIGHT,
                 MENUS_TEX_PAUSE_BOTTOM,
                 MENUS_TEX_PAUSE_ALPHA_BOTTOM_TOP)
    }
  },
  { .parts = {
      STXYZ_QUAD(-MENUS_WIN_REL_WIDTH, MENUS_WIN_REL_WIDTH,
                 -MENUS_WIN_REL_OPAQUE_HEIGHT,
                 MENUS_WIN_REL_OPAQUE_HEIGHT,
                 MENUS_LAYER,
                 MENUS_TEX_WIN_LEFT, MENUS_TEX_WIN_RIGHT,
                 MENUS_TEX_WIN_ALPHA_BOTTOM_TOP,
                 MENUS_TEX_WIN_ALPHA_TOP_BOTTOM),

      STXYZ_QUAD(-MENUS_WIN_REL_WIDTH, MENUS_WIN_REL_WIDTH,
                 MENUS_WIN_REL_HEIGHT,MENUS_WIN_REL_OPAQUE_HEIGHT,
                 MENUS_LAYER,
                 MENUS_TEX_WIN_LEFT, MENUS_TEX_WIN_RIGHT,
                 MENUS_TEX_WIN_ALPHA_TOP_BOTTOM,MENUS_TEX_WIN_TOP),

      STXYZ_QUAD(-MENUS_WIN_REL_WIDTH, MENUS_WIN_REL_WIDTH,
                 -MENUS_WIN_REL_HEIGHT,-MENUS_WIN_REL_OPAQUE_HEIGHT,
                 MENUS_LAYER,
                 MENUS_TEX_WIN_LEFT, MENUS_TEX_WIN_RIGHT,
                 MENUS_TEX_WIN_BOTTOM,MENUS_TEX_WIN_ALPHA_BOTTOM_TOP)
     }
  },
  };

  if (!windows_buffer) glGenBuffers(1, &windows_buffer);

  glBindBuffer(GL_ARRAY_BUFFER, windows_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct dumb_window)*n_menus,
               windows, GL_STATIC_DRAW);
}

void draw_menu
(enum menus_names const menu,
 struct gl_elements * const gl_elements ) {

  const unsigned int buffer_offset = sizeof(struct dumb_window)*menu;

  glBindBuffer(GL_ARRAY_BUFFER, windows_buffer);

  glUniform1i(gl_elements->uniforms[unif_background], 2);
  glDisable(GL_BLEND);
  glVertexAttribPointer(attr_xyz, 3, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D),
                        (const void *) buffer_offset);
  glVertexAttribPointer(attr_st, 2, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D),
                        (const void *)
                        (buffer_offset+offsetof(struct textured_point_3D, s)));
  glDrawArrays(GL_TRIANGLES, 0, two_triangles_corners);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glVertexAttribPointer(attr_xyz, 3, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D),
                        (const void *) buffer_offset);
  glVertexAttribPointer(attr_st, 2, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D),
                        (const void *)
                        buffer_offset+offsetof(struct textured_point_3D, s));
  glDrawArrays(GL_TRIANGLES, two_triangles_corners,
               two_triangles_corners*2);

  glDisable(GL_BLEND);
}

void destroy_menu_buffer() { glDeleteBuffers(1, &windows_buffer); }
