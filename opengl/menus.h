#ifndef MYY_KLONDIKE_OPENGL_MENUS_H
#define MYY_KLONDIKE_OPENGL_MENUS_H 1

/* All these definitions will soon be replaced by coordinates
 * generated with a script */
#define BASE_SCREEN_WIDTH 1920.0
#define BASE_SCREEN_HEIGHT 1080.0

#define MENUS_TEX_HEIGHT (580.0) // pixels
#define MENUS_TEX_WIDTH (512.0) // pixels
#define MENUS_TEX_HP_HEIGHT (0.5/MENUS_TEX_HEIGHT)
#define MENUS_TEX_HP_WIDTH (0.5/MENUS_TEX_WIDTH)

#define MENUS_TEX_LEFT (0+MENUS_TEX_HP_WIDTH)
#define MENUS_TEX_RIGHT (MENUS_TEX_HEIGHT/MENUS_TEX_HEIGHT-MENUS_TEX_HP_HEIGHT)

#define MENUS_WINDOWS_BORDER_HEIGHT (7) // pixels
#define MENUS_WINDOWS_BORDER_REL_HEIGHT (MENUS_WINDOWS_BORDER_HEIGHT/MENUS_TEX_HEIGHT)

#define MENUS_PAUSE_HEIGHT (256.0)
#define MENUS_PAUSE_WIDTH (512.0)

#define MENUS_PAUSE_REL_HEIGHT (MENUS_PAUSE_HEIGHT*2/BASE_SCREEN_HEIGHT)
#define MENUS_PAUSE_REL_WIDTH (MENUS_PAUSE_WIDTH*2/BASE_SCREEN_WIDTH)
#define MENUS_PAUSE_REL_OPAQUE_HEIGHT (MENUS_PAUSE_REL_HEIGHT-MENUS_WINDOWS_BORDER_REL_HEIGHT*2)

#define MENUS_TEX_PAUSE_HEIGHT (MENUS_PAUSE_HEIGHT/MENUS_TEX_HEIGHT-MENUS_TEX_HP_HEIGHT)
#define MENUS_TEX_PAUSE_WIDTH (MENUS_PAUSE_WIDTH/MENUS_TEX_WIDTH-MENUS_TEX_HP_WIDTH)

#define MENUS_TEX_PAUSE_BOTTOM (0+MENUS_TEX_HP_HEIGHT)
#define MENUS_TEX_PAUSE_TOP (MENUS_TEX_PAUSE_HEIGHT)
#define MENUS_TEX_PAUSE_LEFT (MENUS_TEX_LEFT)
#define MENUS_TEX_PAUSE_RIGHT (MENUS_TEX_PAUSE_WIDTH)

#define MENUS_TEX_PAUSE_ALPHA_BOTTOM_TOP (MENUS_TEX_PAUSE_BOTTOM+MENUS_WINDOWS_BORDER_REL_HEIGHT)
#define MENUS_TEX_PAUSE_ALPHA_TOP_BOTTOM (MENUS_TEX_PAUSE_TOP-MENUS_WINDOWS_BORDER_REL_HEIGHT)

#define MENUS_WIN_HEIGHT (324.0)
#define MENUS_WIN_WIDTH (512.0)

#define MENUS_WIN_REL_HEIGHT (MENUS_WIN_HEIGHT*2/BASE_SCREEN_HEIGHT)
#define MENUS_WIN_REL_WIDTH (MENUS_WIN_WIDTH*2/BASE_SCREEN_WIDTH)
#define MENUS_WIN_REL_OPAQUE_HEIGHT (MENUS_WIN_REL_HEIGHT-(MENUS_WINDOWS_BORDER_REL_HEIGHT*2))
#define MENUS_TEX_WIN_HEIGHT (MENUS_WIN_HEIGHT/MENUS_TEX_HEIGHT-MENUS_TEX_HP_HEIGHT)
#define MENUS_TEX_WIN_WIDTH (MENUS_WIN_WIDTH/MENUS_TEX_WIDTH-MENUS_TEX_HP_WIDTH)

#define MENUS_TEX_WIN_BOTTOM (256/MENUS_TEX_HEIGHT+MENUS_TEX_HP_HEIGHT)
#define MENUS_TEX_WIN_TOP (580/MENUS_TEX_HEIGHT-MENUS_TEX_HP_HEIGHT)
#define MENUS_TEX_WIN_LEFT (0+MENUS_TEX_HP_WIDTH)
#define MENUS_TEX_WIN_RIGHT (512/MENUS_TEX_WIDTH-MENUS_TEX_HP_WIDTH)

#define MENUS_TEX_WIN_ALPHA_BOTTOM_TOP (MENUS_TEX_WIN_BOTTOM+MENUS_WINDOWS_BORDER_REL_HEIGHT)
#define MENUS_TEX_WIN_ALPHA_TOP_BOTTOM (MENUS_TEX_WIN_TOP-MENUS_WINDOWS_BORDER_REL_HEIGHT)

#define MENUS_LAYER 0.10f

#define MENU_PARTS 3
struct dumb_window { two_layered_tris_quad parts[MENU_PARTS]; };
enum dumb_window_parts {
  opaque_part,
  top_transp_part,
  bottom_transp_part
};
enum menu_id { pause_menu, win_menu, n_menus };

#define HITBOX_ACTION_SIGNATURE \
  enum menu_id const menu, \
  struct gl_elements * restrict const gl_elements

#include <helpers/base_gl.h>
#include <cards_logic/gl_cards.h>
#include <opengl/global.h>

struct menu_button {
  struct hitbox hitbox;
  void (*action)(HITBOX_ACTION_SIGNATURE);
};

#define MAX_BUTTONS 2
struct menu_hitboxes {
  struct hitbox inside;
  void (*outside)(HITBOX_ACTION_SIGNATURE);
  unsigned int n_buttons;
  struct menu_button buttons[MAX_BUTTONS];
};

void close_all_menus
(struct gl_elements * restrict const gl_elements);
void close_menu
(enum menu_id const menu,
 struct gl_elements * restrict const gl_elements);
void open_menu
(enum menu_id const menu,
 struct gl_elements * restrict const gl_elements);

void menu_hitbox_action_trigger
(int8_t const x, int8_t const y,
 struct gl_elements * restrict const gl_elements);

void prepare_menus_buffers();
void draw_menu
(enum menu_id const menu,
 struct gl_elements * const gl_elements,
 enum draw_modes const draw_mode);
void destroy_menu_buffers();


#endif
