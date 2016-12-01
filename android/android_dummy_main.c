#include <jni.h>
#include <errno.h>

#include <android/log.h>
#include "android_native_app_glue.h"

#include <EGL/egl.h>
#include <egl_common/myy_eglattrs.h>

#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h> /* chdir */

/* Bad mkdir */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <myy.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

static struct egl_elements {
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;
} egl;

static struct current_window {
  uint16_t width, height;
} current_window;

/**
 * Initialize an EGL context for the current display.
 */
static int add_egl_context_to
(NativeWindowType window, struct egl_elements *e,
 struct current_window *window_infos) {
  // initialize OpenGL ES and EGL

  /*
    * Here specify the attributes of the desired configuration.
    * Below, we select an EGLConfig with at least 8 bits per color
    * component compatible with on-screen windows
    */
  EGLint w, h, dummy, format;
  EGLint numConfigs;
  EGLConfig config;
  EGLSurface surface;
  EGLContext context;

  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  eglInitialize(display, 0, 0);

  /* Here, the application chooses the configuration it desires. In this
    * sample, we have a very simplified selection process, where we pick
    * the first EGLConfig that matches our criteria */
  eglChooseConfig(display, eglAttribs, &config, 1, &numConfigs);

  /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
    * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
    * As soon as we picked a EGLConfig, we can safely reconfigure the
    * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
  eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

  /* Implicitly provided by EGL on Android */
  ANativeWindow_setBuffersGeometry(window, 0, 0, format);

  surface = eglCreateWindowSurface(display, config, window, NULL);
  context = eglCreateContext(display, config, NULL, GiveMeGLES2);

  if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
      return -1;
  }

  e->context = context;
  e->display = display;
  e->surface = surface;

  eglQuerySurface(display, surface, EGL_WIDTH, &w);
  eglQuerySurface(display, surface, EGL_HEIGHT, &h);

  myy_display_initialised(w, h);

  window_infos->width = w;
  window_infos->height = h;

  LOGW("Window initialised\n");
  return 0;
}

static void egl_sync(struct egl_elements* e) {
  eglSwapBuffers(e->display, e->surface);
}

static void egl_stop(struct egl_elements* e) {
  if (e->display != EGL_NO_DISPLAY) {
    eglMakeCurrent(e->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (e->context != EGL_NO_CONTEXT)
        eglDestroyContext(e->display, e->context);
    if (e->surface != EGL_NO_SURFACE)
        eglDestroySurface(e->display, e->surface);
    eglTerminate(e->display);
  }
  e->display = EGL_NO_DISPLAY;
  e->context = EGL_NO_CONTEXT;
  e->surface = EGL_NO_SURFACE;
}


/**
 * Shared state for our app.
 */

int animating;

/**
 * Process the next input event.
 */
unsigned long last_tap = 0;
static int32_t engine_handle_input
(struct android_app* app, AInputEvent* event) {
  // int pc = AMotionEvent_getPointerCount(event);
  // for (int p = 0; p < pc; p++)

  unsigned long tap_time = AMotionEvent_getEventTime(event);

  unsigned int
    action = AMotionEvent_getAction(event),
    x = AMotionEvent_getX(event, 0),
    y = current_window.height - AMotionEvent_getY(event, 0);

  switch(action) {
  case AMOTION_EVENT_ACTION_DOWN:
    if (tap_time - last_tap > 0x10000000) myy_click(x, y, 1);
    else myy_doubleclick(x, y, 1);
    last_tap = tap_time;
    break;
  case AMOTION_EVENT_ACTION_MOVE:
    myy_move(x, y);
    break;
  }

  return 1;
}

static void goto_data_dir(const char* data_dir) {
  chdir(data_dir);
}

struct myy_game_state game_state = {0};

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {

  struct egl_elements *e = &egl;
  struct myy_game_state *state = &game_state;
  switch (cmd) {
  case APP_CMD_INIT_WINDOW:
    LOGW("======================================");
    LOGW("Initialising window");
    if (app->window != NULL)
      add_egl_context_to(app->window, e, &current_window);
    myy_init_drawing();
    break;
  case APP_CMD_RESUME:
    LOGW("Resuming !");
    /* Terrible idea but wrapping file management calls around
     * AAssetsManager is a pain... */
    mkdir("/sdcard/OpenGL", 00777);
    chdir("/sdcard/OpenGL");
    myy_resume_state(state);
    animating = 1;
    break;
  case APP_CMD_PAUSE:
    LOGW("Pause !");
    animating = 0;
    myy_save_state(state);
    break;
  case APP_CMD_STOP:
    myy_stop();
    break;
  case APP_CMD_SAVE_STATE:
    LOGW("State saved !");
    break;
  case APP_CMD_TERM_WINDOW:
    LOGW("Terminated !");
    myy_cleanup_drawing();
    egl_stop(e);
    break;
  }

}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* app) {

  // Make sure glue isn't stripped.
  app_dummy();

  app->onAppCmd = engine_handle_cmd;
  app->onInputEvent = engine_handle_input;

  // Copy assets files into the internalDataPath folder
  goto_data_dir(app->activity->internalDataPath);
  /*copy_assets_to_internal_memory(app->activity->assetManager);*/

  // loop waiting for stuff to do.

  struct egl_elements* e = &egl;
  while (1) {
    // Read all pending events.
    int ident;
    int events;
    struct android_poll_source* source;

    // If not animating, we will block forever waiting for events.
    // If animating, we loop until all events are read, then continue
    // to draw the next frame of animation.
    while ((ident=ALooper_pollAll(animating ? 0 : -1, NULL, &events,
                                  (void**)&source)) >= 0) {

      // Process this event.
      if (source != NULL) { source->process(app, source); }

      // If a sensor has data, process it now.
      if (ident == LOOPER_ID_USER) {}

      // Check if we are exiting.
      if (app->destroyRequested != 0) {
        myy_stop();
        animating = 0;
        return;
      }
    }

    if (animating && app->window != NULL) {
      // Drawing is throttled to the screen update rate, so there
      // is no need to do timing here.
      myy_draw();
      egl_sync(e);
    }
  }
}
