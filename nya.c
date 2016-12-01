# 1 "myy.c"
# 1 "<組み込み>"
# 1 "<コマンドライン>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<コマンドライン>" 2
# 1 "myy.c"
# 1 "myy.h" 1



void myy_init();
void myy_draw();
void myy_click(int x, int y, unsigned int button);
void myy_move(int x, int y);
void myy_key(unsigned int keycode);
# 2 "myy.c" 2

# 1 "/usr/include/GLES2/gl2.h" 1 3 4
# 39 "/usr/include/GLES2/gl2.h" 3 4
# 1 "/usr/include/GLES2/gl2platform.h" 1 3 4
# 20 "/usr/include/GLES2/gl2platform.h" 3 4
# 1 "/usr/include/KHR/khrplatform.h" 1 3 4
# 149 "/usr/include/KHR/khrplatform.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 25 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 366 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 402 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 403 "/usr/include/sys/cdefs.h" 2 3 4
# 367 "/usr/include/features.h" 2 3 4
# 390 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 391 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wchar.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/stdint.h" 2 3 4
# 36 "/usr/include/stdint.h" 3 4

# 36 "/usr/include/stdint.h" 3 4
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;

typedef long int int64_t;







typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;



typedef unsigned long int uint64_t;
# 65 "/usr/include/stdint.h" 3 4
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;

typedef long int int_least64_t;






typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;

typedef unsigned long int uint_least64_t;
# 90 "/usr/include/stdint.h" 3 4
typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 103 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 119 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 134 "/usr/include/stdint.h" 3 4
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
# 10 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stdint.h" 2 3 4
# 150 "/usr/include/KHR/khrplatform.h" 2 3 4
typedef int32_t khronos_int32_t;
typedef uint32_t khronos_uint32_t;
typedef int64_t khronos_int64_t;
typedef uint64_t khronos_uint64_t;
# 228 "/usr/include/KHR/khrplatform.h" 3 4
typedef signed char khronos_int8_t;
typedef unsigned char khronos_uint8_t;
typedef signed short int khronos_int16_t;
typedef unsigned short int khronos_uint16_t;
# 244 "/usr/include/KHR/khrplatform.h" 3 4
typedef signed long int khronos_intptr_t;
typedef unsigned long int khronos_uintptr_t;
typedef signed long int khronos_ssize_t;
typedef unsigned long int khronos_usize_t;






