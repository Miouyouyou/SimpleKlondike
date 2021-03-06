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

### Requirements

* X11 libraries and development headers
* OpenGL ES 2.x libraries and development headers
* EGL libraries and development headers
* C Compiler
* The following tools :
 * find
 * sed
 * xdg-desktop-menu

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

### Requirements

* A Cross-compiling C compiler
* Android SDK Build tools 25.0.1
* Android SDK Platform-tools 25.0.1
* Android SDK Platform 25 (Android 7.1.1)
* Make
* find
* An Android ARM phone, or an Android ARM emulator with OpenGL ES 2.x support

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

# Regenerating the textures

## Requirements

* Ruby (to generate all the SVG from SVG templates)
 * [**myy_color**](https://github.com/Miouyouyou/myy-color) 0.1 (`myy_bmp2raw`)
* ImageMagick (`convert` and `montage`)
* Inkscape (to convert the SVG to PNG)

## Procedure

To regenerate the textures, run `convert.sh` in the **Generator** folder.

## Quick explanation

The generator will :
* Generate 56 cards SVG (52 cards + 4 stack marks) in the `cards` sub-folder using `svg_cards_generator.rb`
* Convert all the SVG in the current folder and `cards` sub-folder, to PNG files in the `png` folder, using Inkscape
* Generate a **montage** of all the 56 cards, the back card picture, the 'reset pool' mark and the selection mark.
* **Extent** the previous montage to add some width padding and copy it to `result/cards_texture.bmp`
 * Currently, the padding is done by adding a part of the background texture to it. However, this part is not used in the game.
 * The width padding is used so that each card takes 1/16 of the texture in width.
* Convert `result/cards_texture.bmp` to `result/all_cards_tex.raw` using `myy_bmp2raw`

* Generate a **montage** of all the menu PNG in the `menus` sub-folder
* `convert` the previous montage to `result/menus.bmp`
* Convert `result/menus.bmp` to `result/menus.raw` using `myy_bmp2raw`

# Money !

I accept bribes and donations !

[![Pledgie !](https://pledgie.com/campaigns/33063.png)](https://pledgie.com/campaigns/33063)

BTC: 16zwQUkG29D49G6C7pzch18HjfJqMXFNrW

[![Tip with Altcoins](https://shapeshift.io/images/shifty/small_light_altcoins.png)](https://shapeshift.io/shifty.html?destination=16zwQUkG29D49G6C7pzch18HjfJqMXFNrW&output=BTC)
