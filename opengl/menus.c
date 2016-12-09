#include <GLES2/gl2.h>

#include <helpers/base_gl.h>
#include <helpers/log.h>
#include <opengl/menus.h>
#include <opengl/global.h>

#include <stddef.h> // offsetof

GLuint windows_buffer = 0;

#define GITHUB_URL "https://github.com/Miouyouyou/SimpleKlondike"

void close_all_menus
(struct gl_elements * restrict const gl_elements) {
  gl_elements->draw_menu = no_action;
  gl_elements->displaying_a_menu = 0;
}

void close_menu
(enum menu_id const menu,
 struct gl_elements * restrict const gl_elements) {
  close_all_menus(gl_elements);
}

void open_menu
(enum menu_id const menu,
 struct gl_elements * restrict const gl_elements) {
  gl_elements->current_menu_id = menu;
  gl_elements->draw_menu = draw_menu;
  gl_elements->displaying_a_menu = 1;
}

void pause_menu_restart
(enum menu_id const menu,
 struct gl_elements * restrict const gl_elements) {
  LOG("[pause_menu_restart]\n");
  basic_klondike_restart(gl_elements);
  close_menu(menu, gl_elements);
}
void pause_menu_continue
(enum menu_id const menu,
 struct gl_elements * restrict const gl_elements) {
  LOG("[pause_menu_continue]\n");
  close_menu(menu, gl_elements);
}

void win_menu_github
(enum menu_id const menu,
 struct gl_elements * restrict const gl_elements) {
  LOG("[win_menu_github]\n");
  open_website(GITHUB_URL);
}
void win_menu_restart
(enum menu_id const menu,
 struct gl_elements * restrict const gl_elements) {
  LOG("[win_menu_restart]\n");
  basic_klondike_restart(gl_elements);
  close_menu(menu, gl_elements);
}

struct menu_hitboxes menus_hitactions[] = {
  [pause_menu] = {
    .inside  = {.range = {{.x = -68, .y = 60}, {.x =  68, .y = -60}}},
    .outside = close_menu,
    .n_buttons = 2,
    .buttons = {
      {
        .hitbox = {.range = {{.x = -56, .y =  25},
                             {.x = -28, .y = -24}}},
        .action = pause_menu_restart
      },
      {
        .hitbox = {.range = {{.x =  28, .y =  25},
                             {.x =  56, .y = -24}}},
        .action = pause_menu_continue
      },
    }
  },
  [win_menu] = {
    .inside = {.range = {{.x = -68, .y = 76}, {.x = 68, .y = -76}}},
    .outside = no_action,
    .n_buttons = 2,
    .buttons = {
      {
        .hitbox = {.range = {{.x = -36, .y = -18},
                             {.x = -8,  .y = -67}}},
        .action = win_menu_github
      },
      {
        .hitbox = {.range = {{.x = 7,  .y = -18},
                             {.x = 35, .y = -67}}},
        .action = win_menu_restart
      }
    }
  }
};


inline unsigned int outside_hitbox_range
(int8_t x, int8_t y,
 struct hitbox * restrict const current_hitbox) {

  return x < current_hitbox->range[0].x ||
         y > current_hitbox->range[0].y ||
         x > current_hitbox->range[1].x ||
         y < current_hitbox->range[1].y;
}

extern unsigned int outside_hitbox_range
(int8_t x, int8_t y, struct hitbox * restrict const hitbox);

/* Generalised */
void hitbox_action_trigger
(int8_t const x, int8_t const y,
 enum menu_id const menu_id,
 struct menu_hitboxes * menu_zones,
 struct gl_elements * restrict const gl_elements) {

  LOG("[hitbox_action_trigger] \n");
  if (!outside_hitbox_range(x, y, &menu_zones->inside)) {
    LOG("  Inside !\n");
    unsigned int const n_buttons = menu_zones->n_buttons;

    for (unsigned int b = 0; b < n_buttons; b++) {
      struct menu_button * const current_button =
         menu_zones->buttons+b;

      if (outside_hitbox_range(x, y, &current_button->hitbox))
        continue;
      else {
        current_button->action(menu_id, gl_elements);
        break;
      }
    }

  }
  else {
    LOG("  Outside...\n");
    menu_zones->outside(menu_id, gl_elements);
  }

}

/* Specialised */
void menu_hitbox_action_trigger
(int8_t const x, int8_t const y,
 struct gl_elements * restrict const gl_elements) {
  enum menu_id const current_menu_id = gl_elements->current_menu_id;
  hitbox_action_trigger(
    x, y, current_menu_id,
    gl_elements->menus_hitboxes_address+current_menu_id,
    gl_elements
  );
}

