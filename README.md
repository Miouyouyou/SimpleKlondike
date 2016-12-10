# About

Simple Klondike is a very simple Klondike game written mainly in C, 
using OpenGL ES 2.x for the graphics engine.

# Platforms support

Simple Klondike currently compiles for the following platforms :

* X11
* Android (ARM)

However, feel free to add support for the platforms you like.

# Compiling

## X11

### Quick version

```bash
make
make install
```

### Explanations

In order to compile this game, simply run `make` in the main folder.

Then :

* if you want to run it from the source folder, just type `.build/SimpleKlondike`.
* if you want to install it, run `make install`.
 * This command will install the game in `~/.local/games/SimpleKlondike` and install a corresponding desktop file.
* Once installed, you can find the game in the 'Games' category of your desktop environment.
* To remove the game, just type `make uninstall`.

## Android

### Quick version

```bash
make android
make android_install
```

### Explanations

* `make android` will generate the android libraries and the APK file in `./myy/platforms/android/apk/app/build/outputs/apk/app-debug.apk`.
 * You will need a cross-compiling gcc for that matter, like `armv7a-hardfloat-linux-gnueabi-gcc`.
 * TODO: Currently, the Makefile does not use the capabitilies of the Android NDK.
* `make android_install` will install the APK file into the plugged ARM phone / ARM emulator.
* `make android_uninstall` will remove the APK file from the plugged ARM phone / ARM emulator.

# Money !

I accept bribes and donations !

[![Pledgie !](https://pledgie.com/campaigns/33063.png)](https://pledgie.com/campaigns/33063)

BTC: 16zwQUkG29D49G6C7pzch18HjfJqMXFNrW

[![Tip with Altcoins](https://shapeshift.io/images/shifty/small_light_altcoins.png)](https://shapeshift.io/shifty.html?destination=16zwQUkG29D49G6C7pzch18HjfJqMXFNrW&output=BTC)
