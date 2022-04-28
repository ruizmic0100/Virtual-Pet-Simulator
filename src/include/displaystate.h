#ifndef DISPLAYSTATE_H
#define DISPLAYSTATE_H
#include "../lib/pico_stdlib/include/pico/stdlib.h"
typedef uint16_t display_state;

// Display states
display_state desired_display;
display_state current_display;
display_state previous_display;
display_state next_display;
display_state update_display;

char setDisplayState();

#endif