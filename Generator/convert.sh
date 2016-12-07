rm cards/*
rm png/*
rm intermediates/*

ruby svg_cards_generator.rb

for file in cards/*.svg *.svg; do
  inkscape -e png/`basename $file .svg`.png -w 87 $file;
done

mkdir intermediates
mkdir result
montage png/{♦,♣,♥,♠}_{0,A,2,3,4,5,6,7,8,9,10,J,Q,K}.png -mode Concatenate -tile 14x4 -background none intermediates/base_montage.png
montage png/Returned.png png/Returned.png png/Selection.png png/Returned.png -mode Concatenate -tile 1x4 -background none intermediates/cards_back.png
montage intermediates/base_montage.png intermediates/cards_back.png -background none -geometry +0+0 intermediates/all_cards.png
convert cardsbackground.bmp -crop 87x540+40+0 intermediates/table_background.bmp
montage intermediates/all_cards.png intermediates/table_background.bmp -background none -geometry +0+0 result/cards_texture.bmp
myy_bmp2raw result/cards_texture.bmp argb8888 result/cards_texture.raw rgba4444

#convert png/NotAdvised.png -crop 128x16+0+112 -background none intermediates/bottom-button-restart.bmp
#convert png/Advised.png -crop 128x16+0+0 -background none intermediates/top-button-continue.bmp
#convert png/Advised.png -crop 128x16+0+112 -background none intermediates/bottom-button-continue.bmp
#convert png/Menu.png -crop 128x16+0+0 -background none intermediates/top-button-menu.bmp
#convert png/Menu.png -crop 128x16+0+112 -background none intermediates/bottom-button-menu.bmp
#montage intermediates/{top,bottom}-button-menu.bmp intermediates/{top,bottom}-button-restart.bmp intermediates/{top,bottom}-button-continue.bmp -background none -tile 1x8 -geometry +0+0 intermediates/button-parts.bmp
#montage intermediates/button-parts.bmp trophy.bmp continue.bmp restart.bmp -background none -tile 1x4 -geometry +0+0 intermediates/menu_parts.bmp
#convert intermediates/menu_parts.bmp -gravity South -background none -extent 128x512 result/menu_parts.bmp
#myy_bmp2raw result/menu_parts.bmp argb8888 result/menu_parts.raw rgba4444
#inkscape -e png/Advised.png -w 128 menu/parts/Advised.svg
#inkscape -e png/NotAdvised.png -w 128 menu/parts/NotAdvised.svg
#inkscape -e png/Menu.png -w 128 menu/parts/Menu.svg

montage menus/win_menu.png menus/pause_menu.png -tile 1x2 -background none -geometry +0+0 result/menus.bmp
myy_bmp2raw result/menus.bmp argb8888 result/menus.raw rgba4444
