#ifndef MYY_KLONDIKE_GLOBAL_H
#define MYY_KLONDIKE_GLOBAL_H 1

#include <myy.h>

enum gl_attributes { attr_xyz, attr_st, attrs_n };
enum gl_uniforms { unif_background };

enum draw_modes { draw_opaque, draw_blended };

enum hitbox_elements {hitbox_upleft, hitbox_downright};
struct hitbox { struct byte_point_2D range[2]; };

void no_action();

#endif
