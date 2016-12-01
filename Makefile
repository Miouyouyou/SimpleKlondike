OBJS = base_gl.o gl_cards.o basics.o klondike.o myy.o
CC = gcc
CFLAGS = -march=native -fPIC -g3 -fuse-ld=gold
INCLUDE_DIRS = -I.
LDFLAGS = -lGLESv2
CCC = $(CC) $(CFLAGS) $(INCLUDE_DIRS)

LIBRARY = libmyy.so

.PHONY: all
all: x11 $(LIBRARY)

.PHONY: x11
x11:
	$(MAKE) -C X11 all
	cp X11/Program ./

.PHONY: distclean
distclean: clean
	$(RM) Program
	$(RM) *~

tests: test-selection

$(LIBRARY): $(OBJS)
	$(CCC) --shared -o libmyy.so $(OBJS) $(LDFLAGS)

myy.o: myy.c
	$(CCC) -c myy.c

base_gl.o: helpers/base_gl.c
	$(CCC) -c helpers/base_gl.c

klondike.o: cards_logic/klondike.c
	$(CCC) -c cards_logic/klondike.c

basics.o: cards_logic/basics.c
	$(CCC) -c cards_logic/basics.c

gl_cards.o: cards_logic/gl_cards.c
	$(CCC) -c cards_logic/gl_cards.c

test-selection.o: tests/test-selection.c
	$(CCC) -c tests/test-selection.c

test-selection: test-selection.o klondike.o basics.o
	$(CCC) -o test-selection test-selection.o klondike.o basics.o

test-load-and-save.o: tests/test-load-and-save.c tests/test-utilities.h cards_logic/klondike.c
	$(CCC) -c tests/test-load-and-save.c

test-load-and-save: test-load-and-save.o klondike.o basics.o
	$(CCC) -o test-load-and-save test-load-and-save.o klondike.o basics.o

test-quickmove.o: tests/test-quickmove.c tests/test-utilities.h cards_logic/klondike.c
	$(CCC) -c tests/test-quickmove.c

test-quickmove: test-quickmove.o klondike.o basics.o
	$(CCC) -o test-quickmove test-quickmove.o klondike.o basics.o

.PHONY: clean
clean:
	$(RM) *.{o,so} $(LIBRARY)

ANDROID_CFLAGS = -fPIC -D__ANDROID__ -DANDROID -O3 -mthumb -mthumb-interwork -fuse-ld=gold -mfloat-abi=softfp -std=c11 -nostdlib
ANDROID_BASE_DIR = $(ANDROID_NDK_HOME)/platforms/android-15/arch-arm/usr
ANDROID_CC = armv7a-hardfloat-linux-gnueabi-gcc
ANDROID_CCC = $(ANDROID_CC) $(ANDROID_CFLAGS) -I$(ANDROID_BASE_DIR)/include -I.
ANDROID_LDFLAGS = -Wl,-soname=libmain.so,--dynamic-linker=/system/bin/linker,--hash-style=sysv -L$(ANDROID_BASE_DIR)/lib -lEGL -lGLESv2 -llog -landroid -lc
ANDROID_OBJS = android_native_app_glue.o android_dummy_main.o android_file.o
ANDROID_APK_PATH = ./android/apk
ANDROID_APK_LIB_PATH = $(ANDROID_APK_PATH)/app/src/main/jniLibs
ANDROID_ASSETS_FOLDER = $(ANDROID_APK_PATH)/app/src/main/assets

android_file.o: android/helpers/android_file.c
	$(CCC) -c android/helpers/android_file.c

android_native_app_glue.o: android/android_native_app_glue.c android/android_native_app_glue.h
	$(CCC) -c android/android_native_app_glue.c

android_dummy_main.o: android/android_dummy_main.c
	$(CCC) -c android/android_dummy_main.c

.PHONY: android
android: CCC = $(ANDROID_CCC)
android: OBJS += $(ANDROID_OBJS)
android: $(OBJS) $(ANDROID_OBJS)
	$(ANDROID_CCC) --shared -o libmain.so $(OBJS) $(ANDROID_LDFLAGS)
	mkdir -p $(ANDROID_ASSETS_FOLDER)/textures
	mkdir -p $(ANDROID_ASSETS_FOLDER)/shaders
	cp -r shaders/* $(ANDROID_ASSETS_FOLDER)/shaders/
	cp -r textures/* $(ANDROID_ASSETS_FOLDER)/textures/
	cp libmain.so $(ANDROID_APK_LIB_PATH)/armeabi/
	cp libmain.so $(ANDROID_APK_LIB_PATH)/armeabi-v7a/
	$(MAKE) -C $(ANDROID_APK_PATH) install