typedef float khronos_float_t;
# 267 "/usr/include/KHR/khrplatform.h" 3 4
typedef khronos_uint64_t khronos_utime_nanoseconds_t;
typedef khronos_int64_t khronos_stime_nanoseconds_t;
# 284 "/usr/include/KHR/khrplatform.h" 3 4
typedef enum {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = 0x7FFFFFFF
} khronos_boolean_enum_t;
# 21 "/usr/include/GLES2/gl2platform.h" 2 3 4
# 40 "/usr/include/GLES2/gl2.h" 2 3 4
# 56 "/usr/include/GLES2/gl2.h" 3 4
typedef khronos_int8_t GLbyte;
typedef khronos_float_t GLclampf;
typedef khronos_int32_t GLfixed;
typedef short GLshort;
typedef unsigned short GLushort;
typedef void GLvoid;
typedef struct __GLsync *GLsync;
typedef khronos_int64_t GLint64;
typedef khronos_uint64_t GLuint64;
typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef char GLchar;
typedef khronos_float_t GLfloat;
typedef khronos_ssize_t GLsizeiptr;
typedef khronos_intptr_t GLintptr;
typedef unsigned int GLbitfield;
typedef int GLint;
typedef unsigned char GLboolean;
typedef int GLsizei;
typedef khronos_uint8_t GLubyte;
# 377 "/usr/include/GLES2/gl2.h" 3 4
__attribute__((visibility("default"))) void glActiveTexture (GLenum texture);
__attribute__((visibility("default"))) void glAttachShader (GLuint program, GLuint shader);
__attribute__((visibility("default"))) void glBindAttribLocation (GLuint program, GLuint index, const GLchar *name);
__attribute__((visibility("default"))) void glBindBuffer (GLenum target, GLuint buffer);
__attribute__((visibility("default"))) void glBindFramebuffer (GLenum target, GLuint framebuffer);
__attribute__((visibility("default"))) void glBindRenderbuffer (GLenum target, GLuint renderbuffer);
__attribute__((visibility("default"))) void glBindTexture (GLenum target, GLuint texture);
__attribute__((visibility("default"))) void glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
__attribute__((visibility("default"))) void glBlendEquation (GLenum mode);
__attribute__((visibility("default"))) void glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
__attribute__((visibility("default"))) void glBlendFunc (GLenum sfactor, GLenum dfactor);
__attribute__((visibility("default"))) void glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
__attribute__((visibility("default"))) void glBufferData (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
__attribute__((visibility("default"))) void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
__attribute__((visibility("default"))) GLenum glCheckFramebufferStatus (GLenum target);
__attribute__((visibility("default"))) void glClear (GLbitfield mask);
__attribute__((visibility("default"))) void glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
__attribute__((visibility("default"))) void glClearDepthf (GLfloat d);
__attribute__((visibility("default"))) void glClearStencil (GLint s);
__attribute__((visibility("default"))) void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
__attribute__((visibility("default"))) void glCompileShader (GLuint shader);
__attribute__((visibility("default"))) void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
__attribute__((visibility("default"))) void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
__attribute__((visibility("default"))) void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
__attribute__((visibility("default"))) void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
__attribute__((visibility("default"))) GLuint glCreateProgram (void);
__attribute__((visibility("default"))) GLuint glCreateShader (GLenum type);
__attribute__((visibility("default"))) void glCullFace (GLenum mode);
__attribute__((visibility("default"))) void glDeleteBuffers (GLsizei n, const GLuint *buffers);
__attribute__((visibility("default"))) void glDeleteFramebuffers (GLsizei n, const GLuint *framebuffers);
__attribute__((visibility("default"))) void glDeleteProgram (GLuint program);
__attribute__((visibility("default"))) void glDeleteRenderbuffers (GLsizei n, const GLuint *renderbuffers);
__attribute__((visibility("default"))) void glDeleteShader (GLuint shader);
__attribute__((visibility("default"))) void glDeleteTextures (GLsizei n, const GLuint *textures);
__attribute__((visibility("default"))) void glDepthFunc (GLenum func);
__attribute__((visibility("default"))) void glDepthMask (GLboolean flag);
__attribute__((visibility("default"))) void glDepthRangef (GLfloat n, GLfloat f);
__attribute__((visibility("default"))) void glDetachShader (GLuint program, GLuint shader);
__attribute__((visibility("default"))) void glDisable (GLenum cap);
__attribute__((visibility("default"))) void glDisableVertexAttribArray (GLuint index);
__attribute__((visibility("default"))) void glDrawArrays (GLenum mode, GLint first, GLsizei count);
__attribute__((visibility("default"))) void glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices);
__attribute__((visibility("default"))) void glEnable (GLenum cap);
__attribute__((visibility("default"))) void glEnableVertexAttribArray (GLuint index);
__attribute__((visibility("default"))) void glFinish (void);
__attribute__((visibility("default"))) void glFlush (void);
__attribute__((visibility("default"))) void glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
__attribute__((visibility("default"))) void glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
__attribute__((visibility("default"))) void glFrontFace (GLenum mode);
__attribute__((visibility("default"))) void glGenBuffers (GLsizei n, GLuint *buffers);
__attribute__((visibility("default"))) void glGenerateMipmap (GLenum target);
__attribute__((visibility("default"))) void glGenFramebuffers (GLsizei n, GLuint *framebuffers);
__attribute__((visibility("default"))) void glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
__attribute__((visibility("default"))) void glGenTextures (GLsizei n, GLuint *textures);
__attribute__((visibility("default"))) void glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
__attribute__((visibility("default"))) void glGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
__attribute__((visibility("default"))) void glGetAttachedShaders (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
__attribute__((visibility("default"))) GLint glGetAttribLocation (GLuint program, const GLchar *name);
__attribute__((visibility("default"))) void glGetBooleanv (GLenum pname, GLboolean *data);
__attribute__((visibility("default"))) void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
__attribute__((visibility("default"))) GLenum glGetError (void);
__attribute__((visibility("default"))) void glGetFloatv (GLenum pname, GLfloat *data);
__attribute__((visibility("default"))) void glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
__attribute__((visibility("default"))) void glGetIntegerv (GLenum pname, GLint *data);
__attribute__((visibility("default"))) void glGetProgramiv (GLuint program, GLenum pname, GLint *params);
__attribute__((visibility("default"))) void glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
__attribute__((visibility("default"))) void glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
__attribute__((visibility("default"))) void glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
__attribute__((visibility("default"))) void glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
__attribute__((visibility("default"))) void glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
__attribute__((visibility("default"))) void glGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
__attribute__((visibility("default"))) const GLubyte * glGetString (GLenum name);
__attribute__((visibility("default"))) void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
__attribute__((visibility("default"))) void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
__attribute__((visibility("default"))) void glGetUniformfv (GLuint program, GLint location, GLfloat *params);
__attribute__((visibility("default"))) void glGetUniformiv (GLuint program, GLint location, GLint *params);
__attribute__((visibility("default"))) GLint glGetUniformLocation (GLuint program, const GLchar *name);
__attribute__((visibility("default"))) void glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params);
__attribute__((visibility("default"))) void glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params);
__attribute__((visibility("default"))) void glGetVertexAttribPointerv (GLuint index, GLenum pname, void **pointer);
__attribute__((visibility("default"))) void glHint (GLenum target, GLenum mode);
__attribute__((visibility("default"))) GLboolean glIsBuffer (GLuint buffer);
__attribute__((visibility("default"))) GLboolean glIsEnabled (GLenum cap);
__attribute__((visibility("default"))) GLboolean glIsFramebuffer (GLuint framebuffer);
__attribute__((visibility("default"))) GLboolean glIsProgram (GLuint program);
__attribute__((visibility("default"))) GLboolean glIsRenderbuffer (GLuint renderbuffer);
__attribute__((visibility("default"))) GLboolean glIsShader (GLuint shader);
__attribute__((visibility("default"))) GLboolean glIsTexture (GLuint texture);
__attribute__((visibility("default"))) void glLineWidth (GLfloat width);
__attribute__((visibility("default"))) void glLinkProgram (GLuint program);
__attribute__((visibility("default"))) void glPixelStorei (GLenum pname, GLint param);
__attribute__((visibility("default"))) void glPolygonOffset (GLfloat factor, GLfloat units);
__attribute__((visibility("default"))) void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
__attribute__((visibility("default"))) void glReleaseShaderCompiler (void);
__attribute__((visibility("default"))) void glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
__attribute__((visibility("default"))) void glSampleCoverage (GLfloat value, GLboolean invert);
__attribute__((visibility("default"))) void glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
__attribute__((visibility("default"))) void glShaderBinary (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
__attribute__((visibility("default"))) void glShaderSource (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
__attribute__((visibility("default"))) void glStencilFunc (GLenum func, GLint ref, GLuint mask);
__attribute__((visibility("default"))) void glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
__attribute__((visibility("default"))) void glStencilMask (GLuint mask);
__attribute__((visibility("default"))) void glStencilMaskSeparate (GLenum face, GLuint mask);
__attribute__((visibility("default"))) void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
__attribute__((visibility("default"))) void glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
__attribute__((visibility("default"))) void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
__attribute__((visibility("default"))) void glTexParameterf (GLenum target, GLenum pname, GLfloat param);
__attribute__((visibility("default"))) void glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
__attribute__((visibility("default"))) void glTexParameteri (GLenum target, GLenum pname, GLint param);
__attribute__((visibility("default"))) void glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
__attribute__((visibility("default"))) void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
__attribute__((visibility("default"))) void glUniform1f (GLint location, GLfloat v0);
__attribute__((visibility("default"))) void glUniform1fv (GLint location, GLsizei count, const GLfloat *value);
__attribute__((visibility("default"))) void glUniform1i (GLint location, GLint v0);
__attribute__((visibility("default"))) void glUniform1iv (GLint location, GLsizei count, const GLint *value);
__attribute__((visibility("default"))) void glUniform2f (GLint location, GLfloat v0, GLfloat v1);
__attribute__((visibility("default"))) void glUniform2fv (GLint location, GLsizei count, const GLfloat *value);
__attribute__((visibility("default"))) void glUniform2i (GLint location, GLint v0, GLint v1);
__attribute__((visibility("default"))) void glUniform2iv (GLint location, GLsizei count, const GLint *value);
__attribute__((visibility("default"))) void glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
__attribute__((visibility("default"))) void glUniform3fv (GLint location, GLsizei count, const GLfloat *value);
__attribute__((visibility("default"))) void glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
__attribute__((visibility("default"))) void glUniform3iv (GLint location, GLsizei count, const GLint *value);
__attribute__((visibility("default"))) void glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
__attribute__((visibility("default"))) void glUniform4fv (GLint location, GLsizei count, const GLfloat *value);
__attribute__((visibility("default"))) void glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
__attribute__((visibility("default"))) void glUniform4iv (GLint location, GLsizei count, const GLint *value);
__attribute__((visibility("default"))) void glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
__attribute__((visibility("default"))) void glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
__attribute__((visibility("default"))) void glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
__attribute__((visibility("default"))) void glUseProgram (GLuint program);
__attribute__((visibility("default"))) void glValidateProgram (GLuint program);
__attribute__((visibility("default"))) void glVertexAttrib1f (GLuint index, GLfloat x);
__attribute__((visibility("default"))) void glVertexAttrib1fv (GLuint index, const GLfloat *v);
__attribute__((visibility("default"))) void glVertexAttrib2f (GLuint index, GLfloat x, GLfloat y);
__attribute__((visibility("default"))) void glVertexAttrib2fv (GLuint index, const GLfloat *v);
__attribute__((visibility("default"))) void glVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z);
__attribute__((visibility("default"))) void glVertexAttrib3fv (GLuint index, const GLfloat *v);
__attribute__((visibility("default"))) void glVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
__attribute__((visibility("default"))) void glVertexAttrib4fv (GLuint index, const GLfloat *v);
__attribute__((visibility("default"))) void glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
__attribute__((visibility("default"))) void glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
# 4 "myy.c" 2
# 1 "/usr/include/GLES2/gl2ext.h" 1 3 4
# 72 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLBLENDBARRIERKHRPROC) (void);
# 91 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void ( *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
# 132 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (* PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (* PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, const void *userParam);
typedef GLuint (* PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void (* PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void (* PFNGLPOPDEBUGGROUPKHRPROC) (void);
typedef void (* PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void (* PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (* PFNGLOBJECTPTRLABELKHRPROC) (const void *ptr, GLsizei length, const GLchar *label);
typedef void (* PFNGLGETOBJECTPTRLABELKHRPROC) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (* PFNGLGETPOINTERVKHRPROC) (GLenum pname, void **params);
# 172 "/usr/include/GLES2/gl2ext.h" 3 4
typedef GLenum (* PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (void);
typedef void (* PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (* PFNGLGETNUNIFORMFVKHRPROC) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (* PFNGLGETNUNIFORMIVKHRPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (* PFNGLGETNUNIFORMUIVKHRPROC) (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
# 224 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void *GLeglImageOES;
typedef void (* PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, GLeglImageOES image);
typedef void (* PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLeglImageOES image);
# 295 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLGETPROGRAMBINARYOESPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
typedef void (* PFNGLPROGRAMBINARYOESPROC) (GLuint program, GLenum binaryFormat, const void *binary, GLint length);
# 309 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void *(* PFNGLMAPBUFFEROESPROC) (GLenum target, GLenum access);
typedef GLboolean (* PFNGLUNMAPBUFFEROESPROC) (GLenum target);
typedef void (* PFNGLGETBUFFERPOINTERVOESPROC) (GLenum target, GLenum pname, void **params);
# 350 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLMINSAMPLESHADINGOESPROC) (GLfloat value);
# 399 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLTEXIMAGE3DOESPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (* PFNGLTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (* PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (* PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
typedef void (* PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (* PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
# 473 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
# 482 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
typedef void (* PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, const GLuint *arrays);
typedef void (* PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
typedef GLboolean (* PFNGLISVERTEXARRAYOESPROC) (GLuint array);
# 526 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *numGroups, GLsizei groupsSize, GLuint *groups);
typedef void (* PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint group, GLint *numCounters, GLint *maxActiveCounters, GLsizei counterSize, GLuint *counters);
typedef void (* PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString);
typedef void (* PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length, GLchar *counterString);
typedef void (* PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint group, GLuint counter, GLenum pname, void *data);
typedef void (* PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
typedef void (* PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
typedef void (* PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint *counterList);
typedef void (* PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
typedef void (* PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
typedef void (* PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei dataSize, GLuint *data, GLint *bytesWritten);
# 571 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
# 582 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
# 591 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (* PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
typedef void (* PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint index, GLuint divisor);
# 630 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *source);
# 655 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount);
# 670 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (* PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (void);
# 704 "/usr/include/GLES2/gl2ext.h" 3 4
typedef GLsync (* PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
typedef GLboolean (* PFNGLISSYNCAPPLEPROC) (GLsync sync);
typedef void (* PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
typedef GLenum (* PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (* PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (* PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
typedef void (* PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
# 795 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
# 810 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei length, const GLchar *label);
typedef void (* PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label);
# 820 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei length, const GLchar *marker);
typedef void (* PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei length, const GLchar *marker);
typedef void (* PFNGLPOPGROUPMARKEREXTPROC) (void);
# 835 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments);
# 850 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLGENQUERIESEXTPROC) (GLsizei n, GLuint *ids);
typedef void (* PFNGLDELETEQUERIESEXTPROC) (GLsizei n, const GLuint *ids);
typedef GLboolean (* PFNGLISQUERYEXTPROC) (GLuint id);
typedef void (* PFNGLBEGINQUERYEXTPROC) (GLenum target, GLuint id);
typedef void (* PFNGLENDQUERYEXTPROC) (GLenum target);
typedef void (* PFNGLQUERYCOUNTEREXTPROC) (GLuint id, GLenum target);
typedef void (* PFNGLGETQUERYIVEXTPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (* PFNGLGETQUERYOBJECTIVEXTPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (* PFNGLGETQUERYOBJECTUIVEXTPROC) (GLuint id, GLenum pname, GLuint *params);
typedef void (* PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 *params);
typedef void (* PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 *params);
# 912 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, const GLenum *bufs);
# 922 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLENABLEIEXTPROC) (GLenum target, GLuint index);
typedef void (* PFNGLDISABLEIEXTPROC) (GLenum target, GLuint index);
typedef void (* PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum mode);
typedef void (* PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (* PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
typedef void (* PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (* PFNGLCOLORMASKIEXTPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef GLboolean (* PFNGLISENABLEDIEXTPROC) (GLenum target, GLuint index);
# 944 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum mode, GLint start, GLsizei count, GLsizei primcount);
typedef void (* PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
# 991 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
# 1004 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint index, GLuint divisor);
# 1018 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void *(* PFNGLMAPBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (* PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
# 1028 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (* PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei primcount);
# 1042 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (* PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
# 1057 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint index);
typedef void (* PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, const GLenum *location, const GLint *indices);
typedef void (* PFNGLGETINTEGERI_VEXTPROC) (GLenum target, GLuint index, GLint *data);
# 1076 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
# 1107 "/usr/include/GLES2/gl2ext.h" 3 4
typedef GLenum (* PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (void);
typedef void (* PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (* PFNGLGETNUNIFORMFVEXTPROC) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (* PFNGLGETNUNIFORMIVEXTPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
# 1140 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint program);
typedef void (* PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
typedef GLuint (* PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei count, const GLchar **strings);
typedef void (* PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, const GLuint *pipelines);
typedef void (* PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
typedef void (* PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (* PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
typedef GLboolean (* PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
typedef void (* PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint program, GLenum pname, GLint value);
typedef void (* PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint program, GLint location, GLfloat v0);
typedef void (* PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint program, GLint location, GLint v0);
typedef void (* PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (* PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (* PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1);
typedef void (* PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (* PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (* PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (* PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (* PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (* PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (* PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (* PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
typedef void (* PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint program, GLint location, GLuint v0);
typedef void (* PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (* PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (* PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (* PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (* PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (* PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (* PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
# 1317 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint value);
# 1327 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLTEXPARAMETERIIVEXTPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (* PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum target, GLenum pname, const GLuint *params);
typedef void (* PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (* PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum target, GLenum pname, GLuint *params);
typedef void (* PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (* PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, const GLuint *param);
typedef void (* PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (* PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
# 1363 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLTEXBUFFEREXTPROC) (GLenum target, GLenum internalformat, GLuint buffer);
typedef void (* PFNGLTEXBUFFERRANGEEXTPROC) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
# 1437 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLTEXSTORAGE1DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (* PFNGLTEXSTORAGE2DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (* PFNGLTEXSTORAGE3DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (* PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (* PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (* PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
# 1465 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
# 1489 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (* PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
# 1549 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
typedef void (* PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
typedef void (* PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
typedef void (* PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
typedef void (* PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
typedef void (* PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *nextQueryId);
typedef void (* PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar *counterName, GLuint counterDescLength, GLchar *counterDesc, GLuint *counterOffset, GLuint *counterDataSize, GLuint *counterTypeEnum, GLuint *counterDataTypeEnum, GLuint64 *rawCounterMaxValue);
typedef void (* PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei dataSize, GLvoid *data, GLuint *bytesWritten);
typedef void (* PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
typedef void (* PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint queryNameLength, GLchar *queryName, GLuint *dataSize, GLuint *noCounters, GLuint *noInstances, GLuint *capsMask);
# 1624 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint value);
typedef void (* PFNGLBLENDBARRIERNVPROC) (void);
# 1641 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
# 1658 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLCOVERAGEMASKNVPROC) (GLboolean mask);
typedef void (* PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
# 1706 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLDRAWBUFFERSNVPROC) (GLsizei n, const GLenum *bufs);







typedef void (* PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (* PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
# 1736 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLDELETEFENCESNVPROC) (GLsizei n, const GLuint *fences);
typedef void (* PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
typedef GLboolean (* PFNGLISFENCENVPROC) (GLuint fence);
typedef GLboolean (* PFNGLTESTFENCENVPROC) (GLuint fence);
typedef void (* PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
typedef void (* PFNGLFINISHFENCENVPROC) (GLuint fence);
typedef void (* PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
# 1760 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
# 1771 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
# 1784 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint index, GLuint divisor);
# 1798 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (* PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
# 1817 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLREADBUFFERNVPROC) (GLenum mode);
# 1882 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
# 1898 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *num, GLsizei size, GLuint *driverControls);
typedef void (* PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei bufSize, GLsizei *length, GLchar *driverControlString);
typedef void (* PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
typedef void (* PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
# 1923 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *numTextures);
typedef void (* PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *numBuffers);
typedef void (* PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *numRenderbuffers);
typedef void (* PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *numFramebuffers);
typedef void (* PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
typedef void (* PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum target, GLenum pname, GLint param);
typedef void (* PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void *texels);
typedef void (* PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum target, void **params);
# 1945 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *numShaders);
typedef void (* PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *numPrograms);
typedef GLboolean (* PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint program);
typedef void (* PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint program, GLenum shadertype, GLchar *source, GLint *length);
# 1996 "/usr/include/GLES2/gl2ext.h" 3 4
typedef void (* PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
typedef void (* PFNGLENDTILINGQCOMPROC) (GLbitfield preserveMask);
# 5 "myy.c" 2
# 1 "./helpers/base_gl.h" 1

# 1 "./helpers/base_gl.h"
struct gleanup {
  void (*check)(GLuint, GLenum, GLint* );
  int verif;
  void (*log)(GLuint, GLsizei, GLsizei*, GLchar*);
};

struct textures {
  int name_i;
  int size;
  int width;
  int height;
  GLuint GLformat;
  GLuint GLtype;
};



int glhLoadShader(GLenum shaderType, const char *name, GLuint program);
GLuint glhSetupProgram(
  const char* vsh_filename, const char* fsh_filename, uint8_t n_attributes,
  const char* attributes_names);
GLuint glhSetupAndUse(const char* vsh_filename, const char* fsh_filename,
                      uint8_t n_attributes, const char* attributes_names);
void uploadTextures(const char *textures_names, int n, GLuint *texid);
# 6 "myy.c" 2
# 1 "./helpers/struct.h" 1
# 7 "myy.c" 2
# 1 "./helpers/log.h" 1


# 1 "/usr/include/stdio.h" 1 3 4
# 29 "/usr/include/stdio.h" 3 4




# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stddef.h" 1 3 4
# 216 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stddef.h" 3 4

# 216 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 34 "/usr/include/stdio.h" 2 3 4

# 1 "/usr/include/bits/types.h" 1 3 4
# 27 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
# 121 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 122 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;
# 36 "/usr/include/stdio.h" 2 3 4
# 44 "/usr/include/stdio.h" 3 4
struct _IO_FILE;



typedef struct _IO_FILE FILE;





# 64 "/usr/include/stdio.h" 3 4
typedef struct _IO_FILE __FILE;
# 74 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/libio.h" 1 3 4
# 31 "/usr/include/libio.h" 3 4
# 1 "/usr/include/_G_config.h" 1 3 4
# 15 "/usr/include/_G_config.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stddef.h" 1 3 4
# 16 "/usr/include/_G_config.h" 2 3 4




# 1 "/usr/include/wchar.h" 1 3 4
# 82 "/usr/include/wchar.h" 3 4
typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
# 21 "/usr/include/_G_config.h" 2 3 4
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
# 32 "/usr/include/libio.h" 2 3 4
# 49 "/usr/include/libio.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.2.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 50 "/usr/include/libio.h" 2 3 4
# 144 "/usr/include/libio.h" 3 4
struct _IO_jump_t; struct _IO_FILE;
# 154 "/usr/include/libio.h" 3 4
typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
# 177 "/usr/include/libio.h" 3 4
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
# 245 "/usr/include/libio.h" 3 4
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
# 293 "/usr/include/libio.h" 3 4
  __off64_t _offset;
# 302 "/usr/include/libio.h" 3 4
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;

  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
# 338 "/usr/include/libio.h" 3 4
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
# 390 "/usr/include/libio.h" 3 4
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
# 434 "/usr/include/libio.h" 3 4
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
# 464 "/usr/include/libio.h" 3 4
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
# 75 "/usr/include/stdio.h" 2 3 4




typedef __gnuc_va_list va_list;
# 90 "/usr/include/stdio.h" 3 4
typedef __off_t off_t;
# 102 "/usr/include/stdio.h" 3 4
typedef __ssize_t ssize_t;







typedef _G_fpos_t fpos_t;




# 164 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 165 "/usr/include/stdio.h" 2 3 4



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;







extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));




extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));








extern FILE *tmpfile (void) __attribute__ ((__warn_unused_result__));
# 209 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));





extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
# 227 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__warn_unused_result__));








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

# 252 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 266 "/usr/include/stdio.h" 3 4






extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) __attribute__ ((__warn_unused_result__));




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
# 295 "/usr/include/stdio.h" 3 4

# 306 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
# 319 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));






extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));





extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));








extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));





extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));

# 412 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));








extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) __attribute__ ((__warn_unused_result__));




extern int scanf (const char *__restrict __format, ...) __attribute__ ((__warn_unused_result__));

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
# 443 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                          __attribute__ ((__warn_unused_result__));
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                         __attribute__ ((__warn_unused_result__));
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 463 "/usr/include/stdio.h" 3 4








extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__warn_unused_result__));





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) __attribute__ ((__warn_unused_result__));


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
# 494 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__warn_unused_result__));
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) __attribute__ ((__warn_unused_result__));
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 522 "/usr/include/stdio.h" 3 4









extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);

# 550 "/usr/include/stdio.h" 3 4
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 561 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);











extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);

# 594 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);








extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __attribute__ ((__warn_unused_result__));
# 640 "/usr/include/stdio.h" 3 4

# 665 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));







extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));








extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

# 737 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) __attribute__ ((__warn_unused_result__));




extern void rewind (FILE *__stream);

# 773 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) __attribute__ ((__warn_unused_result__));
# 792 "/usr/include/stdio.h" 3 4






extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 815 "/usr/include/stdio.h" 3 4

# 824 "/usr/include/stdio.h" 3 4


extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));








extern void perror (const char *__s);






# 1 "/usr/include/bits/sys_errlist.h" 1 3 4
# 26 "/usr/include/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern const char *const sys_errlist[];
# 854 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
# 872 "/usr/include/stdio.h" 3 4
extern FILE *popen (const char *__command, const char *__modes) __attribute__ ((__warn_unused_result__));





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
# 912 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 933 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio.h" 1 3 4
# 43 "/usr/include/bits/stdio.h" 3 4
extern __inline __attribute__ ((__gnu_inline__)) int
getchar (void)
{
  return _IO_getc (stdin);
}




extern __inline __attribute__ ((__gnu_inline__)) int
fgetc_unlocked (FILE *__fp)
{
  return (__builtin_expect (((__fp)->_IO_read_ptr >= (__fp)->_IO_read_end), 0) ? __uflow (__fp) : *(unsigned char *) (__fp)->_IO_read_ptr++);
}





extern __inline __attribute__ ((__gnu_inline__)) int
getc_unlocked (FILE *__fp)
{
  return (__builtin_expect (((__fp)->_IO_read_ptr >= (__fp)->_IO_read_end), 0) ? __uflow (__fp) : *(unsigned char *) (__fp)->_IO_read_ptr++);
}


extern __inline __attribute__ ((__gnu_inline__)) int
getchar_unlocked (void)
{
  return (__builtin_expect (((stdin)->_IO_read_ptr >= (stdin)->_IO_read_end), 0) ? __uflow (stdin) : *(unsigned char *) (stdin)->_IO_read_ptr++);
}




extern __inline __attribute__ ((__gnu_inline__)) int
putchar (int __c)
{
  return _IO_putc (__c, stdout);
}




extern __inline __attribute__ ((__gnu_inline__)) int
fputc_unlocked (int __c, FILE *__stream)
{
  return (__builtin_expect (((__stream)->_IO_write_ptr >= (__stream)->_IO_write_end), 0) ? __overflow (__stream, (unsigned char) (__c)) : (unsigned char) (*(__stream)->_IO_write_ptr++ = (__c)));
}





extern __inline __attribute__ ((__gnu_inline__)) int
putc_unlocked (int __c, FILE *__stream)
{
  return (__builtin_expect (((__stream)->_IO_write_ptr >= (__stream)->_IO_write_end), 0) ? __overflow (__stream, (unsigned char) (__c)) : (unsigned char) (*(__stream)->_IO_write_ptr++ = (__c)));
}


extern __inline __attribute__ ((__gnu_inline__)) int
putchar_unlocked (int __c)
{
  return (__builtin_expect (((stdout)->_IO_write_ptr >= (stdout)->_IO_write_end), 0) ? __overflow (stdout, (unsigned char) (__c)) : (unsigned char) (*(stdout)->_IO_write_ptr++ = (__c)));
}
# 124 "/usr/include/bits/stdio.h" 3 4
extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) feof_unlocked (FILE *__stream)
{
  return (((__stream)->_flags & 0x10) != 0);
}


extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) ferror_unlocked (FILE *__stream)
{
  return (((__stream)->_flags & 0x20) != 0);
}
# 934 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/bits/stdio2.h" 1 3 4
# 23 "/usr/include/bits/stdio2.h" 3 4
extern int __sprintf_chk (char *__restrict __s, int __flag, size_t __slen,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int __vsprintf_chk (char *__restrict __s, int __flag, size_t __slen,
      const char *__restrict __format,
      __gnuc_va_list __ap) __attribute__ ((__nothrow__ , __leaf__));


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) sprintf (char *__restrict __s, const char *__restrict __fmt, ...)
{
  return __builtin___sprintf_chk (__s, 2 - 1,
      __builtin_object_size (__s, 2 > 1), __fmt, __builtin_va_arg_pack ());
}






extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) vsprintf (char *__restrict __s, const char *__restrict __fmt, __gnuc_va_list __ap)

{
  return __builtin___vsprintf_chk (__s, 2 - 1,
       __builtin_object_size (__s, 2 > 1), __fmt, __ap);
}



extern int __snprintf_chk (char *__restrict __s, size_t __n, int __flag,
      size_t __slen, const char *__restrict __format,
      ...) __attribute__ ((__nothrow__ , __leaf__));
extern int __vsnprintf_chk (char *__restrict __s, size_t __n, int __flag,
       size_t __slen, const char *__restrict __format,
       __gnuc_va_list __ap) __attribute__ ((__nothrow__ , __leaf__));


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) snprintf (char *__restrict __s, size_t __n, const char *__restrict __fmt, ...)

{
  return __builtin___snprintf_chk (__s, __n, 2 - 1,
       __builtin_object_size (__s, 2 > 1), __fmt, __builtin_va_arg_pack ());
}






extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
__attribute__ ((__nothrow__ , __leaf__)) vsnprintf (char *__restrict __s, size_t __n, const char *__restrict __fmt, __gnuc_va_list __ap)

{
  return __builtin___vsnprintf_chk (__s, __n, 2 - 1,
        __builtin_object_size (__s, 2 > 1), __fmt, __ap);
}





extern int __fprintf_chk (FILE *__restrict __stream, int __flag,
     const char *__restrict __format, ...);
extern int __printf_chk (int __flag, const char *__restrict __format, ...);
extern int __vfprintf_chk (FILE *__restrict __stream, int __flag,
      const char *__restrict __format, __gnuc_va_list __ap);
extern int __vprintf_chk (int __flag, const char *__restrict __format,
     __gnuc_va_list __ap);


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
fprintf (FILE *__restrict __stream, const char *__restrict __fmt, ...)
{
  return __fprintf_chk (__stream, 2 - 1, __fmt,
   __builtin_va_arg_pack ());
}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
printf (const char *__restrict __fmt, ...)
{
  return __printf_chk (2 - 1, __fmt, __builtin_va_arg_pack ());
}







extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
vprintf (const char *__restrict __fmt, __gnuc_va_list __ap)
{

  return __vfprintf_chk (stdout, 2 - 1, __fmt, __ap);



}

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
vfprintf (FILE *__restrict __stream,
   const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __vfprintf_chk (__stream, 2 - 1, __fmt, __ap);
}


extern int __dprintf_chk (int __fd, int __flag, const char *__restrict __fmt,
     ...) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int __vdprintf_chk (int __fd, int __flag,
      const char *__restrict __fmt, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 3, 0)));


extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
dprintf (int __fd, const char *__restrict __fmt, ...)
{
  return __dprintf_chk (__fd, 2 - 1, __fmt,
   __builtin_va_arg_pack ());
}





extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) int
vdprintf (int __fd, const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __vdprintf_chk (__fd, 2 - 1, __fmt, __ap);
}
# 241 "/usr/include/bits/stdio2.h" 3 4
extern char *__fgets_chk (char *__restrict __s, size_t __size, int __n,
     FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern char *__fgets_alias (char *__restrict __s, int __n, FILE *__restrict __stream) __asm__ ("" "fgets")

                                        __attribute__ ((__warn_unused_result__));
extern char *__fgets_chk_warn (char *__restrict __s, size_t __size, int __n, FILE *__restrict __stream) __asm__ ("" "__fgets_chk")


     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("fgets called with bigger size than length " "of destination buffer")))
                                 ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) char *
fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
{
  if (__builtin_object_size (__s, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p (__n) || __n <= 0)
 return __fgets_chk (__s, __builtin_object_size (__s, 2 > 1), __n, __stream);

      if ((size_t) __n > __builtin_object_size (__s, 2 > 1))
 return __fgets_chk_warn (__s, __builtin_object_size (__s, 2 > 1), __n, __stream);
    }
  return __fgets_alias (__s, __n, __stream);
}

extern size_t __fread_chk (void *__restrict __ptr, size_t __ptrlen,
      size_t __size, size_t __n,
      FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern size_t __fread_alias (void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __asm__ ("" "fread")


            __attribute__ ((__warn_unused_result__));
extern size_t __fread_chk_warn (void *__restrict __ptr, size_t __ptrlen, size_t __size, size_t __n, FILE *__restrict __stream) __asm__ ("" "__fread_chk")




     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("fread called with bigger size * nmemb than length " "of destination buffer")))
                                 ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) size_t
fread (void *__restrict __ptr, size_t __size, size_t __n,
       FILE *__restrict __stream)
{
  if (__builtin_object_size (__ptr, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__size)
   || !__builtin_constant_p (__n)
   || (__size | __n) >= (((size_t) 1) << (8 * sizeof (size_t) / 2)))
 return __fread_chk (__ptr, __builtin_object_size (__ptr, 0), __size, __n, __stream);

      if (__size * __n > __builtin_object_size (__ptr, 0))
 return __fread_chk_warn (__ptr, __builtin_object_size (__ptr, 0), __size, __n, __stream);
    }
  return __fread_alias (__ptr, __size, __n, __stream);
}
# 327 "/usr/include/bits/stdio2.h" 3 4
extern size_t __fread_unlocked_chk (void *__restrict __ptr, size_t __ptrlen,
        size_t __size, size_t __n,
        FILE *__restrict __stream) __attribute__ ((__warn_unused_result__));
extern size_t __fread_unlocked_alias (void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __asm__ ("" "fread_unlocked")


                     __attribute__ ((__warn_unused_result__));
extern size_t __fread_unlocked_chk_warn (void *__restrict __ptr, size_t __ptrlen, size_t __size, size_t __n, FILE *__restrict __stream) __asm__ ("" "__fread_unlocked_chk")




     __attribute__ ((__warn_unused_result__)) __attribute__((__warning__ ("fread_unlocked called with bigger size * nmemb than " "length of destination buffer")))
                                        ;

extern __inline __attribute__ ((__always_inline__)) __attribute__ ((__gnu_inline__)) __attribute__ ((__artificial__)) __attribute__ ((__warn_unused_result__)) size_t
fread_unlocked (void *__restrict __ptr, size_t __size, size_t __n,
  FILE *__restrict __stream)
{
  if (__builtin_object_size (__ptr, 0) != (size_t) -1)
    {
      if (!__builtin_constant_p (__size)
   || !__builtin_constant_p (__n)
   || (__size | __n) >= (((size_t) 1) << (8 * sizeof (size_t) / 2)))
 return __fread_unlocked_chk (__ptr, __builtin_object_size (__ptr, 0), __size, __n,
         __stream);

      if (__size * __n > __builtin_object_size (__ptr, 0))
 return __fread_unlocked_chk_warn (__ptr, __builtin_object_size (__ptr, 0), __size, __n,
       __stream);
    }


  if (__builtin_constant_p (__size)
      && __builtin_constant_p (__n)
      && (__size | __n) < (((size_t) 1) << (8 * sizeof (size_t) / 2))
      && __size * __n <= 8)
    {
      size_t __cnt = __size * __n;
      char *__cptr = (char *) __ptr;
      if (__cnt == 0)
 return 0;

      for (; __cnt > 0; --__cnt)
 {
   int __c = (__builtin_expect (((__stream)->_IO_read_ptr >= (__stream)->_IO_read_end), 0) ? __uflow (__stream) : *(unsigned char *) (__stream)->_IO_read_ptr++);
   if (__c == (-1))
     break;
   *__cptr++ = __c;
 }
      return (__cptr - (char *) __ptr) / __size;
    }

  return __fread_unlocked_alias (__ptr, __size, __n, __stream);
}
# 937 "/usr/include/stdio.h" 2 3 4






# 4 "./helpers/log.h" 2
# 8 "myy.c" 2
# 16 "myy.c"

# 16 "myy.c"
struct point_2D { GLfloat x, y; } __attribute__((__packed__)) __attribute__((aligned(4)));
struct triangle_2D { struct point_2D a, b, c; } __attribute__((__packed__)) __attribute__((aligned(4)));
struct two_triangles_quad_2D {
  struct triangle_2D first, second; } __attribute__((__packed__)) __attribute__((aligned(4)));

struct textured_point_2D { GLfloat x, y, s, t; } __attribute__((__packed__)) __attribute__((aligned(4)));
struct textured_triangle_2D { struct textured_point_2D a, b, c; } __attribute__((__packed__)) __attribute__((aligned(4)));
struct two_triangles_textured_quad_2D {
  struct textured_triangle_2D first, second;
}

typedef struct two_triangles_textured_quad_2D GLCard;
# 36 "myy.c"
GLCard sample_card = {
  .first = {
    .a = { .x = -0.09f, .y = 0.254f, .s = 0, .t = 0 +0.25f},
    .b = { .x = -0.09f, .y = -0.254f, .s = 0, .t = 0},
    .c = { .x = 0.09f, .y = 0.254f, .s = 0 +0.0625f, .t = 0 +0.25f},
  },
  .second = {
    .a = { .x = 0.09f, .y = -0.254f, .s = 0 +0.0625f, .t = 0},
    .b = { .x = 0.09f, .y = 0.254f, .s = 0 +0.0625f, .t = 0 +0.25f},
    .c = { .x = -0.09f, .y = -0.254f, .s = 0, .t = 0}
  },
};

GLCard cards[120];
unsigned int n_cards = 0;
# 67 "myy.c"
void copy_card_with_offset(GLfloat *model, GLfloat x_offset, GLfloat y_offset,
                           GLfloat *card_copy) {
  for (int i = 0; i < 12; i += 4) {
    card_copy[i] = model[i] + x_offset;
    card_copy[i+1] = model[i+1] + y_offset;
  }
}
# 85 "myy.c"
void add_card(GLfloat x_offset, GLfloat y_offset) {
  copy_card_with_offset((GLfloat *) &sample_card, x_offset, y_offset,
                        (GLfloat *) (cards+n_cards));
  n_cards++;
}

void move_card_at(unsigned int i, GLfloat x_offset, GLfloat y_offset) {
  copy_card_with_offset((GLfloat *) &sample_card, x_offset, y_offset,
                        (GLfloat *) (cards+i));
}

void move_last_card_at(GLfloat x, GLfloat y) {
  if (n_cards > 0) move_card_at(n_cards-1, x, y);
  else fprintf(
# 98 "myy.c" 3 4
      stderr
# 98 "myy.c"
      , "%s\n", "Currently no card in the deck");
}

void move_last_card_previous_y(GLfloat x) {
  move_last_card_at(x, cards[n_cards-1 -1].first.a.y-0.254f);
}

void remove_last_card() { if (n_cards) n_cards--; }

GLfloat menu_bar[8] = {
  0.85f, 1.0f,
  0.85f, -1.0f,
  1.0f, 1.0f,
  1.0f, -1.0f
};

enum attributes { attrs_xyst, attrs_n };

GLint cards_tex;
void myy_init() {
  uploadTextures("cards.raw\0", 1, &cards_tex);
  GLuint program =
    glhSetupAndUse("shaders/standard.vert", "shaders/standard.frag",
                   1, "xyst");
  add_card(-0.2f, 0.4f);
  glEnableVertexAttribArray(attrs_xyst);
}

void myy_draw() {
  glClear( 
# 127 "myy.c" 3 4
          0x00000100 
# 127 "myy.c"
                              | 
# 127 "myy.c" 3 4
                                0x00004000 
# 127 "myy.c"
                                                    );
  glClearColor(0.2f,0.6f,0.3f,1.0f);
  glVertexAttribPointer(attrs_xyst, 4, 
# 129 "myy.c" 3 4
                                      0x1406
# 129 "myy.c"
                                              , 
# 129 "myy.c" 3 4
                                                0
# 129 "myy.c"
                                                        , 0, (GLfloat *) cards);
  glDrawArrays(
# 130 "myy.c" 3 4
              0x0004
# 130 "myy.c"
                          , 0, n_cards*6);
  glVertexAttribPointer(attrs_xyst, 2, 
# 131 "myy.c" 3 4
                                      0x1406
# 131 "myy.c"
                                              , 
# 131 "myy.c" 3 4
                                                0
# 131 "myy.c"
                                                        , 0, (GLfloat *) &menu_bar);
  glDrawArrays(
# 132 "myy.c" 3 4
              0x0005
# 132 "myy.c"
                               , 0, 4);
}

void normalise(GLfloat *gx, int x, GLfloat *gy, int y) {
  *gx = (x/640.0f)-1;
  *gy = (y/360.0f)-1;
}

unsigned int lock;
void myy_click(int x, int y, unsigned int button) {

  GLfloat norm_x, norm_y;
  normalise(&norm_x, x, &norm_y, y);
  if (norm_x < 0.80f) {
    if (!lock) move_last_card_at(norm_x, norm_y);
    else move_last_card_previous_y(norm_x);
  }
}
void myy_move(int x, int y) {

}






void myy_key(unsigned int keycode) {
  switch(keycode) {
    case 24: add_card(0,0); break;
    case 25: remove_last_card(); break;
    case 46: lock ^= 1; break;
  }
}
