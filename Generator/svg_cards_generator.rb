cards_families = {
  "♠" => {color: '#000'},
  "♥" => {color: '#900'},
  "♣" => {color: '#000'},
  "♦" => {color: '#900'}
}

cards_values = %w{A 2 3 4 5 6 7 8 9 10 J Q K}
content = File.read("Template.svg")
stack_mark = File.read("TemplateStackMark.svg")

cards_families.each do |symbol, infos|
  color = infos[:color]
  card_svg = content.clone.gsub!("CARD_SYMBOL", symbol).gsub!("CARD_COLOR", color)
  cards_values.each do |value|
    File.write("cards/#{symbol}_#{value}.svg", card_svg.gsub("CARD_VALUE", value))
  end
  File.write("cards/#{symbol}_0.svg", stack_mark.gsub("CARD_SYMBOL", symbol))
end
