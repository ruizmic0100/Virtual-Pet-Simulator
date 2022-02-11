#include "include/displaystate.h"
#include "include/menus.h"

// Function Declaration
void statsMenuDisplay();
void characterMenuDisplay();
char setDisplayState();

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