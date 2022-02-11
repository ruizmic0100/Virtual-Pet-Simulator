#include "include/inputs.h"

// Function Declaration
char getPlayerInput();

// Get's players input and filters out only the inputs we desire.
char getPlayerInput() {

    char playerinput = getchar_timeout_us(0);

    // Filter. 
    switch(playerinput) {
        case 's':
            return playerinput;
        case 'i':
            return playerinput;
        case 'c':
            return playerinput;
    }
    
}