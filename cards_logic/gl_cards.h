#ifndef MYY_CARDS_POSITIONING
#define MYY_CARDS_POSITIONING 1

#include <cards_logic/klondike.h>
#include <opengl/menus.h>
#include <opengl/global.h>

#define TRANSPARENT_QUADS_PER_CARD 2
#define OPAQUE_QUADS_PER_CARD 1

typedef BUS_two_tris_3D_quad GLCard;
struct GLModelSelection { US_two_tris_quad opaque, top, bottom; };
struct GLSelection { US_two_tris_quad_3D opaque, top, bottom; };

struct gl_elements {
  uint16_t width, height;
  void (*draw_menu)(enum menu_id const menu,
                    struct gl_elements * const gl_elements,
                    enum draw_modes const draw_mode);
  enum menu_id current_menu_id;
  unsigned int displaying_a_menu;
  struct menu_hitboxes * menus_hitboxes_address;
  GLCard *transparent_quads_address, *opaque_quads_address;
  struct GLSelection *selection_quads_address;
  BUS_two_tris_3D_quad *background_address;
  unsigned short n_opaque_points, n_transparent_points;
  unsigned int current_buffer_id;
  GLuint coords_buffers[2];
  GLint uniforms[1];
  GLCard *sample_card_top_address,
         *sample_card_bottom_address,
         *sample_card_body_address;
  struct GLSelection *sample_selection_address;
  struct s_zone *zones_du_jeu[13];
};
// Simply returning two values need so much hacks and structures...
struct generated_parts {
  unsigned int transparent_quads, opaque_quads;
};

struct generated_parts generer_coordonnees_elements_du_jeu
(struct s_zone **zones, GLCard *transparent_coords,
 GLCard *transparent_models_parts, GLCard *opaque_coords,
 GLCard *opaque_model_parts);
void stocker_coordonnees_elements_du_jeu(GLCard *cards_coords,
  unsigned int n_cards, GLCard *parts_coords, unsigned int n_parts,
  BUS_two_tris_3D_quad *background);
void regen_cards_coords();

void generate_horizontal_selection_around
(struct s_selection *selection,
 struct GLSelection *mdl, struct GLSelection *cpy);
void print_selection(struct GLSelection *selection);

void regen_and_store_selection_quad
(struct s_selection *selection, unsigned int n_opaque_points,
 struct GLSelection *model_selection,
 struct GLSelection *selection_quads);

void basic_klondike_restart
(struct gl_elements * restrict const gl_elements);

enum hitbox_zones {
  hitbox_pioche, hitbox_piochees,
  hitbox_stack_spade, hitbox_stack_heart, hitbox_stack_diamond, hitbox_stack_club,
  hitbox_suite1, hitbox_suite2, hitbox_suite3, hitbox_suite4, hitbox_suite5,
  hitbox_suite6, hitbox_suite7, hitbox_unknown
};

enum hitbox_zones determine_clicked_zone(int8_t glx, int8_t gly);

enum zones determine_zone_type(enum hitbox_zones z);

#endif
