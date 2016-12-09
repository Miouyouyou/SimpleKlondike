#include <myy.h>
#include <helpers/log.h>
#include <stdlib.h>
#include <string.h>
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

const char browser_command_name[] = "xdg-open ";
#define SIZEOF_BROWSER_COMMAND (sizeof(browser_command_name)-1)

void myy_open_website(const char * restrict const url) {

  unsigned int url_size = myy_string_size((uint8_t * const) url);
  // Let's avoid blowing up the stack with an URL
  url_size = url_size < 2000 ? url_size : 2000;

  unsigned int browser_command_full_size =
    SIZEOF_BROWSER_COMMAND + url_size;
  uint8_t browser_command[browser_command_full_size+1];

  memcpy(browser_command, browser_command_name, SIZEOF_BROWSER_COMMAND);
  memcpy(browser_command+SIZEOF_BROWSER_COMMAND, url, url_size);

  browser_command[browser_command_full_size] = '\0';

  LOG("[X11/myy_open_website]  \n");
  LOG("  URL : %s, Command : %s\n", url, browser_command);

  system(browser_command);

}
