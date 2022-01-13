#include <stdio.h>
#include "lib/pico_multicore/include/pico/multicore.h"
#include "lib/pico_stdlib/include/pico/stdlib.h"
#include "lib/hardware_irq/include/hardware/irq.h"

#include "lib/LCD/LCD_1in8.h"
#include "lib/Config/Debug.h"
#include "lib/GUI/GUI_Paint.h"
#include "lib/GUI/ImageData.h"
#include "lib/Fonts/fonts.h"

// Multicore parameter needed.
#define FLAG_VALUE 123

// Definitions for stats.
#define STR 0
#define VIT 0
#define INT 0

// Function Declaration
int main(void);
int loop_5ms();
int loop_16ms(UWORD *Image);
int loop_100us();
int initializestats(char class);
int increasestat(int stat);
int increasegold(int totalgold);
int inventory();
int statsMenuDisplay();
char getPlayerInput();
char setPlayerInput(char input);
void core1_entry();

// Parameters Declaration for drawing dots.
uint16_t x_point = 0;
uint16_t y_point = 0;
uint16_t color_one;
DOT_PIXEL pixel_type;
DOT_STYLE dot_style;

// Struct for inventory

// Struct for Stats
struct Stats {
    int Strength;
    int Vitality;
    int Intelligence;
}Warrior;

// Drawing Reference code
// Paint_DrawPoint(2, 1, BLACK, DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
// Paint_DrawLine(10, 5, 40, 36, BLUE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

// Core 1 interrupt handler.
void core1_interrupt_handler() {
    
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
        loop_16ms(BlackImage);
        statsMenuDisplay();
    }

    // Receiver function whenever buffer is valid.
    while (multicore_fifo_rvalid()) { 
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

    char class_selection = 'w';

    initializestats(class_selection);

    // Menu Controls prompt.
    printf("Controls for Menu (s = stats, i = inventory, c = character): \n");


    // Main Loop to refresh the screen.
    while(1) {
        loop_100us();
        loop_5ms();
    }

}


int loop_5ms() {

    getPlayerInput(); 
    DEV_Delay_ms(5);
}

// 16ms loop for 60hz.
int loop_16ms(UWORD *Image) {


    // Parameters for drawpoint.
    color_one = BLACK;
    pixel_type = DOT_PIXEL_2X2;
    dot_style = DOT_FILL_RIGHTUP;


    // Updated the display with Image.
    LCD_1IN8_Display(Image);
    DEV_Delay_ms(16);
}

int loop_100us() {
    
    DEV_Delay_us(100);
}

int initializestats(char class) {

    if (class == 'w') {
        Warrior.Strength = 2;
        Warrior.Intelligence = 0;
        Warrior.Vitality = 4;
    }
}

int increasestat(int stat) {

}

int inventory() {
    int gold = 0;
}

int increasegold(int totalgold) {
    
}

int statsMenuDisplay() {

    char stats_projection[10] = "";

    stats_projection[0] = Warrior.Strength + '0';

    Paint_DrawString_EN(1, 83, "Stats:", &Font12, WHITE, BLACK); 
    Paint_DrawString_EN(1, 125, stats_projection, &Font12, WHITE, BLACK);
}

char getPlayerInput() {

    char playerinput = getchar();
    printf("Got User Input %c\n", playerinput);
    setPlayerInput(playerinput);


}

char setPlayerInput(char input) {

    if(input == 's') {
        printf("Stats Menu Initializing...");
        // Stats Menu input.
    }
    else if(input == 'i') {
        // Inventory Menu input.
    }
    else if(input == 'c') {
        // Character Menu input.
    }
    else {
        //printf("Invalid input!");
    }
}