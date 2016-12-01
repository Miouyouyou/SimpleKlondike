#include <myy.h>

void myy_init() {}
void myy_draw() {}
void myy_stop() {}

void myy_move(int x, int y) {}
void myy_key(unsigned int keycode) {}

void myy_generate_new_state() {}
void myy_save_state(struct myy_game_state *state) {}
void myy_resume_state(struct myy_game_state *state) {}

void myy_click(int x, int y, unsigned int button) {}
void myy_doubleclick(int x, int y, unsigned int button) {}
void myy_display_initialised(unsigned int width, unsigned int height) {}
