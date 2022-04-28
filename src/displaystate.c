#include "include/displaystate.h"
#include "include/menus.h"

// Function Declaration
char setDisplayState();

// Defining Variables
display_state desired_display = 0;
display_state current_display;
display_state previous_display;
display_state next_display;
display_state update_display = 55;

// Sets Display state based on input.
char setDisplayState() {

    char input = getPlayerInput();
    
    if(input == 's') {
        // Stats Menu input.
        desired_display = stats_menu;
    }
    else if(input == 'i') {
        // Inventory Menu input.
        desired_display = inventory_menu;
    }
    else if(input == 'c') {
        // Character Menu input.
        desired_display = character_menu;
    }
    else {
        //printf("Invalid input!%c\n", input);
    }
}