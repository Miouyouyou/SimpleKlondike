if ARGV.size < 1
  puts "usage : ./cards_array_generator.rb n\n  Example : ./cards-generator 3"
  exit
end

n_cards = ARGV[0].to_i
n_cards = 0 if n_cards < 0
n_cards = 52 if n_cards > 52

values = %w{ace two three four five six seven eight nine ten jack queen king}
families = %w{spade heart club diamond}

puts "carte card_array[] = {"
values.product(families).sample(n_cards).each do
  |value, suit|
  puts "  __CARTE(#{value},#{suit}),"
end
puts "};"
