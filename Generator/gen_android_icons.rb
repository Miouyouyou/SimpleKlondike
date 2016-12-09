#!/usr/bin/env ruby

android_sizes = {
  ldpi:    "36x36",
  mdpi:    "48x48",
  tvdpi:   "64x64",
  hdpi:    "72x72",
  xhdpi:   "96x96",
  xxhdpi:  "144x144",
  xxxhdpi: "192x192"
}.each {|size_name, size|
  folder_name = "drawable-#{size_name}"
  `mkdir -p android_icons/#{folder_name}`
  `convert main_icon.png -resize #{size} -background none intermediates/android_icon_#{size}.png`
  `convert intermediates/android_icon_#{size}.png -background none -gravity Center -extent #{size} android_icons/#{folder_name}/simple_klondike.png`
}

