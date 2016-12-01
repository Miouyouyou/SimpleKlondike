require 'set'

values = %w{ace two three four five six seven eight nine ten jack queen king}
families = %w{spade heart club diamond}

deck = Set.new(values.product(families))

f_i = 0
n_families = families.length

values.reverse.each do |v|
  pair = [v, families[f_i]]
  if deck.delete?(pair)
    f_i = (f_i + (random_steps.sample)) % n_families
    puts "  __CARTE(#{pair.join(", ")}),"
  else
    f_i = (f_i + 2) % n_families
    redo
  end
end
