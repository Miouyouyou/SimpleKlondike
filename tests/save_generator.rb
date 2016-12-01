require 'set'

module SimpleKlondike

  Card = Struct.new(:value, :suit)

  ACE   = 1
  TWO   = 2
  THREE = 3
  FOUR  = 4
  FIVE  = 5
  SIX   = 6
  SEVEN = 7
  EIGHT = 8
  NINE  = 9
  TEN   = 10
  JACK  = 11
  QUEEN = 12
  KING  = 13

  SPADE = 1
  HEART = 2
  CLUB  = 3
  DIAMOND = 4

  CARDS = Set.new

  ACE.upto(KING) do |value|
    SPADE.upto(DIAMOND) do |suit| # DIAMOND is last here
      CARDS.add(Card.new(value, suit).freeze)
    end
  end

  class Zone
    attr_reader :zid, :max, :max_returned_cards, :cards
    def initialize(zid:, max:, max_returned_cards:, cards:)
      @zid = zid
      @max = max
      @max_returned_cards = max_returned_cards
      @cards = cards
    end

    def cards_from(card_set, n)
      card_set.to_a.sample(n).each {|card| @cards << card.dup }
      @cards.each {|card| card_set.delete(card)}
    end

    def turn_first_cards(n)
      (0...n).each { |i| @cards[i].value = ~@cards[i].value }
    end

    def to_a
      @cards.map {|card| [@zid, card.value, card.suit, 0]}.flatten
    end

  end

  BASE_ZONES = {
    pool: Zone.new(zid: 0, max: 24, max_returned_cards: 0, cards: []),
    waste: Zone.new(zid: 1, max: 24, max_returned_cards: 0, cards: []),
    stack_spade: Zone.new(zid: 2, max: 13, max_returned_cards: 0, cards: []),
    stack_heart: Zone.new(zid: 3, max: 13, max_returned_cards: 0, cards: []),
    stack_diamond: Zone.new(zid: 4, max: 13, max_returned_cards: 0, cards: []),
    stack_club: Zone.new(zid: 5, max: 13, max_returned_cards: 0, cards: []),
    pile_1: Zone.new(zid: 6, max: 13, max_returned_cards: 0, cards: []),
    pile_2: Zone.new(zid: 7, max: 14, max_returned_cards: 1, cards: []),
    pile_3: Zone.new(zid: 8, max: 15, max_returned_cards: 2, cards: []),
    pile_4: Zone.new(zid: 9, max: 16, max_returned_cards: 3, cards: []),
    pile_5: Zone.new(zid: 10, max: 17, max_returned_cards: 4, cards: []),
    pile_6: Zone.new(zid: 11, max: 18, max_returned_cards: 5, cards: []),
    pile_7: Zone.new(zid: 12, max: 19, max_returned_cards: 6, cards: [])
  }.freeze

  module Generator

    def self.save(zones, n_cards_per_draw)
      save = [n_cards_per_draw, 0, 0, 0,
              zones.map {|name, zone| zone.to_a}].flatten
      p save.each_slice(4).to_a
      save.pack("C*")
    end

    def self.game_start
      zones = BASE_ZONES.clone
      card_set = CARDS.clone
      [:pool, 24, 0,
       :pile_1, 1, 0,
       :pile_2, 2, 1,
       :pile_3, 3, 2,
       :pile_4, 4, 3,
       :pile_5, 5, 4,
       :pile_6, 6, 5,
       :pile_7, 7, 6].each_slice(3) do
        |zone, dealt_cards, turned_cards|
        zones[zone].cards_from(card_set, dealt_cards)
        zones[zone].turn_first_cards(turned_cards)
      end
      zones
    end

  end
end

File.write("test.save", SimpleKlondike::Generator.save(SimpleKlondike::Generator.game_start, 1))