void prepare_menus_buffers() {

  struct dumb_window windows[n_menus] = { 
    [pause_menu] = {
      .parts = {
        STXYZ_QUAD(-MENUS_PAUSE_REL_WIDTH, MENUS_PAUSE_REL_WIDTH,
                   -MENUS_PAUSE_REL_OPAQUE_HEIGHT,
                   MENUS_PAUSE_REL_OPAQUE_HEIGHT,
                   MENUS_LAYER,
                   MENUS_TEX_PAUSE_LEFT, MENUS_TEX_PAUSE_RIGHT,
                   MENUS_TEX_PAUSE_ALPHA_BOTTOM_TOP,
                   MENUS_TEX_PAUSE_ALPHA_TOP_BOTTOM),

        STXYZ_QUAD(-MENUS_PAUSE_REL_WIDTH, MENUS_PAUSE_REL_WIDTH,
                   MENUS_PAUSE_REL_OPAQUE_HEIGHT,
                   MENUS_PAUSE_REL_HEIGHT,
                   MENUS_LAYER,
                   MENUS_TEX_PAUSE_LEFT, MENUS_TEX_PAUSE_RIGHT,
                   MENUS_TEX_PAUSE_ALPHA_TOP_BOTTOM,
                   MENUS_TEX_PAUSE_TOP),

        STXYZ_QUAD(-MENUS_PAUSE_REL_WIDTH, MENUS_PAUSE_REL_WIDTH,
                   -MENUS_PAUSE_REL_HEIGHT,
                   -MENUS_PAUSE_REL_OPAQUE_HEIGHT,
                   MENUS_LAYER,
                   MENUS_TEX_PAUSE_LEFT, MENUS_TEX_PAUSE_RIGHT,
                   MENUS_TEX_PAUSE_BOTTOM,
                   MENUS_TEX_PAUSE_ALPHA_BOTTOM_TOP)
      }
    },
    [win_menu] = {
      .parts = {
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

  /* Last minute hack */
  two_layered_tris_quad pause_button[3] = {
    STXYZ_QUAD(0.9f, 0.94375f, -0.786111f, -0.769444f, 0.20f,
               0.540f, 0.542f, 0.1913f, 0.1913f),
    STXYZ_QUAD(0.9f, 0.94375f, -0.81944f, -0.802777f, 0.20f,
               0.540f, 0.542f, 0.1913f, 0.1913f),
    STXYZ_QUAD(0.9f, 0.94375f, -0.852777f, -0.836111f, 0.20f,
               0.540f, 0.542f, 0.1913f, 0.1913f)
  };

  if (!windows_buffer) glGenBuffers(1, &windows_buffer);

  glBindBuffer(GL_ARRAY_BUFFER, windows_buffer);
  glBufferData(GL_ARRAY_BUFFER,
               // This last minute hack introduces this offset
               sizeof(two_layered_tris_quad) * 3 +
               sizeof(struct dumb_window)*n_menus,
               NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER,
                  0, sizeof(two_layered_tris_quad) * 3,
                  pause_button);
  glBufferSubData(GL_ARRAY_BUFFER,
                 sizeof(two_layered_tris_quad) * 3,
                 sizeof(struct dumb_window)*n_menus,
                 windows);
}

void draw_pause_button
(unsigned int useless,
 struct gl_elements * const gl_elements) {
  glBindBuffer(GL_ARRAY_BUFFER, windows_buffer);
  glUniform1i(gl_elements->uniforms[unif_background], 2);

  glVertexAttribPointer(attr_xyz, 3, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D),
                        (const void *)
                        (offsetof(struct textured_point_3D, x)));
  glVertexAttribPointer(attr_st, 2, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D),
                        (const void *)
                        (offsetof(struct textured_point_3D, s)));
  glDrawArrays(GL_TRIANGLES, 0, two_triangles_corners*3);
}

void draw_menu
(enum menu_id const menu,
 struct gl_elements * const gl_elements,
 enum draw_modes const draw_mode) {

  const unsigned int buffer_offset =
    sizeof(two_layered_tris_quad) * 3 + // <- Last minute hack...
    sizeof(struct dumb_window)*menu;

  glBindBuffer(GL_ARRAY_BUFFER, windows_buffer);
  glUniform1i(gl_elements->uniforms[unif_background], 2);

  glVertexAttribPointer(attr_xyz, 3, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D),
                        (const void *) buffer_offset);
  glVertexAttribPointer(attr_st, 2, GL_FLOAT, GL_FALSE,
                        sizeof(struct textured_point_3D),
                        (const void *)
                        (buffer_offset+offsetof(struct textured_point_3D, s)));
  switch(draw_mode) {
  case draw_opaque:
    glDrawArrays(GL_TRIANGLES, 0, two_triangles_corners);
    break;
  case draw_blended:
    glDrawArrays(GL_TRIANGLES, two_triangles_corners, two_triangles_corners*2);
    break;
  }
}

void destroy_menu_buffers() { glDeleteBuffers(1, &windows_buffer); }
