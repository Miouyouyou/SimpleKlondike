#include <EGL/egl.h>

const EGLint eglAttribs[] =  {
  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
  EGL_CONFORMANT, EGL_OPENGL_ES2_BIT,
  EGL_SAMPLES,			   4,
  EGL_RED_SIZE,        5,
  EGL_GREEN_SIZE,      6,
  EGL_BLUE_SIZE,       5,
  EGL_ALPHA_SIZE,      8,
  EGL_DEPTH_SIZE,     16,
  EGL_NONE
};

const EGLint GiveMeGLES2[] = {
  EGL_CONTEXT_CLIENT_VERSION, 2,
  EGL_NONE
};
