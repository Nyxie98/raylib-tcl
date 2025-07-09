load ./raylib.so

set close 0
set x 16
set y 32
set speed 4

init_window 800 600 "Test Window"
set_target_fps 60
while {$close != 1} {
    set close [window_should_close]

    if {[is_key_down 65] == 1} {
        set x [expr {$x - $speed}]
    } elseif {[is_key_down 68] == 1} {
        set x [expr {$x + $speed}]
    }

    if {[is_key_down 87] == 1} {
        set y [expr {$y - $speed}]
    } elseif {[is_key_down 83] == 1} {
        set y [expr {$y + $speed}]
    }

    begin_drawing

    clear_background {0 0 0 255}
    draw_text "Hello, World!" 16 16 16 {255 255 255 255}
    draw_rectangle $x $y 32 32 {0 255 0 255}

    end_drawing
}

close_window