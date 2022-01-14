#include <stdio.h>
#include "lib/pico_multicore/include/pico/multicore.h"
#include "lib/pico_stdlib/include/pico/stdlib.h"
#include "lib/hardware_irq/include/hardware/irq.h"

#include "lib/LCD/LCD_1in8.h"
#include "lib/Config/Debug.h"
#include "lib/GUI/GUI_Paint.h"
#include "lib/GUI/ImageData.h"
#include "lib/Fonts/fonts.h"

//TODO(MSR): FIX loops not being actually RTOS.

// Multicore parameter needed.
#define FLAG_VALUE 123

// Definitions for stats.
#define STR 0
#define VIT 0
#define INT 0

// Function Declaration
int main(void);
int loop_5ms();
int loop_20ms(UWORD *Image);
int loop_200us();
int loop_1s();
int initializeWarriorStats();
int increaseStrengthStat();
int increasegold(int totalgold);
int inventory();
void statsMenuDisplay();
void characterMenuDisplay();
char getPlayerInput();
char setDisplayState();
void core1_entry();

// Parameters Declaration for drawing dots.
uint16_t x_point = 0;
uint16_t y_point = 0;
uint16_t color_one;
DOT_PIXEL pixel_type;
DOT_STYLE dot_style;

// Struct for inventory

// Struct for Stats
struct WarriorStats {
    int Strength;
    int Vitality;
    int Intelligence;
    int Level;
};

// Type definitions.
typedef int global_stat;
typedef uint16_t display_state;
typedef int menu_state;

// Global Variables.
global_stat Strength;
global_stat Vitality;
global_stat Intelligence;
global_stat Level;

// Display states
display_state desired_display = 0;
display_state current_display;
display_state previous_display;
display_state next_display;
display_state update_display = 55;

// Menu States
menu_state character_menu = 0;
menu_state inventory_menu = 1;
menu_state stats_menu = 2;


// Drawing Reference code
// Paint_DrawPoint(2, 1, BLACK, DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
// Paint_DrawLine(10, 5, 40, 36, BLUE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

// Core 1 interrupt handler.
void core1_interrupt_handler() {

    printf("before while loop");
    // LCD Init
    LCD_1IN8_Init(HORIZONTAL);
    LCD_1IN8_Clear(WHITE);
    
    // Set up Image.
    UDOUBLE Imagesize = LCD_1IN8_HEIGHT*LCD_1IN8_WIDTH*2;
    UWORD *BlackImage;
    BlackImage = (UWORD *)malloc(Imagesize);

    // Create a new image cache named BlackImage and fill it with white
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN8.WIDTH,LCD_1IN8.HEIGHT, 90, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_90);

    while(1) {
        
        // Apply the image in the display loop.
        loop_20ms(BlackImage);

        // Clear the screen.
        Paint_Clear(WHITE);

        // Check what Image is necessary to be displayed.
        if (desired_display == character_menu) {
            characterMenuDisplay();
        } else if (desired_display == stats_menu) {
            statsMenuDisplay();
        } else if (desired_display == inventory_menu) {
            printf("inventory if");
        } else {
            printf("no valid selection");
        }


    }

    // Receiver function whenever buffer is valid.
    if (multicore_fifo_rvalid()) { 
    }
    
    multicore_fifo_clear_irq(); // Clear Interrupt.

}

// Core 1 Main code.
void core1_entry() {

    // Configure Core 1 Interrupt.
    multicore_fifo_clear_irq();
    irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);

    irq_set_enabled(SIO_IRQ_PROC1, true);


    // Infinite While loop that never terminates to wait for interrupt.
    while(1) {
       tight_loop_contents(); 
    }
}


// Runs other loops.
int main(void)
{
    // Delay Main to let other stuff to properly setup.
    DEV_Delay_ms(100);
    printf("LCD_1in8_main Demo\r\n");
    DEV_Module_Init();

    // Launches core1_entry on seconds core.
    multicore_launch_core1(core1_entry);
    
    // Debug Led Setup.
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    
    // Initialize Display Loop();
    uint16_t start = 1;
    multicore_fifo_push_blocking(start);

    // Wait time to initialize Everything.
    DEV_Delay_ms(200);

    // Begin here for game.
    initializeWarriorStats();


    // Menu Controls prompt.
    printf("Controls for Menu (s = stats, i = inventory, c = character): \n");


    // Main Loop to refresh the screen.
    while(1) {
        loop_200us();
        loop_5ms();
        //loop_1s();
    }

}

// 1 seconds loop for game engine.
int loop_1s() {

    increaseStrengthStat();
    DEV_Delay_ms(1000);
}

// Status Loop for periphals.
int loop_5ms() {

    setDisplayState();
    DEV_Delay_ms(5);
}

// Display loop running at 16ms(60hz).
int loop_20ms(UWORD *Image) {
    
    // Updated the display with Image.
    LCD_1IN8_Display(Image);
    DEV_Delay_ms(20);
}


// Fast Auxillary Loop.
int loop_200us() {
    DEV_Delay_us(200);
}

// Stats Can't be zero.
int initializeWarriorStats() {

    struct WarriorStats level_1_stats;
    level_1_stats.Strength = 3;
    level_1_stats.Vitality = 5;
    level_1_stats.Intelligence = 1;
    level_1_stats.Level = 1;
    setWarriorStats(&level_1_stats);
}

int setWarriorStats(struct WarriorStats *stats) {

    Strength = stats->Strength;
    Vitality = stats->Vitality;
    Intelligence = stats->Intelligence;
}

int increaseStrengthStat() {
    Strength = Strength + 1;
}


// Display information for stats Menu.
void statsMenuDisplay() {


    Paint_DrawString_EN(1, 1, "Stats", &Font20, WHITE, BLACK); 
    Paint_DrawString_EN(1, 20, "Level", &Font12, WHITE, BLACK); 
    Paint_DrawString_EN(1, 30, "STR", &Font12, WHITE, BLACK); 
    Paint_DrawString_EN(1, 40, "VIT", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(1, 50, "INT", &Font12, WHITE, BLACK);


    Paint_DrawNum(25, 20, Level, &Font12, 0, BLACK, WHITE);
    Paint_DrawNum(25, 30, Strength, &Font12, 0, BLACK, WHITE);
    Paint_DrawNum(25, 40, Vitality, &Font12, 0, BLACK, WHITE);
    Paint_DrawNum(25, 50, Intelligence, &Font12, 0, BLACK, WHITE);

}

void characterMenuDisplay() {

    Paint_DrawRectangle(50, 50, 100, 100, BLACK, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP);
}


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

char setDisplayState() {

    char input = getPlayerInput();
    printf("%c\n", input);
    
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
        printf("Invalid input!%c\n", input);
    }
}


int inventory() {
    int gold = 0;
}

int increasegold(int totalgold) {
    
}