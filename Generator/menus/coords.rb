pause_buttons = {
  restart:  {x: [45, 150], y: [75, 180]},
  continue: {x: [362, 468], y: [75, 180]},
  menu: {x: [0, 512], y: [0, 256]}
}

win_buttons = {
  github:  {x: [120, 224], y: [200, 304]},
  restart: {x: [284, 388], y: [200, 304]}
}

module WindowCoords

  @@multipliers = {
    GLbyte: [127, :round],
    GLshort: [32787, :round],
    GLfloat: [1, :to_f]
  }

  def self.of(buttons: , in_window: , displayed_on:, scaling: 1,
              denormalise_to: :GLfloat)
    # Denormalise as Denormalised OpenGL coordinates
    # This has nothing to do with vectors
    denorm_mult, denorm_method = @@multipliers[denormalise_to]

    # OpenGL coordinates have +Y pointing to the top while
    # window coordinates have +Y pointing to the bottom
    invert_y = -1

    half_screen_width, half_screen_height = displayed_on.map {|x| x/2.0}
    half_window_width, half_window_height = in_window.map {|x| x/2.0}

    buttons.each do |name, coords|
      normalised_x = coords[:x].map {|coord|
        ((coord - half_window_width)*scaling / half_screen_width) *
          denorm_mult
      }.map(&denorm_method)
      normalised_y = coords[:y].map {|coord|
        ((coord - half_window_height)*scaling / half_screen_height) *
          denorm_mult * invert_y
      }.map(&denorm_method)

      puts("#{name} = {{.x = #{normalised_x.shift}, .y = #{normalised_y.shift}}," <<
           " {.x = #{normalised_x.shift}, .y = #{normalised_y.shift}}};")
    end
  end

end

WindowCoords.of(buttons: pause_buttons, in_window: [512, 256],
                displayed_on: [1920, 1080], scaling: 2,
                denormalise_to: :GLbyte)

WindowCoords.of(buttons: win_buttons, in_window: [512, 324],
                displayed_on: [1920, 1080], scaling: 2,
                denormalise_to: :GLbyte)

