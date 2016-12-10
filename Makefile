O := .build

CC = clang
ifeq ($(origin CFLAGS), undefined)
  CFLAGS = -O3 -march=native
endif
CFLAGS += -fPIC -fuse-ld=gold
INCLUDE_DIRS = -Imyy -I.
LDFLAGS = -lGLESv2
CCC := $(CC) $(CFLAGS) $(INCLUDE_DIRS)

X11_LDFLAGS = -lX11 -lEGL
X11_SOURCES = $(shell find ./myy/platforms/X11 -name '*.c')

ANDROID_CC = armv7a-hardfloat-linux-gnueabi-gcc
ANDROID_CFLAGS = -fPIC -D__ANDROID__ -DANDROID -O3 -mthumb -mthumb-interwork -fuse-ld=gold -mfloat-abi=softfp -std=c11 -nostdlib
ANDROID_BASE_DIR = $(ANDROID_NDK_HOME)/platforms/android-15/arch-arm/usr
ANDROID_CCC = $(ANDROID_CC) $(ANDROID_CFLAGS) -I$(ANDROID_BASE_DIR)/include $(INCLUDE_DIRS)
ANDROID_LIBNAME = libmain.so
ANDROID_LDFLAGS = -Wl,-Bsymbolic,-znow,-soname=$(ANDROID_LIBNAME),--dynamic-linker=/system/bin/linker,--hash-style=sysv -L$(ANDROID_BASE_DIR)/lib -lEGL -lGLESv2 -llog -landroid -lc
ANDROID_APK_PATH = ./myy/platforms/android/apk
ANDROID_APK_LIB_PATH = $(ANDROID_APK_PATH)/app/src/main/jniLibs
ANDROID_ASSETS_FOLDER = $(ANDROID_APK_PATH)/app/src/main/assets
ANDROID_SOURCES = $(shell find ./myy/platforms/android -name '*.c')

ifeq ($(origin PLATFORM), undefined)
  PLATFORM = X11
endif

SOURCES := $(shell find . -name '*.c' -not -path './myy/platforms/*' -not -path './tests/*')
OBJECTS := $(prefix $(O)/, $(notdir SOURCES))

INSTALL_FOLDER = ~/.local/games/SimpleKlondike

.PHONY: all
all: $(PLATFORM)

.PHONY: X11
X11: $(SOURCES)
	mkdir -p $(O)
	$(CCC) -o $(O)/SimpleKlondike $(SOURCES) $(X11_SOURCES) $(LDFLAGS) $(X11_LDFLAGS)

install: X11
	mkdir -p $(INSTALL_FOLDER)
	sed -e "s|~|$(HOME)|g" SimpleKlondike.desktop > $(O)/Miouyouyou-SimpleKlondike.desktop
	cp -r $(O)/SimpleKlondike SimpleKlondike.png textures shaders $(INSTALL_FOLDER)
	xdg-desktop-menu install $(O)/Miouyouyou-SimpleKlondike.desktop

uninstall:
	rm $(INSTALL_FOLDER)/SimpleKlondike*
	rm $(INSTALL_FOLDER)/textures/*
	rm $(INSTALL_FOLDER)/shaders/*
	rmdir $(INSTALL_FOLDER)/*
	mkdir -p $(O)
	sed -e "s|~|$(HOME)|g" SimpleKlondike.desktop > $(O)/Miouyouyou-SimpleKlondike.desktop
	xdg-desktop-menu uninstall $(O)/Miouyouyou-SimpleKlondike.desktop

android: $(SOURCES)
	mkdir -p $(O)
	$(ANDROID_CCC) --shared -o $(O)/$(ANDROID_LIBNAME) $(SOURCES) $(ANDROID_SOURCES) $(ANDROID_LDFLAGS)
	mkdir -p $(ANDROID_ASSETS_FOLDER)/textures
	mkdir -p $(ANDROID_ASSETS_FOLDER)/shaders
	cp -r shaders/* $(ANDROID_ASSETS_FOLDER)/shaders/
	cp -r textures/* $(ANDROID_ASSETS_FOLDER)/textures/
	cp $(O)/$(ANDROID_LIBNAME) $(ANDROID_APK_LIB_PATH)/armeabi/
	cp $(O)/$(ANDROID_LIBNAME) $(ANDROID_APK_LIB_PATH)/armeabi-v7a/
	$(MAKE) -C $(ANDROID_APK_PATH)

android_install: android
	$(MAKE) -C $(ANDROID_APK_PATH) install

android_uninstall:
	$(MAKE) -C $(ANDROID_APK_PATH) uninstall

clean:
	$(RM) SimpleKlondike
	$(RM) -r .build/*
	$(MAKE) -C $(ANDROID_APK_PATH) clean

TEST_HEADERS = tests/test-utilities.h
TEST_COMMON_DEPS = cards_logic/klondike.c cards_logic/basics.c
TEST_O = $(O)/tests
TESTS_NAMES = test-selection test-load-and-save test-quickmove
TESTS_EXECUTABLES = $(addprefix $(TEST_O)/, $(TESTS_NAMES))

$(TEST_O)/test-selection: tests/test-selection.c $(TEST_COMMON_DEPS)
	$(CCC) -o $(TEST_O)/test-selection $^
	./$@

$(TEST_O)/test-load-and-save: tests/test-load-and-save.c $(TEST_COMMON_DEPS)
	$(CCC) -o $(TEST_O)/test-load-and-save $^
	./$@

$(TEST_O)/test-quickmove: tests/test-quickmove.c $(TEST_COMMON_DEPS)
	$(CCC) -o $(TEST_O)/test-quickmove $^
	./$@

.PHONY: create_test_dir
create_test_dir:
	mkdir -p $(TEST_O)

.PHONY: tests
tests: create_test_dir $(TESTS_EXECUTABLES)
	echo $(TESTS_EXECUTABLES)

.PHONY: generate_tests
generate_tests: $(TEST_EXECUTABLES)
