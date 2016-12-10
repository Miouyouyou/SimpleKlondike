SCRIPTDIR=`dirname "$(readlink -f "$0")"`

echo $SCRIPTDIR
pushd .
cd $SCRIPTDIR

rm cards/*
rm png/*
rm intermediates/*

ruby svg_cards_generator.rb

for file in cards/*.svg *.svg; do
  inkscape -e png/`basename $file .svg`.png -w 87 $file;
done

for other_png in EmptyPool.png ResetPool.png; do
  cp $other_png png/;
done

mkdir -p intermediates
mkdir -p result
montage png/{♦,♣,♥,♠}_{0,A,2,3,4,5,6,7,8,9,10,J,Q,K}.png -mode Concatenate -tile 14x4 -background none intermediates/base_montage.png
montage png/Selection.png png/EmptyPool.png png/ResetPool.png png/Returned.png -mode Concatenate -tile 1x4 -background none intermediates/cards_back.png
montage intermediates/base_montage.png intermediates/cards_back.png -background none -geometry +0+0 intermediates/all_cards.png
convert cardsbackground.bmp -crop 87x540+40+0 intermediates/table_background.bmp
montage intermediates/all_cards.png intermediates/table_background.bmp -background none -geometry +0+0 result/cards_texture.bmp
myy_bmp2raw result/cards_texture.bmp argb8888 result/all_cards_tex.raw rgba4444

montage menus/win_menu.png menus/pause_menu.png -tile 1x2 -background none -geometry +0+0 result/menus.bmp
myy_bmp2raw result/menus.bmp argb8888 result/menus.raw rgba4444

popd
