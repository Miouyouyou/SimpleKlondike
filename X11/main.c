#include "myy.h"
#include "init_window.h"

int main() {

  CreateWindowWithEGLContext("Nya !", 1280, 720);
  myy_display_initialised(1280, 720);
  myy_generate_new_state();
  myy_init_drawing();

  while(!UserInterrupt()) {
    myy_draw();
    RefreshWindow();
  }

  myy_stop();
  myy_cleanup_drawing();

}
