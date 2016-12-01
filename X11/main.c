#include "myy.h"
#include "init_window.h"

int main() {

  CreateWindowWithEGLContext("Nya !", 1280, 720);
  myy_display_initialised(1280, 720);
  myy_init();

  while(!UserInterrupt()) {
    myy_draw();
    RefreshWindow();
  }

}
